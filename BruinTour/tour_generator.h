#ifndef TOUR_GENERATOR_H
#define TOUR_GENERATOR_H

#include "base_classes.h"
#include "geodb.h"
#include "router.h"
#include "geotools.h"
#include <vector>

class TourGenerator : public TourGeneratorBase
{
public:
	TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router);
	virtual ~TourGenerator();
	virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
private:
	const GeoDatabaseBase& m_gdb;
	const RouterBase& m_router;
	std::string computeDirection(double angle) const;
};

#endif // !TOUR_GENERATOR_H