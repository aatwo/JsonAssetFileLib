#include <jsonassetfilebuilder.h>
#include <jsonassetfileutils.h>


jaf::Builder::Builder( const char* fileName )
    : mFileName( new std::string( fileName ) ),
      mLastError( new std::string( "" ) ),
      mFile( new std::ofstream() )
{
}

jaf::Builder::Builder( std::string fileName )
    : Builder( fileName.c_str() )
{
}

jaf::Builder::~Builder()
{
    finish();
    delete mFileName;
    delete mLastError;
    delete mFile;
}

bool jaf::Builder::start()
{
    if( mFile->is_open() )
    {
        setError( "file already open" );
        return false;
    }

    if( !mFileName->length() )
    {
        setError( "empty filename" );
        return false;
    }

    mFile->open( mFileName->c_str(), std::ios::out | std::ios::trunc );

    if( !mFile->is_open() )
    {
        setError( "file not open" );
        return false;
    }

    mCount = 0;
    *mFile << "{\n";
    *mFile << "    \"assets\":\n";
    *mFile << "    [";
    return true;
}

bool jaf::Builder::add( jaf::Builder::Asset asset )
{
    if( !mFile->is_open() )
    {
        setError( "file not open" );
        return false;
    }

    if( asset.dataLength <= 0 )
    {
        setError( "invalid data length" );
        return false;
    }

    std::string base64Data = jaf::utils::toBase64( asset.data, asset.dataLength );

    if( !base64Data.length() )
    {
        setError( "base64 encoding returned empty" );
        return false;
    }

    if( mCount )
        *mFile << ",\n";

    *mFile << jaf::common::tab << "{ ";
    *mFile << "\"" << jaf::common::prefixTag     << "\": \"" << asset.prefix << "\",";
    *mFile << "\"" << jaf::common::dataNameTag   << "\": \"" << asset.name   << "\",";
    *mFile << "\"" << jaf::common::dataTag       << "\": \"" << base64Data   << "\"";
    *mFile << " }";

    mCount++;
    return true;
}

bool jaf::Builder::finish()
{
    if( !mFile->is_open() )
    {
        setError( "file not open" );
        return false;
    }

    *mFile << "\n";
    *mFile << jaf::common::tab << "]\n";
    *mFile << "}\n";

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
