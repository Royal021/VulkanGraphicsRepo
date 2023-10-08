#include "mischelpers.h"
 
std::string trim(const std::string& s)
{
    if(s.length()==0)
        return s;
        
    std::size_t i,j;
    i=0;
    while(i<s.length() && std::isspace(s[i]) )
        i++;
    
    if( i == s.length() )
        return "";
        
    j=s.length()-1;
    while(j>i && std::isspace(s[j]))
        j--;
        
    if( i==j )
        return "";
    return s.substr(i,j-i+1);
}

std::vector<std::string> shlex_split(std::string s)
{
    std::vector<std::string> words;
    int i=0;
    int len = (int)s.length();
    
    while(i<len){
        if( s[i] == ' '){
            i++;
            continue;
        }
        
        std::string word;
        if( s[i] == '"' ){
            i++;
            while(i<len && s[i] != '"' ){
                word += s[i];
                i++;
            }
            i++;
            words.push_back(word);
            continue;
        }
        
        while(i<len && s[i] != ' ' ){
            word += s[i];
            i++;
        }
        words.push_back(word);
        continue;
    }
    return words;
}

std::vector<std::string> split(std::string s)
{
    std::vector<std::string> rv;
    std::istringstream iss(s);
    while(true){
        std::string word;
        iss >> word;
        if(iss.fail())
            return rv;
        rv.push_back(word);
    }
}

std::vector<std::string> split(std::string s, char delim)
{
    std::vector<std::string> rv;
    std::istringstream iss(s);
    while(true){
        std::string word;
        getline(iss,word,delim);
        if(iss.fail())
            return rv;
        rv.push_back(word);
    }
}


unsigned len(const std::string& s)
{
    return (unsigned)s.length();
}

std::string operator+(const std::string& a, int b){
    return a+std::to_string(b);
}
std::string operator+(int b,const std::string& a){
    return std::to_string(b)+a;
}
std::string operator+(const std::string& a, unsigned b){
    return a+std::to_string(b);
}
std::string operator+(unsigned b,const std::string& a){
    return std::to_string(b)+a;
}
std::string operator+(const std::string& a, long unsigned b){
    return a+std::to_string(b);
}
std::string operator+(long unsigned b,const std::string& a){
    return std::to_string(b)+a;
}
std::string operator+(const std::string& a, double b){
    return a+std::to_string(b);
}
std::string operator+(double b,const std::string& a){
    return std::to_string(b)+a;
}
//~ std::string operator+(const char* a, const char* b){
    //~ return std::string(a)+std::string(b);
//~ }


