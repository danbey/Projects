#include <iostream> 
#include <vector>

#include <string>
#include <sstream>
#include <fstream>

using namespace std;

using VecToPrtVec = vector<vector<string> *>;


void split(const string& s, char c, vector<string> &v)
{

    int i = 0;
    int j = s.find(c);
    while (j >= 0) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j < 0)
            v.push_back(s.substr(i, s.length()));
    }
}

void loadCSV(istream& in, VecToPrtVec& data)
{
    vector<string> * p =NULL;
    string tmp;
    
    while(!in.eof()) {
        getline(in, tmp, '\n');
        vector<string> p;
        split(tmp, ',', p);
        if (p.size())
            data.push_back(new vector<string>(p));
        cout << tmp << endl;
        tmp.clear();
    }
}

int main()
{ 
   std::string filename("city_names");
   filename.append(".txt");
   //filename += ".txt";

   std::cout << filename << std::endl;
 
   std::ifstream fin(filename);

    if (!fin)
        exit(EXIT_FAILURE);
    

    vector<vector<string> *> data;

    loadCSV(fin, data);

    for (vector<vector<string> *>::iterator p = data.begin();
         p != data.end(); p++) {
        vector<string> &l_v = **p;
        cout << l_v[0] << " : " << l_v[1] << " : " << l_v[2] << endl;
    }
    
    for (vector<vector<string> *>::iterator p = data.begin();
         p != data.end(); p++) {
        delete *p;  
    }

   return 0;

}