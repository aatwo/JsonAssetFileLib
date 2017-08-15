#ifndef JSONASSETFILEBUILDER_H
#define JSONASSETFILEBUILDER_H


#include "jsonassetfilecommon.h"
#include "jsonassetfileutils.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <fstream>


namespace jaf
{


    class Builder
    {
        public:

            struct Asset
            {
                unsigned char*  data        = nullptr;
                size_t          dataLength  = -1;
                std::string     prefix;
                std::string     name;
            };

            Builder( const char* fileName )
                : mFileName( new std::string( fileName ) ),
                  mLastError( new std::string( "" ) ),
                  mJsonFileBuffer( new rapidjson::StringBuffer ),
                  mJsonFileWriter( new rapidjson::Writer<rapidjson::StringBuffer>( *mJsonFileBuffer ) )
            {
            }

            Builder( std::string fileName )
                : Builder( fileName.c_str() )
            {
            }

            ~Builder()
            {
                delete mJsonFileWriter;
                delete mJsonFileBuffer;
                delete mLastError;
                delete mFileName;
            }

            bool start()
            {
                if( mStarted )
                {
                    setError( "already started" );
                    return false;
                }

                if( !mFileName->length() )
                {
                    setError( "empty filename" );
                    return false;
                }

                mJsonFileWriter->StartObject();
                mJsonFileWriter->Key( jaf::common::assetArrayTag.c_str() );
                mJsonFileWriter->StartArray();
                mStarted = true;
                return true;
            }

            bool add( Asset asset )
            {
                if( !mStarted )
                {
                    setError( "not started" );
                    return false;
                }

                mJsonFileWriter->StartObject();

                std::string base64Data = jaf::utils::toBase64( asset.data, asset.dataLength );

                mJsonFileWriter->Key( jaf::common::prefixTag.c_str() );
                mJsonFileWriter->String( asset.prefix.c_str() );

                mJsonFileWriter->Key( jaf::common::dataNameTag.c_str() );
                mJsonFileWriter->String( asset.name.c_str() );

                mJsonFileWriter->Key( jaf::common::dataTag.c_str() );
                mJsonFileWriter->String( base64Data.c_str() );

                mJsonFileWriter->EndObject();
                return true;
            }

            bool finish()
            {
                if( !mStarted )
                {
                    setError( "not started" );
                    return false;
                }

                mStarted = false;
                mJsonFileWriter->EndArray();
                mJsonFileWriter->EndObject();

                std::ofstream file;
                file.open( mFileName->c_str(), std::ios::out | std::ios::trunc );
                if( !file.is_open() )
                {
                    setError( "failed to write to disk" );
                    file.close();
                    return false;
                }

                file << mJsonFileBuffer->GetString();
                file.close();
                return true;
            }

            bool isStarted()
            {
                return mStarted;
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

            bool                mStarted    = false;
            std::string*        mFileName   = nullptr;
            std::string*        mLastError  = nullptr;
            rapidjson::StringBuffer* mJsonFileBuffer = nullptr;
            rapidjson::Writer<rapidjson::StringBuffer>* mJsonFileWriter = nullptr;


    }; // Builder


} // jaf


#endif // JSONASSETFILEBUILDER_H
