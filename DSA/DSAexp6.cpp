#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Graph {
    vector<vector<int>> matrix;
    vector<string> names;

public:
    Graph(int n) {
        matrix = vector<vector<int>>(n, vector<int>(n, 0));
        names.resize(n);
    }

    void add_name(int i, string name) {
        names[i] = name;
    }

    void add_path(int a, int b, int cost) {
        matrix[a][b] = cost;
        matrix[b][a] = cost;
    }

    void show() {
        cout << "Cities:\n";
        for (int i = 0; i < names.size(); i++) {
            cout << i << ": " << names[i] << endl;
        }
        
        cout << "\nMatrix:\n";
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void show_graph() {
        cout << "\nGraph Representation:\n";
        for (int i = 0; i < names.size(); i++) {
            cout << names[i] << " -> ";
            for (int j = 0; j < names.size(); j++) {
                if (matrix[i][j] != 0) {
                    cout << names[j] << "(" << matrix[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }

    void dfs(int start, unordered_set<int>& visited) {
        cout << names[start] << " ";
        visited.insert(start);
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[start][i] != 0 && visited.find(i) == visited.end()) {
                dfs(i, visited);
            }
        }
    }

    void start_dfs(int start) {
        unordered_set<int> visited;
        cout << "\nDFS Traversal: ";
        dfs(start, visited);
        cout << endl;
    }
};

int main() {
    Graph g(4);
    
    g.add_name(0, "Delhi");
    g.add_name(1, "Mumbai");
    g.add_name(2, "Bangalore");
    g.add_name(3, "Kolkata");
    
    g.add_path(0, 1, 120);
    g.add_path(0, 2, 150);
    g.add_path(1, 3, 180);
    g.add_path(2, 3, 160);
    
    g.show();
    g.show_graph();
    g.start_dfs(0);
    return 0;
}