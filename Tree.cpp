#include "Tree.h"

// O(n)
MyAVLTree::~MyAVLTree(){
    // Traverse the tree inorder and delete at every node
    // travel down the left node first, and then when you reach a nullptr delete the current node
    root = postorderDestructor(root);
}

// O(n)
MyAVLTree::Node* MyAVLTree::postorderDestructor(Node* currentNode){
    // Traverse postorder and delete
    if (currentNode == nullptr){
        return currentNode;
    }
    else{
        postorderDestructor(currentNode->left);
        postorderDestructor(currentNode->right);
        delete currentNode;
        currentNode = nullptr;
    }
    return currentNode;
}

// O(log(N))
// Insert a new node into the tree, returns successful if successful, and unsuccessful otherwise
void MyAVLTree::insert(std::string name, unsigned int ID){

    // Update root
    root = insertHelper(root, ID, name);
}

// O(log(n))
// Recursive function to find node that will be updated with new child node
MyAVLTree::Node* MyAVLTree::insertHelper(Node* currentNode, unsigned int ID, std::string& name){ 
    if (currentNode == nullptr){  // If the end of the tree is reached then return a new node
        std::cout << "successful\n";
        return new Node(name, ID);
    }

    // A nullptr is returned if a duplicate is found
    if (ID == currentNode->studentID) {
        std::cout << "unsuccessful\n";
        return nullptr;
    }
    else if(ID < currentNode->studentID)                                    // Traverse down the left subtree and assign the new node to left
        currentNode->left = insertHelper(currentNode->left, ID, name);
    else
        currentNode->right = insertHelper(currentNode->right, ID, name);    // Traverse down the right subtree and assign the new node to right
  
    return balanceTree(currentNode);         // Will return new nodes or the unchanged node depending on whether tree is balanced
}

// O(1)
void MyAVLTree::UpdateHeight(Node* currentNode) {
    if (currentNode != nullptr) {                       // If the current Node is empty don't update the height
        currentNode->height = 1 + std::max(getHeight(currentNode->left), getHeight(currentNode->right));
    }
}

// O(1)
// Balance tree and update height values accordingly
MyAVLTree::Node* MyAVLTree::balanceTree(Node* currentNode)
{
    // Update height of ancestors
    UpdateHeight(currentNode);
    
    // Get the balance factor of current Node
    int parentBfactor = getBalance(currentNode);
    int childBfactor;
    
    // Determine if the tree is left or right heavy
    if (parentBfactor < -1) {                           // Right heavy tree
        childBfactor = getBalance(currentNode->right);
        if (childBfactor > 0) {                         // Right Left case
            currentNode->right = rotateRight(currentNode->right);
            return rotateLeft(currentNode);
        }
        else if (childBfactor < 0) {                   // Right Right case
            return rotateLeft(currentNode);
        }
    }
    else if (parentBfactor > 1) {                       // Left heavy tree
        childBfactor = getBalance(currentNode->left);
        if (childBfactor < 0) {                        // Left Right case
           currentNode->left = rotateLeft(currentNode->left);
           return rotateRight(currentNode);
        }
        else if (childBfactor > 0) {
            return rotateRight(currentNode);                   // Left left case
        }
    }

    return currentNode;
}

// O(1)
int MyAVLTree::getBalance(Node* currentNode) {
    return getHeight(currentNode->left) - getHeight(currentNode->right);
}

// Search for a name, if multiple names are the same output the student ID on individual lines
void MyAVLTree::search(std::string name){
    // Traverse in preOrder and print out any nodes with the same student name
    std::queue<unsigned int> IDs;
    searchNameHelper(this->root, name, IDs);

    if (IDs.empty()){           // Return unsuccessful if name was not found
        std::cout << "unsuccessful\n";
        return;
    }

    // Output the IDs in preorder
    while (!IDs.empty()){
        std::cout << IDs.front() << std::endl;
        IDs.pop();
    }

}

// Worst Case O(n) 
// traverses the tree in preorder and compares the names, if the name is same then add ID to the queue
void MyAVLTree::searchNameHelper(Node* currentNode, std::string& name, std::queue<unsigned int>& IDs){
    // Preorder traversal
    if (currentNode == nullptr){        // If the end of a sub tree has been reached return to the previous node
        return;
    }
    else{
        if (currentNode->studentName == name){
            IDs.push(currentNode->studentID);
        }
        searchNameHelper(currentNode->left, name, IDs);     // Recurse down the left subyree
        searchNameHelper(currentNode->right, name, IDs);    // Recurse down the right subtree
    }
}

