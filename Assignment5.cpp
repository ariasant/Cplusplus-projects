// PHYS 30762 Programming in C++
// ------------------------------------------------------------------------------------------------------
// Assignment5.cpp
// This program creates a class for handling matrices. Basic algebraic operations and the 
// insertion and extraction operators are overloaded. It is also possible to calculate the 
// determinant of a square matrix using the method of expansion by minors.
// ------------------------------------------------------------------------------------------------------
// Andrea Sante, last updated: 01/04/2022.
// ------------------------------------------------------------------------------------------------------

#include<iostream>
#include<math.h>


class matrix 
{
// Friend functions to overload >> and << operators
friend std::ostream & operator<<(std::ostream &os, const matrix &M);
friend std::istream & operator>>(std::istream &is, const matrix &M);

private:

    // Number of rows in matrix
    int dimension1{};
    // Number of columns in matrix 
    int dimension2{};
    // Pointer to the elements in the matrix
    double * array{nullptr};

public:

    // Default constructor
    matrix(); 
    // Parameterised constructor                         
    matrix(int, int);  
    // Copy constructor                 
    matrix(matrix const&); 
    // Move constructor
    matrix(matrix&& M);
    // Destructor 
    ~matrix();  

    // Copy assignment             
    matrix& operator = (matrix const&);
    // Move assignment 
    matrix& operator=(matrix&& M);
    // Define elements of matrix using an array of doubles as input
    matrix& operator=(double elements[]);
    
    // Defining indexing operator
    double& operator()(int, int);
    // Overloading + operator  
    matrix operator+ (const matrix&M) const;
    // Overloading - operator
    matrix operator- (const matrix&M) const;
    // Overloading * operator 
    matrix operator* (const matrix&M) const;
    matrix operator* (double scalar);
    // Function to delete ith row and jth column 
    matrix delete_row_and_column(int i, int j);
    // Function to calculate determinant of square matrices
    double determinant() const;

};



// Default constructor 
matrix::matrix()
{
    // Create a 1x1 matrix by default
    dimension1 = 1;
    dimension2 = 1;
    array = new double[dimension1*dimension2];
}            
// Parameterised constructor 
matrix::matrix(int i, int j) 
{
    dimension1 = i;
    dimension2 = j;
    array = new double[dimension1*dimension2];
}
// Copy constructor 
matrix::matrix(matrix const& matrix_cp)
{
    dimension1 = matrix_cp.dimension1;
    dimension2 = matrix_cp.dimension2;
    // Allocate memory
    array = new double[dimension1*dimension2];
    // Deep copy
    for (int i{0};i<dimension1*dimension2;++i)
    {
        array[i] = matrix_cp.array[i];
    }
}
// Move constructor
matrix::matrix(matrix&& M) : array(M.array) 
{
    // Avoid undefined behaviour when deleting M
    M.array=nullptr;
}
// Destructor
matrix::~matrix(){delete array;}


// Copy assignment 
matrix& matrix::operator= (matrix const& matrix_rhs)
{
    double* const data_to_copy = matrix_rhs.array;
    int n_rows {matrix_rhs.dimension1};
    int n_columns {matrix_rhs.dimension2};

    // Deals with self-assignment
    if (data_to_copy!=array)
    {
        // Free memory by deleting old data
        delete [] array;
        // Assign memory to new data
        array = new double [n_rows*n_columns];
        dimension1 = n_rows;
        dimension2 = n_columns;

        for (int i{0};i<n_rows*n_columns;++i)
        { // Deep copy
        array[i] = data_to_copy[i];
    }
  }
  return *this;  
}

// Move assignment
matrix& matrix::operator= (matrix&& M)
{
    // Self-assignment detection
	if (&M == this) {return *this;}
	// Release any rhold resource
	delete array;
	// Transfer ownership of data
	array = M.array;
    // Avoid undefined behaviour when deleting M
	M.array = nullptr; 
	return *this;
}

// Assign elements to matrix using = and an array of doubles
matrix& matrix::operator=(double elements[])
{
    for (int i{0};i<dimension1*dimension2;++i)
    {
      array[i] = elements[i];
    }
    return *this;
}


// Defining indexing operator
double& matrix::operator()(int i, int j) 
{
    return array[i*dimension1+j];
}

