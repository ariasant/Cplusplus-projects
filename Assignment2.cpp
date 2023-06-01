// PHYS 30762 Programming in C++
// ------------------------------------------------------------------------------------------------------
// Assignment2.cpp
// This program stores and prints Physics courses and calculates the average mark (with uncertainty) and
// standard deviation of mark ditribution. It also allows the user to visualise course information for
// a particular year and to sort the corresponding list of courses by title or course code.
// ------------------------------------------------------------------------------------------------------
// Andrea Sante, last updated: 28/02/2022.
// ------------------------------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// Function to compute mean
double mean(std::vector<double> array)
{
    // Calculate the sum of all the elements in the vector
    double sum_of_elements{};
    for(std::vector<double>::iterator it = array.begin(); it != array.end(); ++it){
        sum_of_elements += *it;
    }
    double mean{sum_of_elements/array.size()};
    return mean;
}

// Function to compute standard deviation
double standard_deviation(std::vector<double> array)
{
    double mean_of_array = mean(array);
    // Number of elements in the array
    auto N = array.size();
    double sum_of_squared_deviations;
    for(std::vector<double>::iterator it = array.begin(); it != array.end(); ++it){
        sum_of_squared_deviations += pow(*it-mean_of_array,2);
    }
    double std = sqrt( pow(N-1,-1)*sum_of_squared_deviations);
    return std;
}

// Function to sort courses by course code
bool compare_course_code(std::string course_1, std::string course_2)
{
    unsigned int course_code_1 = std::stoi(course_1.substr(5, 5));
    unsigned int course_code_2 = std::stoi(course_2.substr(5, 5));
    bool comparison = course_code_1 < course_code_2;
    return comparison;
}

// Function to sort courses by course title
bool compare_course_title(std::string course_1, std::string course_2)
{
    std::string course_title_1 = course_1.substr(10, course_1.size()-4);
    std::string course_title_2 = course_2.substr(10, course_2.size()-4);
    bool comparison = course_title_1 < course_title_2;
    return comparison;
}


