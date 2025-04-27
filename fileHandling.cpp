#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Student {
  std::string studentID;
  std::string name;
  std::string course;
  int yearLevel;
  float finalGrade;
};

class StudentManagementSystem {
private:
  std::string fileName;
  std::vector<Student> students;
  const int colWidth = 20;

  // Clear input buffer and handle invalid inputs
  void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Validate numeric input
  template <typename T>
  T getValidInput(const std::string &prompt, T min, T max) {
    T value;
    bool validInput = false;

    do {
      std::cout << prompt;
      if (std::cin >> value) {
        if (value >= min && value <= max) {
          validInput = true;
        } else {
          std::cout << "Error: Value must be between " << min << " and " << max
                    << ".\n";
        }
      } else {
        std::cout << "Error: Invalid input. Please enter a number.\n";
        clearInputBuffer();
      }
    } while (!validInput);

    clearInputBuffer();
    return value;
  }

  // Get string input with validation
  std::string getStringInput(const std::string &prompt,
                             bool allowSpaces = false) {
    std::string input;
    std::cout << prompt;

    if (allowSpaces) {
      clearInputBuffer(); // Clear any previous input
      std::getline(std::cin, input);
    } else {
      std::cin >> input;
      clearInputBuffer();
    }

    return input;
  }

  // Load all student records from the file
  bool loadRecords() {
    students.clear();
    std::ifstream inFile(fileName);

    if (!inFile.is_open()) {
      return false;
    }

    Student student;
    while (inFile >> student.studentID >> student.name >> student.course >>
           student.yearLevel >> student.finalGrade) {
      students.push_back(student);
    }

    inFile.close();
    return true;
  }

  // Save all student records to the file
  bool saveRecords() {
    std::ofstream outFile(fileName);

    if (!outFile.is_open()) {
      return false;
    }

    for (const auto &student : students) {
      outFile << student.studentID << " " << student.name << " "
              << student.course << " " << student.yearLevel << " "
              << student.finalGrade << "\n";
    }

    outFile.close();
    return true;
  }

  // Check if a student ID already exists
  bool studentExists(const std::string &id) {
    return std::any_of(students.begin(), students.end(),
                       [&id](const Student &s) { return s.studentID == id; });
  }

  // Print the header for student records
  void printHeader() {
    std::cout << "\n" << std::string(colWidth * 5, '-') << "\n";
    std::cout << std::setw(colWidth) << "Student ID" << std::setw(colWidth)
              << "Name" << std::setw(colWidth) << "Course"
              << std::setw(colWidth) << "Year Level" << std::setw(colWidth)
              << "Final Grade" << "\n";
    std::cout << std::string(colWidth * 5, '-') << "\n";
  }

  // Print a single student record
  void printStudent(const Student &student) {
    std::cout << std::setw(colWidth) << student.studentID << std::setw(colWidth)
              << student.name << std::setw(colWidth) << student.course
              << std::setw(colWidth) << student.yearLevel << std::setw(colWidth)
              << std::fixed << std::setprecision(2) << student.finalGrade
              << "\n";
  }

public:
  StudentManagementSystem(const std::string &file) : fileName(file) {
    if (!loadRecords()) {
      std::cout << "Warning: Could not load file '" << fileName
                << "'. A new file will be created when records are added.\n";
    } else {
      std::cout << "Successfully loaded " << students.size() << " records from "
                << fileName << ".\n";
    }
  }

  void addStudent() {
    std::cout << "\n=== ADD NEW STUDENT ===\n";

    Student student;

    // Get student details with validation
    student.name = getStringInput("Enter Student Name: ", true);

    // Validate student ID is unique
    bool validID = false;
    do {
      student.studentID = getStringInput("Enter Student ID: ");
      if (studentExists(student.studentID)) {
        std::cout << "Error: A student with ID " << student.studentID
                  << " already exists.\n";
      } else {
        validID = true;
      }
    } while (!validID);

    student.course = getStringInput("Enter Student Course: ");
    student.yearLevel =
        getValidInput<int>("Enter Student Year Level (1-6): ", 1, 6);
    student.finalGrade = getValidInput<float>(
        "Enter Student Final Grade (0-100): ", 0.0f, 100.0f);

    students.push_back(student);

    if (saveRecords()) {
      std::cout << "Student added successfully!\n";
    } else {
      std::cout << "Error: Failed to save records to file.\n";
    }
  }

