#include "ConfigParser.h"
#include <iostream>
#include <fstream>
#include "mischelpers.h"

ConfigParser::ConfigParser(std::string infile)
{
    std::ifstream in(infile);
    if(!in.good() ){
        throw std::runtime_error("Cannot open file "+infile);
    }
    
    while(true){
        std::string line;
        getline(in,line);
        if(in.fail() ){
            return;
        }
        std::string s=trim(line);
        if( s.length() == 0 )
            continue;
        if( s[0] == ';' || s[0]=='#' )
            continue;
        if( s[0] == '[' )
            continue;
        auto idx = s.find("=");
        if(idx == std::string::npos ){
            throw std::runtime_error("Bad line in config file "+infile+": "+line);
        }
        std::string key = s.substr(0,idx);
        std::string value = s.substr(idx+1);
        M[key]=value;
    }
}

std::string ConfigParser::get(std::string key, std::string defl)
{
    if( M.find(key) != M.end() )
        return M[key];
    return defl;
}


