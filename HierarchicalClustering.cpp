//
// Created by Ozgur Mert Emir on 3/19/23.
//
#include <cmath>
#include "HierarchicalClustering.h"

#include <chrono>
using namespace std::chrono;

// Start the clock
auto start_hierarchical = high_resolution_clock::now();

double HierarchicalClustering::euclideanDistance(cluster& pos1, cluster& pos2) {
    double xdiff = pos1.avgX - pos2.avgX;
    double ydiff = pos1.avgY - pos2.avgY;
    return sqrt(pow(xdiff, 2) + pow(ydiff, 2));
}



void HierarchicalClustering::formClusters(vector<cluster>& clusters, int n) {


    //loop until we have cluster size = n (starting from cluster size = number of points)
    while(clusters.size() > n) {
        double minDistance = INT_MAX;
        int idx1 = -1, idx2 = -1;

        //find the two clusters that are closest to each other
        for(int i = 0; i < clusters.size(); i++) {
            for(int j = 0; j < clusters.size(); j++) {
                if(i == j) continue;
                double distance = euclideanDistance(clusters[i], clusters[j]);
                if(distance < minDistance) {
                    minDistance = distance;
                    idx1 = i, idx2 = j;
                }
            }
        }

        //merge the closest two clusters
        clusters[idx1].merge(clusters[idx2]);
        //remove the merged cluster from clusters
        clusters.erase(clusters.begin() + idx2);
    }

// Stop the clock
    auto stop_hi = high_resolution_clock::now();

// Calculate the elapsed time
    auto duration_hi = duration_cast<milliseconds>(stop_hi - start_hierarchical);

// Print the elapsed time
    cout << "Time taken Hierarchical: " << duration_hi.count() << " milliseconds" << endl;
}