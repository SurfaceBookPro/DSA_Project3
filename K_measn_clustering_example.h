//
// Created by Jiantong wang on 3/8/23.
//

#ifndef DSA_PROJECT3_K_MEASN_CLUSTERING_EXAMPLE_H
#define DSA_PROJECT3_K_MEASN_CLUSTERING_EXAMPLE_H

class k_measn_clustering_example {
public:
    void run();

private:
    int k;
    int n;
    int d;
    int** data;
    int** centroids;
    int* cluster;
    int* cluster_size;
    int* cluster_sum;
    int* cluster_sum_square;
    int* cluster_sum_square_new;
    int* cluster_sum_new;
    int* cluster_size_new;
    int* cluster_new;

    void read_data();
    void init_centroids();
    void init_cluster();
    void init_cluster_sum();
    void init_cluster_sum_square();
    void init_cluster_size();
    void init_cluster_sum_new();
    void init_cluster_sum_square_new();
    void init_cluster_size_new();
    void init_cluster_new();
    void update_cluster();
    void update_cluster_sum();
    void update_cluster_sum_square();
    void update_cluster_size();
    void update_centroids();
    void update_cluster_sum_new();
    void update_cluster_sum_square_new();
    void update_cluster_size_new();
    void update_cluster_new();

};


#endif //DSA_PROJECT3_K_MEASN_CLUSTERING_EXAMPLE_H
