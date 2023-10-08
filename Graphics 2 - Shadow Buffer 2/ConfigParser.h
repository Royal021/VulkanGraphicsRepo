#pragma once
#include <map>
#include <string>

/// Simple parser for .ini files.
class ConfigParser{
  public:
  
    /// The key/value pairs found in the file
    std::map<std::string, std::string> M;
    
    /// Parse a config file.
    /// @param infile The input file
    ConfigParser(std::string infile);
    
    /// Get a value from the config.
    /// @param key The key to look for
    /// @param defl Default value to return if the key is not found
    /// @return The value from the config file or defl if it wasn't found.
    std::string get(std::string key, std::string defl);
};
