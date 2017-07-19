#include "readertest.h"
#include <jsonassetfilereader.h>
#include <sstream>


ReaderTest::ReaderTest()
{
}

bool ReaderTest::Run()
{
    const int expectedAssetCount = 3;

    // TODO: store the actual assets somewhere and check they match the input

    jaf::Reader reader;
    std::vector<jaf::Reader::Asset> assets;
    if( !reader.getAssets( "test.json", assets ) )
    {
        mLastError = reader.lastError();
        return false;
    }

    if( assets.size() != expectedAssetCount )
    {
        std::stringstream ss;
        ss << "Unexpected asset count (expected " << expectedAssetCount << ", got " << assets.size() << ")";
        mLastError = ss.str();
        return false;
    }

    return true;
}

std::string ReaderTest::LastError()
{
    return mLastError;
}
