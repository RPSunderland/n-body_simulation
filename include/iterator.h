#pragma once
#include "node.h"
class Iterator {
public:
    virtual Node* next() = 0;
    virtual Node* current() = 0;
    virtual bool is_end() = 0;
};

