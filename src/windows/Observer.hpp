#pragma once

template<typename T>
struct Observer
{
    virtual void fieldChanged(T & source, const std::string & fieldName) = 0;
};
