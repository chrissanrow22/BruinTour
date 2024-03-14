#include "base_classes.h"
#include "HashMap.h"
#include "geotools.h"
#include <queue>
#include <vector>

class Router : public RouterBase {
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:

	double computePriority(int n, GeoPoint point, GeoPoint goal) const;

	struct PathNode {
		PathNode(GeoPoint curr, GeoPoint prev, double priority) {
			m_curr = curr;
			m_prev = prev;
			priorityVal = priority;
		}
		GeoPoint m_curr;
		GeoPoint m_prev;
		double priorityVal;
	};
	
	//pathnode comparison operator for prio queue
	class Compare
	{
	public:
		bool operator() (PathNode a, PathNode b)
		{
			return a.priorityVal < b.priorityVal;
		}
	};

	HashMap<GeoPoint> locationOfPreviousWayPoint;
	std::priority_queue<PathNode, vector<PathNode>, Compare> priorityQueue;

	const GeoDatabaseBase& m_gdb;
};