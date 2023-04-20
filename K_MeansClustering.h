//
// Created by Ozgur Mert Emir on 3/23/23.
//

#ifndef DSA_PROJECT3_K_MEANSCLUSTERING_H
#define DSA_PROJECT3_K_MEANSCLUSTERING_H
#include <vector>

using namespace std;
struct point{
    double x;
    double y;
    int id;
    int clusterNo;
};

struct kCluster{

    int size = 0;
    double avgX;
    double avgY;

    double totalX;
    double totalY;
    int clusterID;

    void add(point& p) {
        totalX += p.x;
        totalY += p.y;
        size++;
        //coordinates.push_back(p);
    }

    void remove(point& p) {
        totalX -= p.x;
        totalY -= p.y;
        size--;
        //coordinates.erase(p);
    }

    void updateCenter() {
        avgX = totalX/size;
        avgY = totalY/size;
    }
};
class K_MeansClustering {
    double euclideanDistance(kCluster& cluster, const point& point);
    vector<kCluster> generateClusters(int n, double minLatitude, double minLongtitude, double maxLatitude, double maxLongtitude, vector<point>& points);
    vector<kCluster> generateClusters(int n, double minLatitude, double minLongtitude, double maxLatitude, double maxLongtitude);
    vector<pair<kCluster, vector<point>>> groupByCluster(vector<point>& points, vector<kCluster>& kClusters);
public:
    vector<pair<struct kCluster, vector<struct point>>>
    formClusters(vector<point>& points, int n, double minLat, double minLon, double maxLat, double maxLon);
};

#endif //DSA_PROJECT3_K_MEANSCLUSTERING_H