#pragma once
#include "_constants.hpp"

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

private:


};