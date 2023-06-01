#ifndef ASTRO_DATA_H 
#define ASTRO_DATA_H

class celestial_object
{
    protected:      

        static int number_of_objects;
        static int number_of_galaxies;
        static int number_of_stars;
        static int number_of_planets;

        int id{number_of_objects};
        std::string name{"Unknown Name"};
        double ra{0.0};
        double dec{0.0};


    public:

        celestial_object(){number_of_objects++;}
        virtual ~celestial_object(){number_of_objects--;}

        int get_Objects_Count() {return number_of_objects;}       
        int get_Galaxy_Count() {return number_of_galaxies;}
        int get_Stars_Count() {return number_of_stars;}
        int get_Planets_Count() {return number_of_planets;}

        virtual void create_new()=0;       
        virtual void validate_parameters()=0;

        virtual void convert_to_SI()=0;
        virtual void info()=0;
        virtual std::stringstream get_info()=0;
        virtual std::string get_Type()=0;
        
        virtual double get_Flux()=0;
        virtual double get_Distance()=0;

        std::string get_Name() {return name;}
        int get_ID(){return id;};
        int set_Id(int a) {return id=a;} 
        double get_RA() {return ra;}
        double get_DEC() {return dec;}

};


// Defining static variables
int celestial_object::number_of_objects{0};
int celestial_object::number_of_galaxies{0};
int celestial_object::number_of_stars{0};
int celestial_object::number_of_planets{0};


// Function as interface to create new object as a pointer to a celestial object
template <class c_type> std::unique_ptr<celestial_object> create_new_obj()
{
    std::unique_ptr<celestial_object> new_object(new c_type);
    new_object->create_new();

    return new_object;
}


// Implementation of sorting functions:

template <class c_type> bool sort_by_type(std::shared_ptr<c_type> a, std::shared_ptr<c_type> b)
{
    // Alphabetical order A->Z
    return (a->get_Type() < b->get_Type());
};

template <class c_type> bool sort_by_name(std::shared_ptr<c_type> a, std::shared_ptr<c_type> b)
{
    // Alphabetical order A->Z
    return (a->get_Name() < b->get_Name());
};


template <class c_type> bool sort_by_flux(std::shared_ptr<c_type> a, std::shared_ptr<c_type> b)
{
    // Brightest to faintest
    return (a->get_Flux() > b->get_Flux());
};

template <class c_type> bool sort_by_distance(std::shared_ptr<c_type> a, std::shared_ptr<c_type> b)
{
    // Ignore objects that don't have info on their distance
    if (a->get_Distance() == 0 ) {return false;}
    // Closest to furthest
    return (a->get_Distance() < b->get_Distance());
};


// Function used to check whether a value is not outbound
void validate_numerical_input(double &value, double lower_limit, double upper_limit)
{
    const int InvalidInput{-1};
    bool valid_input;
    try
    {
        valid_input=(value>lower_limit && value<upper_limit);

        if (!valid_input)  {throw InvalidInput;}
    }  

    
    catch (int ErrorFlag)
    {
        if (ErrorFlag==InvalidInput)
        {
            
            do 
            {
                // Clear fail and ignore bad input
                std::cin.clear(); 
                std::cin.ignore(1000, '\n');
                std::cout<<"Input "<<value<<" is out of bounds ("<<lower_limit<<","<<upper_limit<<"). "
                <<"Enter a new value: ";
                std::cin>>value;
            } while (std::cin.fail());
            
            validate_numerical_input(value,lower_limit,upper_limit);
        }
    }
}

// Function to check that a string input is allowed
void validate_string_input(std::string &input, std::vector<std::string> allowed_types)
{
    const int InvalidInput{-1};
    bool valid_input;
    try
    {
        for (int i{0};i<allowed_types.size();++i)
        {
            valid_input += (input==allowed_types[i]);
        }

        if (!valid_input)  {throw InvalidInput;}
    }

    catch (int ErrorFlag)
    {
        if (ErrorFlag==InvalidInput)
        {
            
            do 
            {
                // Clear fail and ignore bad input
                std::cin.clear(); 
                std::cin.ignore(1000, '\n');
                std::cout<<input<<" is an invalid input. Please enter one of the following: "<<std::endl;
                for (int i{0};i<allowed_types.size();++i) {std::cout<<allowed_types[i]<<'.';}
                std::cin>>input;

            } while (std::cin.fail());
            
            validate_string_input(input,allowed_types);
        }
    }
}

#endif
