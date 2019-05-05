#include"state.h"
#ifndef TREE_H_
#define TREE_H_


struct Node
{
    int id;
    State state;
    Node *parenet;
    std::vector<Node> childArray;
};
class Tree
{
public:

    Tree(){};
    ~Tree(){};
    Node root;
    Tree(const Node& r){root=r;}
    void setRoot(const Node& r) { root = r; }
    Node getRoot()const{return root;}
    void addChild(Node& parent, Node& child);


    //Deal with Node
    Node getRandomChildNode(const Node &n) const ;
    Node getChildWithMaxScore(const Node &n) const ;

private:

};

#endif // TREE_H_
