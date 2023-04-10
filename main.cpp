#include <iostream>
#include <vector>
#include <string>
#include "K_measn_clustering.h"

using namespace std;

int main() {

    int choice;
    cout << "Please select the function you want to use:" << endl;
    cout << "1. K-means Clustering" << endl;
    cout << "2. Hierarchical Clustering" << endl;
    cin >> choice;

    if (choice == 1){
        int k;
        cout << "Please enter the number of taxi stations you want to build" << endl;
        cin >> k;
    }
    return 0;
}
