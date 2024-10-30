//Nicholas Guidice
//CS 375 Project 5 "Breadth First Search"

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>

using namespace std;

// Graph class definition
class Graph {
public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int vertices) : adjList(vertices) {}

    // Method to add a directed edge from vertex u to vertex v
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Append v to the adjacency list of u
    }

    // Method to perform BFS and find the shortest path from start to end
    int bfs(int start, int end) {
        // If the start vertex is the same as the end vertex, return 0
        if (start == end) return 0; 
        
        vector<bool> visited(adjList.size(), false);// Vector to keep track of visited vertices
        
        queue<int> q;// Queue for BFS to explore the graph
        
        unordered_map<int, int> distance; // Map to store the distance from the start vertex

        // Initialize the BFS with the start vertex
        q.push(start);
        visited[start] = true; // Mark the start vertex as visited
        distance[start] = 0; 

        // Loop while there are vertices to explore in the queue
        while (!q.empty()) {
            int current = q.front(); // Get the current vertex
            q.pop(); // Remove it from the queue

            // Explore all neighbors of the current vertex
            for (int neighbor : adjList[current]) {
                // If the neighbor hasn't been visited yet
                if (!visited[neighbor]) {
                    visited[neighbor] = true; 
                    distance[neighbor] = distance[current] + 1; // Update distance
                    q.push(neighbor); 

                    // If we reached the end vertex, return the distance
                    if (neighbor == end) {
                        return distance[neighbor];
                    }
                }
            }
        }
        return -1; // Return -1 if the end vertex is not reachable
    }

private:
    vector<vector<int>> adjList; // Adjacency list representation of the graph
};

int main(int argc, char* argv[]) {
    // Check if the correct number of command line arguments are provided
    if (argc != 3) {
        cerr << "Usage: yourprogram <start_vertex> <end_vertex> < inputfile.txt" << endl;
        return 1; 
    }

    // Parse the start and end vertices from command line arguments
    int startVertex = atoi(argv[1]);
    int endVertex = atoi(argv[2]);

    int numVertices, numEdges;
    // Read the number of vertices and edges from standard input
    cin >> numVertices >> numEdges;
    
    // Create a graph with the specified number of vertices
    Graph graph(numVertices);

    // Read edges and construct the graph
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v; // Read each directed edge
        graph.addEdge(u, v); 
    }

    // Perform BFS to find the shortest path from start to end
    int result = graph.bfs(startVertex, endVertex);
    
    // Print the result: number of edges or "not connected"
    if (result == -1) {
        cout << "not connected" << endl; // End vertex is unreachable
    } else {
        cout << result << endl; // Print the number of edges
    }

    return 0; // Successful execution
}
