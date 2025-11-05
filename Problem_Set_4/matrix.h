#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
typedef std::vector<std::vector<double>> MAT2D;
typedef std::vector<double> VEC;

//helper fuction
void swap(VEC& input, int i, int j)
{
    double temp = input.at(i);
    input.at(i) = input.at(j);
    input.at(j) = temp;
}



//operator overloading
VEC operator+(VEC a, VEC b)
{
    VEC result;

    for (int i = 0; i < a.size(); i++)
    {
        result.push_back(a.at(i) + b.at(i));
    }

    return result;
}

VEC operator-(VEC a, VEC b)
{
    VEC result;

    for (int i = 0; i < a.size(); i++)
    {
        result.push_back(a.at(i) - b.at(i));
    }

    return result;
}

VEC operator*(double b, VEC a)
{
    VEC result;

    for (double i : a)
    {
        result.push_back(i * b);
    }

    return result;
}

class Matrix
{
protected:
    
public:
    MAT2D matrix;
    //the multipliers used in finding upper triangular matrix to use to find the lower triangular matrix
    VEC multies;

    Matrix(MAT2D input) : matrix(input) {};

    double MaxColumnIndex(int row, int column);

    void SwitchRows(int row1, int row2);

    int row_swap_count = 0;

    void Print();

    void SetRow(int row, VEC input);

    void SetColumn(int column, VEC input);

    void SetIndex(double value, int i, int j) { matrix[i][j] = value; }

    Matrix GaussPivotElim(VEC b);

    VEC BackSubstitution(VEC b, bool append);

    VEC ForwardSubstitution(VEC b);

    double Determinant();

    Matrix UpperTriangular();

    Matrix LowerTriangular();

    VEC SolveMat(VEC b);
    
       
    //returns a vector of the the specified row
    VEC row(int row);
    
    double no_rows(){ return this->matrix.size(); }
    double no_columns(){ return this->matrix.at(0).size() - 1; }
    double at(int i, int j){ return this->matrix[i][j];}
};

//this returns the row index of the maximum element below a specified matrix coordinate
double Matrix::MaxColumnIndex(int row, int column)
{
    MAT2D input = this->matrix;
    std::vector<double> values;

    for (int k = row; k < input.size(); k++)
        values.push_back(input[k][column]);

    double max_value = values.at(0);
    int max_index = 0;

    for (int i = 1; i < values.size(); i++)
    {
        if (values.at(i) > max_value)
        {
            max_value = values.at(i);
            max_index = i;
        }
    }

    return max_index + row;
}

void Matrix::SwitchRows(int row1, int row2)
{
    MAT2D& mat = this->matrix;
    std::vector<double> temp = mat.at(row1);

    mat.at(row1) = mat.at(row2);
    mat.at(row2) = temp;
}

void Matrix::SetRow(int row, VEC input)
{
    this->matrix.at(row) = input;
}

void Matrix::SetColumn(int column, VEC input)
{
    MAT2D& mat = this->matrix;

    for (int i = 0; i < mat.size(); i++)
    {
        mat[i][column] = input.at(i);
    }

}


VEC Matrix::row(int row)
{
    return this->matrix.at(row);
}


