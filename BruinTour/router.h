#include "base_classes.h"
#include "scaffoldhashmap.h"
#include "geotools.h"
#include <queue>

class Router : public RouterBase {
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	struct PathNode {
		GeoPoint m_curr;
		GeoPoint m_prev;
		double priorityVal;
		bool operator<(const PathNode& other) {
			return this->priorityVal < other.priorityVal;
		}
	};

	double computePriority(int n, GeoPoint point, GeoPoint goal) const;

	HashMap<GeoPoint> locationOfPreviousWayPoint;
	std::priority_queue<PathNode> priorityQueue;

	GeoDatabaseBase* m_gdb;
};