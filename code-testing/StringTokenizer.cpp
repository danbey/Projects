#include <iostream> 
#include <deque>
#include <string>
#include <sstream>

class StringTokenizer {
public:
    StringTokenizer(const std::string & s, const char * delim = NULL)
                    : m_str(s), m_num_tokens(-1), m_begin(0), m_end(0)
    {
        if (!delim)
            m_delim = "\f\n\r\t\v";
        else
            m_delim = delim;

        //Point to the first delim
        m_begin = s.find_first_not_of(m_delim);
        m_end = s.find_first_of(m_delim, m_begin);
    }
    
    size_t countTokens();

    bool hasMoreTokens()
    {
        return (m_begin != m_end);
    }

    void nextToken(std::string & s);

private:
    StringTokenizer() {}
    std::string m_delim;
    std::string m_str;
    int m_num_tokens;
    int m_begin;
    int m_end;

};

size_t StringTokenizer::countTokens()
{
    if (m_num_tokens >= 0)
        return m_num_tokens;

    std::string::size_type n = 0;
    std::string::size_type i = 0;

    for (;;) {
        //advance to the first token
        if ((i = m_str.find_first_not_of(m_delim, i)) == std::string::npos)
            break;
        
        //advance to the next delimiter
        i = m_str.find_first_of(m_delim, i+1);
        n++;
         if (i == std::string::npos)
            break;
    }
    return (m_num_tokens = n);
}

void StringTokenizer::nextToken(std::string & s)
{
    if (m_begin != std::string::npos && m_end != std::string::npos)
    {
        s = m_str.substr(m_begin, m_end - m_begin);
        m_begin = m_str.find_first_not_of(m_delim, m_end);
        m_end = m_str.find_first_of(m_delim, m_begin);
    }
    else if (m_begin != std::string::npos && m_end == std::string::npos)
    {
        s = m_str.substr(m_begin, m_str.length() - m_begin);
        m_begin = m_str.find_first_not_of(m_delim, m_end);
    }
}

int main()
{ 
    std::string s = "Dan,Tel-Aviv,Israel";
    std::string tmp;

    StringTokenizer st(s, ",");

    std::cout << "count: " << st.countTokens() << std::endl;
    while (st.hasMoreTokens())
    {
        st.nextToken(tmp);
        std::cout << "next: " << tmp << std::endl;
    }
 
    return 0;
                                                               }