#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "matrix.h"



typedef std::vector<std::vector<double>> MAT2D;
typedef std::vector<double> VEC;






int main()
{
    MAT2D matrix_augmented = {
      {13, 4, 7, 9, 111},
      {10, 6, 5, 12, 118},
      {1, 8, 2, 16, 114},
      {3, 14, 15, 11, 163}
    };

    MAT2D matrix = {
      {13, 4, 7, 9},
      {10, 6, 5, 12},
      {1, 8, 2, 16},
      {3, 14, 15, 11}
    };

    Matrix mat(matrix_augmented);


    std::cout << "Original Matrix:" << std::endl;
    mat.Print();

    std::cout << "Upper Triangular Form: " << std::endl;
    mat.GaussPivotElim();

    mat.Print();
    std::cout << "new b vector is the last column of the above matrix " << std::endl << std::endl;

    VEC test = mat.BackSubstitution();

    std::cout << "x solution: " << std::endl;

    std::cout << "x1 = " << test.at(0) << std::endl;
    std::cout << "x2 = " << test.at(1) << std::endl;
    std::cout << "x3 = " << test.at(2) << std::endl;
    std::cout << "x4 = " << test.at(3) << std::endl;

    std::cout << "Determinant = " << mat.Determinant() << std::endl;










}
