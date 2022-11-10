#include <iostream> 
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <stack>
#include <algorithm>

using namespace std;

//using VecInt = vector<int>;
//using VecChar = vector<char>;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

  bool isValidBST(TreeNode* root) {
        
    
    stack<TreeNode*> q1;
    vector<int> vec;
    
    if (!root) return false;
    
    q1.push(root);
    
    while(!q1.empty()) {
        
        auto cn = q1.top();
        q1.pop();
        cout << cn->val << endl;
        
        if (cn->left) {
            q1.push(cn);
            q1.push(cn->left);
            cn->left = nullptr;
            
        }
        else {
            vec.push_back(cn->val);
            if (cn->right) {
                q1.push(cn->right);
                cn->right = nullptr;
            }
        }
        
    }
    
    if(is_sorted(vec.begin(), vec.end()) || equal(vec.begin(), vec.end()))
        return true;
    else
        return false;
}

TreeNode* createTree(int a[], int n)
{
    if (n<=0) return NULL;

    TreeNode **tree = new TreeNode*[n];

    for(int i=0; i<n; i++) {
        if (a[i]==0 ){
            tree[i] = NULL;
            continue;
        }
        tree[i] = new TreeNode(a[i]);
    }
    int pos=1;

    for(int i=0; i<n && pos<n; i++) {
        if (tree[i]) {
            tree[i]->left = tree[pos++];
            if (pos<n) {
                tree[i]->right = tree[pos++];
            }
        }
    }
    return tree[0];
}


int main()
{
    cout << isValidBST(NULL) << endl;

    //int a[]={1,1};
    int a[]={2,2,2};
    cout << isValidBST(createTree(a, sizeof(a)/sizeof(int))) << endl;
    
    int b[]={4,2,6,1,7,5,7};
    cout << isValidBST(createTree(b, sizeof(b)/sizeof(int))) << endl;

    return 0;
}