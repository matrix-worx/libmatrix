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

#include "matrix_export.h"
#include <gsl/gsl_matrix.h>

/**
 * @brief The CMatrix class based on GSL matrix implementation
 */
class MATRIX_EXPORT CMatrix
{
public:
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
     * @brief Get matrix rows count
     *
     * @return Rows count
     */
    size_t rows( void ) const;

    /**
     * @brief Get matrix columns count
     *
     * @return Columns count
     */
    size_t cols( void ) const;

    /**
     * @brief Get value from the matrix by index
     *
     * @param rowIndex
     * @param columnIndex
     *
     * @return Value of the matrix cell
     */
    double get( size_t rowIndex, size_t columnIndex ) const;

    /**
     * @brief Set value of the matrix cell by index
     *
     * @param rowIndex
     * @param columnIndex
     * @param value
     */
    void set( size_t rowIndex, size_t columnIndex, double value );

    /**
     * @brief Simplify syntax for getting values from the matrix
     * Const version
     *
     * @param rowIndex
     * @param columnIndex
     * @return Const reference to the value of the matrix cell
     */
    const double& operator()( size_t rowIndex, size_t columnIndex ) const;

    /**
     * @brief Simplify syntax for getting/setting values from/to the matrix
     *
     * @param rowIndex
     * @param columnIndex
     * @return Rreference to the value of the matrix cell
     */
    double& operator()( size_t rowIndex, size_t columnIndex );

private:

    void copyRawMatrix( gsl_matrix* destination, gsl_matrix* source );
    gsl_matrix* matrixAlloc( size_t rows, size_t cols );

private:
    gsl_matrix* mMatrix;
};

#endif // CMATRIX_HPP
