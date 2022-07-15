#ifndef KDTREE_HPP
#define KDTREE_HPP
#include "kdTreeNode.hpp"
 
class kdTree {
public:
    kdTree();
    kdTree(const kdTree& orig);
    virtual ~kdTree();
 
    kdTreeNode* getRoot();
    kdTreeNode* findClosestPoint(kdTreeNode* entry);
    
    void print();
    void remove(kdTreeNode* entry);
    void insert(kdTreeNode* newEntry);
    
    
private:
     
    kdTreeNode *root;
 
};
 
#endif /* KDTREE_H */