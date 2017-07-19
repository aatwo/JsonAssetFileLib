#ifndef BUILDERTEST_H
#define BUILDERTEST_H


#include <string>
#include "common.h"


class BuilderTest
{
    public:

                            BuilderTest();
        bool                Run();
        std::string         LastError();


    private:

        std::string         mLastError;


}; // BuilderTest


#endif // BUILDERTEST_H
