#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Employee {
    int id;
    string name, designation;
    double salary;

    string toString() {
        return to_string(id) + "," + name + "," + designation + "," + to_string(salary);
    }

    static Employee fromString(const string &line) {
        Employee e;
        stringstream ss(line);
        string temp;
        getline(ss, temp, ','); e.id = stoi(temp);
        getline(ss, e.name, ',');
        getline(ss, e.designation, ',');
        getline(ss, temp, ','); e.salary = stod(temp);
        return e;
    }
};

void addEmployee(const string &filename) {
    Employee e;
    cout << "Enter ID, Name, Designation, Salary:\n";
    cin >> e.id; cin.ignore();
    getline(cin, e.name);
    getline(cin, e.designation);
    cin >> e.salary;

    ofstream file(filename, ios::app);
    file << e.toString() << endl;
    cout << "Employee added.\n";
}

void displayEmployee(const string &filename) {
    int searchId;
    cout << "Enter ID to display: ";
    cin >> searchId;

    ifstream file(filename);
    string line;
    bool found = false;

    while (getline(file, line)) {
        Employee e = Employee::fromString(line);
        if (e.id == searchId) {
            cout << "ID: " << e.id << ", Name: " << e.name
                 << ", Designation: " << e.designation
                 << ", Salary: " << e.salary << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Employee not found.\n";
}

void deleteEmployee(const string &filename) {
    int deleteId;
    cout << "Enter ID to delete: ";
    cin >> deleteId;

    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    string line;
    bool deleted = false;

    while (getline(inFile, line)) {
        Employee e = Employee::fromString(line);
        if (e.id != deleteId)
            tempFile << line << endl;
        else
            deleted = true;
    }

    inFile.close();
    tempFile.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (deleted)
        cout << "Employee deleted.\n";
    else
        cout << "Employee not found.\n";
}

int main() {
    string filename = "employees.txt";
    int choice;

    while (true) {
        cout << "\n1. Add Employee\n2. Display Employee\n3. Delete Employee\n4. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) addEmployee(filename);
        else if (choice == 2) displayEmployee(filename);
        else if (choice == 3) deleteEmployee(filename);
        else if (choice == 4) break;
        else cout << "Invalid choice.\n";
    }

    return 0;
}