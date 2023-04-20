//
// Created by Jiantong wang on 3/8/23.
//

#include "K_means_clustering.h"
#include <iostream>
#include <vector>
using namespace std;



struct cluster{
    double x;
    double y;
    vector<pair<double, double>> points;
};

vector<k_means_clustering::cluster> k_means_clustering::generateClusters(int k, vector<double>& latitudes, vector<double>& longitudes) {
    vector<cluster> clusters;
    for (int i = 0; i < k; i++) {
        cluster c;
        c.x = latitudes[i];
        c.y = longitudes[i];
        clusters.push_back(c);
    }
    return clusters;
}

double k_means_clustering::euclideanDistance(pair<double, double>& point1, pair<double, double>& point2) {
    double result = sqrt(pow(point1.first - point2.first, 2) + pow(point1.second - point2.second, 2));
    return result;
}