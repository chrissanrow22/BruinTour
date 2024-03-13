#include "router.h"

Router::Router(const GeoDatabaseBase& geo_db) {

}

Router::~Router() {

}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1, const GeoPoint& pt2) const {

}

int Router::computePriority(int n, GeoPoint point, GeoPoint goal) const {
	//calculate priority based on number of steps taken and the distance to goal
	return 0;
}

void Router::insertToQueue(PathNode node) {
	//insert into bottom right most position

	//swap upwards until you no longer can (i.e. new node is in the correct position)
}

GeoPoint Router::popQueueTop() {
	//return vector[0].point

	//remove vector[0].point from array

	//revert queue into complete binary tree

	//turn back into heap
}