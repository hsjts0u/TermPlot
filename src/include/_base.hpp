#pragma once

#include "_constants.hpp"
#include <cstddef>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <float.h>
#include <math.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef struct graphoptions
{

    bool border = true;
    bool axislabel = true;
    bool axisunitslabel = true;
    std::string title = "";
    unsigned int style = 2;
    unsigned int color = 2;
    graphoptions() = default;
    ~graphoptions() = default;

} graphoptions;

const graphoptions graphoptionsdefault;

class _base 
{

public:
    virtual int plot() = 0;

protected:
    int strcol(const char *const str);
    std::string wrap(const char *const str, const size_t line_length);
    size_t outputlabel(const long double label, std::ostringstream &strm);

private:
    /* empty */

};
