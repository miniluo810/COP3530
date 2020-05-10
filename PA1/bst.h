#pragma once
#include <vector>
#include <exception>
#include <queue>

namespace cop3530 {

    template<typename Key, typename T>
    class bst {
        struct node {
            Key key;// key
            T value;// value
            node *right;// right child
            node *left;// left child
            int balance;
            node() {
                left = nullptr;
                right = nullptr;
                balance=0;
            }

            node(Key k, T t) {
                key = k;
                value = t;
                left = nullptr;
                right = nullptr;
                balance=0;
            }
        };

        node *root;// root of tree
        unsigned int nodeCount=0;

    public:
        bst();

        ~bst();

        void findLeaf(const Key &key, node *&tempNode, const T &t);

        void insert(const Key &key, const T &t);

        node * eraseHelper(const Key &key, node* toDelete);

        void erase(const Key &key);

        T &at(const Key &key);

        bool contains(const Key &key) const;

        bool empty() const;

        size_t size() const;

        void recursiveIn(node *&root, std::vector<std::pair<Key, T>> &inorder);

        void recursivePre(node *&root, std::vector<std::pair<Key, T>> &preorder);

        std::vector<std::pair<Key, T>> inorder_contents();

        std::vector<std::pair<Key, T>> preorder_contents();

        node *recursiveContains(const Key &key, node *tempNode) const;

        node* left_right_rotate(node* &curr);

        node* right_left_rotate(node* &curr);

        node* right_right_rotate(node* &curr);

        node* left_left_rotate(node* &curr);

        void balanceNode(node* &curr);

        int maxHeight(node* curr) const;

        int getBalance(node* curr) const;


    };

    template<typename Key, typename T>
    bst<Key, T>::bst() {
        root = nullptr;
        nodeCount = 0;
    }

    template<typename Key, typename T>
    bst<Key, T>::~bst() {
        //deleteTree(root);
    }

    template<typename Key, typename T>
    void bst<Key, T>::findLeaf(const Key &key, node *&tempNode, const T &t) {
        if ((tempNode->left == nullptr&&key<tempNode->key) ||(tempNode->right == nullptr&&key>tempNode->key)||tempNode->key==key) {//base case

            if (tempNode->key > key) {
                node *newNode = new node(key, t);
                tempNode->left = newNode;
                nodeCount++;
            } else if (tempNode->key < key) {
                node *newNode = new node(key, t);
                tempNode->right = newNode;
                nodeCount++;
            } else {
                tempNode->value = t;
            }
        } else if (tempNode->key > key) {//recursive case if it's greater
            findLeaf(key, tempNode->left, t);
            tempNode->balance++;//add one if to the left
            balanceNode(tempNode);

        } else if (tempNode->key < key) {//recursive case if it's less than
            findLeaf(key, tempNode->right, t);
            tempNode->balance--;//subtract one if to the right
            balanceNode(tempNode);
        }


    }

    template<typename Key, typename T>
    void bst<Key, T>::insert(const Key &key, const T &t) {
        if (nodeCount == 0) {
            root = new node(key, t);
            nodeCount++;
        } else {
            findLeaf(key, root, t);
        }

    }

    template<typename Key, typename T>
    void bst<Key, T>::erase(const Key &key) {
        if(root== nullptr){
            throw std::out_of_range("Not found");
        }else if(!contains(key)){
            throw std::out_of_range("Not found");
        }else{
            root=eraseHelper(key,root);
            nodeCount--;
        }


    }

    template<typename Key, typename T>
    T &bst<Key, T>::at(const Key &key) {
        if(root==nullptr){
            throw std::out_of_range("Error: not found");
        }
        if(!contains(key)){
            throw std::out_of_range("Error: not found");
        }else{
            return recursiveContains(key,root)->value;
        }


    }

    template<typename Key, typename T>
    typename bst<Key, T>::node *bst<Key, T>::recursiveContains(const Key &key, node *tempNode) const{
        if(tempNode->left== nullptr&&tempNode->right== nullptr){
            return tempNode;
        }
        if (tempNode->key > key&&tempNode->left!= nullptr) {//recursive case if it's greater
            return recursiveContains(key,tempNode->left);
        } else if (tempNode->key < key&&tempNode->right!= nullptr) {//recursive case if it's less than
            return recursiveContains(key,tempNode->right);
        } else{
            return tempNode;
        }


    }

    template<typename Key, typename T>
    bool bst<Key, T>::contains(const Key &key) const {
        if(root== nullptr){
            return false;
        }else {
            return recursiveContains(key, root)->key == key;
        }
    }

