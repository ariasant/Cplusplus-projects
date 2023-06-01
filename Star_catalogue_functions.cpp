// PHYS 30762 Programming in C++
// ------------------------------------------------------------------------------------------------------
// Star_catalogue_functions.cpp
// This file contains all the functions used for readin-in, manipulate and save data from astronomical
// objects.
// ------------------------------------------------------------------------------------------------------
// Andrea Sante, last updated: 21/05/2022.
// ------------------------------------------------------------------------------------------------------



std::string get_file_name()
{
    std::string filename{};
    std::ifstream input_file;

    // Ask user to enter the name of the file
    std::cout << "\rEnter name of file you want to open: ";
    std::cin >> filename;
    input_file.open(filename);
    // Check if it is possible to open file
    while (!input_file.is_open()) 
    {
        std::cout<<"Cannot open file correctly or file was not found. "<<
        "Please enter another data filename: ";
        std::cin>>filename;
        input_file.open(filename);
    }

    return filename;
}

// Check whether the file exists in the working directory
bool file_exist(const std::string &filename)
{
    std::ifstream file_to_check(filename);

    return file_to_check.good();

}

// Create a new celestial object based on the specific type and parameters
std::unique_ptr<celestial_object> create_new_object(std::string parameters, 
std::string object_type, char delimiter)
{

    std::stringstream object_parameters(parameters);

    // Define error flag
    const int UndefinedObject{-1};
    std::unique_ptr<celestial_object> new_object;
    try 
    {
        if (object_type == "galaxy")
        {
            new_object.reset(new galaxy{object_parameters, delimiter});
        }
        else if (object_type == "star")
        {
            new_object.reset(new star{object_parameters, delimiter});
        }
        else if (object_type == "planet")
        {
            new_object.reset(new planet{object_parameters, delimiter});
        }
        else {throw UndefinedObject;}
    }
    catch(int ErrorFlag) 
    { 
        if (ErrorFlag==UndefinedObject)
        {
            std::cout<<"Unknown celestial object '"<<object_type<<
            "'. Object could not be created."<<std::endl;
        }
    }
    
    return new_object;

};


// Creating new celestial object from keyboard
std::unique_ptr<celestial_object> create_new_object()
{
    std::string object_type;
    const std::vector<std::string> allowed_objects{"galaxy", "star", "planet"};

    std::cout<<"Creating a new celestial object."<<std::endl;
    std::cout<<"What type of object do you want to create? ";
    std::cin >> object_type;
    validate_string_input(object_type, allowed_objects);

    if (object_type=="galaxy") {return create_new_obj<galaxy>();}
    else if (object_type=="star") {return create_new_obj<star>();}
    else if (object_type=="planet") {return create_new_obj<planet>();}

    else {return nullptr;}
};


// Read data collected in one file
std::vector< std::shared_ptr<celestial_object> > read_data_from_file()
{
    std::ifstream input_file;
    std::string line{};  

    // Get name of the file to open
    std::string filename{get_file_name()};
    std::string user_input;

    input_file.open(filename);
    
    // Get the delimiter between parameter values in the file
    char delimiter;
    // Delimiter defined by default for csv files
    if ( filename.substr(filename.length()-3,filename.back()) == "csv")
    {
        delimiter =',';
    }
    else
    {
        std::cout<<"Enter file entries delimiter (t for tab and s for space): ";
        std::cin>>user_input;
        if (user_input=="t" ){delimiter='\t';}
        else if(user_input=="s"){delimiter=' ';}
        else {delimiter = *(user_input.c_str());} 
    }
        
    // Initialise variables
    std::string object_type;

    // Collect objects in vector
    std::vector< std::shared_ptr<celestial_object> > observed_objects;
    // Skip Header
    std::getline(input_file, line); 
    // Read data from file
    while  ( std::getline(input_file, line, '\n') ) 
    {
        // Extract object type
        std::size_t pos = line.find(delimiter);
        object_type = line.substr(0,pos);

        line.erase(line.begin(), line.begin()+pos+1);

        observed_objects.push_back(create_new_object(line, object_type, delimiter));
        
    }
    
    input_file.close();
    
    return observed_objects;   
};


