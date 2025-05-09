#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Student {
    int rollNumber;
    string name, division, address;
    
    static Student fromString(const string &line) {
        Student s;
        stringstream ss(line);
        string rollStr;
        getline(ss, rollStr, ',');
        s.rollNumber = stoi(rollStr);
        getline(ss, s.name, ',');
        getline(ss, s.division, ',');
        getline(ss, s.address);
        return s;
    }

    string toString() const {
        return to_string(rollNumber) + ", " + name + ", " + division + ", " + address;
    }
};

void addStudent(const string &filename) {
    ofstream file(filename, ios::app);
    Student s;
    cout << "Enter Roll Number, Name, Division, Address: ";
    cin >> s.rollNumber;
    cin.ignore();
    getline(cin, s.name);
    getline(cin, s.division);
    getline(cin, s.address);
    file << s.toString() << endl;
    cout << "Student added.\n";
}

void deleteStudent(const string &filename) {
    ifstream file(filename);
    string line;
    int rollNumber;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumber;
    bool found = false;
    stringstream ss;
    while (getline(file, line)) {
        Student s = Student::fromString(line);
        if (s.rollNumber != rollNumber) {
            ss << line << endl;
        } else {
            found = true;
        }
    }
    file.close();
    
    if (!found) {
        cout << "Student not found.\n";
        return;
    }

    ofstream outFile(filename);
    outFile << ss.str();
    cout << "Student deleted.\n";
}

void displayStudent(const string &filename) {
    ifstream file(filename);
    string line;
    int rollNumber;
    cout << "Enter Roll Number to display: ";
    cin >> rollNumber;
    bool found = false;

    while (getline(file, line)) {
        Student s = Student::fromString(line);
        if (s.rollNumber == rollNumber) {
            cout << "Roll Number: " << s.rollNumber << "\n"
                << "Name: " << s.name << "\n"
                << "Division: " << s.division << "\n"
                << "Address: " << s.address << "\n";
            found = true;
            break;
        }
    }

    if (!found) cout << "Student not found.\n";
}

int main() {
    string filename = "students.txt";
    int choice;
    while (true) {
        cout << "\n1. Add Student\n2. Delete Student\n3. Display Student\n4. Exit\n";
        cin >> choice;
        if (choice == 1) addStudent(filename);
        else if (choice == 2) deleteStudent(filename);
        else if (choice == 3) displayStudent(filename);
        else if (choice == 4) break;
        else cout << "Invalid choice. Try again.\n";
    }
    return 0;
}