    template<typename Key, typename T>
    bool bst<Key, T>::empty() const {
        return root == nullptr;
    }

    template<typename Key, typename T>
    size_t bst<Key, T>::size() const {
        return nodeCount;
    }

    template<typename Key, typename T>
    void bst<Key, T>::recursiveIn(node *&root, std::vector<std::pair<Key, T>> &inorder) {
        if (root == nullptr) {
            return;
        }
        recursiveIn(root->left, inorder);
        inorder.push_back(std::make_pair(root->key, root->value));
        recursiveIn(root->right, inorder);

    }

    template<typename Key, typename T>
    void bst<Key, T>::recursivePre(node *&root, std::vector<std::pair<Key, T>> &preorder) {
        if (root == nullptr) {
            return;
        }
        preorder.push_back(std::make_pair(root->key, root->value));
        recursivePre(root->left, preorder);
        recursivePre(root->right, preorder);

    }

    template<typename Key, typename T>
    std::vector<std::pair<Key, T>> bst<Key, T>::inorder_contents() {
        std::vector<std::pair<Key, T>> contents;
        recursiveIn(root, contents);
        return contents;
    }

    template<typename Key, typename T>
    std::vector<std::pair<Key, T>> bst<Key, T>::preorder_contents() {
        std::vector<std::pair<Key, T>> contents;
        recursivePre(root, contents);
        return contents;
    }

    template<typename Key, typename T>
    typename bst<Key, T>::node *bst<Key, T>::eraseHelper(const Key &key, node* toDelete) {
        if (toDelete->key > key) {
            toDelete->left = eraseHelper(key, toDelete->left);
            balanceNode(toDelete);
        } else if (toDelete->key < key) {
            toDelete->right = eraseHelper(key, toDelete->right);
            balanceNode(toDelete);
        } else {//base case
            if (toDelete->right == nullptr && toDelete->left == nullptr) {
                delete toDelete;
                return nullptr;
            } else if (toDelete->right != nullptr && toDelete->left != nullptr) {//two children
                node *temp = toDelete->left;
                while (temp->right != nullptr) {
                    temp = temp->right;
                }
                toDelete->key = temp->key;
                toDelete->value = temp->value;
                toDelete->left = eraseHelper(temp->key, toDelete->left);

            } else {//one child
                if (toDelete->left != nullptr) {//only left child
                    return toDelete->left;
                } else {
                    return toDelete->right;
                }
            }


        }

        return toDelete;
    }

    template<typename Key, typename T>
    typename bst<Key, T>::node *bst<Key, T>::left_left_rotate(bst::node * &curr) {
        node* temp=curr->right;
        node* temp2=curr->right->left;
        temp->left=curr;
        curr->right=temp2;
        return temp;

    }
    template<typename Key, typename T>
    typename bst<Key, T>::node *bst<Key, T>::left_right_rotate(bst::node * &curr) {
        curr->left=left_left_rotate(curr->left);
        return right_right_rotate(curr);
    }
    template<typename Key, typename T>
    typename bst<Key, T>::node *bst<Key, T>::right_left_rotate(bst::node * &curr) {
        curr->right=right_right_rotate(curr->right);
        return left_left_rotate(curr);

    }
    template<typename Key, typename T>
    typename bst<Key, T>::node *bst<Key, T>::right_right_rotate(bst::node * &curr) {
        node* temp=curr->left;
        node* temp2=curr->left->right;
        temp->right=curr;
        curr->left=temp2;
        return temp;

    }


    template<typename Key, typename T>
    int bst<Key, T>::maxHeight(bst::node *curr) const {
        if(curr== nullptr){
            return 0;
        }
        return std::max(maxHeight(curr->left),maxHeight(curr->right))+1;

    }

    template<typename Key, typename T>
    int bst<Key, T>::getBalance(bst::node *curr) const {
        int diff=0;
        diff=maxHeight(curr->left)-maxHeight(curr->right);
        return diff;

    }

    template<typename Key, typename T>
    void bst<Key, T>::balanceNode(bst::node *&curr) {
        if(getBalance(curr)>1){//left heavy
            if(getBalance(curr->left)<0){//left right rotation
                curr=left_right_rotate(curr);
            }else{//right rotation
                curr=right_right_rotate(curr);
            }
        }else if(getBalance(curr)<-1){//right heavy
            if(getBalance(curr->right)<0){//left rotation
                curr=left_left_rotate(curr);
            }else{//right left rotation
                curr=right_left_rotate(curr);
            }
        }

    }


}