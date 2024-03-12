#include "geodb.h"
#include <stack>
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
	while (getline(infile, line)) {
		istringstream iss(line);
		string name;
		//reset coords
		double coords[4] = { 0, 0, 0, 0 };
		int numPois = 0;

		//LINE 1
		//try to read a name from the file
		if ((iss >> name)) {
			continue;
		}
		//LINE 2
		else if ((iss >> coords[0] >> coords[1] >> coords[2] >> coords[3])) {
			continue;
		}
		//LINE 3
		else if ((iss >> numPois)) {
			continue;
		}
		//LINE P
		else if ((iss >> name >> coords[0] >> coords[1])) {
			GeoPoint poi(to_string(coords[0]), to_string(coords[1])); //FIXME: is this allowable?
			m_pois.insert(name, poi);
			//compute midpoint

			//current street is given by top of streetStack
			string currStreet = streetStack.top();
			continue;
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