#pragma once

#include "_constants.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <float.h>
#include <math.h>
#include <string.h>

typedef struct graphoptions
{

    bool border = true;
    bool axislabel = true;
    bool axisunitslabel = true;
    char *title = nullptr;
    unsigned int style = 2;
    unsigned int color = 2;
    graphoptions(void) = default;
    ~graphoptions(void) = default;

} graphoptions;

const graphoptions graphoptionsdefault;

class _base 
{

public:
    virtual void plot() = 0;

protected:
    int strcol(const char *const str);
    std::string wrap(const char *const str, const size_t line_length);
    size_t outputlabel(const long double label, std::ostringstream &strm);

private:


};
