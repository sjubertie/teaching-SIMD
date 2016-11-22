/**
 * _mm_shuffle_ps.
 * 
 * Extract and combine 2 values from 2 registers.
 * 
 * Limitations:
 * - only mix 2 values from each input register: r0[ a ], r1[ b ], r1[ c ], r1[ d ]
 * - cannot interleave values from input registers: r0[ a ], r1[ b ], r0[ c ], r1[ c ]
 */
#include <immintrin.h>

#include <iostream>


int main()
{
  float v0[ 4 ] __attribute__(( aligned( 16 ) )) = { 0.0f, 1.0f, 2.0f, 3.0f };
  float v1[ 4 ] __attribute__(( aligned( 16 ) )) = { 4.0f, 5.0f, 6.0f, 7.0f };

  __m128 r0 = _mm_load_ps( v0 );
  __m128 r1 = _mm_load_ps( v1 );

  // Identity: r2 = r0.
  std::cout << "Identity:" << std::endl;
  auto r2 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 3, 2, 1, 0 ) );

  _mm_store_ps( v0, r2 );
  for( auto x: v0 ) { std::cout << x << ' '; }
  std::cout << std::endl;
  
  // Reverse r0
  std::cout << "Reverse r0:" << std::endl;
  r2 = _mm_shuffle_ps( r0, r0, _MM_SHUFFLE( 0, 1, 2, 3 ) );

  _mm_store_ps( v0, r2 );
  for( auto x: v0 ) { std::cout << x << ' '; }
  std::cout << std::endl;

  // Even: { r0[ 0 ], r0[ 2 ], r1[ 0 ], r1[ 2 ] }
  std::cout << "Even: { r0[ 0 ], r0[ 2 ], r1[ 0 ], r1[ 2 ] }" << std::endl;
  r2 = _mm_shuffle_ps( r0, r1, _MM_SHUFFLE( 2, 0, 2, 0 ) );

  _mm_store_ps( v0, r2 );
  for( auto x: v0 ) { std::cout << x << ' '; }
  std::cout << std::endl; 

  // Misc: { r0[ 3 ], r0[ 2 ], r1[ 2 ], r1[ 1 ] }
  std::cout << "Misc: { r0[ 3 ], r0[ 2 ], r1[ 2 ], r1[ 1 ] }" << std::endl;
  r2 = _mm_shuffle_ps( r0, r1, _MM_SHUFFLE( 1, 2, 2, 3 ) );

  _mm_store_ps( v0, r2 );
  for( auto x: v0 ) { std::cout << x << ' '; }
  std::cout << std::endl; 
  
  return 0;
}
