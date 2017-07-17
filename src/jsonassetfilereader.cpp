#include <jsonassetfilereader.h>
#include <jsonassetfileutils.h>
#include <fstream>


jaf::Reader::Reader( const char* fileName )
    : mFileName( new std::string( fileName ) ),
      mLastError( new std::string( "" ) ),
      mFile( new std::ifstream() )
{
}

jaf::Reader::Reader( std::string filePath )
    : Reader( filePath.c_str() )
{
}

jaf::Reader::~Reader()
{
    finish();
    delete mFileName;
    delete mLastError;
    delete mFile;
}

bool jaf::Reader::start()
{

    return false;
}

bool jaf::Reader::getNext( Asset& asset_OUT )
{

    return false;
}

bool jaf::Reader::finish()
{

    return false;
}

bool jaf::Reader::isOpen()
{

    return false;
}

std::string jaf::Reader::lastError()
{

    return *mLastError;
}

void jaf::Reader::setError( const char* error )
{

}
