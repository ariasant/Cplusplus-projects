#ifndef STAR_H 
#define STAR_H

class star: public celestial_object
{
    
    private:
        
        double flux{0.0}; // Jy
        std::string spectral_class{"None"};
        double mass{0.0}; // Solar mass
        double radius{0.0}; // Solar radius
        double proper_motion{0.0}; // milliarcsecond per year
        double transverse_velocity{0.0}; //km s^{-1}

    public: 
        star(){number_of_stars++;}
        star(std::stringstream &parameters, char delimiter);
        star(celestial_object &object);
        ~star(){number_of_stars--;}

        void create_new();
        void info();
        std::stringstream get_info();
        
        void validate_parameters();
        void convert_to_SI();

        std::string get_Type() {return "star";}
        std::string get_Spectral_class() {return spectral_class;}
        double get_Mass() {return mass;}
        double get_Flux() {return flux;}
        double get_Distance();
        double get_Apparent_Magnitude();
        double get_Absolute_Magnitude();

};

star::star(std::stringstream &parameters, char delimiter='\t')
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
    flux = std::stod(numerical_parameter);

    std::getline(parameters, spectral_class, delimiter);

    std::getline(parameters, numerical_parameter, delimiter);
    mass = std::stod(numerical_parameter);
    
    std::getline(parameters, numerical_parameter, delimiter);
    radius = std::stod(numerical_parameter);

    std::getline(parameters, numerical_parameter, delimiter);
    proper_motion = std::stod(numerical_parameter);

    std::getline(parameters, numerical_parameter, delimiter);
    transverse_velocity = std::stod(numerical_parameter);

    ++number_of_stars;
    
}

star::star(celestial_object &object)
{
    // Get parameters to copy
    std::stringstream parameters{object.get_info()};
    const int WrongObjectType{-1};

    // Perform deep copy
    try 
    {
        if (object.get_Type()!="star"){throw WrongObjectType;}

        std::string numerical_parameter;
        char delimiter{'\t'};

        std::getline(parameters, name, delimiter);

        std::getline(parameters, numerical_parameter, delimiter);
        ra = std::stod(numerical_parameter);

        std::getline(parameters, numerical_parameter, delimiter);
        dec = std::stod(numerical_parameter);

        std::getline(parameters, numerical_parameter, delimiter);
        flux = std::stod(numerical_parameter);

        std::getline(parameters, spectral_class, delimiter);

        std::getline(parameters, numerical_parameter, delimiter);
        mass = std::stod(numerical_parameter);
        
        std::getline(parameters, numerical_parameter, delimiter);
        radius = std::stod(numerical_parameter);

        std::getline(parameters, numerical_parameter, delimiter);
        proper_motion = std::stod(numerical_parameter);

        std::getline(parameters, numerical_parameter, delimiter);
        transverse_velocity = std::stod(numerical_parameter);

        // Copy of the object has same id of original object
        id = object.get_ID();

    }
    catch (int ErrorFlag)
    {
        if (ErrorFlag==WrongObjectType)
        {
            std::cout<<"Error creating object. Poiter to star object was expected "
            <<"but "<<object.get_Type()<<" was given. Deafult star created"<<std::endl;
        }
    }    

}

std::stringstream star::get_info()
{
    std::stringstream s;

    s << name <<"\t"<< ra <<"\t"<< dec <<"\t"
    << flux <<"\t"<< spectral_class <<"\t"  
    << mass <<"\t"<< radius <<"\t"<< proper_motion <<"\t"<< transverse_velocity;

    return s;
}

