#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

class Graph {
    int V;
    vector<list<pii>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int cost) {
        adj[u].push_back(make_pair(cost, v));
        adj[v].push_back(make_pair(cost, u));
    }

    void primMST() {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vector<int> key(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> inMST(V, false);

        pq.push(make_pair(0, 0));
        key[0] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (list<pii>::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
                int cost = it->first;
                int v = it->second;

                if (!inMST[v] && cost < key[v]) {
                    key[v] = cost;
                    pq.push(make_pair(cost, v));
                    parent[v] = u;
                }
            }
        }

        for (int i = 1; i < V; i++) {
            if (parent[i] == -1) {
                cout << "Disconnected graph. MST not available.\n";
                return;
            }
        }

        cout << "\nMST Result:\n";
        cout << "From\tTo\tCost\n";
        for (int i = 1; i < V; i++) {
            cout << parent[i] << "\t" << i << "\t" << key[i] << "\n";
        }
    }
};

int main() {
    int V, edges;
    cout << "Offices: ";
    cin >> V;

    Graph g(V);

    cout << "Connections: ";
    cin >> edges;

    cout << "Enter each connection as: from to cost\n";

    for (int i = 0; i < edges; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g.addEdge(a, b, c);
    }

    g.primMST();

    return 0;
}