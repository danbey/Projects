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

/* c++11
class Singleton {
  public:
  static const Singleton& get_instanse() {
    static Singleton sg;

    return sg;
  }

  private:
  Singleton(){}
  Singleton(const Singleton &other) = delete;
  Singleton& operator=(const Singleton &other) = delete;

};
*/

/* c++98
class Singleton {
  public:
  static const Singleton* get_instanse() {

    if (sg == NULL)
    //todo lock_guard(mutex)
      sg = new Singleton();
    
    return sg;
  }

  private:
  static Singleton * sg;
  Singleton(){}


};

 Singleton * Singleton::sg = NULL;
*/
int main()
{ 

  //auto x = Singleton::get_instanse();

  
 //  const Singleton* sing = Singleton::get_instanse();
  
  
   string s("DAN debug aaa");

   cout << s << endl;


   return 0;

}