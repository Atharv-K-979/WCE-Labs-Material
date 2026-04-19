#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int vertices, edges;
    cout << "Enter vertices: ";
    cin >> vertices;
    cout << "Enter edges: ";
    cin >> edges;
    vector<vector<int>> adjMatrix(vertices, vector<int>(vertices, 0));
    bool directed;
    char choice;
    cout << "Is the graph directed? (y/n): ";
    cin >> choice;
    directed = (choice == 'y' || choice == 'Y');
    cout << "Enter edges (u v) from 0:\n";
    for (int i = 0; i < edges; ++i)
    {
        int u, v;
        cin >> u >> v;

        adjMatrix[u][v] = 1;
        if (!directed)
        {
            adjMatrix[v][u] = 1;
        }
    }
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}