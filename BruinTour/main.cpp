/*
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "geodb.h"
#include "router.h"
#include "stops.h"
#include "tourcmd.h"
#include "tour_generator.h"

using namespace std;

void print_tour(vector<TourCommand>& tcs)
{
    double total_dist = 0;
    std::string direction;
    double street_distance = 0;

    cout << "Starting tour...\n";

    for (size_t i = 0; i < tcs.size(); ++i)
    {
        if (tcs[i].get_command_type() == TourCommand::commentary)
        {
            cout << "Welcome to " << tcs[i].get_poi() << "!\n";
            cout << tcs[i].get_commentary() << "\n";
        }
        else if (tcs[i].get_command_type() == TourCommand::turn)
        {
            cout << "Take a " << tcs[i].get_direction() << " turn on " << tcs[i].get_street() << endl;
        }
        else if (tcs[i].get_command_type() == TourCommand::proceed)
        {
            total_dist += tcs[i].get_distance();
            if (direction.empty())
                direction = tcs[i].get_direction();
            street_distance += tcs[i].get_distance();
            if (i+1 < tcs.size() && tcs[i+1].get_command_type() == TourCommand::proceed 
                && tcs[i+1].get_street() == tcs[i].get_street() && tcs[i].get_street() != "a path")
            {
                continue;
            }

            cout << "Proceed " << std::fixed << std::setprecision(3) << street_distance << " miles " << direction << " on " << tcs[i].get_street() << endl;
            street_distance = 0;
            direction.clear();
        }
    }

    cout << "Your tour has finished!\n";
    cout << "Total tour distance: " << std::fixed << std::setprecision(3) << total_dist << " miles\n";
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "usage: BruinTour mapdata.txt stops.txt\n";
        return 1;
    }

    GeoDatabase geodb;
    if (!geodb.load(argv[1]))
    {
        cout << "Unable to load map data: " << argv[1] << endl;
        return 1;
    }

    Router router(geodb);
    TourGenerator tg(geodb, router);

    Stops stops;
    if (!stops.load(argv[2]))
    {
        cout << "Unable to load tour data: " << argv[2] << endl;
        return 1;
    }

    std::cout << "Routing...\n\n";

    vector<TourCommand> tcs = tg.generate_tour(stops);
    if (tcs.empty())
        cout << "Unable to generate tour!\n";
    else
        print_tour(tcs);
}
*/

// TESTING HASHMAP

#include <iostream>
#include <cassert>
#include "HashMap.h"
using namespace std;

int main() {
    HashMap<int> testHashMap;
    testHashMap.insert("Chris", 33);
    testHashMap.insert("Caitlan", 22);
    assert(testHashMap.size() == 2);
    testHashMap["Chris"] = 22;
    assert(testHashMap.size() == 2 && testHashMap["Chris"] == 22);
    testHashMap["Jul"] = 77;
    assert(testHashMap.size() == 3 && testHashMap["Jul"] == 77);

    //insert items until load factor is reached (i.e. add 10 items)
    testHashMap.insert("trash", 11);
    testHashMap.insert("thirtiethfloor", 30);
    testHashMap.insert("Waterfall", 3);
    testHashMap.insert("victim", 233);
    testHashMap.insert("westernunion", 2);
    testHashMap.insert("thevoid", 331);
    testHashMap.insert("acidrain", 224);


    testHashMap.insert("YOULOSE", 237);
    testHashMap.insert("someday", 422);
    testHashMap.insert("had enough", 228);
    testHashMap.insert("whitenoise", 315);
    testHashMap.insert("Jspretend", 344);
    testHashMap.insert("home", 337);
    testHashMap.insert("MG1", 46);
    testHashMap.insert("IonicFunk", 434);
}