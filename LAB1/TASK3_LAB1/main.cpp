#include <iostream>
#include <vector>
using namespace std;

class Course {
public:
    string courseName;
    int courseCode;
};

class Grade {
public:
    int mark;
    char the_grade;
    bool finalized;

    Grade() {
        finalized = false;
    }

    void assignMark(int m) {
        if (!finalized) {
            mark = m;
            if (mark > 69) the_grade = 'A';
            else if (mark > 59) the_grade = 'B';
            else if (mark > 49) the_grade = 'C';
            else if (mark > 39) the_grade = 'D';
            else the_grade = 'E';
            finalized = true;
        } else {
            cout << "Grade already finalized.\n";
        }
    }

    void printGrade() {
        if (finalized)
            cout << "Mark: " << mark << ", Grade: " << the_grade << endl;
        else
            cout << "Grade not yet assigned.\n";
    }
};

class Student {
public:
    string name, reg_no;
    int age;
    Course course;
    Grade grade;

    void inputDetails() {
        cout << "Enter name: ";
        getline(cin >> ws, name);
        cout << "Enter registration number: ";
        cin >> reg_no;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter course name: ";
        getline(cin >> ws, course.courseName);
        cout << "Enter course code: ";
        cin >> course.courseCode;
    }

    void editDetails() {
        cout << "Editing " << name << "'s details.\n";
        inputDetails();
    }

    void printDetails() {
        cout << "Name: " << name << "\nReg No: " << reg_no << "\nAge: " << age << endl;
        cout << "Course: " << course.courseName << " (" << course.courseCode << ")" << endl;
        grade.printGrade();
        cout << "-------------------------\n";
    }
};

int main() {
    vector<Student> students;
    int choice;

    while (true) {
        cout << "\nMenu:\n1. Add student\n2. Edit student\n3. Enter marks\n4. Display students\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            if (students.size() >= 40) {
                cout << "Limit reached.\n";
                continue;
            }
            Student s;
            s.inputDetails();
            students.push_back(s);
        }
        else if (choice == 2) {
            int i;
            cout << "Enter index (0 to " << students.size() - 1 << "): ";
            cin >> i;
            if (i >= 0 && i < students.size())
                students[i].editDetails();
        }
        else if (choice == 3) {
            int i, m;
            cout << "Enter index (0 to " << students.size() - 1 << "): ";
            cin >> i;
            if (i >= 0 && i < students.size()) {
                cout << "Enter marks: ";
                cin >> m;
                students[i].grade.assignMark(m);
            }
        }
        else if (choice == 4) {
            for (Student& s : students)
                s.printDetails(); 
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid.\n";
        }
    }

    return 0;
}
