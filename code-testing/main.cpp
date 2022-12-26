#include <iostream> 
#include <vector>

#include "spdlog/spdlog.h"


using namespace std;


int main()
{
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);

  cout << "Hello World" << endl;

    return 0;
}