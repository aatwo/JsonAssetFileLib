#ifndef JSONASSETFILEUTILS_H
#define JSONASSETFILEUTILS_H


#include <string>
#include <vector>


namespace jaf
{


    namespace utils
    {


        const std::string base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        std::string                 toBase64( const unsigned char* data, size_t dataLength );
        std::vector<unsigned char>  fromBase64( std::string const& base64 );
        bool                        isBase64( unsigned char c );


    } // utils


} // jaf


#endif // JSONASSETFILEUTILS_H
