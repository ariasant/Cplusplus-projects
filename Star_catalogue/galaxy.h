#ifndef GALAXY_H 
#define GALAXY_H

class galaxy: public celestial_object
{
    
    private:

        double flux{0.0};
        std::string hubble_type{"None"};
        double diameter{0.0};
        double redshift{0.0};
    
    public: 
        galaxy(){number_of_galaxies++;}
        galaxy(std::stringstream &parameters, char delimiter);
        galaxy(celestial_object &object);
        ~galaxy(){number_of_galaxies--;}

        void create_new();
        void info();
        std::stringstream get_info();
        
        void validate_parameters();
        void convert_to_SI();

        std::string get_Type() {return "galaxy";}
        double get_Flux() {return flux;}
        double get_Distance();

};

galaxy::galaxy(std::stringstream &parameters, char delimiter='\t')
{
    // Parameters used to store the string value corresponfing to 
    // numerical parameters
    std::string numerical_parameter;

    std::getline(parameters, name, delimiter);

    std::getline(parameters, numerical_parameter, delimiter);
    ra = std::stod(numerical_parameter);

    std::getline(parameters, numerical_parameter, delimiter);
    dec = std::stod(numerical_parameter);

    std::getline(parameters, hubble_type, delimiter);

    std::getline(parameters, numerical_parameter, delimiter);
    flux = std::stod(numerical_parameter);

    std::getline(parameters, numerical_parameter, delimiter);
    diameter = std::stod(numerical_parameter);
    
    std::getline(parameters, numerical_parameter, delimiter);
    redshift = std::stod(numerical_parameter);

    number_of_galaxies++;
}

galaxy::galaxy(celestial_object &object)
{
    // Get parameters to copy
    std::stringstream parameters{object.get_info()};
    const int WrongObjectType{-1};

    // Perform deep copy
    try 
    {
        if (object.get_Type()!="galaxy"){throw WrongObjectType;}

        std::string numerical_parameter;
        char delimiter{'\t'};

        std::getline(parameters, name, delimiter);

        std::getline(parameters, numerical_parameter, delimiter);
        ra = std::stod(numerical_parameter);

        std::getline(parameters, numerical_parameter, delimiter);
        dec = std::stod(numerical_parameter);

        std::getline(parameters, hubble_type, delimiter);

        std::getline(parameters, numerical_parameter, delimiter);
        flux = std::stod(numerical_parameter);

        std::getline(parameters, numerical_parameter, delimiter);
        diameter = std::stod(numerical_parameter);
        
        std::getline(parameters, numerical_parameter, delimiter);
        redshift = std::stod(numerical_parameter);

        number_of_galaxies++;

    }
    catch (int ErrorFlag)
    {
        if (ErrorFlag==WrongObjectType)
        {
            std::cout<<"Error creating object. Poiter to galaxy object was expected "
            <<"but "<<object.get_Type()<<" was given. Deafult galaxy created"<<std::endl;
        }
    }    

    // Copy of the object has same id of original object
    id = object.get_ID();

}

std::stringstream galaxy::get_info()
{
    std::stringstream s;

    s << name <<"\t"<< ra <<"\t"<< dec <<"\t" << hubble_type 
    <<"\t"<< flux <<"\t"<< diameter<<"\t" << redshift;

    return s;
}

// Create galaxy object from keyboard
void galaxy::create_new()
{
    std::cout<<"Creating new galaxy object. "<<std::endl;
    std::cout<<"Enter name of the galaxy: ";
    std::cin>>name;
    
    std::cout<<"Enter RA (deg) of the galaxy: ";
    std::cin>>ra;
    validate_numerical_input(ra,0,360);

    std::cout<<"Enter Dec (deg) of the galaxy: ";
    std::cin>>dec;
    validate_numerical_input(dec,-90,90);

    const std::vector<std::string> allowed_hubble_types{"E0", "E1", "E2", "E3", "E4",
        "E5", "E6", "E7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};
    std::cout<<"Enter Hubble class of the galaxy: ";
    std::cin>>hubble_type;
    validate_string_input(hubble_type, allowed_hubble_types);

    std::cout<<"Enter flux (Jy) of the galaxy: ";
    std::cin>>flux;
    validate_numerical_input(flux,0,4500);

    std::cout<<"Enter diameter  (kpc) of the galaxy: ";
    std::cin>>diameter;
    validate_numerical_input(diameter,0.09,5e3);

    std::cout<<"Enter redshift of the galaxy: ";
    std::cin>>redshift;
    validate_numerical_input(redshift,0,10);

    std::cout<<"Galaxy '"<<name<<"' successfully created."<<std::endl;

}


void galaxy::validate_parameters()
{
    std::cout<<"Validating input data for galaxy '"<<name<<"'..."<<std::endl;

    validate_numerical_input(ra, 0,360);
    validate_numerical_input(dec,-90,90);

    const std::vector<std::string> allowed_hubble_types{"E0", "E1", "E2", "E3", "E4",
        "E5", "E6", "E7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};
    validate_string_input(hubble_type, allowed_hubble_types);

    validate_numerical_input(flux,0,4500);

    validate_numerical_input(diameter,0.09,5e3);;

    validate_numerical_input(redshift,0,10);

}

void galaxy::convert_to_SI()
{
    double Jy{1e-26};
    double kilo_parsec{3.06e19};

    flux *= Jy;
    diameter *= kilo_parsec;
}


void galaxy::info()
{
    std::cout.precision(3);

    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"Galaxy: "<<name<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"ID: ASTRO+"<<id<<std::endl
    <<"RA: "<<ra<<std::endl
    <<"DEC: "<<dec<<std::endl
    <<"Hubble class: "<<hubble_type<<std::endl
    <<"Diameter (kpc): "<<diameter<<std::endl
    <<"Flux (Jy): "<<flux<<std::endl
    <<"Redshift: "<<redshift<<std::endl;
    std::cout<<"------------------------------"<<std::endl;

}

double galaxy::get_Distance() 
{
    double speed_of_light_in_vacuum{299792.458}; //km s^{-1}
    double Hubble_constant{68.0}; //km s^{-1} Mpc{-1}

    double distance{0.0};

    // Applying Hubble's law: v=c*z=H_0*d
    distance = (speed_of_light_in_vacuum*redshift)/Hubble_constant;
    return distance;
}


#endif
