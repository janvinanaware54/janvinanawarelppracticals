#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    int x, y;
    int g, h;
    Node* parent;

    int f() const {
        return g + h;
    }
};

// Comparator for priority queue
struct compare {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f();
    }
};

// Manhattan distance heuristic
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check valid cell
bool isValid(int x, int y, int n, int m, vector<vector<int>> &maze) {
    return (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0);
}

// Print path
void printPath(Node* node) {
    if (!node) return;
    printPath(node->parent);
    cout << "(" << node->x << "," << node->y << ") ";
}

// A* function
void AStar(vector<vector<int>> &maze, int sx, int sy, int gx, int gy) {
    int n = maze.size();
    int m = maze[0].size();

    priority_queue<Node*, vector<Node*>, compare> pq;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    Node* start = new Node{sx, sy, 0, heuristic(sx, sy, gx, gy), NULL};
    pq.push(start);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node* curr = pq.top();
        pq.pop();

        int x = curr->x;
        int y = curr->y;

        if (visited[x][y]) continue;
        visited[x][y] = true;

        // Goal reached
        if (x == gx && y == gy) {
            cout << "Path found:\n";
            printPath(curr);
            cout << endl;
            cout << "Total cost: " << curr->g << endl;
            return;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, n, m, maze) && !visited[nx][ny]) {
                Node* next = new Node{
                    nx, ny,
                    curr->g + 1,
                    heuristic(nx, ny, gx, gy),
                    curr
                };
                pq.push(next);
            }
        }
    }

    cout << "No path found.\n";
}

// Main
int main() {
    int n, m;
    cout << "Enter rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));

    cout << "Enter maze (0 = path, 1 = wall):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    int sx, sy, gx, gy;
    cout << "Enter start (x y): ";
    cin >> sx >> sy;

    cout << "Enter goal (x y): ";
    cin >> gx >> gy;

    AStar(maze, sx, sy, gx, gy);

    return 0;
}