#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
typedef std::vector<std::vector<double>> MAT2D;
typedef std::vector<double> VEC;
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
    MAT2D matrix;

public:

    Matrix(MAT2D input) : matrix(input) {};

    double MaxColumnIndex(int row, int column);

    void SwitchRows(int row1, int row2);

    bool negative_determinant = false;

    void Print();

    void SetRow(int row, VEC input);

    Matrix GaussPivotElim();

    VEC BackSubstitution();

    double Determinant();

    //returns a vector of the the specified row
    VEC row(int row);
    
    double no_rows()
    {
        return this->matrix.size();
    }

    double no_columns()
    {
        return this->matrix.at(0).size() - 1;
    }

    double at(int i, int j)
    {
        return this->matrix[i][j];
    }
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

VEC Matrix::row(int row)
{
    return this->matrix.at(row);
}


void Matrix::Print() {
    MAT2D& v = this->matrix;
    // Traversing the 2D vector
    for (VEC& i : v) {
        for (double& j : i) {
            std::cout << std::setw(10) << j;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Matrix Matrix::GaussPivotElim()
{
    Matrix& mat = *this;
    double pivot_row = 0;

    for (int k = 0; k < mat.no_columns(); k++)
    {
        //performing the pivoting
        if (mat.MaxColumnIndex(pivot_row, k) != pivot_row)
        {
            mat.SwitchRows(pivot_row, mat.MaxColumnIndex(pivot_row, k));

            //setting the determinant negative as a row exchange has occured
            mat.negative_determinant = true;
        }

        for (int j = pivot_row; j < mat.no_rows() - 1; j++)
        {
            double multiplier = (mat.at(j + 1, k)) / mat.at(pivot_row, k);

            VEC temp = multiplier * mat.row(pivot_row);

            VEC newrow = temp - mat.row(j + 1);

            mat.SetRow(j + 1, newrow);
        }

        pivot_row++;
    }

    return mat;

}

VEC Matrix::BackSubstitution()
{
    Matrix& mat = *this;

    VEC result;

    double x1, x2, x3, x4;

    x4 = mat.at(3, 4) / mat.at(3, 3);

    x3 = (mat.at(2, 4) - x4 * mat.at(2, 3)) / mat.at(2, 2);

    x2 = (mat.at(1, 4) - x4 * mat.at(1, 3) - x3 * mat.at(1,2)) / mat.at(1, 1);

    x1 = (mat.at(0, 4) - x4 * mat.at(0, 3) - x3 * mat.at(0,2) - x2 * mat.at(0,1)) / mat.at(0, 0);

    result = { x1, x2, x3, x4 };

    return result;
}

double Matrix::Determinant()
{
    Matrix& mat = *this;

    double determinant = mat.at(0,0);

    for (int i = 1; i < mat.no_rows(); i++)
    {
        determinant *= mat.at(i, i);
    }

    double result = (mat.negative_determinant) ? -determinant : determinant;

    return result;
}



