#pragma once

#include "_constants.hpp"
#include <cstddef>
#include <sstream>
#include <string>

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
    virtual void graph() = 0;
    int strcol(const char *const str);
    std::string wrap(const char *const str, const std::size_t line_length);
    std::size_t outputlabel(const long double label, std::ostringstream &strm);

private:


};
