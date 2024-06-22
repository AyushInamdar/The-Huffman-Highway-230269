#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
private:
    std::unordered_map<int, std::vector<int>> paths;

    void dfs(TreeNode* node, std::vector<int>& path) {
        if (!node) return;

        path.push_back(node->val);
        paths[node->val] = path;

        dfs(node->left, path);
        dfs(node->right, path);

        path.pop_back();
    }

    TreeNode* lca(TreeNode* root, int p, int q) {
        if (!root || root->val == p || root->val == q) return root;
        TreeNode* left = lca(root->left, p, q);
        TreeNode* right = lca(root->right, p, q);
        if (left && right) return root;
        return left ? left : right;
    }

public:
    std::vector<std::vector<int>> treePathQueries(TreeNode* root, std::vector<std::pair<int, int>>& queries) {
        std::vector<int> path;
        dfs(root, path);

        std::vector<std::vector<int>> results;

        for (const auto& query : queries) {
            int node1 = query.first;
            int node2 = query.second;

            TreeNode* lca_node = lca(root, node1, node2);
            std::vector<int> path1 = paths[node1];
            std::vector<int> path2 = paths[node2];
            std::vector<int> lca_path = paths[lca_node->val];

            std::vector<int> full_path;
            for (int i = path1.size() - 1; i >= 0; i--) {
                if (std::find(lca_path.begin(), lca_path.end(), path1[i]) == lca_path.end()) {
                    full_path.push_back(path1[i]);
                } else {
                    break;
                }
            }

            for (size_t i = lca_path.size() - 1; i < path2.size(); i++) {
                full_path.push_back(path2[i]);
            }

            int sum = 0;
            int max_val = INT_MIN;
            int min_val = INT_MAX;

            for (int val : full_path) {
                sum += val;
                max_val = std::max(max_val, val);
                min_val = std::min(min_val, val);
            }

            results.push_back({sum, max_val, min_val});
        }

        return results;
    }
};

int main()
{
    // Create the tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // Create queries
    std::vector<std::pair<int, int>> queries = {{2, 4}, {5, 1}};

    Solution solution;
    std::vector<std::vector<int>> results = solution.treePathQueries(root, queries);

    // Print results
    for (size_t i = 0; i < results.size(); i++) {
        std::cout << "Query " << i+1 << ": ";
        std::cout << "Sum = " << results[i][0] << ", ";
        std::cout << "Max = " << results[i][1] << ", ";
        std::cout << "Min = " << results[i][2] << std::endl;
    }

    return 0;
}
