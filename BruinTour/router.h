#ifndef ROUTER_H
#define ROUTER_H

#include "base_classes.h"
#include "HashMap.h"
#include "geotools.h"
#include <queue>
#include <vector>
#include <algorithm>

class Router : public RouterBase {
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:

	double heuristic(GeoPoint point, GeoPoint goal) const;

	//struct to store GeoPoint
	struct PathNode {
		PathNode(GeoPoint curr, double priority) {
			m_point = curr;
			m_priority = priority;
		}
		GeoPoint m_point;
		double m_priority;
	};
	
	//pathnode comparison operator for prio queue
	class Compare
	{
	public:
		bool operator() (PathNode a, PathNode b)
		{
			return a.m_priority > b.m_priority;
		}
	};

	const GeoDatabaseBase& m_gdb;
};

#endif // !ROUTER_H