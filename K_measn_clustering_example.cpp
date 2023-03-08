//
// Created by Jiantong wang on 3/8/23.
//
#include "K_measn_clustering_example.h"
#include <iostream>

void k_measn_clustering_example::run() {
    read_data();
    init_centroids();
    init_cluster();
    init_cluster_sum();
    init_cluster_sum_square();
    init_cluster_size();
    init_cluster_sum_new();
    init_cluster_sum_square_new();
    init_cluster_size_new();
    init_cluster_new();
    update_cluster();
    update_cluster_sum();
    update_cluster_sum_square();
    update_cluster_size();
    update_centroids();
    update_cluster_sum_new();
    update_cluster_sum_square_new();
    update_cluster_size_new();
    update_cluster_new();
}

void k_measn_clustering_example::read_data() {
    std::cin >> k >> n >> d;
    data = new int*[n];
    for (int i = 0; i < n; i++) {
        data[i] = new int[d];
        for (int j = 0; j < d; j++) {
            std::cin >> data[i][j];
        }
    }
}

void k_measn_clustering_example::init_centroids() {
    centroids = new int*[k];
    for (int i = 0; i < k; i++) {
        centroids[i] = new int[d];
        for (int j = 0; j < d; j++) {
            std::cin >> centroids[i][j];
        }
    }
}