// Overloading + operator
matrix matrix::operator+(const matrix&M) const 
{
    // Initialising a sum matrix with same dimension as the two matrices
    matrix sum{dimension1,dimension2};
    // Checking that the two matrices have same dimensions
    if (dimension1 != M.dimension1 || dimension2 != M.dimension2)
    {
        std::cout<<"Error. Cannot add the two matrices."<<std::endl;
    }
    else
    {
        for (int i{0};i<dimension1*dimension2;++i)
        {
            // Sum the two matrices element-wise
            sum.array[i] = array[i]+M.array[i];
        }
    }
    return sum;
}

// Overloading - operator
matrix matrix::operator-(const matrix&M) const 
{
    // Initialising a matrix with same dimension as the two matrices
    matrix difference{dimension1,dimension2};
    // Checking that the two matrices have same dimensions
    if (dimension1 != M.dimension1 || dimension2 != M.dimension2)
    {
        std::cout<<"Error. Cannot add the two matrices."<<std::endl;
    }
    else
    {
        for (int i{0};i<dimension1*dimension2;++i)
        {
            // Subtract the two matrices element-wise
            difference.array[i] = array[i]-M.array[i];
        }
    }
    return difference;
}

// Overloading * operator for matrix multiplication
matrix matrix::operator*(const matrix&M) const
{
    // Initialising a product matrix with adequate dimension as the first matrix
    matrix product{dimension1,M.dimension2};
    // Checking that if the product between the two matrices is possible
    if (dimension2==M.dimension1)
    { 
        // Implementing matrix multiplication as in 
        // https://stackoverflow.com/questions/10252621/matrix-multiplication-using-1d-arrays
        for (int i{0};i<dimension1;++i)
        {
            for (int j{0};j<M.dimension2;++j)
            {
                double sum{};
                for (int k{0};k<M.dimension2;++k)
                {
                    sum += array[i*dimension2+k] * M.array[k*M.dimension2+j];
                    product.array[i*product.dimension2+j] = sum;
                }
            }
        }
    }
    else
    {
        std::cout<<"Error. Cannot multiply the two matrices together."<<std::endl;
    }
    return product;
}
// Multiplication of a matrix by a scalar
matrix matrix::operator* (double scalar)
{
    // Initialising a product matrix with adequate dimension as the first matrix
    matrix product{dimension1, dimension2};
    for (int i{0};i<dimension1*dimension2;++i)
    {
        product.array[i] = scalar*array[i];
    }
    return product;
}

// Function to delete ith row and jth column (first row/column corresponds to i/j=0)
matrix matrix::delete_row_and_column (int i, int j)
{   // Copy old data
    double* old_data = array;
    // Define new matrix with m-1 rows and n-1 columns
    matrix M{dimension1-1, dimension2-1};
    // Iterator used to assign elements to M
    int idx{0};
    // Deleting elements in row i
    for (int n{0}; n<(dimension1)*(dimension2); ++n)
    {
        // Copying old data into new matrix up to ith row 
        if (n<dimension2*i)
        {
            // Copy elements in row that are not in jth column
            if ((n+dimension2)%dimension2!=j)
            {
                M.array[idx]=array[n];
                ++idx;
            } 
        }
        // Copying old data into new matrix after ith row 
        else if (n>=dimension2*i+dimension2)
        {
            // Copy elements in row that are not in jth column
            if (n%dimension2!=j)
            {
                M.array[idx]=array[n];
                ++idx;
            }
        }    
    }
    return M;
}

// Function to calculate determinant of square matrices
double matrix::determinant() const
{
    int n_rows{dimension1};
    int n_columns{dimension2};
    
    // Crete a copy of the matrix to work with
    matrix M{*this};
    
    double determinant_M{};
    // Check whether matrix is a square matrix
    if (n_rows==n_columns)
    {
        // For a 1x1 matrix
        if (n_rows==1) {determinant_M = M.array[0];}
        // For a 2x2 matrix
        if (n_rows==2) {determinant_M = M.array[0]*M.array[3]-M.array[1]*M.array[2];}
        // For a nxn matrix
        else
        {
            for (int i{0};i<n_columns;++i)
            {
                matrix minor_of_M{M.delete_row_and_column(0,i)};
                // Calculate determinant using expansion by minors
                determinant_M += pow(-1,i)*M.array[i]*minor_of_M.determinant();
            }
        }
    }
    else
    // If not a square matrix
    {
        std::cout<<"Cannot compute determinant."<<std::endl;
    }
    return determinant_M;
}


