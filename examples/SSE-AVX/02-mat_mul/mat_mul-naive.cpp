#include <mat_mul.hpp>


void mat_mul( matrix_f32 const & m_A,
              matrix_f32 const & m_B,
              matrix_f32 & m_C,
              std::size_t dim
            )
{
  #pragma omp parallel for
  for( std::size_t j = 0 ; j < dim ; ++j )
  {
    for( std::size_t i = 0 ; i < dim ; ++i )
    {
      for( std::size_t k = 0 ; k < dim ; ++k )
      {
        m_C[ j * dim + i ] += m_A[ j * dim + k ] * m_B[ k * dim + i ];
      }
    }
  }
}
