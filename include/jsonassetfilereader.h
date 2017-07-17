#ifndef JSONASSETFILEREADER_H
#define JSONASSETFILEREADER_H


#include "jsonassetfilecommon.h"
#include <string>
#include <vector>


namespace jaf
{


    class __EXPORTED__ Reader
    {
        public:

            struct Asset
            {
                std::vector<unsigned char>  data;
                size_t          dataLength = -1;
                std::string     prefix;
                std::string     name;
            };

                                Reader( const char* fileName );
                                Reader( std::string filePath );
                                ~Reader();

            bool                start();
            bool                getNext( Asset& asset_OUT );
            bool                finish();
            bool                isOpen();
            std::string         lastError();


        private:

            void                setError( const char* error );

            std::string*        mFileName   = nullptr;
            std::string*        mLastError  = nullptr;
            std::ifstream*      mFile       = nullptr;



    }; // Reader


} // jaf


#endif // JSONASSETFILEREADER_H
