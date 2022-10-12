//
// Created by konstantin on 29.09.22.
//

#ifndef OCEAN_ERROR_H
#define OCEAN_ERROR_H
#include "stdexcept"

class Exception : public std::runtime_error{
public:
    Exception(const std::string& exception) : std::runtime_error(exception){}
};
#endif //OCEAN_ERROR_H