// Read data from multiple files
std::vector< std::shared_ptr<celestial_object> > read_data()
{
    std::vector< std::shared_ptr<celestial_object> > objects_in_file;
    std::vector< std::shared_ptr<celestial_object> > objects_read;

    std::string command;
    std::vector<std::string> allowed_commands{"y", "n"};

    do {
        objects_in_file = read_data_from_file();

        // Append new data to existing data
        objects_read.insert(objects_read.end(), objects_in_file.begin(), objects_in_file.end());

        std::cout<<"Do you want to read another file? ('y'/'n') ";
        std::cin>>command;
        validate_string_input(command, allowed_commands);

    } while (command=="y");

    // Print number of objects read
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"Number of objects collected: "<<objects_read[0]->get_Objects_Count()<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;
    std::cout<<"Number of galaxies: "<<objects_read[0]->get_Galaxy_Count()<<std::endl;
    std::cout<<"Number of stars: "<<objects_read[0]->get_Stars_Count()<<std::endl;
    std::cout<<"Number of planets: "<<objects_read[0]->get_Planets_Count()<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;
    

    return objects_read;
}

// Print type and name of objects contained in a vector
void print_data(std::vector< std::shared_ptr<celestial_object> > objects)
{

    // Print content of vectors with less than 10 elements
    if (objects.size()<10) 
    {
        for (int i{0}; i<objects.size(); ++i)
        {
            std::cout<<objects[i]->get_Type()<<"\t"<<objects[i]->get_Name()<<std::endl;
        }
    }
    // Allow the user to choose how many elements to visualise
    else
    {
        std::string command;
        std::vector<std::string> allowed_commands{"y","n"};
        int i{0};
        int o{1};
        auto limit = objects.size();
        do 
        {
            
            while ( (i<o*10) && (i<limit) )
            {
                std::cout<<objects[i]->get_Type()<<"\t"<<objects[i]->get_Name()<<std::endl;
                ++i;
            }
            
            if (i<limit)
            {
                std::cout<<"... Do you want to load more data? ('y'/'n') ";
                std::cin>>command;
                validate_string_input(command, allowed_commands);
                ++o;
            }
            else {command="n";}
            

        } while (command=="y");

    }
    
    
};

// Removes a particular celestial object from the vector
template <class c_type> std::vector<std::shared_ptr<c_type>> delete_object(double object_id, 
std::vector< std::shared_ptr<c_type> > data)
{

    // Create vector with the IDs of the objects in data
    std::vector<double> data_IDs;
    
    for (int i{0}; i<data.size(); ++i)
    {
        data_IDs.push_back(data[i]->get_ID());
    }
    
    std::vector<double>::iterator begin_data_ID{data_IDs.begin()};
    std::vector<double>::iterator end_data_ID{data_IDs.end()};

    const int ObjNotFound{-1};

    auto object_position = find(begin_data_ID, end_data_ID, object_id)-begin_data_ID;
    
    try
    {
        // If the object is not in the vector
        if ( object_position >= data_IDs.size() )  
        {
            throw ObjNotFound;
        }

        // Delete object found in vector
        std::vector<std::shared_ptr<celestial_object>>::iterator it{data.begin()+object_position};
        data.erase(it);  

    }
    catch (int ErrorFlag)
    {
        if (ErrorFlag==ObjNotFound) {std::cout<<"Object not found."<<std::endl;}
    }

    return data;
}


// Removes a particular celestial object from the vector 
template <class c_type> std::vector<std::shared_ptr<c_type>> delete_object_by_name(double object_name, 
std::vector< std::shared_ptr<c_type> > data)
{

    // Create vector with the names of the objects in data
    std::vector<std::string> data_names;
    
    for (int i{0}; i<data.size(); ++i)
    {
        data_names.push_back(data[i]->get_Name());
    }
    
    std::vector<std::string>::iterator begin_data_names{data_names.begin()};
    std::vector<std::string>::iterator end_data_names{data_names.end()};

    const int ObjNotFound{-1};

    auto object_position = find(begin_data_names, end_data_names, object_name)-begin_data_names;
    
    try
    {
        
        if ( object_position >= data_names.size() )  
        {
            throw ObjNotFound;
        }

        std::vector<std::shared_ptr<celestial_object>>::iterator it{data.begin()+object_position};
        data.erase(it);  

    }
    catch (int ErrorFlag)
    {
        if (ErrorFlag==ObjNotFound) {std::cout<<"Object not found."<<std::endl;}
    }

    return data;
}


// Find object in vector by specifying the name of the object
template <class c_type> std::shared_ptr<c_type> find_by_id(double object_id, 
std::vector< std::shared_ptr<c_type> > data)
{

    // Create vector with the IDs of the objects in data
    std::vector<double> data_IDs;
    
    for (int i{0}; i<data.size(); ++i)
    {
        data_IDs.push_back( data[i]->get_ID()  );
    }
    
    std::vector<double>::iterator begin_data_ID{data_IDs.begin()};
    std::vector<double>::iterator end_data_ID{data_IDs.end()};

    const int ObjNotFound{-1};

    auto object_position = find(begin_data_ID, end_data_ID, object_id)-begin_data_ID;
    std::shared_ptr<c_type> object_found;

    try
    {
        
        if ( object_position >= data_IDs.size() )  
        {
            throw ObjNotFound;
        }

        object_found = data[object_position];
       
    }
    catch (int ErrorFlag)
    {
        if (ErrorFlag==ObjNotFound) 
        {
            std::cout<<"Object not found."<<std::endl;
            object_found = nullptr;
        }
    }
    
    return object_found;
}


