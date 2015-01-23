/*************************************************************************
 * libmatrix
 *************************************************************************
 * @file    CMatrixException.hpp
 * @date    21.01.15
 * @author  Hlieb Romanov <rgewebppc@gmail.com>
 * @brief   The CMatrixException class declaration
 ************************************************************************/
#ifndef CMATRIXEXCEPTION_HPP
#define CMATRIXEXCEPTION_HPP

#include <exception>
#include <string>

#include "matrix_export.h"

class MATRIX_EXPORT CMatrixException : public std::exception
{
public:
    CMatrixException( const std::string& message );

    virtual ~CMatrixException( void ) throw();
    // exception interface
public:
    virtual const char* what( void ) const throw();

private:
    std::string mWhat;
};

#endif // CMATRIXEXCEPTION_HPP
