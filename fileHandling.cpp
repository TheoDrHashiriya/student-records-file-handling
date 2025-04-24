#include <conio.h>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdlib.h>
#include <vector>

struct Student {
  std::string name;
  std::string studentID;
  std::string course;
  int yearLevel;
  float finalGrade;
};
int studentCount = 3;

const int colW = 20;

void addStudent(std::string &fileName) {
  std::ofstream outFile(fileName, std::ios::app);

  Student student;

  if (!outFile.is_open()) {
    std::cout << "ERROR: File not found.\n";
    return;
  }

  std::cout << "Enter Student Name: ";
  std::cin >> student.name;
  std::cout << "Enter student ID: ";
  std::cin >> student.studentID;
  std::cout << "Enter student Course: ";
  std::cin >> student.course;
  std::cout << "Enter student Year Level: ";
  std::cin >> student.yearLevel;
  std::cout << "Enter student Final Grade: ";
  std::cin >> student.finalGrade;

  outFile << std::setw(colW) << student.studentID << std::setw(colW)
          << student.name << std::setw(colW) << student.course
          << std::setw(colW) << student.yearLevel << std::setw(colW)
          << student.finalGrade << "\n";
  studentCount++;
  outFile.close();
}

void viewAllRecords(std::string fileName) {
  Student student[studentCount];

  std::fstream inFile(fileName);

  if (!inFile.is_open()) {
    std::cout << "ERROR: Error opening file\n";
    return;
  }

  std::string line;

  std::cout << '\n' << std::setw(colW * 5) << "Student\n";
  std::cout << std::setw(colW) << "name" << std::setw(colW) << "ID"
            << std::setw(colW) << "course" << std::setw(colW) << "yearlevel"
            << std::setw(colW) << "finalgrade\n";
  int i = 0;

  while (i < studentCount && inFile >> student[i].studentID >>
                                 student[i].name >> student[i].course >>
                                 student[i].yearLevel >>
                                 student[i].finalGrade) {
    i++;
  }

  inFile.close();

  for (int j = 0; j < i; j++) {
    std::cout << student[j].studentID << " " << student[j].name << " "
              << student[j].course << " " << student[j].yearLevel << " "
              << student[j].finalGrade << '\n';
  }
}

void sortFile(std::string fileName) {
  std::ifstream inFile(fileName);

  if (!inFile.is_open()) {
    std::cout << "ERROR: error opening file\n";
    return;
  }

  Student student[studentCount];

  std::vector<std::string> lines;
  std::string line;

  int a = 0;

  while (a < studentCount && inFile >> student[a].studentID >>
                                 student[a].name >> student[a].course >>
                                 student[a].yearLevel >>
                                 student[a].finalGrade) {
    a++;
  }

  for (int i = 0; i < studentCount; i++) {
    for (int j = 0; j < studentCount - i - 1; j++) {
      if (student[j].studentID < student[j + 1].studentID) {
        Student temp = student[j];
        student[j] = student[j + 1];
        student[j + 1] = temp;
      }
    }
  }

  std::ofstream outFile(fileName);
  for (int i = 0; i < studentCount; i++) {
    outFile << student[i].studentID << " " << student[i].name << " "
            << student[i].course << " " << student[i].yearLevel << " "
            << student[i].finalGrade << '\n';
  }
}
void searchByStudent(std::string fileName) {
  std::ifstream inFile(fileName);

  if (!inFile.is_open()) {
    std::cout << "ERROR: error opening file\n";
    return;
  }

  Student student[studentCount];

  int a = 0;
  // gets all student in the file
  while (a < studentCount && inFile >> student[a].studentID >>
                                 student[a].name >> student[a].course >>
                                 student[a].yearLevel >>
                                 student[a].finalGrade) {
    a++;
  }

  std::string id;

  std::cout << "\n--Search student--\n";
  std::cout << "Enter Student ID: ";
  std::cin >> id;

  for (int i = 0; i < studentCount; i++) {
    if (student[i].studentID == id) {
      std::cout << student[i].studentID << " " << student[i].name << " "
                << student[i].course << " " << student[i].yearLevel << " "
                << student[i].finalGrade << '\n';
    }
  }
}
void updateRecord(std::string fileName) {
  std::ifstream inFile(fileName);

  Student student[studentCount];

  int a = 0;
  // gets all student in the file
  while (a < studentCount && inFile >> student[a].studentID >>
                                 student[a].name >> student[a].course >>
                                 student[a].yearLevel >>
                                 student[a].finalGrade) {
    a++;
  }

  std::cout << "\n--update student record--\n";
  std::string id;

  // search student by id
  std::cout << "\n\t--Search student--\n";
  std::cout << "Enter Student ID: ";
  std::cin >> id;

  // get student data
  for (int i = 0; i < studentCount; i++) {
    if (student[i].studentID == id) {
      std::cout << "Enter new Student Name: ";
      std::cin >> student[i].name;
      std::cout << "Enter new student ID: ";
      std::cin >> student[i].studentID;
      std::cout << "Enter new student Course: ";
      std::cin >> student[i].course;
      std::cout << "Enter new student Year Level: ";
      std::cin >> student[i].yearLevel;
      std::cout << "Enter new student Final Grade: ";
      std::cin >> student[i].finalGrade;
    }
  }

  // rewrite exisiting record data
  std::ofstream outFile(fileName);

  if (!outFile.is_open()) {
    std::cout << "ERROR: File not found.\n";
    return;
  }

  for (int i = 0; i < studentCount; i++) {
    outFile << student[i].studentID << " " << student[i].name << " "
            << student[i].course << " " << student[i].yearLevel << " "
            << student[i].finalGrade << '\n';
  }
}

int mainMenu() {

  int choice;

  std::cout << "\n--Student Management System\n"
            << "with file handling!\n\n"
            << "[1] Add student\n"
            << "[2] View all Records\n"
            << "[3] Search a student record By ID\n"
            << "[4] Update a record\n"
            << "[5] Exit\n"
            << "Enter Choice: ";
  std::cin >> choice;

  return choice;
}

int main() {

  std::string fileName;

  std::cout << "Please Specify Name of file the file to open \n FILENAME: ";
  getline(std::cin, fileName);

  bool running = true;
  do {
    int opt = mainMenu();

    switch (opt) {
    case 1:
      addStudent(fileName);
      break;

    case 2:
      viewAllRecords(fileName);
      break;

    case 3:
      searchByStudent(fileName);
      break;

    case 4:
      updateRecord(fileName);
      break;

    case 5:
      running = false;
      break;

    default:
      std::cout << "Invalid Input.\n";
      continue;
    }

  } while (running);

  std::cout << "Success: Thank You using my program.\n";

  return 0;
}