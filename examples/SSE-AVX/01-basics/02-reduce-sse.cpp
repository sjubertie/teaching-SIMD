/**
 * Add all the values off an array.
 */
#include <immintrin.h>

#include <iostream>
#include <algorithm>
#include <numeric>


int main()
{
  std::size_t const size = 102;

  float res = 0.0f;
  float tmp[ 4 ] __attribute__((aligned(16)));
  
  float * array = static_cast< float * >( _mm_malloc( size * sizeof( float ), 16 ) );

  std::generate_n( array, size, []() { return std::rand()%10;} );

  std::size_t i = 0;
  
  if( size > 4 )
  {
    // Add 4 values at the same time.
    auto r0 = _mm_load_ps( &array[ 0 ] );

    for( i = 4 ; i < size/4 * 4 ; i+=4 )
    {
      r0 = _mm_add_ps( r0, _mm_load_ps( &array[ i ] ) );
      // It is also possible to write: r0 += _mm_load_ps( &array[ i ] ).
    }
    _mm_store_ps( tmp, r0 );
    res = std::accumulate( tmp, tmp + 4, 0.0f );
  }
  // Add remaining values if size not a multiple of 4.
  res = std::accumulate( array + i, array + size, res );

  // Result verification.
  if( res == std::accumulate( array, array + size, 0.0f ) )
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