void Matrix::Print() {
    MAT2D& v = this->matrix;
    // Traversing the 2D vector
    for (VEC& i : v) {
        for (double& j : i) {
            std::cout << std::setw(12) << j;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Matrix Matrix::GaussPivotElim(VEC b)
{
    Matrix& mat = *this;

    //augement the input vector b to the end of the input matrix

    for (int i = 0; i < mat.no_rows(); i++)
    {
        mat.matrix.at(i).push_back(b.at(i));
    }

    double pivot_row = 0;

    for (int k = 0; k < mat.no_columns(); k++)
    {
        //performing the pivoting
        if (mat.MaxColumnIndex(pivot_row, k) != pivot_row)
        {
            mat.SwitchRows(pivot_row, mat.MaxColumnIndex(pivot_row, k));

            //record the swap in the row swap counter in order to later determine the sign of the determinant
            mat.row_swap_count++;
        }

        for (int j = pivot_row; j < mat.no_rows() - 1; j++)
        {
            double multiplier = (mat.at(j + 1, k)) / mat.at(pivot_row, k);

            VEC temp = multiplier * mat.row(pivot_row);

            VEC newrow = mat.row(j + 1) - multiplier * mat.row(pivot_row);

            mat.SetRow(j + 1, newrow);
        }

        pivot_row++;
    }

    return mat;

}



VEC Matrix::BackSubstitution(VEC b, bool append)
{
    Matrix& mat = *this;

    //augement the input vector b to the end of the matrix

    if (append)
    {
        for (int i = 0; i < mat.no_rows(); i++)
        {
            mat.matrix.at(i).push_back(b.at(i));
        }
    }


    int last_row_index = mat.no_rows() - 1;
    int last_column_index = mat.no_columns() - 1;

    VEC solutions;

    for (int i = 0; i <= last_row_index; i++)
    {
        solutions.push_back(0);
    }

    solutions.at(last_row_index) = mat.at(last_row_index, last_column_index + 1) / mat.at(last_row_index, last_column_index);

    for (int i = last_row_index - 1; i >= 0; i--)
    {
        double sum = 0;

        for (int j = i + 1; j <= last_row_index; j++)
            sum += mat.at(i, j) * solutions.at(j);

        solutions.at(i) = (mat.at(i, last_column_index + 1) - sum) / mat.at(i, i);
    }

    return solutions;

}

VEC Matrix::ForwardSubstitution(VEC b)
{
    Matrix& mat = *this;

    //augement the input vector b to the end of the input matrix

    for (int i = 0; i < mat.no_rows(); i++)
    {
        mat.matrix.at(i).push_back(b.at(i));
    }

    int last_row_index = mat.no_rows() - 1;
    int last_column_index = mat.no_columns() - 1;

    VEC solutions;

    for (int i = 0; i <= last_row_index; i++)
    {
        solutions.push_back(0);
    }

    solutions.at(0) = mat.at(0, last_column_index + 1) / mat.at(0, 0);

    for (int i = 1; i < mat.no_rows(); i++)
    {
        double sum = 0;

        for (int j = 0; j <= last_column_index - 1; j++)
            sum += mat.at(i, j) * solutions.at(j);

        solutions.at(i) = (mat.at(i, last_column_index + 1) - sum) / mat.at(i, i);
    }

    return solutions;
}

VEC Matrix::SolveMat(VEC b)
{
    Matrix mat = *this;

    MAT2D temp = this->matrix;

    this->GaussPivotElim(b);

    
    
    VEC solution = this->BackSubstitution(b, false);

    this->matrix = temp;

    return solution;

}

double Matrix::Determinant()
{
    Matrix& mat = *this;

    double determinant = mat.at(0,0);

    for (int i = 1; i < mat.no_rows(); i++)
    {
        determinant *= mat.at(i, i);
    }

    //if row_swap_count is odd set negative determinant
    double result = (mat.row_swap_count % 2 == 0) ? determinant : -determinant;

    return result;
}



Matrix Matrix::UpperTriangular()
{
    Matrix& mat = *this;
    int pivot_row = 0;

    for (int k = 0; k < mat.no_columns(); k++)
    {
      

        for (int j = pivot_row; j < mat.no_rows() - 1; j++)
        {
            double multiplier = (mat.at(j + 1, k)) / mat.at(pivot_row, k);

            //save the multipler to use later for lower triangular matrix
            mat.multies.push_back(multiplier);

            VEC temp = multiplier * mat.row(pivot_row);
            VEC newrow = mat.row(j + 1) - multiplier * mat.row(pivot_row);
            mat.SetRow(j + 1, newrow);
        }

        pivot_row++;
    }

    

    return mat;
}




Matrix Matrix::LowerTriangular()
{
    VEC columns;
    VEC rows;

    //make a new zero matrix of the size of the class matrix

    for (int i = 0; i < this->no_rows(); i++)
    {
        rows.push_back(0);
    }

    for (int i = 0; i < this->no_columns(); i++)
    {
        columns.push_back(0);
    }

    MAT2D mat0;

    for (int i = 0; i < this->no_rows(); i++)
        mat0.push_back(rows);
    
    //set the new zero matrix to the class matrix
    this->matrix = mat0;

    Matrix& mat = *this;

    int last_row_index = mat.no_rows() - 1;
    int last_column_index = mat.no_columns();

    //to record the current index of the mulites being read
    int multies_index = 0;

    int i = 0;

    for (int j = 0; j <= last_column_index; j++)
    {
        
            mat.SetIndex(1, i, j);

            for (int k = i + 1; k <= last_row_index; k++)
            {
                mat.SetIndex(multies.at(multies_index), k, j);
                multies_index++;
            }
            i++;
    }

    
    return mat;
}

