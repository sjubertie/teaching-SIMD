#include <mat_mul.hpp>

#include <immintrin.h>


void mat_mul( matrix_f32 const & m_A,
	      matrix_f32 const & m_B,
	      matrix_f32 & m_C,
	      std::size_t dim
	    )
{
  #pragma omp parallel for
  for( std::size_t j = 0 ; j < dim ; ++j )
  {
    auto js = j * dim;

    for( std::size_t k = 0 ; k < dim ; ++k )
    {
      auto ks = k * dim;
      auto r1 = _mm256_set1_ps( m_A[ js + k ] );

      for( std::size_t i = 0 ; i < dim ; i+=8 )
      {
      	asm("#BEGIN");
	auto r3 = _mm256_load_ps( &m_C[ js + i ] );
	auto r2 = _mm256_load_ps( &m_B[ ks + i ] );
        r3 += r1 * r2;
        _mm256_store_ps( &m_C[ js + i ], r3 );
        asm("#END");
      }
    }
  }
}
