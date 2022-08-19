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

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        vector<TreeNode*> stack;
        TreeNode* current = root;
        while (current != nullptr || stack.size() > 0) {
            while (current != nullptr) {
                stack.push_back(current);
                current = current->left;
            }
            if (!stack.empty()) {
                current = stack.back();
                stack.pop_back();
                res.push_back(current->val);
                current = current->right;
            }
        }
        return res;
    }
};