#pragma once

#include "InsertedBytes.hpp"

class IInsertedBytesRepository
{
public:
    virtual ~IInsertedBytesRepository() { }
    virtual void save(CInsertedBytes bytes) = 0;
};