// O(log(N))
// Search for ID, if the ID is found output the name, otherwise return unsuccessful
void MyAVLTree::search(unsigned int ID){
    // Traverse in preOrder and print out any nodes with the same student name
    Node* foundNode = searchIDHelper(root, ID);
    if (foundNode == nullptr){
        std::cout << "unsuccessful\n";
    }
    else {
        std::cout << foundNode->studentName << std::endl;
    }
    return;
}

// Worst Case O(logn)
// Search for ID and return if the node contains the same ID
MyAVLTree::Node* MyAVLTree::searchIDHelper(Node* currentNode, unsigned int ID){
    if (currentNode == nullptr || currentNode->studentID == ID){     // End of subtree has been reached or the ID has been found
        return currentNode;
    }
    else if (ID < currentNode->studentID){                           // traverse down the left subtree
        return searchIDHelper(currentNode->left, ID);
    }
    else{
        return searchIDHelper(currentNode->right, ID);                  // Traverse down the right subtree
    }
}

// Search for the ID and remove if found
void MyAVLTree::remove(unsigned int ID){

    if (!removeHelper(root, root, ID)){
        std::cout << "unsuccessful\n";
    }
    else {
        std::cout << "successful\n";
    }

    return;
}

// O(log(N)) to search for ID
// Remove parent node to node that is being deleted
 bool MyAVLTree::removeHelper(Node* currentNode, Node* parentNode, unsigned int ID){
    if (currentNode == nullptr)                                         // ID not found
        return false;
    if (ID < currentNode->studentID)                                    // Traverse down the left subtree                
        return removeHelper(currentNode->left, currentNode, ID);
    else if(ID > parentNode->studentID)                                 // Traverse down the right subtree
        return removeHelper(currentNode->right, currentNode, ID);
    else{                                                               // Node has been found and delete the node
        deleteNode(currentNode, parentNode);
        return true;
    }
}

// O(log(n))
// Delete the currentNode, use the ParentNode in one or no child cases
void MyAVLTree::deleteNode(Node* currentNode, Node* parentNode){
    
    // O(1)
    // No children
    if (currentNode->left == nullptr && currentNode->right == nullptr){
        if (currentNode->studentID < parentNode->studentID)
            parentNode->left = nullptr;
        else if (currentNode->studentID > parentNode->studentID)
            parentNode->right = nullptr;
        else    // Root node case parent = current
            parentNode = nullptr;

        delete currentNode;
        currentNode = nullptr;
    }
    // Two Child
    else if (currentNode->left != nullptr && currentNode->right != nullptr){ 
        // Find inorder successor and then call delete one or delete two child case
        deleteInorderSuccessor(currentNode->right, currentNode, currentNode);
    }

    // O(1)
    // One Child
    else{
        if(currentNode->studentID < parentNode->studentID){ // General case
            if(currentNode->left != nullptr)
                parentNode->left = currentNode->left;
            else
                parentNode->left = currentNode->right;
        }   
        else if (currentNode->studentID > parentNode->studentID){
            if(currentNode->left != nullptr)
                parentNode->right = currentNode->left;
            else
                parentNode->right = currentNode->right;
        }   
        else{ // Root node case current == parent
            if (currentNode->left != nullptr)
                root = currentNode->left;
            else
                root = currentNode->right;
        }
        delete currentNode;
        currentNode = nullptr;
    }

    // O(1)
    UpdateHeight(currentNode);
    UpdateHeight(parentNode);
}

// O(log(n))
// Find the inordersuccessor and delete the node
void MyAVLTree::deleteInorderSuccessor(Node* inorderSuccessor, Node* parentNode, Node* targetNode){
    if (inorderSuccessor->left == nullptr){
        // Replace target node with the inordersuccessor values and then delete inordersuccessor
        unsigned int tempID = inorderSuccessor->studentID;
        std::string tempName = inorderSuccessor->studentName;
        deleteNode(inorderSuccessor, parentNode);
        targetNode->studentID = tempID;
        targetNode->studentName = tempName;
    }
    else{
        // Traverse until the inordersuccessor is found
        deleteInorderSuccessor(inorderSuccessor->left, inorderSuccessor, targetNode);
    }
}

