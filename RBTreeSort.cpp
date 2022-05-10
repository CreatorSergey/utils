#include <vector>
#include <iostream>

class RBTree
{
    enum class Color
    {
       BLACK = 0,
       RED = 1 
    };

    struct Node
    {
        int data;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
    };

private:
    Node* root;
    Node* null;

    void initializeNullNode(Node* node, Node* parent)
    {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = Color::BLACK;
    }

    void preOrderHelper(Node* node)
    {
        if(node != null)
        {
            std::cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(Node* node)
    {
        if(node != null)
        {
            inOrderHelper(node->left);
            std::cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(Node* node)
    {
        if(node != null)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            std::cout << node->data << " ";
        }
    }

    Node* searchTreeHelper(Node* node, int key)
    {
        if(node == null || key == node->data)
        {
            return node;
        }

        if(key < node->data)
        {
            return searchTreeHelper(node->left, key);
        }

        return searchTreeHelper(node->right, key);
    }

    void fixDelete(Node* x)
    {
        Node* s;
        while(x != root && x->color == Color::BLACK)
        {
            if(x == x->parent->left)
            {
                s = x->parent->right;
                if(s->color == Color::RED)
                {
                    // case 3.1
                    s->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if(s->left->color == Color::BLACK && s->right->color == Color::BLACK)
                {
                    // case 3.2
                    s->color = Color::RED;
                    x = x->parent;
                }
                else
                {
                    if(s->right->color == Color::BLACK)
                    {
                        // case 3.3
                        s->left->color = Color::BLACK;
                        s->color = Color::RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    s->right->color = Color::BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else
            {
                s = x->parent->left;
                if(x->color == Color::RED)
                {
                    // case 3.1
                    s->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if(s->left->color == Color::BLACK && s->right->color == Color::BLACK)
                {
                    // case 3.2
                    s->color = Color::RED;
                    x = x->parent;
                }
                else
                {
                    if(s->left->color == Color::BLACK)
                    {
                        // case 3.3
                        s->right->color = Color::BLACK;
                        s->color = Color::RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    x->left->color = Color::BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = Color::BLACK;
    }

    void rbTransplant(Node* u, Node* v)
    {
        if(u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node* node, int key)
    {
        Node* z = null;
        Node* x;
        Node* y;
        while(node != null)
        {
            if(node->data == key)
            {
                z = node;
            }

            if(node->data <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if(z == null)
        {
            std::cout << "Couldn\t find key in the tree" << "\n";
            return;
        }

        y = z;
        Color y_original_color = y->color;
        if(z->left == null)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == null)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if(y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if(y_original_color == Color::BLACK)
            fixDelete(x);
    }

    void fixInsert(Node* k)
    {
        Node* u;
        while(k->parent->color == Color::RED)
        {
            if(k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left; // uncle
                if(u->color == Color::RED)
                {
                    // case 3.1
                    u->color = Color::BLACK;
                    k->parent->color = Color::BLACK;
                    k->parent->parent->color = Color::RED;
                    k = k->parent->parent;
                }
                else
                {
                    if(k == k->parent->left)
                    {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }

                    // case 3.2.1
                    k->parent->color = Color::BLACK;
                    k->parent->parent->color = Color::RED;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right; // uncle

                if(u->color == Color::RED)
                {
                    // mirror case 3.1
                    u->color = Color::BLACK;
                    k->parent->color = Color::BLACK;
                    k->parent->parent->color = Color::RED;
                    k = k->parent->parent;
                }
                else
                {
                    if(k == k->parent->right)
                    {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = Color::BLACK;
                    k->parent->parent->color = Color::RED;
                    rightRotate(k->parent->parent);

                }
            }
            if(k == root)
                break;
        }
        root->color = Color::BLACK;
    }

    void printHelper(Node* root, std::string indent, bool last)
    {
        if(root != null)
        {
            std::cout << indent;
            if(last)
            {
                std::cout << "R----";
                indent += "     ";
            }
            else
            {
                std::cout << "L----";
                indent += "|    ";
            }

            std::string sColor = root->color == Color::RED ? "RED": "BLACK";
            std::cout << root->data << "(" << sColor << ")" << "\n";
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RBTree()
    {
        null = new Node();
        null->color = Color::BLACK;
        null->left = nullptr;
        null->right = nullptr;
        root = null;
    }

    void preorder()
    {
        preOrderHelper(root);
    }

    void inorder()
    {
        inOrderHelper(root);
    }

    void postorder()
    {
        postOrderHelper(root);
    }

    Node* searchTree(int k)
    {
        return searchTreeHelper(root, k);
    }

    Node* minimum(Node* node)
    {
        while(node->left != null)
            node = node->left;
        return node;
    }

    Node* maximum(Node* node)
    {
        while(node->right != null)
            node = node->right;
        return node;
    }

    Node* successor(Node* x)
    {
        if(x->right != null)
            return minimum(x->right);

        Node* y = x->parent;
        while(y != null && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node* predecessor(Node* x)
    {
        if(x->left == null)
            return maximum(x->left);

        Node* y = x->parent;
        while(y != null && x == y->left)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    void leftRotate(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        if(y->left != null)
            y->left->parent = x;

        y->parent = x->parent;
        if(x->parent == nullptr)
            root = y;
        else if( x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        if(y->right != null)
            y->right->parent = x;
        
        y->parent = x->parent;
        if(x->parent == nullptr)
            root = y;
        else if(x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right =x ;
        x->parent = y;
    }

    void insert(int key)
    {
        Node* node = new Node();
        node->parent = nullptr;
        node->data = key;
        node->left = null;
        node->right = null;
        node->color = Color::RED;

        Node* y = nullptr;
        Node* x = root;

        while(x != null)
        {
            y = x;
            if(node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if(y == nullptr)
            root = node;
        else if(node->data < y->data)
            y->left = node;
        else
            y->right = node;

        if(node->parent == nullptr)
        {
            node->color = Color::BLACK;
            return;
        }

        if(node->parent->parent == nullptr)
            return;

        fixInsert(node);
    }

    Node* getRoot()
    {
        return root;
    }

    void deleteNode(int data)
    {
        deleteNodeHelper(root, data);
    }



    void prettyPrint()
    {
        if(root)
            printHelper(root, "", true);
    }
};

void RBTreeSort(const std::vector<int>& items)
{
    RBTree tree;
    for(const auto& item: items)
        tree.insert(item);
  
    tree.prettyPrint();
}

int main()
{
    std::vector<int> items {8, 18, 5, 15, 17, 25, 80, 40, 11, 80};
    RBTreeSort(items);
    return 0;
}
