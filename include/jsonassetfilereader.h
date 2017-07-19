#ifndef JSONASSETFILEREADER_H
#define JSONASSETFILEREADER_H


#include "jsonassetfilecommon.h"
#include <string>
#include <vector>
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>


using namespace rapidjson;
using namespace std;


namespace jaf
{


    class __EXPORTED__ Reader
    {
        public:

            struct Asset
            {
                std::vector<unsigned char> data;
                std::string     prefix;
                std::string     name;
            };

                                Reader();
                                ~Reader();

            bool                getAssets( std::string fileName, std::vector<jaf::Reader::Asset>& assets_OUT );
            std::string         lastError();


        private:

            void                setError( const char* error );

            std::string*        mLastError  = nullptr;



    }; // Reader


    class ReaderParseHandler {

        public:

                                ReaderParseHandler( std::vector<Reader::Asset>& assetList ) : assetList( assetList ) {}

            bool                Key( const char* str, SizeType length, bool copy );
            bool                String( const char* str, SizeType length, bool copy );

            // Unrequired types
            bool                StartObject() { return true; }
            bool                EndObject( SizeType /*memberCount*/ ) { return true; }
            bool                StartArray() { return true; }
            bool                EndArray( SizeType /*elementCount*/ ) { return true; }
            bool                Null() { return true; }
            bool                Bool( bool ) { return true; }
            bool                Int( int ) { return true; }
            bool                Uint( unsigned ) { return true; }
            bool                Int64( int64_t ) { return true; }
            bool                Uint64( uint64_t ) { return true; }
            bool                Double( double ) { return true; }
            bool                RawNumber( const char* /*str*/, SizeType /*length*/, bool /*copy*/ ) { return true; }


        private:

            enum class LastKey
            {
                name,
                prefix,
                data,

                none
            };

            LastKey             lastKey     = LastKey::none;
            bool                gotName     = false;
            bool                gotPrefix   = false;
            bool                gotData     = false;
            Reader::Asset       currentAsset;
            std::vector<Reader::Asset>& assetList;



    }; // ReaderParseHandler



} // jaf


#endif // JSONASSETFILEREADER_H
