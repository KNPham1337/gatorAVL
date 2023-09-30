#pragma once
#include <string>
#include <queue>
#include <iostream>

class MyAVLTree{
    private:
        struct Node{
            unsigned int studentID;
            std::string studentName;
            int height;
            Node* left;
            Node* right;

            Node(std::string name, unsigned int ID) : studentID(ID), studentName(name), left(nullptr), right(nullptr), height(1) {}

            // Check if node destructor is right
            ~Node(){
                right = left = nullptr;
            }
        };

        Node* root;

        Node* insertHelper(Node* currentNode, unsigned int ID, std::string& name);
        void UpdateHeight(Node* currentNode);
        Node* postorderDestructor(Node* currentNode);
        void searchNameHelper(Node* currentNode, std::string& name, std::queue<unsigned int>& IDs);
        Node* searchIDHelper(Node* currentNode, unsigned int ID);
        bool removeHelper(Node* currentNode, Node* parentNode, unsigned int ID);
        void deleteNode(Node* currentNode, Node* parentNode);
        void printInorderHelper(Node* currentNode, std::queue<std::string>& names);
        void printPreorderHelper(Node* currentNode, std::queue<std::string>& names);
        void printPostorderHelper(Node* currentNode, std::queue<std::string>& names);
        void deleteInorderSuccessor(Node* rightsubNode, Node* parentNode, Node* targetNode);
        int removeInorderHelper(Node* currentNode, Node* parentNode, int& n);

        // Rotation helpers
        unsigned int getHeight(Node* currentNode);
        Node* rotateLeft(Node* currentNode);
        Node* rotateRight(Node* currentNode);
        Node* balanceTree(Node* currentNode);
        int getBalance(Node* currentNode);

    public:
        // Done
        
        void search(std::string name);
        void search(unsigned int ID);
        void remove(unsigned int ID);
        void printInorder();
        void printPreorder();
        void printPostorder();
        void printLevelCount();
        void removeInorder(int n);
        MyAVLTree() : root(nullptr){}
        ~MyAVLTree();

        // Finish
        void insert(std::string name, unsigned int ID);
};