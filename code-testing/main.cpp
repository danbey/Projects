#include <iostream> 
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <stack>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <deque>


using namespace std;



using VecInt = vector<int>;
//using VecChar = vector<char>;

 
void findMissingRanges(VecInt &vec, int lower, int upper) {

    vector<string> res;
    stringstream  ss;
    //TODO is vec size = 1 
    if (!vec.size()) {
        ss << lower << "->" << upper;
        cout << ss.str();
        return ;
    }

    
    if (lower < vec[0]) {
        ss << lower << "->" << (vec[0]-1);
        res.emplace_back(ss.str());
    }

    for (auto i=0; i < vec.size()-1; i++) {
        auto c_gap = vec[i+1] - vec[i];
        if (c_gap > 1) {
            
            ss.str("");
            if (c_gap > 2) {
                ss << (vec[i]+1);
                ss <<  "->" ;
                ss << (vec[i+1]-1);
            } else
                ss << (vec[i]+1);
            
            res.emplace_back(ss.str());

        }
    }

    if (vec[vec.size()-1] < upper) {
        ss.str("");
        ss << (vec[vec.size()-1]+1) << "->" << upper;
        res.emplace_back(ss.str());
    }

    for (auto &i:res)
        cout << i << ',';
    
}

int main()
{
    
   //VecInt vec = {0,1,3,50,75};
   VecInt vec = {0,90};
  
    findMissingRanges(vec, 0, 99);

    return 0;
}