  void viewAllRecords() {
    if (students.empty()) {
      std::cout << "\nNo student records found.\n";
      return;
    }

    std::cout << "\n=== ALL STUDENT RECORDS ===\n";
    std::cout << "Total records: " << students.size() << "\n";

    printHeader();

    for (const auto &student : students) {
      printStudent(student);
    }

    std::cout << std::string(colWidth * 5, '-') << "\n";
  }

  void searchStudent() {
    if (students.empty()) {
      std::cout << "\nNo student records found.\n";
      return;
    }

    std::cout << "\n=== SEARCH STUDENT RECORD ===\n";
    std::string searchID = getStringInput("Enter Student ID to search: ");

    auto it = std::find_if(
        students.begin(), students.end(),
        [&searchID](const Student &s) { return s.studentID == searchID; });

    if (it != students.end()) {
      std::cout << "\nStudent found!\n";
      printHeader();
      printStudent(*it);
      std::cout << std::string(colWidth * 5, '-') << "\n";
    } else {
      std::cout << "No student found with ID: " << searchID << "\n";
    }
  }

  void updateRecord() {
    if (students.empty()) {
      std::cout << "\nNo student records found.\n";
      return;
    }

    std::cout << "\n=== UPDATE STUDENT RECORD ===\n";
    std::string searchID = getStringInput("Enter Student ID to update: ");

    auto it = std::find_if(
        students.begin(), students.end(),
        [&searchID](const Student &s) { return s.studentID == searchID; });

    if (it != students.end()) {
      std::cout << "\nCurrent student details:\n";
      printHeader();
      printStudent(*it);
      std::cout << std::string(colWidth * 5, '-') << "\n\n";

      std::cout << "Enter new details (press Enter to keep current value)\n";

      std::string input;

      // Update name
      std::cout << "Current Name: " << it->name << "\n";
      std::cout << "Enter new Name (or press Enter to keep current): ";
      clearInputBuffer();
      std::getline(std::cin, input);
      if (!input.empty()) {
        it->name = input;
      }

      // Update ID (with uniqueness check)
      bool validID = false;
      do {
        std::cout << "Current ID: " << it->studentID << "\n";
        std::cout << "Enter new ID (or press Enter to keep current): ";
        std::getline(std::cin, input);

        if (input.empty()) {
          validID = true;
        } else if (input != it->studentID && studentExists(input)) {
          std::cout << "Error: A student with ID " << input
                    << " already exists.\n";
        } else {
          it->studentID = input;
          validID = true;
        }
      } while (!validID);

      // Update course
      std::cout << "Current Course: " << it->course << "\n";
      std::cout << "Enter new Course (or press Enter to keep current): ";
      std::getline(std::cin, input);
      if (!input.empty()) {
        it->course = input;
      }

      // Update year level
      std::cout << "Current Year Level: " << it->yearLevel << "\n";
      std::cout
          << "Enter new Year Level (1-6, or press Enter to keep current): ";
      std::getline(std::cin, input);
      if (!input.empty()) {
        try {
          int newYearLevel = std::stoi(input);
          if (newYearLevel >= 1 && newYearLevel <= 6) {
            it->yearLevel = newYearLevel;
          } else {
            std::cout << "Invalid year level. Keeping current value.\n";
          }
        } catch (const std::exception &) {
          std::cout << "Invalid input. Keeping current value.\n";
        }
      }

      // Update final grade
      std::cout << "Current Final Grade: " << it->finalGrade << "\n";
      std::cout
          << "Enter new Final Grade (0-100, or press Enter to keep current): ";
      std::getline(std::cin, input);
      if (!input.empty()) {
        try {
          float newGrade = std::stof(input);
          if (newGrade >= 0.0f && newGrade <= 100.0f) {
            it->finalGrade = newGrade;
          } else {
            std::cout << "Invalid grade. Keeping current value.\n";
          }
        } catch (const std::exception &) {
          std::cout << "Invalid input. Keeping current value.\n";
        }
      }

      if (saveRecords()) {
        std::cout << "\nStudent record updated successfully!\n";
      } else {
        std::cout << "\nError: Failed to save updated records to file.\n";
      }
    } else {
      std::cout << "No student found with ID: " << searchID << "\n";
    }
  }

