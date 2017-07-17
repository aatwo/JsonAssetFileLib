#include <jsonassetfilebuilder.h>
#include <jsonassetfileutils.h>


jaf::Builder::Builder( const char* fileName )
    : mFileName( new std::string( fileName ) ),
      mLastError( new std::string( "" ) ),
      mFile( new std::ofstream() ),
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
    if( mFile->is_open() )
        mFile->close();

    delete mJsonFileWriter;
    delete mJsonFileBuffer;
    delete mFile;
    delete mLastError;
    delete mFileName;
}

bool jaf::Builder::start()
{
    if( !mFileName->length() )
    {
        setError( "empty filename" );
        return false;
    }

    mJsonFileWriter->StartObject();
    mJsonFileWriter->Key( jaf::common::assetArrayTag.c_str() );
    mJsonFileWriter->StartArray();
    return true;
}

bool jaf::Builder::add( jaf::Builder::Asset asset )
{
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
    mJsonFileWriter->EndArray();
    mJsonFileWriter->EndObject();

    mFile->open( mFileName->c_str(), std::ios::out | std::ios::trunc );
    if( !mFile->is_open() )
    {
        setError( "failed to write to disk" );
        return false;
    }

    *mFile << mJsonFileBuffer->GetString();
    mFile->close();
    return true;
}

bool jaf::Builder::isOpen()
{
    return mFile->is_open();
}

std::string jaf::Builder::lastError()
{
    return *mLastError;
}

void jaf::Builder::setError( const char* error )
{
    *mLastError = error;
}
