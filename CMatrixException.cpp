/*************************************************************************
 * libmatrix
 *************************************************************************
 * @file    CMatrixException.cpp
 * @date    21.01.15
 * @author  Hlieb Romanov <rgewebppc@gmail.com>
 * @brief   The CMatrixException class definition
 ************************************************************************/
#include "CMatrixException.hpp"

CMatrixException::CMatrixException( const std::string& message )
    : std::exception()
    , mWhat( message )
{
}

CMatrixException::~CMatrixException( void ) throw()
{
}


const char* CMatrixException::what( void ) const throw()
{
    return mWhat.c_str();
}
