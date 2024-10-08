#include "geodb.h"
using namespace std;

GeoDatabase::GeoDatabase() {

}

GeoDatabase::~GeoDatabase() {

}

bool GeoDatabase::load(const std::string& map_data_file){
	ifstream infile(map_data_file);
	if (!infile)		        // Did opening the file fail?
	{
		return false;
	}

	//read each line in mapdata
	string line;
	//name of poi
	string name;
	//current street
	string currStreet;
	//starting / ending coordinates
	string startLat;
	string startLong;
	string endLat;
	string endLong;
	//number of points of interest
	int numPois = -1;
	
	GeoPoint segmentMidpoint;
	GeoPoint streetPoint1;
	GeoPoint streetPoint2;
	string segmentMidpointString;
	string point1String;
	string point2String;
	
	string poiLat;
	string poiLong;

	bool onStreet = true; //first line of the segment -> street name

	while (getline(infile, line)) {
		//istringstream iss(line);
		//LINE 1
		if (onStreet) {
			currStreet = line;
			onStreet = false;
		}
		//LINE 2
		if ((infile >> startLat >> startLong >> endLat >> endLong)) {
			streetPoint1 = GeoPoint(startLat, startLong);
			streetPoint2 = GeoPoint(endLat, endLong);
			
			point1String = streetPoint1.to_string();
			point2String = streetPoint2.to_string();

			//create bidirectional connection between start and end coord
			m_connectedPoints[point1String].push_back(streetPoint2);
			m_connectedPoints[point2String].push_back(streetPoint1);

			//associate the street name with its start and end coords

			m_segmentNames.insert(point1String + point2String, currStreet);
		}
		//LINE 3
		if ((infile >> numPois)) {
			infile.ignore(10000, '\n');
			if (numPois > 0) {
				//compute midpoint

				segmentMidpoint = midpoint(streetPoint1, streetPoint2);
				segmentMidpointString = segmentMidpoint.to_string();

				//create bidirectional connection b/w midpoint and starting positions

				//point 1 and midpoint

				m_connectedPoints[point1String].push_back(segmentMidpoint);
				m_connectedPoints[segmentMidpointString].push_back(streetPoint1);

				//point 2 and midpoint

				m_connectedPoints[point2String].push_back(segmentMidpoint);
				m_connectedPoints[segmentMidpointString].push_back(streetPoint2);

				//associate street name with street segments
				m_segmentNames.insert(point1String + segmentMidpointString, currStreet);
				m_segmentNames.insert(point2String + segmentMidpointString, currStreet);

				//process each p value
				for (int i = 0; i < numPois; i++) {
					getline(infile, line);
					name = line.substr(0, line.find('|'));
					line = line.substr(line.find('|') + 1);
					poiLat = line.substr(0, line.find(' '));
					poiLong = line.substr(line.find(' ') + 1);
					GeoPoint poi(poiLat, poiLong); //FIXME: is this allowable?
					string poiString = poi.to_string();

					//create bidirectional connection b/w midpoint and poi
					m_connectedPoints[poiString].push_back(segmentMidpoint);
					m_connectedPoints[segmentMidpointString].push_back(poi);

					//associate poi with its name
					m_pois.insert(name, poi);

					//associate the street name with the poi and midpoint
					m_segmentNames.insert(poiString + segmentMidpointString, "a path");
				}
				//processed all pois, so next line should be a street
				onStreet = true;
			}
			else {
				onStreet = true;
			}
		}
	}
	return true;
}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const{
	if (m_pois.find(poi) == nullptr) {
		cerr << poi << endl;
		return false;
	}
	point = *m_pois.find(poi);
	return true;
}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const{
	vector<GeoPoint> returnVector;
	if (m_connectedPoints.find(pt.to_string()) != nullptr) {
		return *(m_connectedPoints.find(pt.to_string()));
	}
	return returnVector;
}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const{
	string returnVal = "";
	//check both permutations
	if (m_segmentNames.find(pt1.to_string() + pt2.to_string()) != nullptr) {
		returnVal = *(m_segmentNames.find(pt1.to_string() + pt2.to_string()));
	}
	else if (m_segmentNames.find(pt2.to_string() + pt1.to_string()) != nullptr) {
		returnVal = *(m_segmentNames.find(pt2.to_string() + pt1.to_string()));
	}
	return returnVal;
}