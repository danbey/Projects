#include <iostream> 
#include <deque>
#include <string>
#include <sstream>
#include <fstream>

void countStuff(std::ifstream &file , int &c, int &w , int &l)
{
    char cur = '\0';

    char last = '\0';

    c = w = l = 0;

    while (file.get(cur))
    {
        if (cur == '\n' || (cur == '\f' && last == '\r'))
            l++;
        else
            c++;
        
        if (!std::isalnum(cur) && std::isalnum(last))
            w++;

        last = cur;

    }

    if (c > 0) {

        if (std::isalnum(last))
            w++;
        l++;
    }

}

int main()
{ 
   std::string filename("city_names");
     
   filename += ".txt";

   std::cout << filename << std::endl;
 
   std::ifstream fin(filename);

    if (!fin)
        exit(EXIT_FAILURE);
    

    int c ,w ,l ;

    countStuff(fin, c, w, l);

    std::cout << "c:" << c << "w:" << w << "l:" << l << std::endl;

   return 0;

}