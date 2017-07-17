#include <iostream>
#include <buildertest.h>


using namespace std;


int main()
{
    cout << "Performing builder test...";
    BuilderTest builderTest;
    if( builderTest.Run() )
        cout << "[PASS]" << endl;
    else
        cout << "[FAIL] - " << builderTest.LastError() << endl;


    return 0;
}
