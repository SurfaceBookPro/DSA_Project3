//
// Created by Jiantong wang on 3/8/23.
//

#ifndef DSA_PROJECT3_K_MEANS_CLUSTERING_H
#define DSA_PROJECT3_K_MEANS_CLUSTERING_H
#include <vector>
using namespace std;

class k_means_clustering {
public:

    struct cluster{
        double x;
        double y;
        vector<pair<double, double>> points;
    };

    vector<cluster> clusters;

    vector<cluster> generateClusters(int k, vector<double>& latitudes, vector<double>& longitudes);

    double euclideanDistance(pair<double, double>& point1, pair<double, double>& point2);


};


#endif //DSA_PROJECT3_K_MEANS_CLUSTERING_H
