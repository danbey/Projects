
#include <queue>

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 } ;

 typedef struct TreeNode TreeNode_t;

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        


        std::deque<std::pair<TreeNode_t *, int>> q1 , q2, *curr_q, *other_q;
        q1.push_front({root, 0});

        int max_width = 0;


        while (!q1.empty() || !q2.empty()) {
           
            if (!q1.empty()) {
                curr_q = &q1;
                other_q = &q2;
            }
            else if (!q2.empty()) {
                curr_q = &q2;
                other_q = &q1;
            }
            int found_not_null = 0, width = 0, null_width = 0;
            
            while (!curr_q->empty())
            {
                
                TreeNode_t * lf = curr_q->front()->left;
                TreeNode_t * rt = curr_q->front()->right;

                if (lf != nullptr) {
                    other_q->push_back(lf);
                    found_not_null = 1;
                    width += null_width;
                    null_width = 0;
                    width++;
                }
                else if (found_not_null) {
                    null_width++;
                }
                
                if (rt != nullptr) {
                    other_q->push_back(rt);
                    found_not_null = 1;
                    width += null_width;
                    null_width = 0;
                    width++;
                }
                else if (found_not_null) {
                    null_width++;
                }
                curr_q->pop_front();
            }

            if (width > max_width)
                max_width = width;
        }

        return max_width;
    }
        

        return 0;
    }
};




int main()
{
  struct TreeNode n12(12);
  TreeNode_t n5(5);
  TreeNode_t n8(8);
  n8.left = &n5;
  n8.right = &n12;
  
  TreeNode_t n3(3);
  TreeNode_t n20(20);
  
  n5.left = &n3;
  n12.right = &n20;

   return 0;
}