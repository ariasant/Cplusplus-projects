// PHYS 30762 Programming in C++
// ------------------------------------------------------------------------------------------------------
// Assignment4.cpp
// This program creates a class for handling complex numbers. Basic algebraic operations and the 
// insertion and extraction operators are overloaded.
// ------------------------------------------------------------------------------------------------------
// Andrea Sante, last updated: 18/03/2022.
// ------------------------------------------------------------------------------------------------------

#include <iostream>
#include <math.h>
#include <string>
#include <sstream>

class complex_number
{
// Friend functions to overload >> and << operators
friend std::ostream & operator<<(std::ostream &os, const complex_number &z);
friend std::istream & operator>>(std::istream &os, const complex_number &z);
private:
    double real_part{};
    double imaginary_part{};
public:
    // Default constructor
    complex_number() = default;
    // Parameterised constructor
    complex_number(double real_component, double imaginary_component)
    {
        real_part = real_component;
        imaginary_part = imaginary_component;
    }
    // Parameterised constructor for a real number
    complex_number(double real_number)
    {
        real_part = real_number;
        imaginary_part = 0;
    }
    // Destructor
    ~complex_number(){}
    // Function to return real part
    double real(){return real_part;}
    // Function to return imaginary part
    double imaginary(){return imaginary_part;}
    // Function to return modulus
    double modulus() const
    {
        double modulus{};
        modulus = sqrt( pow(real_part,2) + pow(imaginary_part,2) );
        return modulus;
    }
    // Function to return argument 
    double argument(std::string units = "rad") const
    {
        const double pi{3.14159265};
        double argument{};
        // Return result in degrees
        if (units=="deg")
        {
            argument = tan( imaginary_part/real_part ) * 180/pi;
        }
        // Default in radians
        else {argument = tan( imaginary_part/real_part );}
        return argument;
    }
    // Function to return complex conjugate
    complex_number complex_conjugate() const
    {
        complex_number complex_conjugate{real_part, -imaginary_part};
        return complex_conjugate;
    }
    // Overloading + operator
    complex_number operator+(const complex_number &z) const
    {
        complex_number sum{real_part+z.real_part, imaginary_part+z.imaginary_part};
        return sum;
    }
    // Overloading - operator
    complex_number operator-(const complex_number &z) const
    {
        complex_number difference{real_part-z.real_part, imaginary_part-z.imaginary_part};
        return difference;
    }
    // Overloading the * operator
    complex_number operator*(const complex_number &z) const
    {
        // (a+bi) * (c+di) = (ac - bd) + (ad +bc)i
        double real_part_product{real_part*z.real_part-imaginary_part*z.imaginary_part};
        double imaginary_part_product{real_part*z.imaginary_part+imaginary_part*z.real_part};
        complex_number product{real_part_product, imaginary_part_product};
        return product;
    }
    // Overloading the / operator
    complex_number operator/(const complex_number &z) const
    {
        // a+bi / c+di = (a+bi)*(c-di) / c^2+d^2
        complex_number conjugate_of_z{z.complex_conjugate()};
        // Calculate (a+bi)*(c-di)
        complex_number product_numerator{(*this)*conjugate_of_z};
        // Calculate 1 / c^2-d^2
        complex_number product_denominator{ 1 /
        (pow(conjugate_of_z.real_part,2) + pow(conjugate_of_z.imaginary_part,2)) };
        //std::cout<<product_denominator.real();
        complex_number quotient{product_numerator*product_denominator};
        return quotient;
    }
};

// Function to overload << operator for complex numbers
std::ostream & operator<<(std::ostream &os, const complex_number &z) 
{
    // Handle formatting of negative imaginary parts
    if (z.imaginary_part < 0)
    {
        os<<z.real_part<<z.imaginary_part<<"i";
    }
    else{ os<<z.real_part<<"+"<<z.imaginary_part<<"i"; }
  
  return os;
}
// Function to overload >> operator for complex numbers
std::istream & operator>>(std::istream &is, complex_number &z)
{
    char plus_minus{};
    char i{};
    double real_part{};
    double imaginary_part{};
    is >> real_part >> plus_minus >> imaginary_part >> i;
    if (plus_minus == '-')
    {
        z = complex_number(real_part, -imaginary_part);
    }   
    else  {z = complex_number(real_part, imaginary_part);}
    return is;
}
    

int main()
{  
    std::cout.precision(3);
    // Create two complex numbers
    complex_number a(3,4);
    complex_number b(1,-2);
    // Get real and imaginary components, modulus and argument for a and b
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Complex number a: "<<a<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Real part: "<<a.real()<<std::endl;
    std::cout<<"Imaginary part: "<<a.imaginary()<<std::endl;
    std::cout<<"Modulus: "<<a.modulus()<<std::endl;
    std::cout<<"Argument (radians): "<<a.argument()<<std::endl;
    std::cout<<"Argument (degrees): "<<a.argument("deg")<<std::endl;
    std::cout<<"Complex conjugate. "<<a.complex_conjugate()<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Complex number b: "<<b<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Real part: "<<b.real()<<std::endl;
    std::cout<<"Imaginary part: "<<b.imaginary()<<std::endl;
    std::cout<<"Modulus: "<<b.modulus()<<std::endl;
    std::cout<<"Argument (radians): "<<b.argument()<<std::endl;
    std::cout<<"Argument (degrees): "<<b.argument("deg")<<std::endl;
    std::cout<<"Complex conjugate. "<<b.complex_conjugate()<<std::endl;
    std::cout<<"----------------------"<<std::endl;

    // Get sum, difference, product and quotient of a and b
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Algebraic operations"<<std::endl;
    std::cout<<"----------------------"<<std::endl;
    std::cout<<"Sum (a+b): "<<a+b<<std::endl;
    std::cout<<"Difference (a-b): "<<a-b<<std::endl;
    std::cout<<"Multiplication (a*b): "<<a*b<<std::endl;
    std::cout<<"Division (a/b): "<<a/b<<std::endl;
    std::cout<<"----------------------"<<std::endl;

    // Ask user to enter a complex number
    complex_number c;
    std::cout<<"Enter a complex number: ";
    std::cin>>c;
    std::cout<<"The entered complex number is: "<<c<<std::endl;

    return 0;
}