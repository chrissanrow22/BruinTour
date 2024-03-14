#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

#include "geotools.h"
#include "base_classes.h"
#include "geopoint.h"
#include "HashMap.h"

class GeoDatabase : public GeoDatabaseBase
{
public:
	GeoDatabase();
	virtual ~GeoDatabase();
	virtual bool load(const std::string& map_data_file);
	virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const;
	virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
	virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const;
private:
	HashMap<GeoPoint> m_pois;
	HashMap<std::vector<GeoPoint>> m_connectedPoints;
	HashMap<std::string> m_segmentNames;
};