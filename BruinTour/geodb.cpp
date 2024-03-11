#include "geodb.h"

GeoDatabase::GeoDatabase() {

}

GeoDatabase::~GeoDatabase() {

}

bool GeoDatabase::load(const std::string& map_data_file){

}

bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const{

}

std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const{

}

std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const{

}