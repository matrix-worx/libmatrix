#include "CMatrixException.hpp"

CMatrixException::CMatrixException( const std::string& message )
    : std::exception()
    , mWhat( message )
{
}


const char *CMatrixException::what() const
{
    return mWhat.c_str();
}
