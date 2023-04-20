//
// Created by Ozgur Mert Emir on 3/23/23.
//

#include <cmath>
#include <iostream>
#include <random>
#include "K_MeansClustering.h"

double K_MeansClustering::euclideanDistance(kCluster& cluster, const point& point) {
    double xdiff = cluster.avgX - point.x;
    double ydiff = cluster.avgY - point.y;
    return sqrt(pow(xdiff, 2) + pow(ydiff, 2));
}
vector<kCluster> K_MeansClustering::generateClusters(int n, double minLatitude, double minLongtitude, double maxLatitude, double maxLongtitude, vector<point>& points) {
    vector<kCluster> clusters(n);

    // Set the first cluster randomly
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> disLat(minLatitude, maxLatitude);
    uniform_real_distribution<> disLon(minLongtitude, maxLongtitude);
    point randomPoint = {disLon(gen), disLat(gen) };
    kCluster& firstCluster = clusters.front();
    firstCluster.clusterID = 0;
    firstCluster.add(randomPoint);
    firstCluster.updateCenter();

    // Set the remaining clusters using kmeans++ initialization
    for (int i = 1; i < n; i++) {
        double sumOfDistances = 0.0;
        for (kCluster& cluster : clusters) {
            for (const auto& point : points) {
                double distance = euclideanDistance(cluster, point);
                sumOfDistances += distance * distance;
            }
        }

        double rnd = disLat(gen) * disLon(gen) * sumOfDistances;
        double partialSum = 0.0;
        int newClusterIndex = 0;
        for (int j = 0; j < clusters.size(); j++) {
            for (const auto& point : points) {
                double distance = euclideanDistance(clusters[j], point);
                partialSum += distance * distance;
                if (partialSum > rnd) {
                    newClusterIndex = j;
                    break;
                }
            }

            if (newClusterIndex != 0) {
                break;
            }
        }

        kCluster& newCluster = clusters[i];
        newCluster.clusterID = i;
        newCluster.add(points[newClusterIndex]);
        newCluster.updateCenter();
    }

    return clusters;
}

vector<kCluster> K_MeansClustering::generateClusters(int n, double minLat, double minLon, double maxLat, double maxLon) {
    vector<kCluster> clusters;

    //random number generator
    random_device rd;
    mt19937 gen(rd());

    //Defining the bounds
    uniform_real_distribution<double> lat(minLat, maxLat);
    uniform_real_distribution<double> lon(minLon, maxLon);

    //initialize clusters with random coordinates
    for(int i = 0; i < n; i++) {
        kCluster cluster;
        cluster.avgY = lat(gen);
        cluster.avgX = lon(gen);
        cluster.totalX = 0;
        cluster.totalY = 0;
        cluster.clusterID = i;
        clusters.push_back(cluster);
    }
    return clusters;
}

vector<pair<struct kCluster, vector<struct point>>> K_MeansClustering::formClusters(vector<point>& points, int n, double minLat, double minLon, double maxLat, double maxLon) {
    vector<kCluster> clusters = generateClusters(n, minLat, minLon, maxLat, maxLon, points);

    //View starting coordinates of clusters
    for (kCluster cluster: clusters) {
        cout << cluster.avgX << "," << cluster.avgY << endl;
    }

    //loop until convergence
    bool flag = true;
    while(flag) {
        flag = false;
        //finding clusters closest to each point
        for (point &point: points) {
            double minDistance = INT_MAX;
            int nearestCluster = point.clusterNo;
            int i = 0;
            //calculating distance to each cluster and assigning the closest one as nearestCluster
            for (kCluster &cluster: clusters) {
                double distance = euclideanDistance(cluster, point);
                if (distance < minDistance) {
                    nearestCluster = i;
                    minDistance = distance;
                }
                i++;
            }
            //change cluster no of the current point if another cluster is closer than the currently assigned cluster
            //Also checks if we converged or not
            if(point.clusterNo != nearestCluster) {
                flag = true;
                clusters[point.clusterNo].remove(point);
                point.clusterNo = nearestCluster;
                clusters[nearestCluster].add(point);
            }
        }
        //update the cluster centers according to the points they have
        for (kCluster &cluster: clusters) cluster.updateCenter();
    }
    return groupByCluster(points, clusters);
}

//grouping points by their cluster no for convenience
vector<pair<kCluster, vector<point>>> K_MeansClustering::groupByCluster(vector<point> &points, vector<kCluster>& kClusters) {
    vector<pair<kCluster, vector<point>>> res;
    int i = 0;
    for (const kCluster& cluster: kClusters) {
        vector<point> cluster_points;
        for(const point& p : points){
            if(p.clusterNo == i) cluster_points.push_back(p);
        }
        pair<kCluster, vector<point>> clusterData;
        clusterData.first = cluster;
        clusterData.second = cluster_points;
        res.push_back(clusterData);
        i++;
    }
    return res;
}