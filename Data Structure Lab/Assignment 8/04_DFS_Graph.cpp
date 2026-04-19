#include <iostream>
#include <vector>
using namespace std;
void DFSUtil(int vertex, const vector<vector<int>>& adjList, vector<bool>& visited) {
    visited[vertex] = true;
    cout << vertex << " ";
    for (int neighbor : adjList[vertex]) {
        if (!visited[neighbor]) {
            DFSUtil(neighbor, adjList, visited);
        }
    }
}
void DFS(const vector<vector<int>>& adjList, int vertices, int start) {
    vector<bool> visited(vertices, false);
    cout << "DFS Traversal starting from vertex " << start << ": ";
    DFSUtil(start, adjList, visited);
    cout << endl;
}
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
        adjList[u].push_back(v);
        if (!directed) {
            adjList[v].push_back(u);
        }
    }
    int startVertex;
    cout << "Enter starting vertex for DFS: ";
    cin >> startVertex;
    DFS(adjList, vertices, startVertex);
    return 0;
}