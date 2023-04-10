//
// Created by Jiantong wang on 3/8/23.
//

#include "K_measn_clustering.h"
#include <iostream>
#include <vector>
using namespace std;

struct point{
    double x = 0.0;
    double y = 0.0;
};

struct cluster{
    point centroid;
    vector<point> points;
};

