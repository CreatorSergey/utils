/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    
    // конвертация дерева в вектор
    void to_vector(TreeNode* root, std::vector<TreeNode*>& store)
    {
        if(root == nullptr)
            return;
        
        to_vector(root->left, store);
        store.push_back(root);
        to_vector(root->right, store);
    }
    
    // так как вектор отсортированный, будем делить его по полам и заполнять элементы
    TreeNode* balance(std::vector<TreeNode*>& store, int start, int end)
    {
        if(start > end)
            return nullptr;
        
        int middle = (start + end) / 2;
        TreeNode* root = store[middle];
        
        root->left = balance(store, start, middle - 1);
        root->right = balance(store, middle + 1, end);
        
        return root;
    }
    
    
    TreeNode* balanceBST(TreeNode* root) {
        std::vector<TreeNode*> store;
        
        to_vector(root, store);
        
        return balance(store, 0, store.size() - 1);
    }
};
