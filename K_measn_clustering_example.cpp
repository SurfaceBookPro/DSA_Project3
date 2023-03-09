//
// Created by Jiantong wang on 3/8/23.
//

#include "K_measn_clustering_example.h"
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

vector<point> k_measn_clustering_example::initCentroids(vector<point>& dataPoints, int k){
    vector<point> centroids;
    for(int i = 0; i < k; i++){
        centroids.push_back(dataPoints[i]);
    }

}