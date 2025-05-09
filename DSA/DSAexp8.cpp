#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int MAX = 20;
float p[MAX]; // Probabilities
float cost[MAX][MAX]; 
int root[MAX][MAX];   


void optimalBST(int n) {
    float sum[MAX] = {0};

    
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + p[i];

    // Initialize cost for single keys
    for (int i = 1; i <= n; i++) {
        cost[i][i] = p[i];
        root[i][i] = i;
    }

    
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost[i][j] = numeric_limits<float>::max();

            for (int r = i; r <= j; r++) {
                float left = (r > i) ? cost[i][r - 1] : 0;
                float right = (r < j) ? cost[r + 1][j] : 0;
                float total = left + right + (sum[j] - sum[i - 1]);

                if (total < cost[i][j]) {
                    cost[i][j] = total;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "\nMinimum search cost: " << cost[1][n] << endl;
}

// Print BST structure
void print(int i, int j, int parent, string pos) {
    if (i > j) return;
    int r = root[i][j];
    if (parent == 0)
        cout << "Key " << r << " is the root" << endl;
    else
        cout << "Key " << r << " is the " << pos << " child of Key " << parent << endl;

    print(i, r - 1, r, "left");
    print(r + 1, j, r, "right");
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter access probabilities (p1 to p" << n << "): ";
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    optimalBST(n);

    cout << "\nBST Structure:\n";
    print(1, n, 0, "");

    return 0;
}

// input 
// Enter number of keys: 4
// Enter access probabilities (p1 to p4): 0.1 0.2 0.4 0.3

// Minimum search cost: 1.7

// BST Structure:
// Key 3 is the root
// Key 2 is the left child of Key 3
// Key 1 is the left child of Key 2
// Key 4 is the right child of Key 3