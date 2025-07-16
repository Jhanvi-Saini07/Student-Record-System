#include <iostream>
#include <fstream>
#include <string>
#include <limits>  // for cin.ignore
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class Student {
public:
    int roll;
    string name;
    string course;

    // Input student data
    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear newline from input buffer

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Course: ";
        getline(cin, course);
    }

    // Display student data
    void show() const {
        cout << "\nRoll No: " << roll << "\nName: " << name << "\nCourse: " << course << "\n";
    }

    // Save student data to file
    void saveToFile(ofstream &fout) {
        fout << roll << "\n" << name << "\n" << course << "\n";
    }

    // Load student data from file
    bool loadFromFile(ifstream &fin) {
        string line;
        if (!getline(fin, line)) return false;
        roll = stoi(line);
        if (!getline(fin, name)) return false;
        if (!getline(fin, course)) return false;
        return true;
    }
};

// Add Student Record
void addStudent() {
    ofstream fout("student.txt", ios::app);
    Student s;
    s.input();
    s.saveToFile(fout);
    fout.close();
    cout<< GREEN << "Student added successfully!"<< RESET << endl;
}

// Display All Students
void displayStudents() {
    int r ;
    cout << CYAN << "Enter Roll Number to search: " << RESET << endl ;
    ifstream fin("student.txt");
    Student s;
    int count = 0;
    while (s.loadFromFile(fin)) {
        s.show();
        cout << "---------------------\n";
        count++;
    }
    if (count == 0)
        cout << "No records found.\n";
    fin.close();
}

// Search by Roll Number
void searchStudent() {
    int r;
    cout << "Enter roll number to search: ";
    cin >> r;
    ifstream fin("student.txt");
    Student s;
    bool found = false;
    while (s.loadFromFile(fin)) {
        if (s.roll == r) {
            s.show();
            found = true;
            break;
        }
    }
    fin.close();
    if (!found) cout<< RED << "Student not found!"<< RESET << endl;
}

// Delete Record
void deleteStudent() {
    int r;
    cout << "Enter roll number to delete: ";
    cin >> r;
    ifstream fin("student.txt");
    ofstream fout("temp.txt");
    Student s;
    bool found = false;
    while (s.loadFromFile(fin)) {
        if (s.roll != r) {
            s.saveToFile(fout);
        } else {
            found = true;
        }
    }
    fin.close();
    fout.close();
    remove("student.txt");
    rename("temp.txt", "student.txt");
    if (found) cout << "Record deleted!\n";
    else cout << "Record not found!\n";
}

// Update Student
void updateStudent() {
    int r;
    cout << "Enter roll number to update: ";
    cin >> r;
    ifstream fin("student.txt");
    ofstream fout("temp.txt");
    Student s;
    bool found = false;
    while (s.loadFromFile(fin)) {
        if (s.roll == r) {
            cout << "Old Data:\n";
            s.show();
            cout << "\nEnter new details:\n";
            s.input();
            found = true;
        }
        s.saveToFile(fout);
    }
    fin.close();
    fout.close();
    remove("student.txt");
    rename("temp.txt", "student.txt");
    if (found) cout << "Record updated successfully!\n";
    else cout << "Record not found!\n";
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\n----- Student Record Menu -----\n";
        cout << "1. Add Student\n2. Display All\n3. Search\n4. Delete\n5. Update\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    return 0;
}