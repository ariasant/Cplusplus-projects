// PHYS 30762 Programming in C++
// ------------------------------------------------------------------------------------------------------
// Assignment6.cpp
// This program contains a class hierarchy to describe the properties of 2D and 3D shapes. For each 
// shape there is a function to print out the area, volume, and information on the dimensions.
// ------------------------------------------------------------------------------------------------------
// Andrea Sante, last updated: 09/04/2022.
// ------------------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <math.h>

// Pure abstract base class used as an interface for all shapes
class shape
{ 
    public: 
        virtual ~shape(){}

        virtual void info()=0;
        virtual double volume()=0;
        virtual double area()=0;
        
};

// Abstract derived class for 2D shapes
class shape2D : public shape
{ 
    protected: 
        // 2D shapes are characterised by two dimensions
        double dimension_1{};
        double dimension_2{};
    
    public:
        shape2D() {dimension_1=0; dimension_2=0;}
        ~shape2D(){};

        virtual void set_dimensions(double, double )=0;
        // Set dimensions for shapes defined by one dimension (circle/square)
        virtual void set_dimensions(double)=0;
        // 2D shapes have no volume
        double volume(){return 0.0;}

};

// Abstract derived class for 3D shapes
class shape3D : public shape
{ 
    protected: 
        // 3D shapes are characterised by three dimensions
        double dimension_1{};
        double dimension_2{};
        double dimension_3{};
    
    public:
        shape3D() {dimension_1=0; dimension_2=0; dimension_3=0;}
        ~shape3D(){};

        virtual void set_dimensions(double, double, double)=0;
        // Set dimensions for shapes defined by one dimension (sphere)
        virtual void set_dimensions(double)=0;
};



class rectangle: public shape2D
{
    public:
        rectangle(): shape2D(){};
        rectangle(double width, double height) {dimension_1=width; dimension_2=height;} 
        ~rectangle(){};

        void set_dimensions(double width, double height){dimension_1=width; dimension_2=height;}
        // If both dimensions have same size, the rectangle is a square
        void set_dimensions(double side){dimension_1=side; dimension_2=side;}

        double area() {return dimension_1*dimension_2;}   

        void info()
        {
            std::cout<<"Rectangle. \nWidth = "<<dimension_1<<"\nHeigth = "<<dimension_2<<std::endl;
        }
};

class square: public rectangle
{
    public:
        square(double side) {dimension_1=side; dimension_2=side;}
        square(): rectangle() {}; 
        ~square(){};

    void info()
    {
        std::cout<<"Square. \nSide = "<<dimension_1<<std::endl;
    }
};

class ellipse: public shape2D
{
    // Ellipse is a 2D defined by:
    // - semi-major axis (a);
    // - semi-minor axis (b).
    public:
        ellipse(): shape2D() {};
        ellipse(double a, double b) {dimension_1=a; dimension_2=b;}
        ~ellipse(){};

        void set_dimensions(double a, double b) {dimension_1=a; dimension_2=b;}
        // If both dimensions have same size, the ellipse is a circle
        void set_dimensions(double r) {dimension_1=r; dimension_2=r;}

        // Takin pi = 3.14159
        double area() {return 3.14159*dimension_1*dimension_2;}

        void info()
        {
            std::cout<<"Ellipse. \nSemi-major axis = "<<dimension_1<<"\nSemi-minor axis = "<<dimension_2<<std::endl;
        }
};

class circle: public ellipse
{
    // A circle is an ellipse with equal axes
    public:
        circle(double radius) {dimension_1=radius; dimension_2=radius;}
        circle(): ellipse() {}; 
        ~circle(){};

    void info()
    {
        std::cout<<"Circle. \nRadius = "<<dimension_1<<std::endl;
    }

};

class cuboid: public shape3D
{
    public:
        cuboid(): shape3D(){};
        cuboid(double width, double height, double length): shape3D()
        {
            dimension_1 = width;
            dimension_2 = height;
            dimension_3 = length;
        } 
        ~cuboid(){};

        void set_dimensions(double width, double height, double length)
        {
            dimension_1=width; 
            dimension_2=height;
            dimension_3=length;
        }
        // If all dimensions have same size, the cuboid is a cube
        void set_dimensions(double side){dimension_1=side; dimension_2=side; dimension_3=side;}

        double area() {return 2*dimension_1*dimension_2 + 2*dimension_2*dimension_3 + 2*dimension_1*dimension_3;}
        double volume() {return dimension_1*dimension_2*dimension_3;}
        
