//
// Created by Jiantong wang on 3/8/23.
//

#ifndef DSA_PROJECT3_K_MEASN_CLUSTERING_EXAMPLE_H
#define DSA_PROJECT3_K_MEASN_CLUSTERING_EXAMPLE_H
#include <vector>
using namespace std;

class k_measn_clustering_example {
    struct point{
        int id;
        double x;
        double y;
    };

    struct cluster{
        point centroid;
        vector<point> points;
    };

    // Initialize the centroids by randomly selecting k points from the data set
    vector<point> initCentroids(vector<point>& dataPoints, int k);

    // Assign each data point to its nearest centroid based on Euclidean distance
    void assignPointsToClusters(const std::vector<point>& dataPoints, const std::vector<point>& centroids, std::vector<cluster>& clusters);

    // Calculate the new centroid for each cluster as the mean of all the data points assigned to that cluster
    void updateCentroids(std::vector<cluster>& clusters);

    // Perform k-means clustering by iterating the assignPointsToClusters and updateCentroids functions until the centroids no longer move significantly or a maximum number of iterations is reached
    void kMeansClustering(std::vector<point>& dataPoints, int k, int maxIterations, std::vector<cluster>& clusters);

    // Compute the sum of squared errors (SSE) for the clustering, which is a measure of how well the data points are clustered around their centroids
    double computeSumOfSquaredErrors(const std::vector<cluster>& clusters);

    void readData(string fileName);
};


#endif //DSA_PROJECT3_K_MEASN_CLUSTERING_EXAMPLE_H
