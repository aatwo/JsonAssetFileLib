#include <jsonassetfilereader.h>
#include <jsonassetfileutils.h>
#include <fstream>


jaf::Reader::Reader()
    : mLastError( new std::string( "" ) )
{
}

jaf::Reader::~Reader()
{
    delete mLastError;
}

bool jaf::Reader::getAssets( std::string fileName, std::vector<jaf::Reader::Asset>& assets_OUT )
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

std::string jaf::Reader::lastError()
{
    return *mLastError;
}

void jaf::Reader::setError( const char* error )
{
    *mLastError = std::string( error );
}

bool jaf::ReaderParseHandler::Key( const char* str, SizeType length, bool /*copy*/ )
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

bool jaf::ReaderParseHandler::String( const char* str, SizeType length, bool /*copy*/ )
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
        currentAsset = Reader::Asset();
    }

    return true;
}
