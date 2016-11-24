/**
 * Add two arrays.
 */
#include <immintrin.h>

#include <iostream>
#include <algorithm>


int main()
{
  std::size_t const size = 99;

  float * array0 = static_cast< float * >( _mm_malloc( size * sizeof( float ), 16 ) );
  float * array1 = static_cast< float * >( _mm_malloc( size * sizeof( float ), 16 ) );
  float * array2 = static_cast< float * >( _mm_malloc( size * sizeof( float ), 16 ) );
 
  std::generate_n( array0, size, []() { return std::rand()%100;} );
  std::generate_n( array1, size, []() { return std::rand()%100;} );

  std::size_t i = 0;
  for( ; i < size/4 * 4 ; i+=4 )
  {
    auto r0 = _mm_add_ps( _mm_load_ps( &array0[ i ] ), _mm_load_ps( &array1[ i ] ) );
    _mm_store_ps( &array2[ i ], r0 );
  }
  // Add remaining values if any.
  std::transform( array0 + i, array0 + size, array1 + i, array2 + i, std::plus<float>() );

  // array1 = array0 + array1.
  std::transform( array0, array0 + size, array1, array1, std::plus<float>() );

  // array2 == array1 ?
  if( std::equal( array2, array2 + size, array1 ) )
  {
    std::cout << "Success." << std::endl;
  }
  else
  {
    std::cerr << "Error." << std::endl;
  }
  
  _mm_free( array0 );
  _mm_free( array1 );
  _mm_free( array2 );

  return 0;
}
