#include <iostream>
#include "buildertest.h"
#include "readertest.h"


using namespace std;


int main()
{
    // TODO - make the unit test classes generic


    cout << "Performing builder test...";
    BuilderTest builderTest;
    if( builderTest.Run() )
        cout << "[PASS]" << endl;
    else
        cout << "[FAIL] - " << builderTest.LastError() << endl;

    cout << "Performing reader test...";
    ReaderTest readerTest;
    if( readerTest.Run() )
        cout << "[PASS]" << endl;
    else
        cout << "[FAIL] - " << readerTest.LastError() << endl;


    return 0;
}