// Find object in vector by specifying the name of the object
template <class c_type> std::shared_ptr<c_type> find_by_name(std::string object_name, 
std::vector< std::shared_ptr<c_type> > data)
{

    // Create vector with the IDs of the objects in data
    std::vector<std::string> data_names;
    
    for (int i{0}; i<data.size(); ++i)
    {
        data_names.push_back(data[i]->get_Name() ) ;
    }
    
    std::vector<std::string>::iterator begin_data_names{data_names.begin()};
    std::vector<std::string>::iterator end_data_names{data_names.end()};

    const int ObjNotFound{-1};

    auto object_position = find(begin_data_names, end_data_names, object_name)-begin_data_names;
    std::shared_ptr<c_type> object_found;
    try
    {
        
        if ( object_position >= data_names.size() )  
        {
            throw ObjNotFound;
        }

        object_found = data[object_position];
       

    }
    catch (int ErrorFlag)
    {
        if (ErrorFlag==ObjNotFound) 
        {
            std::cout<<"Object not found."<<std::endl;
            object_found = nullptr;
        }
    }

    return object_found;
}

// Collect RA for all objects in the vector
template <class c_type> std::vector<double> get_ra_array(std::vector<std::shared_ptr<c_type>> data)
{
    std::vector<double> ra_array;

    for (int i{0}; i<data.size(); ++i)
    {
        ra_array.push_back( data[i]->get_RA() );
    }

    return ra_array;
}

// Collect DEC for all objects in the vector
template <class c_type> std::vector<double> get_dec_array(std::vector<std::shared_ptr<c_type>> data)
{
    std::vector<double> dec_array;

    for (int i{0}; i<data.size(); ++i)
    {
        dec_array.push_back( data[i]->get_DEC() );
    }

    return dec_array;
}


// Create a vector with objects of the same type
std::vector< std::shared_ptr<celestial_object> > get_objects( std::string type,
    std::vector< std::shared_ptr<celestial_object> > data)
{
    std::vector< std::shared_ptr<celestial_object> >::iterator begin_vector{data.begin()};
    std::vector< std::shared_ptr<celestial_object> >::iterator end_vector{data.end()};
    std::vector< std::shared_ptr<celestial_object> >::iterator iterator;

    std::vector<std::shared_ptr<celestial_object>> objects;
    std::shared_ptr<celestial_object> object;

    // Check if each object is of the specified type
    for (iterator=begin_vector; iterator!=end_vector; ++iterator)
    {

        if ( (*iterator)->get_Type() == "galaxy" && type == "galaxy" )
        {
            std::stringstream parameters_to_copy{(*iterator)->get_info()};
            object.reset(new galaxy{parameters_to_copy, '\t'});
            // Copy ID from galaxy to copy
            object->set_Id( (*iterator)->get_ID() );  
            objects.push_back(object);         

        }
        else if ( (*iterator)->get_Type() == "star" && type == "star" )
        {
            std::stringstream parameters_to_copy{(*iterator)->get_info()};
            object.reset(new star{parameters_to_copy});
            // Copy ID from galaxy to copy
            object->set_Id( (*iterator)->get_ID() );
            objects.push_back(object);

        }
        else if ( (*iterator)->get_Type() == "planet" && type == "planet" )
        {
            std::stringstream parameters_to_copy{(*iterator)->get_info()};
            object.reset(new planet{parameters_to_copy});
            // Copy ID from galaxy to copy
            object->set_Id( (*iterator)->get_ID() );
            objects.push_back(object);

        }
        
    }

    return objects;
};


