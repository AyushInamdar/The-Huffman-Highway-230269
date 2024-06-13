#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

//will be using a vector to store student data, because it is the best for
//implementation of a simple task like a student database management system

//class to store the data for every student
class Student
{
public:
    string name;
    int roll_no;
    string course;
    int total_marks;

    Student(const string& name, int roll_no, const string& course, int total_marks) :
        name(name), roll_no(roll_no), course(course), total_marks(total_marks) {}
};

//function to create a new student record
void create_record(vector<Student>& students)
{
    string name;
    int roll_no;
    string course;
    int total_marks;

    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter roll number: ";
    while (!(cin >> roll_no)) //false if entered number is not an integer
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();//resets the input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //clears any leftover characters characters in the input stream, including newline
        //ensures leftover characters are not read
    }
    cin.ignore(); // Consume the newline character

    cout << "Enter course: ";
    getline(cin, course);

    cout << "Enter total marks: ";
    while (!(cin >> total_marks)) //same as above
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Consume the newline character

    students.push_back(Student(name, roll_no, course, total_marks));
    cout << "Student record created successfully!" << endl;
}

//function to search for a student record
void search_record(const vector<Student>& students)
{
    int roll_no;
    bool found = false;

    cout << "Enter roll number to search: ";
    while (!(cin >> roll_no))
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); //same as above

    for (const Student& student : students) {
        if (student.roll_no == roll_no) {
            cout << "Name: " << student.name << endl;
            cout << "Roll Number: " << student.roll_no << endl;
            cout << "Course: " << student.course << endl;
            cout << "Total Marks: " << student.total_marks << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student record not found!" << endl;
    }
}

//function to delete a student record
void delete_record(vector<Student>& students) {
    int roll_no;
    bool found = false;

    cout << "Enter roll number to delete: ";
    while (!(cin >> total_marks)) //same as above
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    //iterating through all the entries
    for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it)
    {
        if (it->roll_no == roll_no)
        {
            students.erase(it);
            found = true;
            cout << "Student record deleted successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Student record not found!" << endl;
    }
}

// Function to show all student records
void show_records(const vector<Student>& students) {
    if (students.empty())
    {
        cout << "No student records found!" << endl;
    }
    else
    {
        for (const Student& student : students) {
            cout << "Name: " << student.name << endl;
            cout << "Roll Number: " << student.roll_no << endl;
            cout << "Course: " << student.course << endl;
            cout << "Total Marks: " << student.total_marks << endl;
            cout << "-------------------------" << endl;
        }
    }
}

int main() {
    vector<Student> students;
    int choice;

    while (true)
        {
        cout << "\nStudent Record Management System" << endl;
        cout << "1. Create Student Record" << endl;
        cout << "2. Search Student Record" << endl;
        cout << "3. Delete Student Record" << endl;
        cout << "4. Show All Student Records" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice (1-5): ";
        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(); // Consume the newline character

        switch (choice) {
            case 1:
                create_record(students);
                break;
            case 2:
                search_record(students);
                break;
            case 3:
                delete_record(students);
                break;
            case 4:
                show_records(students);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0; // This line is unreachable but good practice to keep it
}

