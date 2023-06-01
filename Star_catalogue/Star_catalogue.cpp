// PHYS 30762 Programming in C++
// ------------------------------------------------------------------------------------------------------
// Star_catalogue.cpp
// The program allows the user to collect data from different observations and perform data manipulation 
// by finding, deleting and sorting specific objects. Functions for data visualisation and for calculating
// physical quantities, such as the apparent magnitude of stars, are also implemented. The program also 
// allows the user to collect and save the derived properties of the objects into external files.
// ------------------------------------------------------------------------------------------------------
// Andrea Sante, last updated: 21/05/2022.
// ------------------------------------------------------------------------------------------------------


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <memory>
#include <math.h>

#include "Star_catalogue.h"
#include "galaxy.h"
#include "star.h"
#include "planet.h"

#include "Star_catalogue_functions.cpp"


int main() 
{
    
    // Reading data from multiple files 
    // The following inputs are recommended:
    //  - "exoplanet.eu_catalog.csv", "y"
    //  - "stars.txt", "t", "n"
    std::vector< std::shared_ptr<celestial_object> > data{read_data()};
    
    // Print type and name of objects read
    print_data(data);

    // Sort data by object name
    sort(data.begin(), data.end(), sort_by_name<celestial_object>);
    print_data(data);

    // Add new object to data from keyboard
    std::shared_ptr<celestial_object> new_object{create_new_object()};
    data.push_back(new_object);
    print_data(data);

    // Create three vectors containing only a certain type of objects
    std::vector< std::shared_ptr<celestial_object> > galaxies{get_objects("galaxy",data)};
    std::vector< std::shared_ptr<celestial_object> > stars{get_objects("star",data)};
    std::vector< std::shared_ptr<celestial_object> > planets{get_objects("planet",data)};


    //====================================================================================//
    //
    //              Testing data manipulation functions with galaxy vector
    //
    //====================================================================================//

    
    //Print content of starting vector
    print_data(galaxies);

    // Validate content of galaxy vector
    for (int i{0}; i<galaxies.size(); ++i) {galaxies[i]->validate_parameters();}

    // Print content of mock galaxy
    galaxy mock_galaxy{*galaxies[0]};
    // Delete mock galaxy in the vector by specifying the ID
    galaxies = delete_object(mock_galaxy.get_ID(), galaxies);
    std::cout<<"Deleting mock galaxy..."<<std::endl;
    print_data(galaxies);
    std::cout<<"Searching for mock galaxy..."<<std::endl;
    find_by_name(mock_galaxy.get_Name(), galaxies);


    //====================================================================================//
    //
    //              Computing physics quantities using the star vector
    //
    //====================================================================================//
    

    // Sort stars by flux 
    sort(stars.begin(), stars.end(), sort_by_flux<celestial_object>);
    std::cout<<"The brightest star in the catalogue is "<<stars[0]->get_Name()<<"!"<<std::endl;
    star brightest_star{*stars[0]};
    std::cout<<brightest_star.get_Name()<<" has an apparent magnitude of "<<
    brightest_star.get_Apparent_Magnitude()<<"."<<std::endl;
    brightest_star.info();

    // Sort stars by distance
    sort(stars.begin(), stars.end(), sort_by_distance<celestial_object>);
    std::cout<<"The closest star in the catalogue is "<<stars[0]->get_Name()<<"!"<<std::endl;
    star closest_star{*stars[0]};
    std::cout<<closest_star.get_Name()<<" is "<< closest_star.get_Distance()<<
    " pc away from Earth."<<std::endl;
    closest_star.info();

    
    // Extract parameters to plot the HR diagram for the stellar population
    std::vector<double> absolute_magnitude;  
    std::vector<std::string> spectral_classes;

    for (int i{0};i<stars.size();++i)
    {
        std::shared_ptr<star> object(new star{*stars[i]});

        absolute_magnitude.push_back(object->get_Absolute_Magnitude());
        spectral_classes.push_back(object->get_Spectral_class());

    }
    
    // Save data in a csv file for plotting 
    save_arrays_2D_plot(absolute_magnitude, spectral_classes, "HR_diagram_M_vs_Sclass");

    // Save information of stars objects into an external file
    save_data(stars, "Stars_hold.dat");
    
    //====================================================================================//
    //
    //              Testing general operation of functions with planet vector
    //
    //====================================================================================//


    // Sort planets by distance
    sort(planets.begin(), planets.end(), sort_by_distance<celestial_object>);
    std::cout<<"The closest exoplanet to Earth is "<<planets[0]->get_Name()<<"!"<<std::endl;
    std::cout<<planets[0]->get_Name()<<" is distant "<<planets[0]->get_Distance()
    <<" pc from Earth."<<std::endl;

    // Find a random exoplanet in the vector (ID: ASTRO+4352)
    planet exoplanet{*find_by_id(4352, planets)};
    exoplanet.info();

    // Collect equatorial coordinates of exoplanets to make star chart
    std::vector<double> RA_array{get_ra_array(data)};
    std::vector<double> DEC_array{get_dec_array(data)};
    //Save data in a csv file for plotting 
    save_arrays_2D_plot(RA_array, DEC_array, "Star_chart");


    return 0;

}
