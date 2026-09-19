#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int id, age;
    string name;
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    cout << "Enter Student ID: ";
    cin >> s.id;
    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Student Age: ";
    cin >> s.age;

    file << s.id << "|" << s.name << "|" << s.age << endl;
    file.close();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");
    string line;

    cout << "\n===== Student Records =====\n";

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void updateStudent() {
    int searchId;
    cout << "Enter Student ID to Update: ";
    cin >> searchId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        int pos1 = line.find("|");
        int id = stoi(line.substr(0, pos1));

        if (id == searchId) {
            Student s;

            s.id = searchId;

            cin.ignore();
            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;

            temp << s.id << "|" << s.name << "|" << s.age << endl;

            found = true;
        } else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Updated Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

void deleteStudent() {
    int searchId;
    cout << "Enter Student ID to Delete: ";
    cin >> searchId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        int pos1 = line.find("|");
        int id = stoi(line.substr(0, pos1));

        if (id == searchId) {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                cout << "Exiting Program...\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
