#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

struct Cell {
    int x, y, z;
    int dist;
    Cell(int x, int y, int z, int dist) : x(x), y(y), z(z), dist(dist) {}
};

bool isValid(int x, int y, int z, int X, int Y, int Z) {
    return (x >= 0 && x < X && y >= 0 && y < Y && z >= 0 && z < Z);
}

int shortestPath(vector<vector<vector<int>>>& grid, int xs, int ys, int zs, int xd, int yd, int zd) {
    int X = grid.size();
    int Y = grid[0].size();
    int Z = grid[0][0].size();

    if (grid[xs][ys][zs] == 1 || grid[xd][yd][zd] == 1) {
        return -1;
    }

    vector<vector<int>> directions = {
        {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}
    };

    vector<vector<vector<bool>>> visited(X, vector<vector<bool>>(Y, vector<bool>(Z, false)));
    queue<Cell> q;

    q.push(Cell(xs, ys, zs, 0));
    visited[xs][ys][zs] = true;

    while (!q.empty()) {
        Cell curr = q.front();
        q.pop();

        if (curr.x == xd && curr.y == yd && curr.z == zd) {
            return curr.dist;
        }

        for (const auto& dir : directions) {
            int nx = curr.x + dir[0];
            int ny = curr.y + dir[1];
            int nz = curr.z + dir[2];

            if (isValid(nx, ny, nz, X, Y, Z) && !visited[nx][ny][nz] && grid[nx][ny][nz] == 0) {
                visited[nx][ny][nz] = true;
                q.push(Cell(nx, ny, nz, curr.dist + 1));
            }
        }
    }

    return -1;
}

int main() {
    int X, Y, Z;
    cin >> X >> Y >> Z;

    int xs, ys, zs, xd, yd, zd;
    cin >> xs >> ys >> zs >> xd >> yd >> zd;

    vector<vector<vector<int>>> grid(X, vector<vector<int>>(Y, vector<int>(Z)));

    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            for (int k = 0; k < Z; k++) {
                cin >> grid[i][j][k];
            }
        }
    }

    int result = shortestPath(grid, xs, ys, zs, xd, yd, zd);
    if (result == -1) {
        cout << "No path exists" << endl;
    } else {
        cout << "Shortest path length: " << result << endl;
    }

    return 0;
}
