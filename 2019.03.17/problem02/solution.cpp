#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

map<int, int> networks;

struct Edge {
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
    Edge(int _a, int _b, int _c): a(_a), b(_b), cost(_c) {}
    int a, b, cost;
};

int get_root(int n) {
    int p;
    while (n != (p = networks[n])) {
        n = p;
    }
    return n;
}

void set_root(int n, int root) {
    do {
        int p = networks[n];
        networks[n] = root;
        n = p;
    } while (n != root);
}

/*
 * Given an existing network connecting a number of cities and a number
 * of new roads, find the minimum costs to connect all cities of the network.
 * This is a problem of how to create a fully connected graphs from a set of
 * subgraphs (given a set of new edges).
*/
int getMinimumCostToConstruct(int numTotalAvailableCities,
                              int numTotalAvailableRoads,
                              vector<vector<int>> roadsAvailable,
                              int numNewRoadsConstruct,
                              vector<vector<int>> costNewRoadsConstruct)
{
    for (int i = 1; i <= numTotalAvailableCities; ++i)
        networks[i] = i;
    for (int i = 0; i < numTotalAvailableRoads; ++i) {
        int a = roadsAvailable[i][0];
        int b = roadsAvailable[i][1];
        int root_a = get_root(a);
        int root_b = get_root(b);
        if (root_a < root_b)
            set_root(b, root_a);
        else
            set_root(a, root_b);
    }

    long long cost = 0;

    vector<Edge> edges;
    for (int i = 0; i < numNewRoadsConstruct; ++i) {
        edges.emplace_back(costNewRoadsConstruct[i][0], costNewRoadsConstruct[i][1], costNewRoadsConstruct[i][2]);
    }
    sort(begin(edges), end(edges));

    for(auto& e: edges) {
        int a = e.a;
        int b = e.b;
        int root_a = get_root(a);
        int root_b = get_root(b);
        if (root_a == root_b)
            continue;
        cost += e.cost;
        if (root_a < root_b)
            set_root(b, root_a);
        else
            set_root(a, root_b);
    }
    return cost;
}

int main()
{
    int numTotalAvailableCities = 6;
    int numTotalAvailableRoads = 3;
    vector<vector<int>> roadsAvailable{{1,4}, {4,5}, {2,3}};
    int numNewRoadsConstruct = 4;
    vector<vector<int>> costNewRoadsConstruct{{1,2,5}, {1,3,10}, {1,6,2}, {5,6,5}};

    cout << "Result: " << getMinimumCostToConstruct(numTotalAvailableCities,
                                                   numTotalAvailableRoads,
                                                   roadsAvailable,
                                                   numNewRoadsConstruct,
                                                   costNewRoadsConstruct) << endl;
    return 0;
}
