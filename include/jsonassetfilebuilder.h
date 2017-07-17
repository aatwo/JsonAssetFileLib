#ifndef JSONASSETFILEBUILDER_H
#define JSONASSETFILEBUILDER_H


#include "jsonassetfilecommon.h"
#include <string>
#include <fstream>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


namespace jaf
{


    class __EXPORTED__ Builder
    {
        public:

            struct Asset
            {
                unsigned char*  data        = nullptr;
                size_t          dataLength  = -1;
                std::string     prefix;
                std::string     name;
            };

                                Builder( const char* fileName );
                                Builder( std::string fileName );
                                ~Builder();

            bool                start();
            bool                add( Asset asset );
            bool                finish();
            bool                isOpen();
            std::string         lastError();


        private:

            void                setError( const char* error );

            std::string*        mFileName   = nullptr;
            std::string*        mLastError  = nullptr;
            std::ofstream*      mFile       = nullptr;
            rapidjson::StringBuffer* mJsonFileBuffer = nullptr;
            rapidjson::Writer<rapidjson::StringBuffer>* mJsonFileWriter = nullptr;


    }; // Builder


} // jaf


#endif // JSONASSETFILEBUILDER_H