// O(n)
// Traverse inorder and print the names
void MyAVLTree::printInorder(){
    std::queue<std::string> names;
    printInorderHelper(this->root, names);

    while(!names.empty()){
        if (names.size() == 1)
            break;
        
        std::cout << names.front() << ", ";
        names.pop();
    }
    std::cout << names.front() << std::endl;
    names.pop();
}

// O(n)
// Uses recursion to traverse inorder and returns a queue with all of the names
void MyAVLTree::printInorderHelper(Node* currentNode, std::queue<std::string>& names){
    if (currentNode == nullptr){
        return;
    }
    else{
        printInorderHelper(currentNode->left, names);
        names.push(currentNode->studentName);
        printInorderHelper(currentNode->right, names);
    }
}

// O(n)
// Print all names in preorder 
void MyAVLTree::printPreorder(){
    std::queue<std::string> names;
    printPreorderHelper(this->root, names);

    while(!names.empty()){
        if (names.size() == 1)
            break;
        
        std::cout << names.front() << ", ";
        names.pop();
    }
    std::cout << names.front() << std::endl;
    names.pop();
}

// O(n)
// Traverse preorder and returns all names in a queue
void MyAVLTree::printPreorderHelper(Node* currentNode, std::queue<std::string>& names){
    if (currentNode == nullptr){
    }
    else{
        names.push(currentNode->studentName);
        printPreorderHelper(currentNode->left, names);
        printPreorderHelper(currentNode->right, names);
    }
}

// O(n)
// Print postorder names
void MyAVLTree::printPostorder(){
    std::queue<std::string> names;
    printPostorderHelper(this->root, names);

    while(!names.empty()){
        if (names.size() == 1)
            break;
        
        std::cout << names.front() << ", ";
        names.pop();
    }
    std::cout << names.front() << std::endl;
    names.pop();
}

// O(n)
// Traverse postorder and returns a queue of names
void MyAVLTree::printPostorderHelper(Node* currentNode, std::queue<std::string>& names){
    if (currentNode == nullptr){}
    else{
        printPostorderHelper(currentNode->left, names);
        printPostorderHelper(currentNode->right, names);
        names.push(currentNode->studentName);
    }
}

// O(1)
// Calculate and print the height of the tree
void MyAVLTree::printLevelCount(){
    unsigned int height = getHeight(root);
    std::cout << height << std::endl;
}


// O(1)
unsigned int MyAVLTree::getHeight(Node* currentNode){
    if (currentNode == nullptr){        // Return 0 if there are no nodes
        return 0;
    }

    return currentNode->height;
}

// O(1)
// The source for the implementations of rotation comes from the balancing trees slides
MyAVLTree::Node* MyAVLTree::rotateLeft(Node* currentNode)
{
    Node* newParent = currentNode->right;
    Node* grandchild = currentNode->right->left;

    newParent->left = currentNode;
    currentNode->right = grandchild;

    // All are O(1)
    UpdateHeight(grandchild);
    UpdateHeight(currentNode);
    UpdateHeight(newParent);

    return newParent;
}

// O(1)
MyAVLTree::Node* MyAVLTree::rotateRight(Node* currentNode) {
    Node* newParent = currentNode->left;
    Node* grandchild = currentNode->left->right;

    newParent->right = currentNode;
    currentNode->left = grandchild;

    UpdateHeight(grandchild);
    UpdateHeight(currentNode);
    UpdateHeight(newParent);

    return newParent;
}

// O(n)
// Traverse inorder and find the nth node to delete
void MyAVLTree::removeInorder(int n){
    // Recursively traverse the tree keeping a count of the nodes passed, get the node to be deleted and the parent node;
    if (removeInorderHelper(root, root, n) == 0)
        std::cout << "successful\n";
    else
        std::cout << "unsuccessful\n";
}

// O(n + log(n)) => O(n)
int MyAVLTree::removeInorderHelper(Node* currentNode, Node* parentNode, int& n){
    // Check if end of the tree reached

    if (currentNode == nullptr){}
    else {
        removeInorderHelper(currentNode->left, currentNode, n);
        if (n == 0) {
            deleteNode(currentNode, parentNode);
            return n;
        }
        n--;
        removeInorderHelper(currentNode->right, currentNode, n);
    }
    return n;
}