int main()
{
    std::string filename{};
    std::ifstream input_file;
    std::string line{};
    char plus_minus=241;

    // Ask user to enter the name of the file
    std::cout << "\rEnter data filename: ";
    std::cin >> filename;
    // Open file and check if successful
    input_file.open(filename);
    while (!input_file.is_open()) {
        std::cout<<"Cannot open file correctly or file was not found. "<<
        "Please enter another data filename: ";
        std::cin>>filename;
        input_file.open(filename);
    }

    // Determine number of data lines in the file
    int number_of_datalines{};
    while (std::getline(input_file, line)){
        ++number_of_datalines;
    }
    input_file.close();

    input_file.open(filename);
    if (input_file.is_open()){
         // Allocate memory for data
        double *course_marks = new double[number_of_datalines];
        std::string *course_list = new std::string[number_of_datalines];
        // Initialise variables
        unsigned int course_code{};
        std::string course_name{};
        std::ostringstream course_title;
        std::ostringstream course_data;
        int i{0};
        // Read data from file
        while ( std::getline(input_file, line) ){
            // Extract course mark from line and covert it to a double
            course_marks[i] = std::stod(line.substr(0,4));
            // Extract course code from line
            course_code = std::stoi(line.substr(5, 5));
            // Delete course mark and code from line
            line.erase (line.begin(), line.begin()+12);
            course_name = line;
            // Stream course code and name into course title
            course_title<<"PHYS"<<course_code<<course_name;
            // Stream course title and mark into course_data
            course_data<<course_title.str()<<"\t"<<course_marks[i];
            course_list[i] = course_data.str();
            // Clear stream contents
            course_title.str(""); 
            course_data.str("");
            // Update iterator
            ++i;
        }
        // Close file
        input_file.close();
        i = 0;
        // Create course_marks and course_list vectors
        std::vector<double> course_marks_vector;
        std::vector<std::string> course_list_vector;
        for (i;i<number_of_datalines;++i){
            course_marks_vector.push_back(course_marks[i]);
            course_list_vector.push_back(course_list[i]);
        }
        // Calculate number of data in the file
        std::cout<<"Number of data lines: "<<course_marks_vector.size()<<" ."<<std::endl;
        std::cout.setf(std::ios::fixed,std::ios::floatfield);
        // Calculate average course mark and relative uncertainty
        double error_mean_mark = standard_deviation(course_marks_vector)/sqrt(course_marks_vector.size());
        std::cout<<"Average course mark: "<<std::setprecision(1)<<mean(course_marks_vector)<<plus_minus<<
        std::setprecision(1)<<error_mean_mark<<" ."<<std::endl;
        // Calculate standard deviation of mark distribution
        std::cout<<"Standard deviation of mark distribution: "<<std::setprecision(1)<<
        standard_deviation(course_marks_vector)<<" ."<<std::endl;
        // Free memory
        delete[] course_marks;
        course_marks_vector.clear();
        
        // Ask user if wants to print out course list
        std::string yes_or_no{};
        while (yes_or_no!="y" && yes_or_no!="n"){
            std::cout<<"Do you want to print the full list of courses (y/n)? "<<std::endl;
            std::cin>>yes_or_no;
            if (yes_or_no!="y" && yes_or_no!="n"){
                std::cout<<"Invalid input. ";
                // Clear fail and ignore bad input
                std::cin.clear(); 
                std::cin.ignore(1000, '\n'); 
            }
        }
        // Define iterators to manipulate course_list vector
        std::vector<std::string>::iterator iterator_vector;
        std::vector<std::string>::iterator vector_begin{course_list_vector.begin()};
        std::vector<std::string>::iterator vector_end{course_list_vector.end()};

        if (yes_or_no=="y"){
            // Print out information for each course using an iterator
            for(iterator_vector=vector_begin;iterator_vector<vector_end;++iterator_vector){
                std::cout<<*iterator_vector<<std::endl;
            }
        }

        // Ask user if wants to print out course info for a specific year
        do {
            std::cout<<"Do you want to print the list of courses for a specific year (y/n)? "<<std::endl;
            std::cin>>yes_or_no;
            if (yes_or_no!="y" && yes_or_no!="n"){
                std::cout<<"Invalid input. ";
                // Clear fail and ignore bad input
                std::cin.clear(); 
                std::cin.ignore(1000, '\n'); 
            }
        } while(yes_or_no!="y" && yes_or_no!="n");

        if (yes_or_no=="y"){
            // Allow the user to choose the year of interest
            std::string year{};
            while (year!="1" && year!="2" && year!="3" && year!="4"){
                std::cout<<"what year are you interested in (1/2/3/4)? "<<std::endl;
                std::cin>>year;
                if (year!="1" && year!="2" && year!="3" && year!="4"){
                    std::cout<<"Invalid input. ";
                    // Clear fail and ignore bad input
                    std::cin.clear(); 
                    std::cin.ignore(1000, '\n');
                }
            } 
            // Find number of courses in that year
            int number_of_courses=0;
            for (iterator_vector=vector_begin;iterator_vector<vector_end;++iterator_vector){
                if ((*iterator_vector).find("PHYS"+year)!= std::string::npos){
                    ++number_of_courses;
                }
            }
            std::cout<<number_of_courses<<" courses were found."<<std::endl;
            // Find course mark and title for each course of that year
            std::vector<std::string> course_list_str;
            std::string course_mark_str;
            course_marks = new double[number_of_courses];
            std::string *course_list_year = new std::string[number_of_courses];
            i=0;
            for(iterator_vector=vector_begin;iterator_vector<vector_end;++iterator_vector){
                if ((*iterator_vector).find("PHYS"+year)!= std::string::npos){
                    // If course mark is an integer
                    if ((*iterator_vector).end()[-3]=='\t'){
                        course_mark_str = (*iterator_vector).substr((*iterator_vector).size()-2,2);
                        course_marks[i] = std::stod(course_mark_str);
                        course_list_year[i] = (*iterator_vector).substr(0, (*iterator_vector).find(course_mark_str));
                        ++i;
                    } else {
                        // If course mark has decimals               
                        course_mark_str = (*iterator_vector).substr((*iterator_vector).size()-4,4);
                        course_marks[i] = std::stod(course_mark_str);
                        course_list_year[i] = (*iterator_vector).substr(0, (*iterator_vector).find(course_mark_str));
                        ++i;
                    }   
                }
            }
            // Create vectors containing course marks and titles
            i=0;
            course_list_vector.clear();
            for (i;i<number_of_courses;++i){
                course_marks_vector.push_back(course_marks[i]);
                course_list_vector.push_back(course_list_year[i]);
            }
            // Calculate average course mark and relative uncertainty
            std::cout<<"Average mark for the year: "<<std::setprecision(1)<<mean(course_marks_vector)<<plus_minus
            <<standard_deviation(course_marks_vector)/sqrt(course_marks_vector.size())<<" ."<<std::endl;
            // Calculate standard deviation for mark distribution
            std::cout<<"Standard deviation for the mark distribution: "<<std::setprecision(1)
            <<standard_deviation(course_marks_vector)<<" ."<<std::endl;
            // Ask user how the list of courses should be printed
            std::string marker{};
            while (marker!="cc" && marker!="ct"){
                std::cout<<"Do you want to sort the courses by course code (cc) or course title (ct)? ";
                std::cin>> marker;
                if (marker!="cc" && marker!="ct"){
                    std::cout<<"Invalid input. ";
                    // Clear fail and ignore bad input
                    std::cin.clear(); 
                    std::cin.ignore(1000, '\n');
                }
            }
            // Define iterators to manipulate course_list vector
            vector_begin = course_list_vector.begin();
            vector_end = course_list_vector.end();
            if (marker=="cc"){
                // Sort by course code
                sort(vector_begin,vector_end, compare_course_code);
                // Print course list
                for(iterator_vector=vector_begin;iterator_vector<vector_end;++iterator_vector){
                    std::cout<<*iterator_vector<<std::endl;
                }
            } else if (marker=="ct"){
                // Sort by course title
                sort(vector_begin, vector_end, compare_course_title);
                // Print course list
                for(iterator_vector=vector_begin;iterator_vector<vector_end;++iterator_vector){
                    std::cout<<*iterator_vector<<std::endl;
                }
            }
        }
    } else std::cout<<"Cannot open file correctly.";
    return 0;
}
    
