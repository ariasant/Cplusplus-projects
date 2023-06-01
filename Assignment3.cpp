// PHYS 30762 Programming in C++
// ------------------------------------------------------------------------------------------------------
// Assignment3.cpp
// This program allows the user to define galaxy objects by entering: the Hubble type, the redshift, the 
// total mass, the stellar mass fraction, and the number of satellite of each galaxy. The program returns
// also the total stellar mass for each galaxy object. 
// ------------------------------------------------------------------------------------------------------
// Andrea Sante, last updated: 07/03/2022.
// ------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

class galaxy
{
    friend galaxy initialise_galaxy();
private:
    // Default values for galaxy properties
    std::string Hubble_type{"E0"};
    double redshift{0.0}; // range:0-10
    double total_mass{1e7}; //range: 10^7-10^12
    double stellar_mass_fraction{0.0}; // 0-0.05
    std::vector<galaxy> satellites;

public:
    // Default constructor
    galaxy() = default;
    // Parametrised constructor
    galaxy( std::string galaxy_type, double galaxy_redshift, 
    double galaxy_total_mass, double galaxy_stellar_mass_fraction):
        Hubble_type{galaxy_type},
        redshift{galaxy_redshift}, // range:0-10
        total_mass{galaxy_total_mass}, //range: 10^7-10^12
        stellar_mass_fraction{galaxy_stellar_mass_fraction} // 0-0.05
    {   // Print warninge message if inputs are out of bounds
        bool valid_input{false};
        // Vector containing valid inputs
        std::vector<std::string> allowed_types{"E0", "E1", "E2", "E3", "E4",
        "E5", "E6", "E7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};
        for (int i{0};i<allowed_types.size();++i)
        {
            valid_input += (Hubble_type==allowed_types[i]);
        }
        if (!valid_input)
        {
            //Warning message
            std::cout<<"WARNING: The redshift value is out of bounds!"<<std::endl;
        }
        if (redshift<0 || redshift>10)
        {
            //Warning message
            std::cout<<"WARNING: The redshift value is out of bounds!"<<std::endl;
        }
        if (total_mass<1e7 || total_mass>1e12)
        {
            //Warning message
            std::cout<<"WARNING: The value of the total mass of the galaxy is out of bounds!"<<std::endl;
        }
        if (stellar_mass_fraction<0 || stellar_mass_fraction>0.05)
        {
            //Warning message
            std::cout<<"WARNING: The value of the stellar mass fraction is out of bounds!"<<std::endl;
        }
    }  
    // Destructor
    ~galaxy(){}  

    // Function to print out the properties of the galaxy
    void print_data();
    // Function to change Hubble type of the galaxy:
    // from the scope
    void set_type(std::string galaxy_type); 
    // for the user
    void set_type(); 
    // Function to calculate stellar mass in the galaxy
    double stellar_mass();
    // Function to add satellite to the galaxy:
    // create a satellite galaxy
    void add_satellite(std::string satellite_type,double satellite_redshift, 
    double satellite_total_mass, double satellite_stellar_mass_fraction); 
    // add an existing galaxy as a satellite
    void add_satellite(galaxy & galaxy_1); 
};
// End of class and associated member functions
// --------------------------------------------------------------------------------------------------------

// Define long functions outside class environment
void galaxy::print_data()
{
    // Set precision of output values
    std::cout.precision(1); // 2 significant figures
    std::cout<<"Hubble type: "<<Hubble_type<< 
    "\nRedshift: "<<redshift<<
    "\nTotal Mass (Solar masses): "<<total_mass<<
    "\nStellar Mass Fraction: "<<stellar_mass_fraction<<
    "\nNumber of satellites: "<<satellites.size()<<std::endl;
    // Print properties of satellite galaxies (if any)
    if (satellites.size()!=0)
    {
        for(int i{0};i<satellites.size();++i)
        {
            std::cout<<"Properties of satellite "<<i+1<<":"<<std::endl;
            std::cout<<"-------"<<std::endl;
            satellites[i].print_data();
        }
    }
    return;
}
// Member function to change Hubble type of a galaxy from the scope
void galaxy::set_type(std::string galaxy_type)
{   
    bool valid_input{false};
    // Vector containing valid inputs
    std::vector<std::string> allowed_types{"E0", "E1", "E2", "E3", "E4",
    "E5", "E6", "E7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};
    for (int i{0};i<allowed_types.size();++i)
    {
        valid_input += (galaxy_type==allowed_types[i]);
    }
    if (valid_input)
    {
        Hubble_type = galaxy_type;
    }
    else {std::cout<<"Cannot change galaxy type. Invalid input."<<std::endl;}
    return;   
}
// Member function to allow user to change Hubble type of a galaxy 
void galaxy::set_type()
{   
    std::string galaxy_type;
    bool valid_input{false};
    // Vector containing valid inputs
    std::vector<std::string> allowed_types{"E0", "E1", "E2", "E3", "E4",
    "E5", "E6", "E7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};
    while (!valid_input)
    {
        std::cout<<"Enter the Hubble class for the galaxy: ";
        std::cin>>galaxy_type;
        for (int i{0};i<allowed_types.size();++i)
        {
            valid_input += (galaxy_type==allowed_types[i]);
        }
        if (!valid_input)
        {   // Clear and ignore bad inputs
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
    }
    Hubble_type = galaxy_type;
    return;
}
// Member unction to calculate the stellar mass in the galaxy (in solar masses)
double galaxy::stellar_mass()
{
    double stellar_mass_galaxy{};
    stellar_mass_galaxy = stellar_mass_fraction*total_mass;
    std::cout.setf(std::ios::scientific,std::ios::floatfield);
    std::cout<<"Total stellar mass (Solar masses): "<<stellar_mass_galaxy<<std::endl;
    return stellar_mass_galaxy;
}
// Member function to create satellite galaxies
void galaxy::add_satellite(std::string satellite_type,double satellite_redshift, 
double satellite_total_mass, double satellite_stellar_mass_fraction)
{   
    // Construct satellite galaxies
    galaxy satellite{satellite_type,satellite_redshift, satellite_total_mass, 
    satellite_stellar_mass_fraction};
    satellites.push_back(satellite);
    return;
}
// Function to add a galaxy as a satellite of another galaxy
void galaxy::add_satellite(galaxy & galaxy_1)
{
    satellites.push_back(galaxy_1);
}

// Function to allow user to enter the Hubble type of a galaxy
std::string enter_hubble_type()
{    
    std::string galaxy_type;
    bool valid_input{false};
    std::vector<std::string> allowed_types{"E0", "E1", "E2", "E3", "E4",
    "E5", "E6", "E7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};
    while (!valid_input)
    {
        std::cout<<"Enter a valid Hubble class for the galaxy: ";
        std::cin>>galaxy_type;
        for (int i{0};i<allowed_types.size();++i)
        {
            valid_input += (galaxy_type==allowed_types[i]);
        }
        if (!valid_input)
        {
            std::cin.clear();
        }
    }
    return galaxy_type;
}
// Function to allow the user to enter a value for the redshift
double enter_redshift()
{
    double input{};
    bool invalid_input{true};
    bool is_negative{};
    bool is_in_range{}; // range [0-10]
    while (invalid_input)
    {
        // Ask user to enter a value
        std::cout<<"Enter a valid value for the redshift(0-10): ";
        std::cin>>input;
        // Check whether input is valid
        is_in_range = input>10;
        is_negative = input<0;
        invalid_input = (std::cin.fail()) || is_negative || is_in_range;
        // Clear and ignore bad input
        if (invalid_input) 
        {
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
    }
    return input;
}
// Function to allow the user to enter a value for the total mass
double enter_total_mass()
{
    double input{};
    bool invalid_input{true};
    bool is_negative{};
    bool is_in_range{}; // range [10^7-10^12] Solar masses
    while (invalid_input)
    {
        // Ask user to enter a value
        std::cout<<"Enter a valid value for the total mass of the "
        <<"galaxy in solar massess (10^7-10^12): ";
        std::cin>>input;
        // Check whether input is valid
        is_in_range = input<pow(10,7) || input>pow(10,12);
        is_negative = input<0;
        invalid_input = (std::cin.fail()) || is_negative || is_in_range;
        // Clear and ignore bad input
        if (invalid_input) 
        {
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
    }
    return input;
}
// Function to allow the user to enter a value for the stellar mass fraction
double enter_stellar_mass_fraction()
{
    double input{};
    bool invalid_input{true};
    bool is_negative{};
    bool is_in_range{}; // range [0-0.05] 
    while (invalid_input)
    {
        // Ask user to enter a value
        std::cout<<"Enter a valid value for the stellar "
        <<"mass fraction in the galaxy (0-0.05): ";
        std::cin>>input;
        // Check whether input is valid
        is_in_range = input>0.05;
        is_negative = input<0;
        invalid_input = (std::cin.fail()) || is_negative || is_in_range;
        // Clear and ignore bad input
        if (invalid_input) 
        {
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }
    }
    return input;
}

// Function to create a galaxy object using parametrised construction
galaxy initialise_galaxy()
{
    // Initialise properties of the galaxy
    std::string type = enter_hubble_type();
    double redshift = enter_redshift();
    double total_mass = enter_total_mass();
    double stellar_mass_fraction = enter_stellar_mass_fraction();
    // Create galaxy object
    galaxy Galaxy_1{type,redshift,total_mass,stellar_mass_fraction};
    return Galaxy_1;
}

//-----------------------------------------------------------------------------

int main()
{
    // Example using default constructor
    std::cout<<"A galaxy with default properties has been created:"<<std::endl;
    galaxy default_galaxy{}; 
    // Print properties of default galaxy
    default_galaxy.print_data();
    // Change Hubble type of default galaxy
    std::cout<<"You can change the Hubble type of the galaxy:"<<std::endl;
    default_galaxy.set_type();
    // Print new properties of galaxy
    std::cout<<"These are the new properties of the galaxy:"<<std::endl;
    default_galaxy.print_data();
    // Example using parameterised constructor:
    // Ask user how many galaxies he wants to enter
    unsigned int number_of_galaxies;
    std::cout<<"How many galaxies do you want to create? "<<std::endl;
    std::cin>>number_of_galaxies;
    // Create a vector to store the galaxy objects
    galaxy* galaxies = new galaxy[number_of_galaxies];
    // Create galaxy objects and store them in the vector
    for (int i{0};i<number_of_galaxies;++i)
    {   std::cout<<"Creating galaxy "<<i+1<<": "<<std::endl;
        galaxies[i] = initialise_galaxy();
        galaxy current_galaxy{galaxies[i]};       
    }
    // Create a vector to store the galaxy objects
    std::vector<galaxy> vector_galaxies;
    for (int i{0};i<number_of_galaxies;++i)
    {
        vector_galaxies.push_back(galaxies[i]);
    }
    // Define iterators to manipulate galaxy vector
    std::vector<galaxy>::iterator iterator_vector;
    std::vector<galaxy>::iterator vector_begin{vector_galaxies.begin()};
    std::vector<galaxy>::iterator vector_end{vector_galaxies.end()};
    // Print content and stellar mass of each galaxy
    int i{0};
    for (iterator_vector=vector_begin;iterator_vector!=vector_end;++iterator_vector)
    {
        // Add satellite galaxies to each galaxy object
        int number_of_satellite_galaxies;
        std::cout<<"Enter number of satellites for galaxy "<<i+1<<" ";
        std::cin>> number_of_satellite_galaxies;
        for (int o{0};o<number_of_satellite_galaxies;++o)
        {
            // Define properties of satellite
            std::cout<<"Enter properties of satellite "<<o+1<<":"<<std::endl;
            std::string satellite_type{enter_hubble_type()};
            double satellite_redshift{enter_redshift()};
            double satellite_total_mass{enter_total_mass()};
            double satellite_stellar_mass_fraction{enter_stellar_mass_fraction()};
            // Construct satellite galaxy
            (*iterator_vector).add_satellite(satellite_type, satellite_redshift, satellite_total_mass, 
            satellite_stellar_mass_fraction);
        }
        // Printing properties of each galaxy
        std::cout<<"----------------------"<<std::endl;
        std::cout<<"Properties of Galaxy "<<i+1<<":"<<std::endl;
        std::cout<<"----------------------"<<std::endl;
        iterator_vector->print_data();
        iterator_vector->stellar_mass();
        ++i;
    }    
    
  return 0;
}