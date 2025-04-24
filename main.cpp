#include <iostream>
#include <ios>
#include <fstream>
#include <limits>


const int MAX_STUDENTS = 1000;

struct Student {
  std::string name;
  std::string studentID;
  std::string course;
  int yearLevel;
  float finalGrade;
};

void createNewStudent(Student stu[], int count){
  std::ofstream outFile("data.txt", std::ios::app);
  Student newStudent;

  if (outFile.is_open()){
    std::cout << "ADD NEW INFO" << std::endl;
    
    std::cout << "Enter an ID: ";
    std::cin >> newStudent.studentID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the Name: ";
    std::getline(std::cin, newStudent.name); 

    std::cout << "Enter the Course: ";
    std::getline(std::cin,newStudent.course);

    std::cout << "Enter Year Level: ";
    while (!(std::cin >> newStudent.yearLevel)) {
      std::cout << "Invalid input. Enter a number for Year Level: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter the Final Grade: ";
    std::cin >> newStudent.finalGrade;

    outFile << newStudent.name << " " << newStudent.studentID << " " 
            << newStudent.course << " " << newStudent.yearLevel << " " 
            << newStudent.finalGrade << std::endl;
    outFile.close();
    
    stu[count++] = newStudent;
    std::cout << "\n Added Succefully!!" << std::endl;
  } else {
    std::cerr << "Failed to open the file for writing" << std::endl;
  }


}

int main() {
  int option;
  int count = 0;
  Student studentRecord[MAX_STUDENTS];

  do{
    
    std::cout << "1. Add a student record\n"
    "2. View all records\n"
    "3. Search a record by Student ID\n"
    "4. Update a record\n"
    "5. Delete a record\n"
    "6. Exit\n"
    "Enter option: ";

    bool isValid = false;

    // Input validation for option
    while (!isValid) {
    if (!(std::cin >> option)) {
    std::cout << "Option should be a number! Try again: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    continue;
    }

    if (option < 1 || option > 6) {
    std::cout << "Option should be between 1 and 6! Try again: ";
    continue;
    } else {
    isValid = true;
    }
    }

    // Main logic stuff
    switch (option) {
      case 1:
        createNewStudent(studentRecord,count);
        break;
      case 2:
        
        break;

    default:
      break;
    } 

  } while (option != 0);
  



}
