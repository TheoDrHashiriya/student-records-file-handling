#include <iostream>

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
  std::cin >> option;
}
