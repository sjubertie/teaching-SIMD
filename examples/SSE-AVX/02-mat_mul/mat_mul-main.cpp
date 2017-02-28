#include <iostream>
#include <chrono>
#include <vector>

#include <mat_mul.hpp>



int main( int argc, char * argv[] )
{
  std::size_t size = 2048;

  if( argc > 1 )
  {
    try
    {
      size = std::stoull( argv[ 1 ] );
    }
    catch( ... )
    {
      std::cerr << "Exception: std::stoull invalid argument or out of range value - setting size to default.\n";
    }
  }

  matrix_f32 m_A( size * size );
  matrix_f32 m_B( size * size );
  matrix_f32 m_C( size * size );

  std::fill( begin(m_A), end(m_A), 1.0f);
  std::fill( begin(m_B), end(m_B), 1.0f);

  auto start = std::chrono::system_clock::now();

  mat_mul( m_A, m_B, m_C, size );

  auto stop = std::chrono::system_clock::now();

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop -start).count() << "ms\n";
  /*
  for( std::size_t j = 0 ; j < size ; ++j )
  {
    for( std::size_t i = 0 ; i < size ; ++i )
    {
      std::cout << m_C[ j * size + i ] << ' ';
    }
    std::cout << std::endl;
  }
  */
  return 0;
}
