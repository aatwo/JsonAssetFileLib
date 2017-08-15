#ifndef JSONASSETFILEREADER_H
#define JSONASSETFILEREADER_H


#include "jsonassetfilecommon.h"
#include "jsonassetfileutils.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using namespace rapidjson;
using namespace std;


namespace jaf
{


    struct ReaderAsset
    {
        std::vector<unsigned char> data;
        std::string     prefix;
        std::string     name;
    };


    class ReaderParseHandler {

        public:

            ReaderParseHandler( std::vector<ReaderAsset>& assetList )
                : assetList( assetList )
            {
            }

            bool Key( const char* str, SizeType length, bool /*copy*/ )
            {
                std::string key( str, length );

                if( key == jaf::common::dataNameTag )
                    lastKey = LastKey::name;

                else if( key == jaf::common::prefixTag )
                    lastKey = LastKey::prefix;

                else if( key == jaf::common::dataTag )
                    lastKey = LastKey::data;

                else
                    lastKey = LastKey::none;

                return true;
            }

            bool String( const char* str, SizeType length, bool /*copy*/ )
            {
                switch( lastKey )
                {
                case LastKey::name:
                {
                    gotName = true;
                    currentAsset.name = std::string( str, length );
                    break;
                }

                case LastKey::prefix:
                {
                    gotPrefix = true;
                    currentAsset.prefix = std::string( str, length );
                    break;
                }

                case LastKey::data:
                {
                    gotData = true;
                    std::string base64Data( str, length );
                    currentAsset.data = jaf::utils::fromBase64( base64Data );
                    break;
                }

                default: {}
                }

                if( gotName && gotPrefix && gotData )
                {
                    gotName     = false;
                    gotPrefix   = false;
                    gotData     = false;

                    assetList.push_back( currentAsset );
                    currentAsset = ReaderAsset();
                }

                return true;
            }

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
            ReaderAsset         currentAsset;
            std::vector<ReaderAsset>& assetList;



    }; // ReaderParseHandler


    class Reader
    {
        public:

            Reader()
                : mLastError( new std::string( "" ) )
            {
            }

            ~Reader()
            {
                delete mLastError;
            }

            bool getAssets( std::string fileName, std::vector<jaf::ReaderAsset>& assets_OUT )
            {
                std::ifstream file;
                file.open( fileName.c_str(), std::ios::in );
                if( !file.is_open() )
                {
                    setError( "failed to read from file" );
                    return false;
                }

                std::vector<char> data;

                char c = file.get();
                data.push_back( c );

                while( file.good() )
                {
                    c = file.get();
                    data.push_back( c );
                }

                file.close();

                rapidjson::StringStream jsonFileStream( data.data() );

                ReaderParseHandler handler( assets_OUT );

                rapidjson::Reader reader;
                reader.Parse( jsonFileStream, handler );

                return true;
            }

            std::string lastError()
            {
                return *mLastError;
            }


        private:

            void setError( const char* error )
            {
                *mLastError = std::string( error );
            }

            std::string* mLastError  = nullptr;



    }; // Reader



} // jaf


#endif // JSONASSETFILEREADER_H
