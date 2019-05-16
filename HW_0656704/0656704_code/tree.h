#include"state.h"
#ifndef TREE_H_
#define TREE_H_
struct Node
{
    State state;
    Node *parenet=NULL;
    std::vector<Node*> childArray ;
};
class Tree
{
public:

    Tree(){};
    ~Tree(){};
    Tree(const Node& r){root=r;}
    Node& getRoot(){return root;}
    void addChild(Node& parent, Node& child);

    Node* getRandomChildNode(Node* n);
    Node* getChildWithMaxScore(Node& n)  ;
private:
    Node root;
};

#endif // TREE_H_
