#pragma once

#include <cstddef>
#include <vector>

namespace test::Util
{

template< typename DataType = double >
class Matrix
{
public:
    Matrix( std::size_t const rows, std::size_t const cols ) : rows_{ rows }, cols_{ cols }, data_( rows * cols ) {};

    inline DataType & operator()( std::size_t const row, std::size_t const col )
    {
        return data_[ row * cols_ + col ];
    }

    inline DataType operator()( std::size_t const row, std::size_t const col ) const
    {
        return data_[ row * cols_ + col ];
    }

    inline std::size_t rows() const { return rows_; }
    inline std::size_t cols() const { return cols_; }

private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector< DataType > data_;
};

}