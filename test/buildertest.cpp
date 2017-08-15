#include "buildertest.h"
#include "jsonassetfilebuilder.h"


BuilderTest::BuilderTest()
{
}

bool BuilderTest::Run()
{
    jaf::Builder builder( "test.json" );

    if( !builder.start() )
    {
        mLastError = builder.lastError();
        return false;
    }

    { // Asset 1

        jaf::Builder::Asset asset;
        std::string data = "Asset one data";
        asset.data = (unsigned char*)data.data();
        asset.dataLength = data.length();
        asset.name = "testNameOne";
        asset.prefix = "testPrefixOne";
        if( !builder.add( asset ) )
        {
            mLastError = builder.lastError();
            return false;
        }
    }

    { // Asset 2

        jaf::Builder::Asset asset;
        std::string data = "Asset two data";
        asset.data = (unsigned char*)data.data();
        asset.dataLength = data.length();
        asset.name = "testNameTwo";
        asset.prefix = "testPrefixTwo";
        if( !builder.add( asset ) )
        {
            mLastError = builder.lastError();
            return false;
        }
    }

    { // Asset 2

        jaf::Builder::Asset asset;
        std::string data = "Asset three data";
        asset.data = (unsigned char*)data.data();
        asset.dataLength = data.length();
        asset.name = "testNameThree";
        asset.prefix = "testPrefixThree";
        if( !builder.add( asset ) )
        {
            mLastError = builder.lastError();
            return false;
        }
    }

    if( !builder.finish() )
    {
        mLastError = builder.lastError();
        return false;
    }

    return true;
}

std::string BuilderTest::LastError()
{
    return mLastError;
}
