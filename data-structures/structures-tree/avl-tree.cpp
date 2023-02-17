#include <iostream>


struct node {

    int32_t key;
    uint8_t subtree_height;

    node* left_subtree;
    node* right_subtree;

    node(int _key) {
        key             = _key;
        subtree_height  = 0;
        left_subtree    = nullptr;
        right_subtree   = nullptr;
    }

};


class AVLTree {
    
    public:
        node* root;

    public:
        AVLTree() {
            root = nullptr;
        }

    private:
        uint8_t subtree_height(node* subtree_root) {
            if (subtree_root != nullptr) {
                return subtree_root->subtree_height;
            }
            return 0;
        }

        uint8_t balance_factor(node* subtree_root) {
            return (
                subtree_height(subtree_root->right_subtree) -
                subtree_height(subtree_root->left_subtree)
            );
        }

        void adjust_height(node* subtree_root) {
            subtree_root->subtree_height = 1 + std::max(
                subtree_height(subtree_root->right_subtree),
                subtree_height(subtree_root->left_subtree)
            );
        }

        node* small_right_rotate(node* rotations_node) {
            
            node* left_child = rotations_node->left_subtree;
            rotations_node->left_subtree = left_child->right_subtree;
            left_child->right_subtree = rotations_node;
            
            adjust_height(rotations_node);
            adjust_height(left_child);
            
            return left_child;
        }

        node* small_left_rotate(node* rotations_node) {

            node* right_child = rotations_node->right_subtree;
            rotations_node->right_subtree = right_child->left_subtree;
            right_child->left_subtree = rotations_node;

            adjust_height(rotations_node);
            adjust_height(right_child);

            return right_child;
        }

        node* balance_node(node* balanced_node) {

            adjust_height(balanced_node);

            if (balance_factor(balanced_node) == 2) {
                if (balance_factor(balanced_node->right_subtree) < 0) {
                    balanced_node->right_subtree = 
                        small_right_rotate(balanced_node->right_subtree);
                }
                return small_left_rotate(balanced_node);
            }
            if (balance_factor(balanced_node) == -2) {
                if (balance_factor(balanced_node->left_subtree) > 0) {
                    balanced_node->left_subtree = 
                        small_left_rotate(balanced_node->left_subtree);
                }
                return small_right_rotate(balanced_node);
            }

            return balanced_node;
        }

        node* insert_helper(int _key, node* subtree_root) {
            
            if (subtree_root == nullptr) {
                subtree_root = new node(_key);
                return subtree_root;
            }

            if (_key < subtree_root->key) {
                subtree_root->left_subtree = 
                    insert_helper(_key, subtree_root->left_subtree);
            }
            else {
                subtree_root->right_subtree = 
                    insert_helper(_key, subtree_root->right_subtree);
            }

            return balance_node(subtree_root);
        }

    public:
        void insert(int _key) {
            root = insert_helper(_key, root);
        }

        void print(node* this_node) {
            if (this_node == nullptr) {
                return;
            }
            print(this_node->left_subtree);
            std::cout << this_node->key << ' ';
            print(this_node->right_subtree);
        }
};


int main() {

    AVLTree avl = AVLTree();

    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        avl.insert(tmp);
    }
    avl.print(avl.root);

    return 0;
}

