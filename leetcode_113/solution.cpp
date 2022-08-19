#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> res;
    vector<int> stack;

    void dfs (TreeNode* root, int targetSum) {
        if (root == nullptr) return;
        stack.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            if (root->val == targetSum) res.push_back(stack);
        }
        dfs(root->left, targetSum - root->val);
        dfs(root->right, targetSum - root->val);
        stack.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        dfs(root, targetSum);
        return res;
    }
};