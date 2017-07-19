#ifndef READERTEST_H
#define READERTEST_H


#include <string>
#include "common.h"


class ReaderTest
{
    public:

                            ReaderTest();
        bool                Run();
        std::string         LastError();


    private:

        std::string         mLastError;


}; // ReaderTest


#endif // READERTEST_H