// Create new star object from keyboard
void star::create_new()
{
    std::cout<<"Creating new star object. "<<std::endl;
    std::cout<<"Enter name of the star: ";
    std::cin>>name;
    
    std::cout<<"Enter RA (deg) of the star: ";
    std::cin>>ra;
    validate_numerical_input(ra,0,360);

    std::cout<<"Enter Dec (deg) of the star: ";
    std::cin>>dec;
    validate_numerical_input(dec,-90,90);

    // Defining allowed spectral classes for stars
    std::vector<std::string> allowed_spectral_types;
    std::vector<std::string> allowed_spectral_classes {"O","B","A","F","G","K","M"};

    for (int it{0}; it<allowed_spectral_classes.size(); ++it)
    {
        for (int i{0}; i<10; ++i)
        {
            allowed_spectral_types.push_back(allowed_spectral_classes[it]+std::to_string(i));
        }
    }
    
    std::cout<<"Enter spectral class of the star: ";
    std::cin>>spectral_class;
    validate_string_input(spectral_class, allowed_spectral_types);

    std::cout<<"Enter flux (Jy) of the star: ";
    std::cin>>flux;
    validate_numerical_input(flux,0,1e8);

    std::cout<<"Enter mass (Solar Masses) of the star: ";
    std::cin>>mass;
    validate_numerical_input(mass,0.09,150);

    std::cout<<"Enter radius (Solar radius) of the star: ";
    std::cin>>radius;
    validate_numerical_input(radius,1e-5,1800);

    std::cout<<"Enter proper motion (milliarc per year) of the star: ";
    std::cin>>proper_motion;
    validate_numerical_input(proper_motion,0,11e3);

    std::cout<<"Enter transverse velocity (km s^-1) of the star: ";
    std::cin>>transverse_velocity;
    validate_numerical_input(transverse_velocity,0,170);

    std::cout<<"Star '"<<name<<"' successfully created."<<std::endl;

}


void star::validate_parameters()
{
    std::cout<<"Validating input data for star '"<<name<<"'..."<<std::endl;

    validate_numerical_input(ra, 0,360);
    validate_numerical_input(dec,-90,90);

    // Defining allowed spectral classes for stars
    std::vector<std::string> allowed_spectral_types;
    std::vector<std::string> allowed_spectral_classes {"O","B","A","F","G","K","M"};
    std::vector<std::string>::iterator it;
    for (it = allowed_spectral_classes.begin(); it != allowed_spectral_classes.begin(); ++it)
    {
        for (int i{0}; i<10; ++i)
        {
            allowed_spectral_types.push_back(*it+std::to_string(i));
        }
    }

    validate_numerical_input(flux,0,1e8);

    validate_numerical_input(mass, 0.09,150);

    validate_numerical_input(radius,1e-5,1800);

    validate_numerical_input(proper_motion,0,11e3);

    validate_numerical_input(transverse_velocity,0,170);

}

void star::convert_to_SI()
{
    double Jy{1e-26};
    double solar_mass{2e30};
    double solar_radius{7e8};

    flux *= Jy;
    mass *= solar_mass;
    radius *= solar_radius;
}


void star::info()
{
    std::cout.precision(3);

    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"Star: "<<name<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"ID: ASTRO+"<<id<<std::endl
    <<"RA: "<<ra<<std::endl
    <<"DEC: "<<dec<<std::endl
    <<"Spectral class: "<<spectral_class<<std::endl
    <<"Mass(M_sun): "<<mass<<std::endl
    <<"Radius (R_sun): "<<radius<<std::endl
    <<"Flux (Jy): "<<flux<<std::endl
    <<"Proper Motion (marc/yr): "<<proper_motion<<std::endl
    <<"Transverse velocity (km/s): "<<transverse_velocity<<std::endl;
    std::cout<<"------------------------------"<<std::endl;

}

double star::get_Distance() 
{
    // Apply relation between transverse velocity and proper motion (mu):
    //  
    //          V_T = 4.7e-3*d*mu

    double distance{0.0};

    // Units of parsecs
    distance = transverse_velocity/(4.7e-3*proper_motion);
    return distance; 
}


double star::get_Apparent_Magnitude()
{
    // Calculate apparent magnitude of object considering
    // the apparent magnitude of Vega as a reference:
    //
    // m_Vega - m_Obj = -2.5*log10(F_Vega / F_obj)
    double m_Vega{0.03};
    double F_Vega{3630}; //in units of Jy
    
    double apparent_magnitude{0.0};

    const int DivisionError{-1};
    try 
    {
        if (get_Flux() == 0.0) {throw DivisionError;}
        apparent_magnitude = m_Vega + 2.5*std::log10(F_Vega/get_Flux());
    }
    catch (int ErrorFlag)
    {
        if (ErrorFlag==DivisionError) {return 0;}
    }

    return apparent_magnitude;
}

double star::get_Absolute_Magnitude()
{
    // Calculate absolute magnitude of the object using
    //
    //  M = m - 5*log10(d/10)

    double absolute_magnitude{get_Apparent_Magnitude()-5*std::log10(get_Distance()/10)};
    

    return absolute_magnitude;
}

#endif
