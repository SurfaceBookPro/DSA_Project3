#include <iostream>
#include "HierarchicalClustering.h"
#include "K_MeansClustering.h"
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <set>
#include <matplot/matplot.h>

using namespace std;
//randomly picks n points from the dataset
pair<vector<point>, vector<cluster>> sample(int n, vector<double>& latitudes, vector<double>& longitudes){
    // random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, latitudes.size() - 1);
    set<int> chosen_indices;

    vector<point> sample_Kmeans;
    vector<cluster> sample_Hierarchical;
    for (int i = 0; i < n; i++) {
        int index = dis(gen);
        while(chosen_indices.find(index) != chosen_indices.end())  index = dis(gen);
        chosen_indices.insert(index);

        point KmeansPoint{
            .x = longitudes[index],
            .y = latitudes[index],
            .id = i,
            .clusterNo = -1
        };

        coordinate HierarchicalCoordinate{
            .x = longitudes[index],
            .y = latitudes[index],
            .id = i
        };

        vector<coordinate> c;
        c.push_back(HierarchicalCoordinate);

        cluster HierarchicalCluster{
                .coordinates = c,
                .avgX = longitudes[index],
                .avgY = latitudes[index],
        };

        sample_Kmeans.push_back(KmeansPoint);
        sample_Hierarchical.push_back(HierarchicalCluster);
    }

   return {sample_Kmeans, sample_Hierarchical};
}

int main() {
    std::cout << "Please type the number of cluster you want:" << std::endl;
    string n;
    getline(cin, n);
    int clusterNum = stoi(n);

    HierarchicalClustering hierarchicalClustering;
    K_MeansClustering kMeansClustering;

    ///Fetching Points
    vector<double> latitudes;
    vector<double> longitudes;
    int i = 0;

    ifstream file("NY_Taxi_Pickup_Data_Mini.csv");
    if (file.is_open()) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            i++;
            stringstream ss(line);
            string lat_str, lon_str;
            getline(ss, lat_str, ',');
            getline(ss, lon_str);

            double lat_double = stod(lat_str);
            double lon_double = stod(lon_str);

            if(lat_str.empty() || lon_str.empty()) continue;
            if(lat_double == 0.0 || lon_double == 0.0 || lon_double < -74.2 || lon_double > -70.0 || lat_double < 40.5 || lat_double > 41.2) continue;
            double lat = stod(lat_str);
            double lon = stod(lon_str);

            latitudes.push_back(lat);
            longitudes.push_back(lon);
        }
    } else {
        cout << "Error: could not open file ./NY_Taxi_Pickup_Data.csv" << endl;
    }


    // print out the latitudes and longitudes
    cout << "Lat Size: " << latitudes.size() << ", Lon Size: " << longitudes.size() << endl;
    cout << "Empty Row Count:" << i-latitudes.size() << endl;

    //Sampling Test
    pair<vector<point>, vector<cluster>> testSet = sample(100, latitudes, longitudes);

    double maxLat = INT_MIN;
    double maxLon = INT_MIN;
    double minLat = INT_MAX;
    double minLon = INT_MAX;

    //finding the boundaries of the dataset
    for(point& p : testSet.first){
        //cout << p.x << ", " << p.y << ", " << p.id << ", " << p.clusterNo << endl;
        maxLat = max(maxLat, p.y);
        minLat = min(minLat, p.y);
        maxLon = max(maxLon, p.x);
        minLon = min(minLon, p.x);
    }


    //for(cluster& c : testSet.second)
      //  cout << c.coordinates[0].x << ", " << c.coordinates[0].y << ", " << c.coordinates[0].id << endl;

    /// Hierarchical Clustering Test
    vector<double> hierarchicalClustersLat;
    vector<double> hierarchicalClustersLon;
    hierarchicalClustering.formClusters(testSet.second, clusterNum);
    int clusterID = 0;
    for(const cluster& cluster : testSet.second){
        cout << "Cluster ID: " << clusterID << "   Size: " << cluster.coordinates.size() << endl;
        cout << "Cluster Center Coordinates: " << cluster.avgX << "," << cluster.avgY << endl;
        hierarchicalClustersLat.push_back(cluster.avgX);
        hierarchicalClustersLon.push_back(cluster.avgY);
        //cluster.print();
        for(const coordinate& c : cluster.coordinates){
            cout << c.x << "," << c.y;
        }
        clusterID++;
        cout << endl;
        cout << endl;
    }

    /// K-means Clustering Test
    vector<double> kClusterLatitudes;
    vector<double> kClusterLongitudes;

    vector<pair<kCluster, vector<point>>> kClusters = kMeansClustering.formClusters(testSet.first, clusterNum, minLat, minLon, maxLat, maxLon);
    for(const auto& clusterData : kClusters){
        /*
        for(const point& p : clusterData.second){
            cout << "ID: " << p.id << ",   Coordinates: " << p.x << "," << p.y << "   , Cluster No: " << p.clusterNo <<endl;
        }
         */
        cout << "Cluster ID: " << clusterData.first.clusterID << "   Size: " << clusterData.first.size << endl;
        cout << "Cluster Center Coordinates: " << clusterData.first.avgX << "," << clusterData.first.avgY<< endl;
        cout << endl;
        kClusterLatitudes.push_back(clusterData.first.avgX);
        kClusterLongitudes.push_back(clusterData.first.avgY);
    }

    // Visualization: step 1
    cout << "Visualization started." << endl;

    auto dataPoints = matplot::scatter(longitudes, latitudes);
    cout << "Data points number for datapoints" << longitudes.size() << " " << latitudes.size() << endl;
    dataPoints->marker_size(5);
    dataPoints->marker_face(true);
    dataPoints->marker_face_color({100.0, 200.0, 100.0});
    matplot::hold(matplot::on);


    //Your Longtitudes and Latitudes are reversed. I swapped them here.
    auto kClusterPoints = matplot::scatter(kClusterLatitudes, kClusterLongitudes );
    cout << "Data points number for k-means" << kClusterLatitudes.size() << " " << kClusterLongitudes.size() << endl;
    kClusterPoints->marker_size(18);
    kClusterPoints->marker_face(true);
    kClusterPoints->marker_face_color({300.0, 100.0, 100.0});
    matplot::hold(matplot::on);


    auto hierarchicalClusterPoints = matplot::scatter(hierarchicalClustersLat, hierarchicalClustersLon);
    cout << "Data points number for hierarchical" << hierarchicalClustersLat.size() << " " << hierarchicalClustersLon.size() << endl;
    hierarchicalClusterPoints->marker_size(10);
    hierarchicalClusterPoints->marker_face(true);
    hierarchicalClusterPoints->marker_face_color({100.0, 100.0, 300.0});
    matplot::hold(matplot::on);



    cout << "Visualization completed." << endl;
    matplot::show();

    return 0;
}