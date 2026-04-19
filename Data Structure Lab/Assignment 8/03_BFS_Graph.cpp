#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(int start, const vector<vector<int>>& adjList, int vertices) {
    vector<bool> visited(vertices, false); 
    queue<int> q; 
    visited[start] = true;
    q.push(start);
    cout << "BFS Traversal starting from vertex " << start << ": ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";
        for (int neighbor : adjList[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
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
    cout << "Enter starting vertex for BFS: ";
    cin >> startVertex;

    BFS(startVertex, adjList, vertices);

    return 0;
}