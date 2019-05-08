#include"tree.h"
void Tree::addChild(Node& parent,Node& child)
{
    parent.childArray.push_back(&child);
    parent.childArray.back()->parenet=&parent;

}

Node* Tree::getRandomChildNode(Node* n)
{
    int noOfPossibleMoves = n->childArray.size();
    srand(time(NULL));
    int selectRandom = rand()%noOfPossibleMoves;
    return n->childArray[selectRandom];
}
Node* Tree::getChildWithMaxScore(Node& n)
{
    Node* maxNode;
    int vc=0;
    for(auto const& node: n.childArray)
     {
         if(node->state.getVisitCount()>=vc)
         {
             vc=node->state.getVisitCount();
             maxNode = node;
         }
         std::cout<<node->state.getPosition().row<<","<<node->state.getPosition().col<<" ("<<node->state.getVisitCount()<<") ";
     }
     return maxNode;
}
