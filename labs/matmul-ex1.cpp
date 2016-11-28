#include <iostream>
#include <chrono>
#include <algorithm>

int main()
{
  std::size_t dim = 1024;
  
  float * A = new float[ dim * dim ];
  float * B = new float[ dim * dim ];
  float * C = new float[ dim * dim ];

  std::generate_n( A, dim * dim, []() { return std::rand()%5; } );
  std::generate_n( B, dim * dim, []() { return std::rand()%5; } );

  auto start = std::chrono::system_clock::now();

  // Pour chaque élément (i,j) de la matrice C on calcul le produit scalaire
  // de la ligne i par la colonne j.
  for( std::size_t i = 0 ; i < dim ; ++i )
  {
    for( std::size_t j = 0 ; j < dim ; ++j )
    {
      for( std::size_t k = 0 ; k < dim ; ++k )
      {
	C[ i * dim + j ] += A[ i * dim + k ] * B[ k * dim + j ]; 
      }
    }
  }

  auto stop = std::chrono::system_clock::now();

  std::cout <<
      std::chrono::duration_cast<std::chrono::milliseconds>( stop - start ).count()
       << "ms" << std::endl;

  delete [] A;
  delete [] B;
  delete [] C;

  return 0;
}
