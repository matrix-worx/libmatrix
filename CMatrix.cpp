/*************************************************************************
 * libmatrix
 *************************************************************************
 * @file    CMatrix.cpp
 * @date    21.01.15
 * @author  Hlieb Romanov <rgewebppc@gmail.com>
 * @brief   The CMatrix class definition
 ************************************************************************/
#include <boost/thread/locks.hpp>

#include "CMatrix.hpp"
#include "CMatrixException.hpp"

using namespace matrix;

CMatrix::CMatrix( void )
    : mMatrix( 0 )
{
}

CMatrix::CMatrix( size_t rows, size_t cols )
{
    mMatrix = gsl_matrix_calloc( rows, cols );
    if ( !mMatrix )
    {
        throw CMatrixException( "Can't allocate memory for matrix" );
    }
}

CMatrix::CMatrix( const CMatrix& other )
{
    mMatrix = matrixAlloc( other.rows(), other.cols() );
    copyRawMatrix( mMatrix, other.mMatrix );
}

CMatrix& CMatrix::operator=( const CMatrix& other )
{
    if ( this != &other )
    {
        if ( rows() != other.rows() || cols() != other.cols() )
        {
            boost::lock_guard<boost::shared_mutex> lock( mGuard );
            gsl_matrix* newMatrix = matrixAlloc( other.rows(), other.cols() );
            copyRawMatrix( newMatrix, other.mMatrix );
            gsl_matrix_free( mMatrix );
            mMatrix = newMatrix;
        }
        else
        {
            boost::lock_guard<boost::shared_mutex> lock( mGuard );
            copyRawMatrix( mMatrix, other.mMatrix );
        }
    }
    return *this;
}

CMatrix::~CMatrix( void )
{
    if ( isValid() )
    {
        gsl_matrix_free( mMatrix );
    }
}

size_t CMatrix::rows( void ) const
{
    validateMatrix();
    boost::shared_lock<boost::shared_mutex> lock( mGuard );
    return mMatrix->size1;
}

size_t CMatrix::cols() const
{
    validateMatrix();
    boost::shared_lock<boost::shared_mutex> lock( mGuard );
    return mMatrix->size2;
}

double CMatrix::get( size_t rowIndex, size_t columnIndex ) const
{
    validateMatrix();
    boost::shared_lock<boost::shared_mutex> lock( mGuard );
    return gsl_matrix_get( mMatrix, rowIndex, columnIndex );
}

void CMatrix::set( size_t rowIndex, size_t columnIndex, double value )
{
    validateMatrix();
    boost::lock_guard<boost::shared_mutex> lock( mGuard );
    gsl_matrix_set( mMatrix, rowIndex, columnIndex, value );
}

const double& CMatrix::operator()( size_t rowIndex, size_t columnIndex ) const
{
    validateMatrix();
    boost::shared_lock<boost::shared_mutex> lock( mGuard );
    return *gsl_matrix_const_ptr( mMatrix, rowIndex, columnIndex );
}

double& CMatrix::operator()( size_t rowIndex, size_t columnIndex )
{
    validateMatrix();
    boost::lock_guard<boost::shared_mutex> lock( mGuard );
    return *gsl_matrix_ptr( mMatrix, rowIndex, columnIndex );
}

void CMatrix::swap( CMatrix& other )
{
    using std::swap;

    boost::lock_guard<boost::shared_mutex> lock( mGuard );

    swap( mMatrix, other.mMatrix );
}

void CMatrix::copyRawMatrix( gsl_matrix* destination, gsl_matrix* source )
{
    int result = gsl_matrix_memcpy( destination, source );
    if ( result != GSL_SUCCESS )
    {
        throw CMatrixException( "Can't copy matrix" );
    }
}

gsl_matrix* CMatrix::matrixAlloc( size_t rows, size_t cols )
{
    gsl_matrix* matrix = gsl_matrix_alloc( rows, cols );

    if ( !matrix )
    {
        throw CMatrixException( "Can't allocate memory for matrix" );
    }

    return matrix;
}

inline void CMatrix::validateMatrix( void ) const
{
    if ( !isValid() )
    {
        throw CMatrixException( "Invalid matrix. Operation not performed." );
    }
}

bool CMatrix::isValid( void ) const
{
   boost::shared_lock<boost::shared_mutex> lock( mGuard );
   return (mMatrix != 0 );
}
