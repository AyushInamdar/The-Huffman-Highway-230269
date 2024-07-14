#include <bits/stdc++.h>
using namespace std;

int knapsack(int N, int W, vector<int>& weights, vector<int>& values, vector<int>& dependencies, vector<int>& categories, vector<int>& limits) {
    // Create a 2D DP table: dp[i][w] represents the maximum value achievable
    // with first i items and weight capacity w
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    // Create a map to store items by category
    map<int, vector<int>> category_items;
    for (int i = 0; i < N; i++) {
        category_items[categories[i]].push_back(i);
    }

    // Iterate through items
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= W; w++) {
            // Initialize with the value without including the current item
            dp[i][w] = dp[i-1][w];

            // Check if we can include the current item
            for (int count = 1; count <= limits[i-1]; count++) {
                if (w >= count * weights[i-1]) {
                    int new_value = dp[i-1][w - count * weights[i-1]] + count * values[i-1];

                    // Check dependency constraint
                    if (dependencies[i-1] != -1 && dp[i-1][w - count * weights[i-1]] == dp[dependencies[i-1]][w - count * weights[i-1]]) {
                        continue;  // Dependency not satisfied
                    }

                    // Check category constraint
                    bool category_valid = true;
                    for (int item : category_items[categories[i-1]]) {
                        if (item != i-1 && dp[i-1][w - count * weights[i-1]] != dp[item][w - count * weights[i-1]]) {
                            category_valid = false;
                            break;
                        }
                    }

                    if (category_valid) {
                        dp[i][w] = max(dp[i][w], new_value);
                    }
                }
            }
        }
    }

    return dp[N][W];
}

int main() {
    int N = 10;
    int W = 100;
    vector<int> weights = {10, 20, 30, 40, 15, 25, 35, 45, 55, 50};
    vector<int> values = {60, 100, 120, 240, 150, 90, 200, 170, 250, 300};
    vector<int> dependencies = {-1, 0, -1, 2, -1, -1, 1, 4, -1, 7};
    vector<int> categories = {1, 0, 0, 1, 2, 2, 3, 3, 4, 4};
    vector<int> limits = {1, 2, 1, 1, 1, 1, 1, 1, 1, 1};

    int result = knapsack(N, W, weights, values, dependencies, categories, limits);
    cout << "Maximum Knapsack Value: " << result << endl;

    return 0;
}
