#include <iostream>

using namespace std;

const int MAXN = 100;

const int MAXSIZE = 100;

void printmatrix(double mat[4][5], int n)
{
     for(int a = 0; a < 4; a++)
  {
    for(int b = 0; b < 5; b++)
    {
      cout << mat[a][b] << " ";
    }
    cout << endl;
  }  
}

void partial_pivot(double A[4][5], int n) {
    for (int i = 0; i < n; i++) {
        int pivot_row = i;
        for (int j = i+1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivot_row][i])) {
                pivot_row = j;
            }
        }
        if (pivot_row != i) {
            for (int j = i; j <= n; j++) {
                swap(A[i][j], A[pivot_row][j]);
            }
        }
        for (int j = i+1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k <= n; k++) {
                A[j][k] -= factor * A[i][k];
            }
        }
    }
}










int main()
{
  double matrix[4][5] = {
    {13, 4, 7, 9, 111},
    {10, 6, 5, 12, 118},
    {1, 8, 2, 16, 114},
    {3, 14, 15, 11, 163}
  };


  partial_pivot(matrix, 4);

  printmatrix(matrix, 4);

  

  














 
}
