#ifndef JSONASSETFILEBUILDER_H
#define JSONASSETFILEBUILDER_H


#include "jsonassetfilecommon.h"
#include <string>
#include <fstream>


namespace jaf
{


    class __EXPORTED__ Builder
    {
        public:

            struct Asset
            {
                unsigned char*  data        = nullptr;
                unsigned int    dataLength  = -1;
                std::string     prefix;
                std::string     name;
            };

                                Builder( const char* fileName );
                                Builder( std::string fileName );
                                ~Builder();

            bool                start();
            bool                add( Asset data );
            bool                finish();
            bool                isOpen();
            std::string         lastError();


        private:

            void                setError( const char* error );

            std::string*        mFileName   = nullptr;
            std::string*        mLastError  = nullptr;
            std::ofstream*      mFile       = nullptr;
            int                 mCount      = 0;



    }; // Builder


} // jaf


#endif // JSONASSETFILEBUILDER_H
