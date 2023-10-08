#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>

extern bool _useColors;
extern bool _printErrors;
extern bool _printWarnings;
extern bool _printInfo;
extern bool _printVerbose;
 
/// Set options for various kinds of output
/// @param printErrors Show output from error()
/// @param printWarnings Show output from warn()
/// @param printInfo Show output from info()
/// @param printVerbose Show output from verbose()
/// @param useColor True to use color
void setOutputOptions( bool printErrors, bool printWarnings, bool printInfo,
    bool printVerbose, bool useColor );
    
/// Style for printed text
enum class PrintStyle{
    NONE,       ///< No style; use default
    RED,        ///< Red
    RED_BOLD,   ///< Red (boldface)
    PINK,       ///< Pink
    OLIVE,      ///< Olive (dark yellow)
    YELLOW,     ///< Yellow
    GREEN,      ///< Green
    LIME,       ///< Lime Green
    CYAN,       ///< Cyan
    BLUE,       ///< Blue
    DARKGREY,   ///< Dark grey
    GREY,       ///< Light grey
    PURPLE,     ///< Purple
    PERIWINKLE, ///< Periwinkle
    LIGHTBLUE,  ///< Light blue
    MAGENTA,    ///< Magenta
    WHITE       ///< White
};

/// Convert an arbitrary item to a string. Uses the extractor (<<) operator.
/// @param item The item to convert.
/// @return The string.
template<typename T>
std::string toString(const T& item)
{
    std::ostringstream oss;
    oss << item;
    return oss.str();
}

/// Convenience function to convert a vector to a string. Returns
/// output in Python-style [] list format.
/// @param item The item to convert.
/// @return The string.
template<typename T>
std::string toString(const std::vector<T>& item)
{
    std::ostringstream oss;
    oss << "[";
    for(unsigned i=0;i<(unsigned)item.size();++i){
        if(i!=0)
            oss << ", ";
        oss << toString(item[i]);
    }
    oss << "]";
    return oss.str();
}

/// Internal helper function for adding the stringified version of a variable to a vector.
/// Uses toString().
/// @param v The vector of strings
/// @param x The item to stringify
template<typename T>
void printHelper(std::vector<std::string>& v, const T& x){
    v.push_back(toString(x));
}

/// Internal helper function for adding the stringified versions of one or more variables to a vector.
/// Uses toString().
/// @param v The vector of strings
/// @param x The item to stringify
/// @param args Additional parameters to stringify
template<typename T1, typename... T>
void printHelper(std::vector<std::string>& v, const T1& item, T... args)
{
    v.push_back(toString(item));
    printHelper(v,args...);
}

/// Internal helper function to convert a set of arguments to a string.
/// @param args The arguments
/// @return All the arguments concatenated into a string, with spaces between them.
template<typename... T>
std::string printHelper(T... args)
{
    std:: vector<std::string> V;
    printHelper(V, args...);
    std::ostringstream oss;
    for(std::size_t i=0;i<V.size();++i){
        if(i!=0)
            oss << " ";
        oss << V[i];
    }
    return oss.str();
}


/// C++ implementation of a Python-style print() function.
/// @param args The things to print
template<typename ...T>
void print(T... args)
{
    std::cout << printHelper(args...) << "\n";
}
  
/// C++ implementation of a Python-style print() function.
/// @param args The thing to print
template<typename T>
void print(const T& x){
    std::cout << toString(x) << "\n";
}

/// Internal helper function for printing to the console.
/// @param style The style (color/boldface)
/// @param prefix Prefix to be printed before the string
/// @param s The string to be formatted & wrapped.
void printWrapHelper(PrintStyle style,const std::string& prefix, const std::string& s);

/// Internal helper function for printing to the console.
/// @param style The style (color/boldface)
/// @param prefix Prefix to be printed before the string
/// @param args The items to be formatted & wrapped.
template<typename ...T>
void printWrap(PrintStyle style, std::string prefix, T... args)
{
    printWrapHelper(style, prefix,printHelper(args...));
}

/// Print an error message to the console.
/// @param args The items to be printed.
template<typename ...T>
void error(T... args)
{
    if(_printErrors)
        printWrap(PrintStyle::RED, "ERROR:   ",args...);
}
   
/// Print a warning message to the console.
/// @param args The items to be printed.
template<typename ...T>
void warn(T... args)
{
    if(_printWarnings)
        printWrap(PrintStyle::YELLOW, "WARNING: ",args...);
}
  
/// Print an note message to the console.
/// @param args The items to be printed.
template<typename ...T>
void note(T... args)
{
    if(_printWarnings)
        printWrap(PrintStyle::OLIVE, "NOTE:    ",args...);
}
  
/// Print an informational message to the console.
/// @param args The items to be printed.
template<typename ...T>
void info(T... args)
{
    if(_printInfo)
        printWrap(PrintStyle::GREEN, "INFO:    ",args...);
}
 
/// Print debugging/verbose output message to the console.
/// @param args The items to be printed.
template<typename ...T>
void verbose(T... args)
{
    if(_printVerbose)
        printWrap(PrintStyle::DARKGREY, "DEBUG:   ",args...);
}
 

/// Write a colored string to the console
/// @param pstyle The style
/// @param s The string to write
void outputConsoleString(PrintStyle pstyle, const std::string& s);
 
/// Color test
void consoleColorTest();
