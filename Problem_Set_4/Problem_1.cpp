#include <iostream>
#include <vector>
#include <fstream>

#include <iomanip>

#include "matrix.h"

#define LINEBREAK std::cout << "\n\n---------------------------------------------------------------------------------------------\n\n";

typedef std::vector<std::vector<double>> MAT2D;
typedef std::vector<double> VEC;

int main()
{
  
    MAT2D matrix = {
      {13, 4, 7, 9},
      {10, 6, 5, 12},
      {1, 8, 2, 16},
      {3, 14, 15, 11}
    };

    Matrix mat(matrix);

    std::cout << "Part (a)" << "\n\n";
    
    VEC b = { 111, 118, 114, 163 };

    std::cout << "Original Matrix" << "\n";
    mat.Print();

    std::cout << "Upper Triangular Form Augmented: " << "\n";
    mat.GaussPivotElim(b);

    mat.Print();
    std::cout << "b = " << "<" << mat.at(0,4) << ", " << mat.at(1, 4) << ", " << mat.at(2, 4) << ", " << mat.at(3, 4) << ">" << "\n\n";

    VEC solutions = mat.BackSubstitution(b, false);

    std::cout << "x solution: " << std::endl;

    for (int i = 0; i < solutions.size(); i++)
        std::cout << "x" << i + 1 << " = " << solutions.at(i) << "\n";

    std::cout << std::endl;
    std::cout << "Determinant = " << mat.Determinant();

    LINEBREAK

    //----------------------------------------------------------------------------------------------------------------------------
    //Part (b) ------------------------------------------------------------------------------------------------------------------\\
    //------------------------------------------------------------------------------------------------------------------------------

    std::cout << "Part (b): LU Decomposition" << "\n\n";

    Matrix mat2(matrix);

    //save the upper triangular matrix in another matrix
    Matrix upper_triangular(mat2.UpperTriangular());

    std::cout << "Upper Triangular:" << "\n";
    upper_triangular.Print();

    std::cout << "Lower Triangular:" << "\n";

    //save the lower triangular matrix in another matrix
    Matrix lower_triangular(mat2.LowerTriangular());

    lower_triangular.Print();

    b = { 111,118,114,163 };

    VEC Z = lower_triangular.ForwardSubstitution(b);

    solutions = upper_triangular.BackSubstitution(Z, true);
    
    std::cout << "x solution via LU decomposition: " << std::endl;

    for (int i = 0; i < solutions.size(); i++)
        std::cout << "x" << i + 1 << " = " << solutions.at(i) << "\n";
 
    Matrix inverse(matrix);
        
    //finding inverse. Each I1, I2... denotes a column of the inverse matrix I 
    //Defining columns of the identity matrix ID
    VEC ID1 = { 1, 0, 0, 0 };
    VEC ID2 = { 0, 1, 0, 0 };
    VEC ID3= { 0, 0, 1, 0 };
    VEC ID4 = { 0, 0, 0, 1 };

    //find the the solution to each column of the inverse matrix by solving the original matrix with columns of the identity matrix

    VEC I1 = inverse.SolveMat(ID1);
    VEC I2 = inverse.SolveMat(ID2);
    VEC I3 = inverse.SolveMat(ID3);
    VEC I4 = inverse.SolveMat(ID4);

    inverse.SetColumn(0, I1);
    inverse.SetColumn(1, I2);
    inverse.SetColumn(2, I3);
    inverse.SetColumn(3, I4);

    std::cout << "\n" << "Inverse Matrix: " << "\n";

    inverse.Print();

}