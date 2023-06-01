// Assignment1.cpp
// This program returns the energy of a photon emitted after an electron tranistion.
// It allows the user to choose whether the energy is calculated in J or eV, and to
// re-run the code.
// --------------------------------------------------------------------------------
// Variables                |   Meaning
// --------------------------------------------------------------------------------
// atomic_number            |   The number of protons in the atom where the 
//                          |   transition occurs.
// --------------------------------------------------------------------------------
// initial_quantum_number   |   The principal quantum number of the state where 
//                          |   the transition starts.
// --------------------------------------------------------------------------------
// final_quantum_number     |   The principal quantum number of the state where 
//                          |   the transition ends.   
// --------------------------------------------------------------------------------
// Andrea Sante, last updated 16/02/2022

#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>

double transition_energy_eV(double atomic_number, double initial_quantum_number, 
                        double final_quantum_number) {
    double photon_energy;
    photon_energy = 13.6*pow(atomic_number,2)*
                    (  pow(final_quantum_number,-2) - pow(initial_quantum_number,-2)  );
    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    std::cout<<std::setprecision(2)<<photon_energy<<" eV."<<std::endl;
    return photon_energy;
}

double transition_energy_J(double atomic_number, double initial_quantum_number, 
                        double final_quantum_number) {
    // Declare constants needed for the calculation
    const double Rydberg_constant{10'973'731.6};  // 1/m
    const double speed_of_light_in_vacuum{299'792'458.}; // m / s
    const double planck_constant{6.62607004e-34}; // m2 kg / s
    double photon_energy;
    photon_energy = planck_constant*speed_of_light_in_vacuum*Rydberg_constant*
                    (  pow(final_quantum_number,-2) - pow(initial_quantum_number,-2)  );
    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    std::cout<<std::setprecision(2)<<photon_energy<<" J."<<std::endl;
    return photon_energy;
}


int main()
{
    double atomic_number{};
    double initial_quantum_number{};
    double final_quantum_number{};
    double photon_energy{};
    bool invalid_input{}; 
    bool is_negative{};
    bool is_non_integer{};
    bool is_unphysical{};
    std::string runner{}; // "y" to re-run the code and "n" to exit
    std::string units{}; // "J" for Joule and "e" for eV

    do {

        invalid_input=true;
        while (invalid_input) {
            // Ask user to enter atomic number 
            std::cout << "\rEnter a valid atomic number: ";
            std::cin >> atomic_number;
            // Check whether input is valid
            is_negative = atomic_number <= 0;
            is_non_integer = (atomic_number - int(atomic_number))  != 0;
            is_unphysical = atomic_number > 118;
            invalid_input = (std::cin.fail()) || is_negative || is_non_integer || is_unphysical;
            // Clear and ignore bad inputs
            if (invalid_input) {
                std::cin.clear(); 
                std::cin.ignore(1000,'\n'); 
            }
        }

        invalid_input = true;
        while (invalid_input) {
            // Ask user to enter an initial quantum number 
            std::cout << "\rEnter a valid initial quantum number: ";
            std::cin >> initial_quantum_number;
            // Check whether input is valid
            is_negative = initial_quantum_number < 1; //cannot be 0 
            is_non_integer = (initial_quantum_number - int(initial_quantum_number))  != 0;
            invalid_input = (std::cin.fail()) || is_negative || is_non_integer;
            // Clear and ignore bad input
            if (invalid_input) {
                std::cin.clear(); 
                std::cin.ignore(1000,'\n'); 
            }
        }

        invalid_input = true;
        while (invalid_input) {
            // Ask user to enter a final quantum number
            std::cout<<"\rEnter a valid final quantum number: ";
            std::cin>>final_quantum_number;
            // Check whether the input is valid
            is_negative = final_quantum_number <= 0;
            is_non_integer = (final_quantum_number - int(final_quantum_number))  != 0;
            // For a transition to occur:
            is_unphysical = final_quantum_number >= initial_quantum_number; 
            invalid_input = (std::cin.fail()) || is_negative || is_non_integer || is_unphysical;
            // Clear and ignore bad input
            if (invalid_input) {
                // Clear fail bit and ignore bad input
                std::cin.clear(); 
                std::cin.ignore(1000,'\n'); 
            }
        }

         do {
            // Ask the user to decide the units of the output
            std::cout<<"Do you want the photon energy to be expressed in Joules or eV? (J/e) ";
            std::cin>>units;
            // Check whether the input is correct
            invalid_input = (std::cin.fail()) || (units!="J" && units!="e");
            // Clear fail and ignore bad input
            if (invalid_input) {
                std::cout<<"Invalid input. "; // Error message
                std::cin.clear(); 
                std::cin.ignore(1000,'\n'); 
            }
        } while (invalid_input);

        if (units=="e"){
            std::cout<<"The energy of the photon emitted from the transition is ";
            // Calculates the energy of the photon emitted via the transition in eV
            photon_energy = transition_energy_eV(atomic_number, initial_quantum_number, final_quantum_number);
        }
        else if (units=="J"){
            std::cout<<"The energy of the photon emitted from the transition is ";
            // Calculates the energy of the photon emitted via the transition in J
            photon_energy = transition_energy_J(atomic_number, initial_quantum_number, final_quantum_number);
        }
        
    
        do {
            // Ask the user to re-run the program
            std::cout<<"Do you want to do a new calculation? (y/n) ";
            std::cin>>runner;
            // Check whether the input is correct
            invalid_input = (std::cin.fail()) || (runner!="y" && runner!="n");
            // Clear fail and ignore bad input
            if (invalid_input) {
                std::cout<<"Invalid input. "; // Error message
                std::cin.clear(); 
                std::cin.ignore(1000, '\n'); 
            }
        } while (invalid_input);
   
    } while (runner=="y"); 
    
    return 0;
}
