#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>

class BinaryTree
{
public:
    using Visitor = std::function<void(int)>;

private:
    struct Node
    {
        std::shared_ptr<Node> left, right;
        int value;
    };

    std::shared_ptr<Node> root;

private:
    void insert_recursive(const std::shared_ptr<Node>& cur, const std::shared_ptr<Node>& insert)
    {
        bool insertIsLess = insert->value < cur->value;
        if(insertIsLess)
        {
            // в левое
            if(cur->left == nullptr)
                cur->left = insert;
            else
                insert_recursive(cur->left, insert);
        }
        else
        {
            // в правое
            if(cur->right == nullptr)
                cur->right = insert;
            else
                insert_recursive(cur->right, insert);
        }
    }

    void visit_recursive(const std::shared_ptr<Node>& node, const Visitor& visitor)
    {
        // в левое
        if(node->left != nullptr)
            visit_recursive(node->left, visitor);

        visitor(node->value);

        // в правое
        if(node->right != nullptr)
            visit_recursive(node->right, visitor);
    }

public:
    void insert(int value)
    {
        std::shared_ptr<Node> insert = std::make_shared<Node>();
        insert->value = value;

        if(root == nullptr)
        {
            root = insert;
            return;
        }

        insert_recursive(root, insert);
    }

    void visit(Visitor call)
    {
        if(root == nullptr)
            return;

        visit_recursive(root, call);
    }
};

void BinaryTreeSort(std::vector<int>& items)
{
    BinaryTree tree;
    for(const auto item: items)
    {
        tree.insert(item);
    }

    tree.visit([](int value)
    {
        std::cout << value << ",";
    });

    std::cout << "\n";
}

int main()
{
    std::vector<int> items {10, 25, 13, 6, 52, 1};
    BinaryTreeSort(items);
    return 0;
}
