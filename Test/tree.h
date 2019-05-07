#include"state.h"
#ifndef TREE_H_
#define TREE_H_


struct Node
{
    State state;
    Node *parenet;
    std::vector<Node*> childArray ;
};
class Tree
{
public:

    Tree(){};
    ~Tree(){};
    Node root;
    Tree(const Node& r){root=r;}
    void setRoot(const Node* r) { root = *r; }
    Node& getRoot(){return root;}
    void addChild(Node& parent, Node& child);


    //Deal with Node
    Node* getRandomChildNode(Node* n) const ;
    Node* getChildWithMaxScore(Node& n)  ;

private:

};

#endif // TREE_H_
