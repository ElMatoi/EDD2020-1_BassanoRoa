#include "kdTree.hpp"
#include <cstddef>
 
using namespace std;
 
class kdTree;
 
kdTree::kdTree() {
    root = NULL;
    cantidadNodos = 0;
}
 
kdTree::kdTree(const kdTree& orig) {
}
 
kdTree::~kdTree() {
    if(root != NULL){
        delete root;
    }
    root = NULL;
}
 
kdTreeNode* kdTree::getRoot(){
    return root;
}
 
void kdTree::insert(kdTreeNode* newEntry){
    if(root == NULL){
        //tree is empty
        newEntry->setLevel(true); //set the root to x-level
        newEntry->setParent(NULL); //set parent
        root = newEntry;
    }else{
        root->insertNode(newEntry, root);
    }
}
 
void kdTree::remove(kdTreeNode* entry){
    if(root == NULL)
        return;         
    else{
        root->removeNode(entry, root);
    }
}
 
kdTreeNode* kdTree::findClosestPoint(kdTreeNode* entry){
    if(root == NULL)
        return NULL;
    else{
        return(root->findClosestNode(entry));
    }
}
 
void kdTree::print(){
    if(root == NULL)
        return;
    else
        root->printNodes();
}

int kdTree::getCantidadNodos(){
    return cantidadNodos;
}

void kdTree::setCantidadNodos(int x){
    cantidadNodos = x;
}