// Save two arrays of double into a csv file
template <class c_type1, class c_type2> void save_arrays_2D_plot(
    std::vector<c_type1> arr1, std::vector<c_type2> arr2, std::string filename)
{

    const int VectorMismatch{-1};
    const int ReadingError{-2};

    std::string command;
    std::vector<std::string> allowed_commands{"a", "o"};
    std::ofstream output_file;
    
    // Check if file already exists in working directory
    if ( file_exist(filename+".csv") )
    {
        // Ask the user if wants to overwrite the already existing file
        std::cout<<"File '"<<filename<<".csv' already exists. Do you want to append ('a')"
        <<" or overwrite ('o') the content? ";
        std::cin>>command;
        validate_string_input(command, allowed_commands);
        
        if (command==allowed_commands[0]) {output_file.open(filename+".csv", std::ios_base::app);}
        else if (command==allowed_commands[1]) {output_file.open(filename+".csv");}
    }

    else {output_file.open(filename+".csv");}
    
    // Save elements of first vector in the first column and of second vector in the second column
    try
    {
        // Check that all vectors have same size
        if (arr1.size() != arr2.size()) {throw VectorMismatch;}

        else if (!output_file.is_open()) {throw ReadingError;}
        
        for (int i{0}; i<arr1.size(); ++i)
        {
            output_file << arr1[i] << "," << arr2[i] << "\n";
        }
    }

    catch (int ErrorFlag)
    {
        if (ErrorFlag==VectorMismatch)
        {
            std::cout<<"Error. Vector of size "<<arr1.size()<<"cannot be plotted with "
            <<"vector of size "<<arr2.size()<<". Vector were not saved.";

            output_file.close();
        }
        else if (ErrorFlag==ReadingError)
        {
            std::cout<<"Error. Cannot open file '"<<filename<<"' correctly."
            <<std::endl;

            output_file.close();
        }
    }
    
};

// Save three arrays of double into a csv file
template <class c_type1, class c_type2, class c_type3> void save_arrays_3D_plot(
std::vector<double> arr1, std::vector<double> arr2, std::vector<double> arr3, std::string filename)
{
    
    const int VectorMismatch{-1};
    const int ReadingError{-2};

    std::string command;
    std::vector<std::string> allowed_commands{"a", "o"};
    std::ofstream output_file;
    
    if ( file_exist(filename+".csv") )
    {
        std::cout<<"File '"<<filename<<".csv' already exists. Do you want to append ('a')"
        <<" or overwrite ('o') the content? ";
        std::cin>>command;
        validate_string_input(command, allowed_commands);
        
        if (command==allowed_commands[0]) {output_file.open(filename+".csv", std::ios_base::app);}
        else if (command==allowed_commands[1]) {output_file.open(filename+".csv");}
    }
    else {output_file.open(filename+".csv");}
    
    // Save elements of first vector in the first column; of second vector in second columns; of third
    // third vector in the third column.
    try
    {
        // Check that all vectors have same size
        if (arr1.size() != arr2.size() || arr1.size() != arr3.size() || arr2.size() != arr3.size()) 
        {
            throw VectorMismatch;
        }

        else if (!output_file.is_open()) {throw ReadingError;}
        
        for (int i{0}; i<arr1.size(); ++i)
        {
            output_file << arr1[i] << "," << arr2[i] << "," << arr3[i] << "\n";
        }
    }

    catch (int ErrorFlag)
    {
        if (ErrorFlag==VectorMismatch)
        {
            std::cout<<"Error. Vector of size "<<arr1.size()<<", "
            <<arr2.size()<<", "<<arr3.size()<<"cannot be plotted together."
            <<"Vectors were not saved.";

            output_file.close();
        }
        else if (ErrorFlag==ReadingError)
        {
            std::cout<<"Error. Cannot open file '"<<filename<<"' correctly."
            <<std::endl;

            output_file.close();
        }
    }
    
};

// Save objects into an external file
template <class c_type> void save_data(std::vector<std::shared_ptr<c_type>> data, std::string filename)
{
    const int ReadingError{-2};

    std::string command;
    std::vector<std::string> allowed_commands{"a", "o"};
    std::ofstream output_file;
    
    if ( file_exist(filename) )
    {
        std::cout<<"File '"<<filename<<".txt' already exists. Do you want to append ('a')"
        <<" or overwrite ('o') the content? ";
        std::cin>>command;
        validate_string_input(command, allowed_commands);
        
        if (command==allowed_commands[0]) {output_file.open(filename, std::ios_base::app);}
        else if (command==allowed_commands[1]) {output_file.open(filename);}
    }
    else {output_file.open(filename);}
    
    //Save elements of first vector in the first column;
    try
    {
       if (!output_file.is_open()) {throw ReadingError;}

       for (int i{0}; i<data.size(); ++i)
       {
           std::stringstream object_parameters{data[i]->get_info()};
           output_file << data[i]->get_Type() << "\t" << object_parameters.rdbuf() << "\n";
       }
    }

    catch (int ErrorFlag)
    {
        if (ErrorFlag==ReadingError)
        {
            std::cout<<"Error. Cannot open file '"<<filename<<"' correctly."
            <<std::endl;

            output_file.close();
        }
    }
    
};





