#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <conio.h>
using namespace std;

struct Student {
	string name;
	string studentID;
	string course;
	int yearLevel;
	float finalGrade;
};
int studentCount = 3;

void addStudent(string fileName) {
	ofstream outFile(fileName, ios::app);
	
	Student student;
	
	if(!outFile.is_open()) {
		cout << "ERROR: File not found.\n";
		return;
	}
	
	cout << "Enter Student Name: "; cin >> student.name;
	cout << "Enter student ID: "; cin >> student.studentID;
	cout << "Enter student Course: "; cin >> student.course;
	cout << "Enter student Year Level: "; cin >> student.yearLevel;
	cout << "Enter student Final Grade: "; cin >> student.finalGrade;
	
	outFile << student.studentID << " " << student.name << " " << student.course << " " << student.yearLevel << " " << student.finalGrade << endl;
	studentCount++;
	outFile.close();
	
}
void viewAllRecords(string fileName) {
	Student student[studentCount];
	
	fstream inFile(fileName);
	
	if(!inFile.is_open()) {
		cout << "ERROR: error opening file\n";
		return;
	}

	string line;
	
	cout << "\n--Student--\n";
	cout << "name/ID/course/yearlevel/finalgrade\n";
	int i = 0;
	
	 while (i < studentCount && inFile >> student[i].studentID >> student[i].name >> student[i].course >> student[i].yearLevel >> student[i].finalGrade) {
        i++;
    }
	
	inFile.close();
	
	for(int j = 0; j < i; j++) {
		cout << student[j].studentID << " " << student[j].name << " " << student[j].course << " " << student[j].yearLevel << " " << student[j].finalGrade << endl; 
	
	}
	
}

void sortFile(string fileName) {	
	
	ifstream inFile(fileName);
	
	if(!inFile.is_open()) {
		cout << "ERROR: error opening file\n";
		return;
	}
	
	Student student[studentCount];
	
	vector <string> lines;
	string line;
	
	int a = 0;
	
	while (a < studentCount && inFile >> student[a].studentID >> student[a].name >> student[a].course >> student[a].yearLevel >> student[a].finalGrade) {
        a++;
    }
	
	for(int i = 0; i < studentCount; i++) {
		for(int j = 0; j < studentCount - i - 1; j++) {
			if(student[j].studentID < student[j+1].studentID) {
 			    Student temp = student[j];
				student[j] = student[j + 1];
				student[j + 1] = temp;
			}
		}
	}
	
	ofstream outFile(fileName);
	for(int i = 0; i < studentCount; i++) {
		outFile << student[i].studentID << " " << student[i].name << " " << student[i].course << " " << student[i].yearLevel << " " << student[i].finalGrade << endl;
	}
	
}	
void searchByStudent(string fileName)  {
	ifstream inFile(fileName);
	
	if(!inFile.is_open()) {
		cout << "ERROR: error opening file\n";
		return;
	}
	
	Student student[studentCount];
	
	int a = 0;
	//gets all student in the file
	while (a < studentCount && inFile >> student[a].studentID >> student[a].name >> student[a].course >> student[a].yearLevel >> student[a].finalGrade) {
        a++;
    }
    
    string id;
    
    cout << "\n--Search student--\n";
    cout << "Enter Student ID: ";
	cin >> id;
	
	for(int i = 0; i < studentCount; i++) {
		if(student[i].studentID == id) {
			cout << student[i].studentID << " " << student[i].name << " " << student[i].course << " " << student[i].yearLevel << " " << student[i].finalGrade << endl;
		}
	}	
}
void updateRecord(string fileName) {
	ifstream inFile(fileName);
	
	Student student[studentCount];
	
	int a = 0;
	//gets all student in the file
	while (a < studentCount && inFile >> student[a].studentID >> student[a].name >> student[a].course >> student[a].yearLevel >> student[a].finalGrade) {
        a++;
    }
    
    cout << "\n--update student record--\n";
    string id;
    
    //search student by id
    cout << "\n\t--Search student--\n";
    cout << "Enter Student ID: ";
	cin >> id;
	
	//get student data
	for(int i = 0; i < studentCount; i++) {
		if(student[i].studentID == id) {
			cout << "Enter new Student Name: "; cin >> student[i].name;
			cout << "Enter new student ID: "; cin >> student[i].studentID;
			cout << "Enter new student Course: "; cin >> student[i].course;
			cout << "Enter new student Year Level: "; cin >> student[i].yearLevel;
			cout << "Enter new student Final Grade: "; cin >> student[i].finalGrade;
		}
	}
    
    //rewrite exisiting record data
    ofstream outFile(fileName);
    
    if(!outFile.is_open()) {
		cout << "ERROR: File not found.\n";
		return;
	}
	
	for(int i = 0; i < studentCount; i++) {
		outFile << student[i].studentID << " " << student[i].name << " " << student[i].course << " " << student[i].yearLevel << " " << student[i].finalGrade << endl;
	}
	
	
}

int mainMenu() {
	
	int choice;
	
	cout << "\n--Student Management System\n"
	     << "with file handling!\n"
	     << endl
	     << "[1] Add student\n"
	     << "[2] View all Records\n"
	     << "[3] Search a student record By ID\n"
	     << "[4] Update a record\n"
	     << "[5] Exit\n"
	     << "Enter Choice: ";
	     cin >> choice;
	     
	return choice;
}
int main() {

	string fileName;
	
	cout << "Please Specify Name of file the file to open \n FILENAME: ";
	getline(cin, fileName);
	
	bool running = true;
	do {
		int opt = mainMenu();
	
		switch(opt) {
			case 1: addStudent(fileName); break;
			
			case 2: viewAllRecords(fileName); break;
			
			case 3: searchByStudent(fileName); break;
			
			case 4: updateRecord(fileName); break;
			
			case 5: running = false; break;
			
			default: cout << "Invalid Input.\n"; continue;
		}
		
	} while(running);
	
	cout << "Success: Thank You using my program.\n";

	
	return 0;
	
}