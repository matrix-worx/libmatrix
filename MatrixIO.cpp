#include <stdio.h>
#include <fstream>

#include "MatrixIO.hpp"
#include "CMatrix.hpp"

bool matrix::io::readFromBinFile( const std::string& path, matrix::CMatrix& matrix )
{
    bool success = false;
    FILE* sourceFile = fopen( path.c_str(), "rb" );

    if ( sourceFile )
    {
        size_t dimensions[2];
        size_t result = fread( dimensions, sizeof( size_t ), 2, sourceFile );

        if ( result == sizeof( size_t ) * 2 )
        {
            CMatrix m( dimensions[0], dimensions[1] );
            int status = gsl_matrix_fread( sourceFile, m.mMatrix );
            if ( status == GSL_SUCCESS )
            {
                m.swap( matrix );
                success = true;
            }
        }
        fclose( sourceFile );
    }

    return success;
}

bool matrix::io::writeToBinFile( const std::string& path, const matrix::CMatrix& matrix )
{
    bool success = false;
    FILE* destFile = fopen( path.c_str(), "wb" );

    if ( destFile )
    {
        size_t dimensions[2];
        dimensions[0] = matrix.rows();
        dimensions[1] = matrix.cols();

        size_t result = fwrite( dimensions, sizeof( size_t ), 2, destFile );

        if ( result == sizeof( size_t ) * 2 )
        {
            int status = gsl_matrix_fwrite( destFile, matrix.mMatrix );
            if ( status == GSL_SUCCESS )
            {
                success = true;
            }
        }
        fclose( destFile );
    }

    return success;
}

bool matrix::io::readFromTextFile( const std::string& path, matrix::CMatrix& matrix )
{
    bool success = false;
    std::ifstream stream( path.c_str() );

    if ( stream.good() )
    {
        size_t rows, cols;
        stream >> rows >> cols;

        CMatrix m( rows, cols );

        double value;

        for ( size_t i = 0; i < rows; i++ )
        {
            for ( size_t j = 0; j < cols; j++ )
            {
                stream >> value;
                m( i, j ) = value;
            }
        }

        success = true;
    }

    stream.close();

    return success;
}


bool matrix::io::writeToTextFile(const std::string &path, const matrix::CMatrix &matrix)
{
    bool success = false;
    std::ofstream stream( path.c_str() );

    if ( stream.good() )
    {
        stream << matrix.rows() << " " << matrix.cols() << std::endl;

        for ( size_t i = 0; i < matrix.rows(); i++ )
        {
            for ( size_t j = 0; j < matrix.cols(); j++ )
            {
                stream << matrix( i, j );
            }
        }

        success = true;

    }

    stream.close();

    return success;
}
