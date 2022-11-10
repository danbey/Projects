#include <iostream> 
#include <array>
#include <algorithm>
#include <string>
#include <sstream>
#include <random>
#include <functional>

using namespace std;

//using VecInt = vector<int>;
//using VecChar = vector<char>;


int main()
{ 

   random_device rd;

   array<int , std::mt19937::state_size> seed_data {};
   generate(begin(seed_data), end(seed_data), ref(rd));

   seed_seq seq(begin(seed_data), end(seed_data));

   auto eng = mt19937{seq};

  auto dist = uniform_real_distribution<>{0, 100};
   cout << round(dist(eng)) << endl;
   cout << round(dist(eng)) << endl;
   cout << dist(eng) << endl;
   cout << dist(eng) << endl;
   

   


   return 0;

}