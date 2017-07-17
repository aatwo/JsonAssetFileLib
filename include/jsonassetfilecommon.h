#ifndef JSONASSETFILECOMMON_H
#define JSONASSETFILECOMMON_H


#ifdef _WIN32
    #ifdef JSONASSETFILELIB_LIBRARY
        #define __EXPORTED__ __declspec(dllexport)
    #else
        #define __EXPORTED__ __declspec(dllimport)
    #endif
#elif
    #ifdef JSONASSETFILELIB_LIBRARY
        #define __EXPORTED__ __attribute__((visibility("default")))
    #else
        #define __EXPORTED__
    #endif
#endif


#include <string>


namespace jaf
{


    namespace common
    {


        const std::string tab           = "    ";
        const std::string assetArrayTag = "assets";
        const std::string prefixTag     = "prefix";
        const std::string dataNameTag   = "name";
        const std::string dataTag       = "prefix";


    } // common


} // jaf


#endif // JSONASSETFILECOMMON_H
