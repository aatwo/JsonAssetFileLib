#include <jsonassetfilebuilder.h>
#include <jsonassetfileutils.h>


jaf::Builder::Builder( const char* fileName )
    : mFileName( new std::string( fileName ) ),
      mLastError( new std::string( "" ) ),
      mJsonFileBuffer( new rapidjson::StringBuffer ),
      mJsonFileWriter( new rapidjson::Writer<rapidjson::StringBuffer>( *mJsonFileBuffer ) )
{
}

jaf::Builder::Builder( std::string fileName )
    : Builder( fileName.c_str() )
{
}

jaf::Builder::~Builder()
{
    delete mJsonFileWriter;
    delete mJsonFileBuffer;
    delete mLastError;
    delete mFileName;
}

bool jaf::Builder::start()
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

bool jaf::Builder::add( jaf::Builder::Asset asset )
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

bool jaf::Builder::finish()
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

bool jaf::Builder::isStarted()
{
    return mStarted;
}

std::string jaf::Builder::lastError()
{
    return *mLastError;
}

void jaf::Builder::setError( const char* error )
{
    *mLastError = std::string( error );
}
