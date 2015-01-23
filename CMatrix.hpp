/*************************************************************************
 * libmatrix
 *************************************************************************
 * @file    CMatrix.hpp
 * @date    21.01.15
 * @author  Hlieb Romanov <rgewebppc@gmail.com>
 * @brief   The CMatrix class declaration
 ************************************************************************/
#ifndef CMATRIX_HPP
#define CMATRIX_HPP

#include <algorithm>
#include <gsl/gsl_matrix.h>
#include <string>
#include "matrix_export.h"
#include "MatrixIO.hpp"

namespace matrix
{

/**
 * @brief The CMatrix class based on GSL matrix implementation
 */

class MATRIX_EXPORT CMatrix
{
public:

    /**
     * @brief CMatrix default constructor
     * Creates empty invalid matrix for further loading from file
     *
     * @sa matrix::io::readFromBinFile()
     * @sa matrix::io::readFromTextFile()
     */
    CMatrix( void );

    /**
     * @brief Constructor
     *
     * @param rows - rows count
     * @param cols - columns count
     * @throw CMatrixException
     */
    CMatrix( size_t rows, size_t cols );

    /**
     * @brief Copy constructor
     *
     * @param other - another matrix object
     * @throw CMatrixException
     */
    CMatrix( const CMatrix& other );

    /**
     * @brief Assigment operator
     *
     * @param other - another matrix object
     * @return Reference to this object
     * @throw CMatrixException
     */
    CMatrix& operator=( const CMatrix& other );

    ~CMatrix( void );

    /**
     * @brief Gets matrix rows count
     *
     * @return Rows count
     */
    size_t rows( void ) const;

    /**
     * @brief Gets matrix columns count
     *
     * @return Columns count
     */
    size_t cols( void ) const;

    /**
     * @brief Gets value from the matrix by index
     *
     * @param rowIndex
     * @param columnIndex
     *
     * @return Value of the matrix cell
     */
    double get( size_t rowIndex, size_t columnIndex ) const;

    /**
     * @brief Sets value of the matrix cell by index
     *
     * @param rowIndex
     * @param columnIndex
     * @param value
     */
    void set( size_t rowIndex, size_t columnIndex, double value );

    /**
     * @brief Simplifies syntax for getting values from the matrix
     * Const version
     *
     * @param rowIndex
     * @param columnIndex
     * @return Const reference to the value of the matrix cell
     */
    const double& operator()( size_t rowIndex, size_t columnIndex ) const;

    /**
     * @brief Simplifies syntax for getting/setting values from/to the matrix
     *
     * @param rowIndex
     * @param columnIndex
     * @return Rreference to the value of the matrix cell
     */
    double& operator()( size_t rowIndex, size_t columnIndex );

    /**
     * @brief Swaps two matrices without data copying
     *
     * @param other - reference to another matrix object
     */
    void swap( CMatrix& other );

    /**
     * @brief Check whether matrix valid or not
     *
     * @return True if this object is valid matrix, false - otherwise
     */
    bool isValid() const { return (mMatrix != 0 ); }

    friend bool ::matrix::io::writeToBinFile( const std::string& path, const CMatrix& matrix );
    friend bool ::matrix::io::readFromBinFile( const std::string& path, CMatrix& matrix );
    friend bool ::matrix::io::readFromTextFile( const std::string& path, CMatrix& matrix );
    friend bool ::matrix::io::writeToTextFile( const std::string& path, const CMatrix& matrix );

private:

    void copyRawMatrix( gsl_matrix* destination, gsl_matrix* source );
    gsl_matrix* matrixAlloc( size_t rows, size_t cols );
    inline void validateMatrix( void ) const;

private:
    gsl_matrix* mMatrix;
};
}

namespace std
{

/**
 * @brief Specialize std::swap template function for matrix::CMatrix class
 */
template<>
void swap( matrix::CMatrix& a, matrix::CMatrix& b )
{
    a.swap( b );
}

}


#endif // CMATRIX_HPP
