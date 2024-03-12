#include "geodb.h"
using namespace std;

GeoDatabase::GeoDatabase() {

}

GeoDatabase::~GeoDatabase() {

}

bool GeoDatabase::load(const std::string& map_data_file){
	ifstream infile("mapdata.txt");    // infile is a name of our choosing
	if (!infile)		        // Did opening the file fail?
	{
		return false;
	}

	stack<string> streetStack;

	//read each line in mapdata
	string line;
	istringstream iss(line);
	string name;
	double coords[4];
	int numPois = 0;
	GeoPoint segmentMidpoint;

	while (getline(infile, line)) {
		//LINE 1
		//try to read a name from the file
		if ((iss >> name)) {
			if (!streetStack.empty()) {
				//remove previous street to keep size of stack low
				streetStack.pop();
			}
			streetStack.push(name);
		}
		//LINE 2
		else if ((iss >> coords[0] >> coords[1] >> coords[2] >> coords[3])) {
			//FIXME: is this allowable?
			GeoPoint streetPoint1(to_string(coords[0]), to_string(coords[1]));
			GeoPoint streetPoint2(to_string(coords[2]), to_string(coords[3]));
			
			//associate the street name with its start and end coords
			vector<GeoPoint> coords;
			coords.push_back(streetPoint1);
			coords.push_back(streetPoint2);

			m_streetSegments.insert(streetStack.top(), coords);
		}
		//LINE 3
		else if ((iss >> numPois)) {
			if (numPois > 0) {
				GeoPoint streetPoint1(to_string(coords[0]), to_string(coords[1]));
				GeoPoint streetPoint2(to_string(coords[2]), to_string(coords[3]));
				//compute midpoint
				segmentMidpoint = midpoint(streetPoint1, streetPoint2);

				//create bidirectional connection b/w midpoint and starting positions
			}
		}
		//LINE P
		else if ((iss >> name >> coords[0] >> coords[1])) {
			GeoPoint poi(to_string(coords[0]), to_string(coords[1])); //FIXME: is this allowable?
			m_pois.insert(name, poi);
			//current street is given by top of streetStack
			string currStreet = streetStack.top();
		}
		else {
			//badly formatted line (SHOULD NEVER OCCUR)
			return false;
		}

		return true;
	}
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const{

}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const{

}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const{

}