#include <ios>
#include <iostream>
#include <limits>

const int MAX_STUDENTS = 1000;

struct Student {
  std::string name;
  std::string studentID;
  std::string course;
  int yearLevel;
  float finalGrade;
};

int main() {
  int option;
  std::cout << "1. Add a student record\n"
               "2. View all records\n"
               "3. Search a record by Student ID\n"
               "4. Update a record\n"
               "5. Exit\n"
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

    if (option < 1 || option > 5) {
      std::cout << "Option should be between 1 and 5! Try again: ";
      continue;
    } else {
      isValid = true;
    }
  }

  // Main logic stuff
}
