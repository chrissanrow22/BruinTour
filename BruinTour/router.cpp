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
	//check if start is goal and return either one if they are equal
	if (pt1.to_string() == pt2.to_string()) {
		fullRoute.push_back(pt1);
		return fullRoute;
	}

	//priority queue to keep track of what node to check next
	priority_queue<PathNode, vector<PathNode>, Compare> priorityQueue;
	//keep track of the connections between checked nodes
	HashMap<GeoPoint> locationOfPreviousWayPoint;
	//keep track of nodes we have already checked and their associated f values
	HashMap<double> fCosts;

	//push the first node to the priority queue
	PathNode currNode(pt1, 0);
	priorityQueue.push(currNode);
	fCosts[pt1.to_string()] = 0;

	locationOfPreviousWayPoint[pt1.to_string()] = pt1;

	while (!priorityQueue.empty()) {
		//get the lowest priority item
		currNode = priorityQueue.top();
		priorityQueue.pop();

		//reached the end
		if (currNode.m_point.to_string() == pt2.to_string()) {
			break;
		}

		for (GeoPoint next : m_gdb.get_connected_points(currNode.m_point)) {
			//compute the priority for the new node
			//compute the new f cost
			double fCost = fCosts[currNode.m_point.to_string()] + distance_earth_km(currNode.m_point, next);
			
			
			//only process this node if it hasn't already been processed or if its new fCost is lower
			//(i.e.) there is a shorter way to reach it
			if (fCosts.find(next.to_string()) == nullptr || fCost < fCosts[next.to_string()]) {
				//update/insert fcost
				fCosts[next.to_string()] = fCost;
 
			//compute heuristic value
			double hCost = heuristic(next, pt2);
			double newPriority = fCost + hCost;

			//construct a node representing this new node and its associated priority
			PathNode nextNode(next, newPriority);
				//push the new node to priority queue
				priorityQueue.push(nextNode);
				//update/insert where the new node came from
				locationOfPreviousWayPoint[next.to_string()] = currNode.m_point;
			}
		}
	}
	
	//if no valid path was found, return an empty vector
	if (locationOfPreviousWayPoint.size() > 1) {
		//follow locationOfPreviousWayPoint and construct fullroute
		//start at goal and traverse locationOfPreviousWayPoint until reaching start

		GeoPoint currPoint = pt2;
		fullRoute.push_back(pt2);
		while (currPoint.to_string() != pt1.to_string()) {
			currPoint = locationOfPreviousWayPoint[currPoint.to_string()];
			fullRoute.push_back(currPoint);
		}

		std::reverse(fullRoute.begin(), fullRoute.end());
	}

	return fullRoute;
}

double Router::heuristic(GeoPoint point, GeoPoint goal) const {
	//calculate priority based on number of steps taken and the distance to goal
	return distance_earth_km(point, goal);
}