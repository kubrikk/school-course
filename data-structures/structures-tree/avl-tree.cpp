#include <iostream>


struct node {

    int64_t key;
    uint8_t subtree_height;

    node* left_subtree;
    node* right_subtree;

    node(int64_t _key) {
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
        /* Метод нахождения высоты дерева с корнем в вершине `subtree_root`.
         *
         * Так как для каждой вершины (node) мы храним высоту дерева, у
         * которого в качестве корня берётся данная вершина, то нам достаточно
         * вернуть значение соответсвующего поля.
         */
        uint8_t subtree_height(node* subtree_root) {
            if (subtree_root != nullptr) {
                return subtree_root->subtree_height;
            }
            // если вершины не существует -- возвращаем в качестве высоты 0
            return 0;
        }

        /* Метод, возвращающий фактор баланса для вершины `subtree_root`.
         *
         * Классически рассамтрвиаем разницу между высотой правого поддерева
         * и левого поддерева дерева с вершиной `subtree_root`.
         */
        uint8_t balance_factor(node* subtree_root) {
            return (
                subtree_height(subtree_root->right_subtree) -
                subtree_height(subtree_root->left_subtree)
            );
        }

        /* Метод для корректировки высоты дерева с вершиной `subtree_root`.
         * 
         * Устанавливает актуальную высоту для дерева с корнем `subtree_root`.
         */
        void adjust_height(node* subtree_root) {
            subtree_root->subtree_height = 1 + std::max(
                subtree_height(subtree_root->right_subtree),
                subtree_height(subtree_root->left_subtree)
            );
        }

        /* Малое правое вращение.
         */
        node* small_right_rotate(node* rotations_node) {
            
            node* left_child = rotations_node->left_subtree;
            rotations_node->left_subtree = left_child->right_subtree;
            left_child->right_subtree = rotations_node;
            
            adjust_height(rotations_node);
            adjust_height(left_child);
            
            return left_child;
        }

        /* Малое левое вращение.
         */
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

        node* insert_helper(int64_t _key, node* subtree_root) {
            
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

        node* find_min(node* subtree_root) {
            if (subtree_root->left_subtree != nullptr) {
                return find_min(subtree_root->left_subtree);
            }
            return subtree_root;
        }

        node* remove_min(node* subtree_root) {
            if (subtree_root->left_subtree == nullptr) {
                return subtree_root->right_subtree;
            }
            subtree_root->left_subtree = remove_min(subtree_root->left_subtree);
            return balance_node(subtree_root);
        }

        node* erase_helper(int64_t _key, node* subtree_root) {
            
            if (subtree_root == nullptr) {
                return nullptr;
            }

            if (_key < subtree_root->key) {
                subtree_root->left_subtree = 
                    erase_helper(_key, subtree_root->left_subtree);
            }
            else if (_key > subtree_root->key) {
                subtree_root->right_subtree = 
                    erase_helper(_key, subtree_root->right_subtree);
            } 
            else {

                if (subtree_root->left_subtree == nullptr) {
                    return subtree_root->right_subtree;
                }

                node* new_node = find_min(subtree_root->right_subtree);
                new_node->left_subtree = subtree_root->left_subtree;
                new_node->right_subtree = remove_min(subtree_root->right_subtree);

                subtree_root = new_node;

            }

            return balance_node(subtree_root);
        }

    public:
        void insert(int64_t _key) {
            root = insert_helper(_key, root);
        }

        void erase(int64_t _key) {
            root = erase_helper(_key, root);
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
        avl.print(avl.root);
    }

    for (int i = 0; i < n; i++) {
        int tmp;
        std::cin >> tmp;
        avl.erase(tmp);
        avl.print(avl.root);
    }

    return 0;
}

