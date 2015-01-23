#ifndef MATRIXIO_HPP
#define MATRIXIO_HPP

#include <string>
#include "matrix_export.h"

namespace matrix
{

class CMatrix;

namespace io {

/**
 * @brief Read matrix from the binary file
 *
 * @param[in] path - full path to the binary file with matrix data
 * @param[out] matrix - reference to the empty matrix created by default constructor
 *
 * @return True - on success, false - otherwise
 */
bool MATRIX_EXPORT readFromBinFile( const std::string& path, matrix::CMatrix& matrix );

/**
 * @brief Write matrix to the binary file
 *
 * @param path - full path to the destination binary file
 * @param matrix - reference to the valid matrix object
 *
 * @return True - on success, false - otherwise
 */
bool MATRIX_EXPORT writeToBinFile( const std::string& path, const matrix::CMatrix& matrix );

/**
 * @brief Read matrix from the text file
 *
 * @param[in] path - full path to the text file with matrix data
 * @param[out] matrix - reference to the empty matrix created by default constructor
 *
 * @return True - on success, false - otherwise
 */
bool MATRIX_EXPORT readFromTextFile( const std::string& path, matrix::CMatrix& matrix );

/**
 * @brief Write matrix to the text file
 *
 * @param path - full path to the destination text file
 * @param matrix - reference to the valid matrix object
 *
 * @return True - on success, false - otherwise
 */
bool MATRIX_EXPORT writeToTextFile( const std::string& path, const matrix::CMatrix& matrix );

}
}

#endif // MATRIXIO_HPP
