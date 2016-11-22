/**
 * Copy float values from an array to another.
 */
#include <immintrin.h>

#include <iostream>
#include <algorithm>
#include <cassert>


int main()
{
  std::size_t const size = 101;
  
  float * array0 = static_cast< float * >( _mm_malloc( size * sizeof( float ), 32 ) );
  float * array1 = static_cast< float * >( _mm_malloc( size * sizeof( float ), 32 ) );

  std::generate_n( array0, size, [](){ return std::rand() % 10; } );

  std::size_t i = 0;
  // Copy by 8 floats.
  for( ; i < size / 8 * 8 ; i+=8 )
  {
    _mm256_store_ps( &array1[ i ], _mm256_load_ps( &array0[ i ] ) );
  }
  // Copy the remaining floats when size is not a multiple of 8.
  for( ; i < size ; ++i )
  {
    array1[ i ] = array0[ i ];
  }
  
  if( std::equal( array0, array0 + size, array1 ) )
  {
    std::cout << "Copy successful." << std::endl;
  }
  else
  {
    std::cerr << "Error: incorrect copy." << std::endl;
  }
  
  _mm_free( array0 );
  _mm_free( array1 );

  return 0;
}
