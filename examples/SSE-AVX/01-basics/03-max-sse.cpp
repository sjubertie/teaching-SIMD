/**
 * Find the max value in an array.
 */
#include <immintrin.h>

#include <iostream>
#include <algorithm>
#include <numeric>


int main()
{
  std::size_t const size = 103;

  float tmp[ 4 ] __attribute__((aligned(16)));
  float res;
  
  float * array = static_cast< float * >( _mm_malloc( size * sizeof( float ), 16 ) );

  std::generate_n( array, size, []() { return std::rand()%1000; } );

  std::size_t i = 0;

  if( size > 4 )
  {
    // Compute the max between 4 values at the same time.
    auto r0 = _mm_load_ps( &array[ 0 ] );

    for( std::size_t i = 4 ; i < size/4 * 4 ; i+=4 )
    {
      r0 = _mm_max_ps( r0, _mm_load_ps( &array[ i ] ) );
    }
    _mm_store_ps( tmp, r0 );

    // Compute the max between the last 4 values using the scalar max function.
    res = std::accumulate( tmp + 1, tmp + 4, tmp[ 0 ], []( float a, float b ) { return a > b ? a : b; } );

    // Compare remaining values.
    res = std::accumulate( array + i, array + size, res, []( float a, float b ) { return a > b ? a : b; } );
  }
  else
  {
    res = std::accumulate( array + 1, array + size, array[ 0 ], []( float a, float b ) { return a > b ? a : b; } );
  }

  // Result verification.
  if( res == std::accumulate( array + 1, array + size, array[ 0 ], []( float a, float b ) { return a > b ? a : b; } ) )
  {
    std::cout << "Success." << std::endl;
  }
  else
  {
    std::cout << "Error: incorrect result." << std::endl;
  }
  
  _mm_free( array );

  return 0;
}
