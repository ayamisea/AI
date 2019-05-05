#include"tree.h"
void Tree::addChild(Node& parent,Node& child)
{
    parent.childArray.push_back(child);
    parent.childArray.back().parenet=&parent;

}

Node Tree::getRandomChildNode(const Node &n)const
{
    int noOfPossibleMoves = n.childArray.size();
    srand(time(NULL));
    int selectRandom = rand()%noOfPossibleMoves;
    return n.childArray[selectRandom];
}
Node Tree::getChildWithMaxScore(const Node &n)const
{
    Node maxNode;
    int vc=0;
    for(auto const& node: n.childArray)
     {
         if(node.state.getVisitCount()>=vc)
         {
             vc=node.state.getVisitCount();
             maxNode = node;
         }
     }
     return maxNode;
}
