#include <iostream>
#include <stack>

class Node
{
public:
    int m_val;
    Node *m_pletf;
    Node *m_pright;
    
    Node(int val):m_val(val), m_pletf(NULL) ,m_pright(NULL) {}     
};


void PrintPreorderRec(Node *root)
{
    std::stack<Node*> dp;
    dp.push(root);

    while(!dp.empty()) {
        Node *h = dp.top();
        if (!(h->m_pletf) && !(h->m_pright)) {
            std::cout << "val:" << h->m_val << std::endl;
            dp.pop();
        } else  {
            if (h->m_pright) {
                dp.push(h->m_pright);
                h->m_pright = NULL;
            }
            if (h->m_pletf) {
                dp.push(h->m_pletf);
                h->m_pletf = NULL;
            }
        }
    }
};




int main()
{
  Node n12(12);
  Node n5(5);
  Node n8(8);
  n8.m_pletf = &n5;
  n8.m_pright = &n12;
  
  Node n3(3);
  Node n20(20);
  
  n5.m_pletf = &n3;
  n12.m_pright = &n20;
  
  
   PrintPreorderRec(&n8);
   return 0;
}