#include "router.h"
using namespace std;

Router::Router(const GeoDatabaseBase& geo_db)
	: m_gdb(geo_db)
{

}

Router::~Router() {

}

vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {
	vector<GeoPoint> fullRoute;
	vector<PathNode> closedList;

	GeoPoint currPoint = pt1;

	while (currPoint.latitude != pt2.latitude && currPoint.longitude != pt2.longitude) {
		//get available nodes
		openNodes = m_gdb.get_connected_points(currPoint);
		for (int i = 0; i < openNodes.size(); i++) {
			
		}
	}

	//follow locationOfPreviousWayPoint and construct fullroute

	return fullRoute;
}

double Router::computePriority(int n, GeoPoint point, GeoPoint goal) const {
	//calculate priority based on number of steps taken and the distance to goal
	double hVal = distance_earth_km(point, goal);
	return hVal + n;
}