#ifndef PLANET_H 
#define PLANET_H

class planet: public celestial_object
{
    
    private:
        
        double radius{0.0}; // Jupiter radius
        double mass{0.0}; // Jupite mass
        double period{0.0}; //days
        double semi_major_axis{0.0}; //AU
        double eccentricity{0.0};
        double inclination{0.0};
        double distance{0.0}; //pc
        double year_of_discovery{0.0};


    public: 

        planet(){number_of_planets++;}
        planet(std::stringstream &parameters, char delimiter);
        planet(celestial_object &object);
        ~planet(){number_of_planets--;}

        void create_new();
        void info();
        std::stringstream get_info();
        
        void validate_parameters();
        void convert_to_SI();

        std::string get_Type() {return "planet";}
        double get_Mass() {return mass;}
        double get_Flux() {return 0.0;}
        double get_Distance() {return distance;}

};

planet::planet(std::stringstream &parameters, char delimiter='\t')
{
    // Parameters used to store the string value corresponfing to 
    // numerical parameters
    std::string numerical_parameter;

    std::getline(parameters, name, delimiter);

    std::getline(parameters, numerical_parameter, delimiter);
    ra = std::stod(numerical_parameter);

    std::getline(parameters, numerical_parameter, delimiter);
    dec = std::stod(numerical_parameter);

    std::getline(parameters, numerical_parameter, delimiter);
    if (numerical_parameter!="-"){mass = std::stod(numerical_parameter);}

    std::getline(parameters, numerical_parameter, delimiter);
    if (numerical_parameter!="-"){radius = std::stod(numerical_parameter);}
    
    std::getline(parameters, numerical_parameter, delimiter);
    if (numerical_parameter!="-"){period = std::stod(numerical_parameter);}

    std::getline(parameters, numerical_parameter, delimiter);
    if (numerical_parameter!="-"){semi_major_axis = std::stod(numerical_parameter);}

    std::getline(parameters, numerical_parameter, delimiter);
    if (numerical_parameter!="-"){eccentricity = std::stod(numerical_parameter);}

    std::getline(parameters, numerical_parameter, delimiter);
    if (numerical_parameter!="-"){inclination= std::stod(numerical_parameter);}

    std::getline(parameters, numerical_parameter, delimiter);
    if (numerical_parameter!="-"){distance = std::stod(numerical_parameter);}

    std::getline(parameters, numerical_parameter, delimiter);
    if (numerical_parameter!="-"){year_of_discovery = std::stod(numerical_parameter);}
    

    number_of_planets++;
}


planet::planet(celestial_object  &object)
{
    // Get parameters to copy
    std::stringstream parameters{object.get_info()};
    const int WrongObjectType{-1};

    // Perform deep copy
    try 
    {
        if (object.get_Type()!="planet"){throw WrongObjectType;}

        std::string numerical_parameter;
        char delimiter{'\t'};

        std::getline(parameters, name, delimiter);

        std::getline(parameters, numerical_parameter, delimiter);
        ra = std::stod(numerical_parameter);

        std::getline(parameters, numerical_parameter, delimiter);
        dec = std::stod(numerical_parameter);

        std::getline(parameters, numerical_parameter, delimiter);
        if (numerical_parameter!="-"){mass = std::stod(numerical_parameter);}

        std::getline(parameters, numerical_parameter, delimiter);
        if (numerical_parameter!="-"){radius = std::stod(numerical_parameter);}
        
        std::getline(parameters, numerical_parameter, delimiter);
        if (numerical_parameter!="-"){period = std::stod(numerical_parameter);}

        std::getline(parameters, numerical_parameter, delimiter);
        if (numerical_parameter!="-"){semi_major_axis = std::stod(numerical_parameter);}

        std::getline(parameters, numerical_parameter, delimiter);
        if (numerical_parameter!="-"){eccentricity = std::stod(numerical_parameter);}

        std::getline(parameters, numerical_parameter, delimiter);
        if (numerical_parameter!="-"){inclination= std::stod(numerical_parameter);}

        std::getline(parameters, numerical_parameter, delimiter);
        if (numerical_parameter!="-"){distance = std::stod(numerical_parameter);}

        std::getline(parameters, numerical_parameter, delimiter);
        if (numerical_parameter!="-"){year_of_discovery = std::stod(numerical_parameter);}
        
        // Copy of the object has same id of original object
        id = object.get_ID();

    }
    catch (int ErrorFlag)
    {
        if (ErrorFlag==WrongObjectType)
        {
            std::cout<<"Error creating object. Poiter to planet object was expected "
            <<"but "<<object.get_Type()<<" was given. Deafult planet created"<<std::endl;
        }
    }    

}