  void sortRecords() {
    if (students.empty()) {
      std::cout << "\nNo student records found.\n";
      return;
    }

    std::cout << "\n=== SORT STUDENT RECORDS ===\n";
    std::cout << "Sort by:\n"
              << "1. Student ID\n"
              << "2. Name\n"
              << "3. Final Grade (highest first)\n"
              << "4. Year Level\n";

    int choice = getValidInput<int>("Enter choice (1-4): ", 1, 4);

    switch (choice) {
    case 1:
      std::sort(students.begin(), students.end(),
                [](const Student &a, const Student &b) {
                  return a.studentID < b.studentID;
                });
      std::cout << "Records sorted by Student ID.\n";
      break;

    case 2:
      std::sort(
          students.begin(), students.end(),
          [](const Student &a, const Student &b) { return a.name < b.name; });
      std::cout << "Records sorted by Name.\n";
      break;

    case 3:
      std::sort(students.begin(), students.end(),
                [](const Student &a, const Student &b) {
                  return a.finalGrade > b.finalGrade;
                });
      std::cout << "Records sorted by Final Grade (highest first).\n";
      break;

    case 4:
      std::sort(students.begin(), students.end(),
                [](const Student &a, const Student &b) {
                  return a.yearLevel < b.yearLevel;
                });
      std::cout << "Records sorted by Year Level.\n";
      break;
    }

    viewAllRecords();

    if (saveRecords()) {
      std::cout << "Sorted records saved to file.\n";
    } else {
      std::cout << "Error: Failed to save sorted records to file.\n";
    }
  }

  void deleteRecord() {
    if (students.empty()) {
      std::cout << "\nNo student records found.\n";
      return;
    }

    std::cout << "\n=== DELETE STUDENT RECORD ===\n";
    std::string searchID = getStringInput("Enter Student ID to delete: ");

    auto it = std::find_if(
        students.begin(), students.end(),
        [&searchID](const Student &s) { return s.studentID == searchID; });

    if (it != students.end()) {
      std::cout << "\nStudent found:\n";
      printHeader();
      printStudent(*it);
      std::cout << std::string(colWidth * 5, '-') << "\n\n";

      char confirm;
      std::cout << "Are you sure you want to delete this record? (y/n): ";
      std::cin >> confirm;
      clearInputBuffer();

      if (std::tolower(confirm) == 'y') {
        students.erase(it);

        if (saveRecords()) {
          std::cout << "Student record deleted successfully!\n";
        } else {
          std::cout << "Error: Failed to save updated records to file.\n";
        }
      } else {
        std::cout << "Delete operation cancelled.\n";
      }
    } else {
      std::cout << "No student found with ID: " << searchID << "\n";
    }
  }

  void runMenu() {
    int choice;
    bool running = true;

    do {
      std::cout << "\n=== STUDENT MANAGEMENT SYSTEM ===\n";
      std::cout << "1. Add Student\n";
      std::cout << "2. View All Records\n";
      std::cout << "3. Search Student by ID\n";
      std::cout << "4. Update Student Record\n";
      std::cout << "5. Sort Records\n";
      std::cout << "6. Delete Student Record\n";
      std::cout << "7. Exit\n";

      choice = getValidInput<int>("Enter your choice (1-7): ", 1, 7);

      switch (choice) {
      case 1:
        addStudent();
        break;
      case 2:
        viewAllRecords();
        break;
      case 3:
        searchStudent();
        break;
      case 4:
        updateRecord();
        break;
      case 5:
        sortRecords();
        break;
      case 6:
        deleteRecord();
        break;
      case 7:
        running = false;
        std::cout << "\nThank you for using the Student Management System!\n";
        break;
      }

    } while (running);
  }
};

int main() {
  std::cout << "=== STUDENT MANAGEMENT SYSTEM ===\n\n";
  std::string fileName;

  std::cout << "Please specify name of the file to open: ";
  std::getline(std::cin, fileName);

  StudentManagementSystem sms(fileName);
  sms.runMenu();

  return 0;
}
