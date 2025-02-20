#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_EDGES = 1000; 
const int MAX_VERTICES = 100;

int parent[100];

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

int Saman[100];

void unionSets(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    if (rootU != rootV) {
        if (Saman[rootU] < Saman[rootV]) {
            parent[rootU] = rootV;
        }
        else if (Saman[rootU] > Saman[rootV]) {
            parent[rootV] = rootU;
        }
        else {
            parent[rootV] = rootU;
            Saman[rootU]++;
        }
    }
}

bool compareEdges(const vector<int>& a, const vector<int>& b) {
    return a[2] < b[2];
}

pair<int, vector<int>> kruskalMST(int n, vector<vector<int>>& edges) {
    vector<int> mstEdges; 
    int totalCost = 0; 

    sort(edges.begin(), edges.end(), compareEdges);

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        Saman[i] = 0;
    }

    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        int index = edge[3];

        if (find(u) != find(v)) {
            mstEdges.push_back(index); 
            totalCost += weight; 
            unionSets(u, v); 
        }
    }

    return { totalCost, mstEdges };
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges(m, vector<int>(4));

    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges[i][0] = u;
        edges[i][1] = v;
        edges[i][2] = weight;
        edges[i][3] = i + 1; 
    }

    auto result = kruskalMST(n, edges);

    int totalCost = result.first;
    vector<int> mstEdges = result.second;

    cout << totalCost << endl;
    sort(mstEdges.begin(), mstEdges.end());
    for (int index : mstEdges) {
        cout << index << endl;
    }

    return 0;
}
