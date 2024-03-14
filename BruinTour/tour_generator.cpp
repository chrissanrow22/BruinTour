#include "tour_generator.h"
using namespace std;

TourGenerator::TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router)
	: m_gdb(geodb), m_router(router)
{

}

TourGenerator::~TourGenerator() {

}

vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const {
	//create a result vector that will hold the instructions
	vector<TourCommand> tour;

	string poi;
	string talkingPoint;
	TourCommand command;

	vector<GeoPoint> path;

	//for each point of interest p in the stops object:
	for (int i = 0; i < stops.size(); i++) {
		//get poi data for the i-th poi in stops
		stops.get_poi_data(i, poi, talkingPoint);

		//generate a commentary tourcommand object and add to result vector
		command.init_commentary(poi, talkingPoint);
		tour.push_back(command);

		//if there are still more points of interest:
		if (i < stops.size() - 1) {
			//create geopoint representing current poi
			GeoPoint currPoi;
			m_gdb.get_poi_location(poi, currPoi);

			//get next poi
			stops.get_poi_data(i + 1, poi, talkingPoint);

			//create geopoint representing next poi
			GeoPoint nextPoi;
			m_gdb.get_poi_location(poi, nextPoi);

			//ROUTE PROCESSING
			//route between current poi to next poi
			path = m_router.route(currPoi, nextPoi);

			//proceed and turn generation
			for (int i = 0; i < path.size() - 1; i++) {
				//compute direction for segment path
				double angle = angle_of_line(path[i], path[i + 1]);
				string direction = computeDirection(angle);

				//compute distance for segment path
				double distance = distance_earth_miles(path[i], path[i + 1]);

				//generate proceed command and add to tour vector
				command.init_proceed(direction, m_gdb.get_street_name(path[i], path[i + 1]), distance, path[i], path[i + 1]);
				tour.push_back(command);
				
				//if there is another different named segment to follow. generate a turn command
				if (i < path.size() - 2) {
					if (m_gdb.get_street_name(path[i], path[i + 1]) != m_gdb.get_street_name(path[i + 1], path[i + 2])) {
						//ensure the angle is not zero
						double angle = angle_of_turn(path[i], path[i + 1], path[i + 2]); //FIXME: should angle be an int
						//initialize street name to turn to
						string proceedingStreet = m_gdb.get_street_name(path[i + 1], path[i + 2]);
						if(angle != 0){
							//what happens if angle is less than 1 or greater than 359
							if (angle >= 1 && angle < 180) {
								command.init_turn("left", proceedingStreet);
							}
							else {
								command.init_turn("right", proceedingStreet);
							}
							tour.push_back(command);
						}
					}
				}
			}
		}
	}


	return tour;
}

string TourGenerator::computeDirection(double angle) const{
	//angle should never be less than 0
	if (angle < 0) {
		return "";
	}
	if (angle < 22.5) {
		return "east";
	}
	if (angle < 67.5) {
		return "northeast";
	}
	if (angle < 112.5) {
		return "north";
	}
	if (angle < 157.5) {
		return "northwest";
	}
	if (angle < 202.5) {
		return "west";
	}
	if (angle < 247.5) {
		return "southwest";
	}
	if (angle < 292.5) {
		return "south";
	}
	if (angle < 337.5) {
		return "southeast";
	}
	else {
		return "east";
	}
}