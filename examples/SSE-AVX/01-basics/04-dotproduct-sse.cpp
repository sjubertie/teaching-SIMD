/**
 * Dot product.
 */
#include <immintrin.h>

#include <iostream>
#include <algorithm>
#include <numeric>


int main()
{
  std::size_t const size = 107;

  float * array0 = static_cast< float * >( _mm_malloc( size * sizeof( float ), 16 ) );
  float * array1 = static_cast< float * >( _mm_malloc( size * sizeof( float ), 16 ) );
 
  std::generate_n( array0, size, []() { return std::rand()%10;} );
  std::generate_n( array1, size, []() { return std::rand()%10;} );

  float res = 0.0f;

  std::size_t i = 0;
  if( size > 4 )
  {
    auto r0 = _mm_mul_ps( _mm_load_ps( &array0[ 0 ] ), _mm_load_ps( &array1[ 0 ] ) );
  
    for( i = 4 ; i < size/4 * 4 ; i+=4 )
    {
      r0 = _mm_add_ps( r0, _mm_mul_ps( _mm_load_ps( &array0[ i ] ), _mm_load_ps( &array1[ i ] ) ) );
      // or: r0 += _mm_load_ps( &array0[ i ] ) * _mm_load_ps( &array1[ i ] );
    }

    float tmp[ 4 ] __attribute__((aligned(16)));
    _mm_store_ps( tmp, r0 );
    res = std::accumulate( tmp, tmp + 4, 0.0f );
  }
  res = std::inner_product( array0 + i, array0 + size, array1 + i, res );
  
  if( res == std::inner_product( array0, array0 + size, array1, 0.0f ) )
  {
    std::cout << "Success." << std::endl;
  }
  else
  {
    std::cerr << "Error." << std::endl;
  }
  
  _mm_free( array0 );
  _mm_free( array1 );

  return 0;
}
