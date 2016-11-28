#include <iostream>
#include <chrono>
#include <algorithm>
#include <cmath>

int main()
{
  std::size_t dim = 1024;
  
  float * A = new float[ dim * dim ];
  float * B = new float[ dim * dim ];
  float * C = new float[ dim * dim ];

  std::generate_n( A, dim * dim, []() { return std::rand()%5; } );
  std::generate_n( B, dim * dim, []() { return std::rand()%5; } );

  std::cout << "Computing AxB..." << std::endl;
  
  auto start = std::chrono::system_clock::now();

  // Your code between here...



  
  // and here.

  auto stop = std::chrono::system_clock::now();

  std::cout <<
      std::chrono::duration_cast<std::chrono::milliseconds>( stop - start ).count()
       << "ms" << std::endl;

  std::cout << "Checking results..." << std::endl;
  
  for( std::size_t i = 0 ; i < dim ; ++i )
  {
    for( std::size_t j = 0 ; j < dim ; ++j )
    {
      auto tmp = 0.0f;
      for( std::size_t k = 0 ; k < dim ; ++k )
      {
	tmp += A[ i * dim + k ] * B[ k * dim + j ]; 
      }
      if( tmp != C[ i * dim + j ] )
      {
	std::cout << "Value at [ " << i << ", " << j << " ] differs " << std::abs( tmp - C[ i * dim + j ] ) << std::endl;
      }
    }
  }

  delete [] A;
  delete [] B;
  delete [] C;

  return 0;
}
