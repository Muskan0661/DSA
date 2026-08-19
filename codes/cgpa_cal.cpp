#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Course {
private:
    string grade;
    int creditHours;

public:
    void inputCourse() {
        cout << "Enter grade (A, A-, B+, B, B-, C+, C, C-, D, F): ";
        cin >> grade;

        cout << "Enter credit hours: ";
        cin >> creditHours;
    }

    double getGradePoint() {
        if (grade == "A")
            return 4.0;
        else if (grade == "A-")
            return 3.7;
        else if (grade == "B+")
            return 3.3;
        else if (grade == "B")
            return 3.0;
        else if (grade == "B-")
            return 2.7;
        else if (grade == "C+")
            return 2.3;
        else if (grade == "C")
            return 2.0;
        else if (grade == "C-")
            return 1.7;
        else if (grade == "D")
            return 1.0;
        else
            return 0.0;
    }

    int getCreditHours() {
        return creditHours;
    }

    string getGrade() {
        return grade;
    }
};

class Semester {
private:
    int numberOfCourses;
    Course* courses;
    double semesterGPA;
    int totalCredits;

public:
    Semester() {
        numberOfCourses = 0;
        courses = NULL;
        semesterGPA = 0;
        totalCredits = 0;
    }

    void inputSemester(int semesterNumber) {
        cout << "\nSemester " << semesterNumber << endl;
        cout << "Enter number of courses: ";
        cin >> numberOfCourses;

        courses = new Course[numberOfCourses];

        double totalGradePoints = 0;

        for (int i = 0; i < numberOfCourses; i++) {
            cout << "\nCourse " << i + 1 << endl;
            courses[i].inputCourse();

            totalCredits += courses[i].getCreditHours();
            totalGradePoints += courses[i].getGradePoint() * courses[i].getCreditHours();
        }

        semesterGPA = totalGradePoints / totalCredits;
    }

    void displaySemester(int semesterNumber) {
        cout << endl;
        cout << "Semester " << semesterNumber << " Result" << endl;
        cout << endl;

        for (int i = 0; i < numberOfCourses; i++) {
            cout << "Course " << i + 1
                 << " -> Grade: " << courses[i].getGrade()
                 << ", Credit Hours: " << courses[i].getCreditHours() << endl;
        }

        cout << fixed << setprecision(2);
        cout << "Semester GPA: " << semesterGPA << endl;
    }

    double getSemesterGPA() {
        return semesterGPA;
    }

    int getTotalCredits() {
        return totalCredits;
    }

    double getWeightedPoints() {
        return semesterGPA * totalCredits;
    }

    ~Semester() {
        delete[] courses;
    }
};

class Student {
private:
    int numberOfSemesters;
    Semester* semesters;
    double cgpa;

public:
    void inputStudentData() {
        cout << "Enter number of semesters: ";
        cin >> numberOfSemesters;

        semesters = new Semester[numberOfSemesters];

        double totalPoints = 0;
        int overallCredits = 0;

        for (int i = 0; i < numberOfSemesters; i++) {
            semesters[i].inputSemester(i + 1);

            totalPoints += semesters[i].getWeightedPoints();
            overallCredits += semesters[i].getTotalCredits();
        }

        cgpa = totalPoints / overallCredits;
    }

    void displayResult() {
        for (int i = 0; i < numberOfSemesters; i++) {
            semesters[i].displaySemester(i + 1);
        }

        cout << endl;
        cout << "Final CGPA: " << fixed << setprecision(2) << cgpa << endl;
        cout << endl;
    }

    ~Student() {
        delete[] semesters;
    }
};

int main() {
    cout << "===== CGPA Calculator =====" << endl;

    Student s;
    s.inputStudentData();
    s.displayResult();

    return 0;
}