// Function to overload << operator for matrices
std::ostream & operator<<(std::ostream &os, const matrix &M) 
{
    int n_rows {M.dimension1};
    int n_columns {M.dimension2};
    double* element {M.array};
  
    for (int i{1};i<=n_rows;++i)
    {
        // Print each element in a row
        for (int j{1};j<=n_columns;++j)
        {
            // Add borders to delimit matrix in scope
            if (j==1) {os<<"| "<<element[(i-1)*n_columns+(j-1)]<<"\t";}
            else if (j==n_columns) {os<<element[(i-1)*n_columns+(j-1)]<<" |\n";}
            else {os<<element[(i-1)*n_columns+(j-1)]<<"\t";} 
        }
    }
    return os;
}

// Function to overload >> operator for matrices
std::istream & operator>>(std::istream &is, matrix &M) 
{
    int n_rows{};
    int n_columns{};
    // Ask user to input matrix dimensions
    std::cout<<"Enter number of rows: ";
    std::cin>>n_rows;
    std::cout<<"Enter number of columns: ";
    std::cin>>n_columns;
    // Create a matrix to store input values
    matrix M_input{n_rows, n_columns};
    double array_elements [n_rows*n_columns];
    for (int i{1};i<=n_rows;++i)
    {
        for (int j{1};j<=n_columns;++j)
        {
            std::cout<<"Enter matrix element ("<<i<<","<<j<<") : ";
            // Assign element to array
            is>>array_elements[(i-1)*n_columns+(j-1)];
        }
    }
    // Assign input values to input matrix and deep copy into original matrix
    M_input = array_elements;
    M = M_input;
    return is;
}

int main()
{
    // Initialise matrices A, B, and C:
    // 
    //      | 1  2  3 |      | 5  5  4 | 
    //  A = | 9  8  7 |  B = | 1  2  3 |  C = | 3  4  1 |
    //      | 4  2  6 |      | 6  9  8 |      | 2  5  6 |
    // 
    double elements_A[] = {1,2,3,9,8,7,4,2,6};
    double elements_B[] = {5,5,4,1,2,3,6,9,8};
    double elements_C[] = {3,4,1,2,5,6};
    matrix A{3,3};
    matrix B{3,3};
    matrix C{2,3};
    A = elements_A;
    B = elements_B;
    C = elements_C;

    // Print the three matrices
    std::cout<<"Matrix A: "<<std::endl;
    std::cout<<A<<std::endl;
    std::cout<<"Matrix B: "<<std::endl;
    std::cout<<B<<std::endl;
    std::cout<<"Matrix C: "<<std::endl;
    std::cout<<C<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    // Demonstrate use of operators with matrices
    matrix sum_AB{A+B};
    std::cout<<"A+B: "<<std::endl;
    std::cout<<sum_AB<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    matrix difference_AB{A-B};
    std::cout<<"A-B: "<<std::endl;
    std::cout<<difference_AB<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    matrix A_times_B{A*B};
    std::cout<<"A*B: "<<std::endl;
    std::cout<<A_times_B<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    matrix C_times_B{C*B};
    std::cout<<"C*B: "<<std::endl;
    std::cout<<C_times_B<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    matrix B_times_C{B*C};
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Determinant of A:"<<A.determinant()<<std::endl;
    std::cout<<"Determinant of B:"<<B.determinant()<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    // Use copy assignment on A
    A = A;
    // Use copy assignment on C
    C = A;
    // Use copy constructor
    matrix copy_A{A};

    std::cout<<"Matrix A: "<<std::endl;
    std::cout<<A<<std::endl;
    std::cout<<"Matrix copy_A: "<<std::endl;
    std::cout<<copy_A<<std::endl;
    std::cout<<"Matrix copy_A*3: "<<std::endl;
    std::cout<<copy_A*3<<std::endl;
    std::cout<<"Matrix C=A: "<<std::endl;
    std::cout<<C<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Matrix A: "<<std::endl;
    std::cout<<A<<std::endl;
  
    // Allow user to enter a matrix
    std::cout<<"Create your own matrix."<<std::endl;
    matrix M{};
    std::cin>>M;
    std::cout<<M<<std::endl;
    std::cout<<M.determinant();
    return 0;
}