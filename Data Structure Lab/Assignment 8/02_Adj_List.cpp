#include <iostream>
#include <vector>
using namespace std;
int main() {
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;
    cout << "Enter number of edges: ";
    cin >> edges;
    vector<vector<int>> adjList(vertices);
    bool directed;
    char choice;
    cout << "Is the graph directed? (y/n): ";
    cin >> choice;
    directed = (choice == 'y' || choice == 'Y');
    cout << "Enter edges (u v) with vertex indices starting from 0:\n";
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;

        adjList[u].push_back(v); // add v to u's list
        if (!directed) {
            adjList[v].push_back(u); // add u to v's list for undirected graph
        }
    }
    cout << "\nAdjacency List Representation:\n";
    for (int i = 0; i < vertices; ++i) {
        cout << i << " -> ";
        for (int node : adjList[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}