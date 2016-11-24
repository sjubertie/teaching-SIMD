/**
 * Convert characters from lowercase to uppercase.
 * If a lowercase character is detected, set its 6th bit to 0 to convert
 * to uppercase (see ASCII table).
 */
#include <immintrin.h>

#include <iostream>
#include <algorithm>


int main()
{
  std::string s( "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam viverra luctus nibh vel turpis duis." );

  std::cout << s << std::endl;
  
  // Fill maska with 16x 'a', maskb with 16x 'b', mask32 with 16x 32.
  auto maska = _mm_set1_epi8( 'a' );
  auto maskz = _mm_set1_epi8( 'z' );
  auto mask32 = _mm_set1_epi8( 32 );
  
  std::size_t i = 0;
  for( ; i < s.size()/16 * 16 ; i+=16 )
  {
    // Unaligned load.
    auto r0 = _mm_loadu_si128( ( __m128i * )&s[ i ] );
    // It is also possible to provide an aligned allocator
    // to the string constructor to perform aligned loads.

    // maskaz contains 0x00 where character between 'a' and 'z', 0xff otherwise.
    auto maskaz = _mm_or_si128( _mm_cmplt_epi8( r0, maska ), _mm_cmpgt_epi8( r0, maskz ) );

    // Set the 6th bit to 0 only for lowercase characters.
    r0 = _mm_andnot_si128( _mm_andnot_si128( maskaz, mask32 ), r0 );

    _mm_storeu_si128( ( __m128i * )&s[ i ], r0 );
  }
  std::transform( begin(s), end( s ), begin( s ), (int (*)(int))std::toupper );

  std::cout << s << std::endl;
  
  return 0;
}
