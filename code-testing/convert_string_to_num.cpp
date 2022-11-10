#include <iostream> 
#include <deque>
#include <string>
#include <sstream>


template<typename Out, typename In> static Out lexical_cast(In input)
{
    std::stringstream ss;
    ss << input;

    Out r;
    if ((ss >> r).fail() || !(ss >> std::ws).eof())
    {
        throw std::bad_cast();
    }

    return r;
}

bool is_numeric(const std::string in)
{
    bool success = false;

    try
    {
        lexical_cast<double>(in);
        success = true;
    }
    catch(std::bad_cast &exc)
    {
        success = false;
    }

    return success;
}

int main()
{ 
    std::stringstream ss;
    ss << "DBY DEBUG :" << 55 << std::endl;

    std::cout << is_numeric("123") << std::endl;

     std::cout << is_numeric(" 12 3") << std::endl;

     std::cout << is_numeric("-123") << std::endl;
    return 0;
}