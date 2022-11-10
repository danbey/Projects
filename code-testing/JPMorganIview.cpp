#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


void func(vector<int> &vec1, vector<int> &vec2)
{
    unordered_map<int, int> u_map1;
    for (auto &i:vec1) {
        u_map1.at(i)++;
    }
    
    unordered_map<int, int> u_map2;
    for (auto &i:vec2) {
        u_map2.at(i)++;
    }

    for (auto &i:u_map1) {
        auto m2_val = u_map1.at(i.first);
        auto num_to_print = max(i.second , m2_val);
        while(num_to_print--)
            cout << i.first;

        }
    }
}

int main(int argc, char *argv[])
{
    vector<int> vec1= {1,5,-1, -2,5,5};
    vector<int> vec2= {-2,-2,5,5, 4};

    vec1_count = {1->1, 5->3, -1 > 1, -2 -> 1}
    vec2_count = {5->2, 4 > 1, -2 -> 2}





    vector<int> res = {1, -2,-2, 5,5,5 ,-1,4}

    
    std::cout << "Hello World !!!" << std::endl;

    return 0;