        void info()
        {
            std::cout<<"Cuboid. \nWidth = "<<dimension_1
            <<"\nHeight = "<<dimension_2
            <<"\nLength = "<<dimension_3<<std::endl;
        }
};

class cube : public cuboid
{
    // A cube is a cuboid with equal dimensions
    public:
        cube(double side) {dimension_1=side; dimension_2=side; dimension_3=side;}
        cube(): cuboid() {}; 
        ~cube(){};

        void info()
        {
            std::cout<<"Cube. \nSide = "<<dimension_1<<std::endl;
        }

};

class ellipsoid: public shape3D
{
    public:
        ellipsoid(): shape3D(){};
        ellipsoid(double a, double b, double c): shape3D()
        {
            dimension_1 = a;
            dimension_2 = b;
            dimension_3 = c;
        } 
        ~ellipsoid(){};

        void set_dimensions(double a, double b, double c)
        {
            dimension_1=a; 
            dimension_2=b;
            dimension_3=c;
        }
        // If all dimensions have same size, the ellipsoid is a sphere
        void set_dimensions(double radius){dimension_1=radius; dimension_2=radius; dimension_3=radius;}

        double area();
        // Takin pi = 3.14159
        double volume() {return (4/3)*3.14159*dimension_1*dimension_2*dimension_3;}

        void info()
        {
            std::cout<<"Ellipsoid. \nDimensions 1 = "<<dimension_1
            <<"\nDimension 2 = "<<dimension_2
            <<"\nDimension 3 = "<<dimension_3<<std::endl;
        }
};

class sphere : public ellipsoid
{
    public:
        sphere(double radius) {dimension_1=radius; dimension_2=radius; dimension_3=radius;}
        sphere(): ellipsoid() {}; 
        ~sphere(){};

        // Takin pi = 3.14159
        double area() {return 4*3.14159*dimension_1*dimension_1;}

        void info()
        {
            std::cout<<"Sphere. \nRadius = "<<dimension_1<<std::endl;
        }

};

class prism: public shape3D
{
    protected:
        shape2D * base;
        double depth;
    public:
        prism(): shape3D(){};
        prism(double dep, shape2D * polygon){base=polygon; depth=dep;}
        ~prism(){};

        void set_dimensions(double dim_1, double dim_2, double dim_3){ base->set_dimensions(dim_1,dim_3); depth=dim_3;}
        void set_dimensions(double){std::cout<<"ERROR. Need to specify a base for the prism"<<std::endl;}

        double area() {std::cout<<"Cannot calculate area for prism: "; return 0;}
        double volume() {return base->area()*depth;}

        void info() 
        {
            std::cout<<"Prism. \nDepth = "<<depth<<"\nBase: ";
            base->info();
        }

};

// Function to calculate surface area of an ellipsoid
double ellipsoid::area()
{
    // Using aproximation found at https://en.wikipedia.org/wiki/Ellipsoid#Surface_area
    double p{1.6075};
    double ap{std::pow(dimension_1,p)};
    double bp{std::pow(dimension_2,p)};
    double cp{std::pow(dimension_3,p)};
    
    double surface{ (ap*bp + ap*cp + bp*cp) / 3};
    surface = 4*3.14159*std::pow(surface, 1/p);

    return surface;
}



int main()
{
    // Define a vector of base class pointers, each pointing to a different shape.
    std::vector<shape*> shapes;
    shapes.push_back(new rectangle{2.0,3.0}); 
    shapes.push_back(new square{4.0});
    shapes.push_back(new ellipse{1.5,3.0});
    shapes.push_back(new circle{4.0});
    shapes.push_back(new cuboid{2.0,3.0,5.0});
    shapes.push_back(new cube{2.0});
    shapes.push_back(new ellipsoid{1.0, 2.0, 3.0});
    shapes.push_back(new sphere{3.0});
    shapes.push_back(new prism{4.0, new rectangle{2.0,3.0}});

    std::cout<<"Number of shapes in scope: "<<shapes.size()<<std::endl;

    // Print out information for each shape
    for (int i{0};i<shapes.size();++i)
    {
        std::cout.precision(3);

        shapes[i]->info();
        std::cout<<"Area: "<<shapes[i]->area()<<std::endl;
        std::cout<<"Volume: "<<shapes[i]->volume()<<std::endl;
        std::cout<<"----------------------------------"<<std::endl;

        // Deleting object
        delete shapes[i];
    }

    shapes.clear();
    
    std::cout<<"Number of shapes in scope: "<<shapes.size()<<std::endl;

    return 0;
}








