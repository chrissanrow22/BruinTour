#include "base_classes.h"
#include "scaffoldhashmap.h"
#include <vector>

class Router : public RouterBase {
public:
	Router(const GeoDatabaseBase& geo_db);
	virtual ~Router();
	virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	struct PathNode {
		GeoPoint point;
		int priorityVal;
	};

	int computePriority(int n, GeoPoint point, GeoPoint goal) const;

	HashMap<GeoPoint> locationOfPreviousWayPoint;
	std::vector<PathNode> priorityqueue;

	void insertToQueue(PathNode node);
	GeoPoint popQueueTop();
};