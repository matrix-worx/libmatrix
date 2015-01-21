#ifndef CMATRIXEXCEPTION_HPP
#define CMATRIXEXCEPTION_HPP

#include <exception>
#include <string>

#include "matrix_export.h"

class MATRIX_EXPORT CMatrixException : public std::exception
{
public:
    CMatrixException( const std::string& message );

    // exception interface
public:
    virtual const char* what() const;

private:
    std::string mWhat;
};

#endif // CMATRIXEXCEPTION_HPP
