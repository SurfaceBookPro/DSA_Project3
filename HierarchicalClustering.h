//
// Created by Ozgur Mert Emir on 3/19/23.
//

#ifndef DSA_PROJECT3_HIERARCHICALCLUSTERING_H
#define DSA_PROJECT3_HIERARCHICALCLUSTERING_H
#include <vector>
#include <iostream>

using namespace std;
struct coordinate{
    double x;
    double y;
    int id;
};

struct cluster{
    vector<coordinate> coordinates;
    double avgX;
    double avgY;

    void merge(cluster& c) {
        int size = coordinates.size();
        int size2 = c.coordinates.size();
        avgX = (avgX*size + c.avgX*size2) / (size+size2);
        avgY = (avgY*size + c.avgY*size2) / (size+size2);

        for(coordinate coordinate : c.coordinates)
            coordinates.push_back(coordinate);
    }

    void print() const {
        for(coordinate c : coordinates){
            cout << "ID: " << c.id << ",   Coordinates: " << c.x << "," << c.y << endl;
        }
    }
};

class HierarchicalClustering {
    double euclideanDistance(cluster& pos1, cluster& pos2);

public:
    void formClusters(vector<cluster>&, int n);
};

#endif //DSA_PROJECT3_HIERARCHICALCLUSTERING_H