std::stringstream planet::get_info()
{
    std::stringstream s;

    s << name <<"\t"<< ra <<"\t"<< dec 
    << "\t" << mass << "\t" << radius << "\t" <<period 
    << "\t" << semi_major_axis << "\t" << eccentricity
    << "\t" << inclination << "\t" << distance 
    << "\t" << year_of_discovery;

    return s;
}

// Create new planet from keyboard
void planet::create_new()
{
    std::cout<<"Creating new planet object. "<<std::endl;
    std::cout<<"Enter name of the planet: ";
    std::cin>>name;
    
    std::cout<<"Enter RA (deg) of the planet: ";
    std::cin>>ra;
    validate_numerical_input(ra,0,360);

    std::cout<<"Enter Dec (deg) of the planet: ";
    std::cin>>dec;
    validate_numerical_input(dec,-90,90);

    std::cout<<"Enter Period (days) of the planet: ";
    std::cin>>period;
    validate_numerical_input(period,0,1000);

    std::cout<<"Enter radius (Jupiter radii) of the planet: ";
    std::cin>>radius;
    validate_numerical_input(radius,6e-12,3);

    std::cout<<"Enter mass (Jupiter Masses) of the planet: ";
    std::cin>>mass;
    validate_numerical_input(mass,2e-6,30);

    std::cout<<"Enter semi major axis (AU) of the orbit the planet: ";
    std::cin>>semi_major_axis;
    validate_numerical_input(semi_major_axis,0.02,50);

    std::cout<<"Enter eccentricity of the orbit the planet: ";
    std::cin>>eccentricity;
    validate_numerical_input(eccentricity,0,1);

    std::cout<<"Enter inclination (deg) of the orbit the planet: ";
    std::cin>>inclination;
    validate_numerical_input(inclination,0,180);

    std::cout<<"Enter angular distance (arcsec) to the planet ";
    std::cin>>distance;
    validate_numerical_input(distance,4,1800);

    std::cout<<"Planet '"<<name<<"' successfully created."<<std::endl;

}


void planet::validate_parameters()
{
    std::cout<<"Validating input data for planet '"<<name<<"'..."<<std::endl;

    validate_numerical_input(ra,0,360);

    validate_numerical_input(dec,-90,90);

    validate_numerical_input(period,0,1000);

    validate_numerical_input(radius,6e-12,3);

    validate_numerical_input(mass,2e-6,30);

    validate_numerical_input(semi_major_axis,0.02,50);

    validate_numerical_input(eccentricity,0,1);

    validate_numerical_input(inclination,0,180);

    validate_numerical_input(distance,4,1800);

}

void planet::convert_to_SI()
{

    double Jupiter_mass{2e27};
    double Jupiter_radius{7e7};
    double astronomical_unit{1.5e11};
    double day{24*3600};

    radius *= Jupiter_radius;
    mass *= Jupiter_mass;
    semi_major_axis *= astronomical_unit;
    period *= day;
}


void planet::info()
{
    std::cout.precision(3);

    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"Planet: "<<name<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"ID: ASTRO+"<<id<<std::endl
    <<"RA: "<<ra<<std::endl
    <<"DEC: "<<dec<<std::endl
    <<"Radius: "<<radius<<std::endl
    <<"Mass(M_Jupiter): "<<mass<<std::endl
    <<"Period (days): "<<period<<std::endl
    <<"Semi major axis (AU): "<<semi_major_axis<<std::endl
    <<"Eccentricity: "<<eccentricity<<std::endl
    <<"Inclination (deg): "<<inclination<<std::endl
    <<"Distance (pc): "<<distance<<std::endl;
    std::cout.precision(0);
    std::cout<<"Year of dicovery: "<<std::fixed<<year_of_discovery<<std::endl;
    std::cout<<"------------------------------"<<std::endl;

}

#endif
