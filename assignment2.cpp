#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Function prototypes
void ScoreCalculator();
void GPACalculator();
void showDataSummary();
void studyReminder();
void saveFile();
void loadFile();

// Global variables
const int MAX_STUDENTS = 100;
string studentNames[MAX_STUDENTS];
float studentScores[MAX_STUDENTS];
string studentGrades[MAX_STUDENTS];
float studentGPA[MAX_STUDENTS];

int studentCount = 0;
int currentstudentCount = 0;



int main() {
    int choice;
    cout << "=====================================" << endl;
    cout << "     MyELearn Assistant System       " << endl;
    cout << "=====================================" << endl;

	loadFile(); // Load existing data from file

    do {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Score Calculator" << endl;
        cout << "2. GPA Calculator" << endl;
        cout << "3. Show Data Summary" << endl;
        cout << "4. Study Reminder" << endl;
        cout << "5. Save Data to File" << endl;
        cout << "6. Show All Student Records" << endl;
        cout << "0. Exit" << endl;
        cout << "================================" << endl;
        cout << "Enter choice (0-6): ";
        cin >> choice;

        switch (choice) {
        case 1:
            ScoreCalculator();
            break;
        case 2:
            GPACalculator();
            break;
        case 3:
            showDataSummary();
            break;
        case 4:
            studyReminder();
            break;
        case 5:
            saveFile();
            break;
        case 6:
			// Show all student records
            if (studentCount == 0) {
                cout << "\nNo student records available." << endl;
            }
            else {
                cout << "\n=== ALL STUDENT RECORDS ===" << endl;
                cout << left
                    << setw(20) << "Name"
                    << setw(10) << "Score"
                    << setw(10) << "Grade"
                    << setw(10) << "GPA" << endl;

                for (int i = 0; i < studentCount; i++) {
                     cout << left
                        << setw(20) << studentNames[i]
                        << setw(10) << fixed << setprecision(2) << studentScores[i]
                        << setw(10) << studentGrades[i]
                        << setw(10) << fixed << setprecision(2) << studentGPA[i] << endl;
                }
            }
            break;
        case 0:
            cout << "\nThank you for using MyElearn System. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid input!" << endl;
        }

        if (choice != 0) {
            system("pause");
        }

    } while (choice != 0);

    return 0;
}

void ScoreCalculator() {
    int numStudents;

    cout << "\nHow many students do you want to enter? ";
    cin >> numStudents;
    cin.ignore(); 

    for (int i = 0; i < numStudents; i++) {
        if (studentCount >= MAX_STUDENTS) {
            cout << "Student cannot exceed 100! Try again." << endl;
            break;
        }

        string name;
        float quiz, assignment, project;

        // get student name and scores
        cout << "\nStudent " << (i + 1) << " Name: ";
        getline(cin, name);

        cout << "Quiz score: ";
        cin >> quiz;

        cout << "Assignment score: ";
        cin >> assignment;
       
        cout << "Project score: ";
        cin >> project;
        cin.ignore(); 

        // Calculate weighted marks 
        // quiz=10%, assignment=40%, project=50%
        
        float marks = (quiz * 0.10) + (assignment * 0.4) + (project * 0.50);
        string grade;

        // Assign grade based on marks
        if (marks >= 90 && marks <= 100) 
            grade = "A+";
        else if (marks >= 80) 
            grade = "A";
        else if (marks >= 75) 
            grade = "A-";
        else if (marks >= 70) 
            grade = "B+";
        else if (marks >= 65) 
            grade = "B";
        else if (marks >= 60) 
            grade = "B-";
        else if (marks >= 55) 
            grade = "C+";
        else if (marks >= 50) 
            grade = "C";
        else if (marks >= 45) 
            grade = "C-";
        else if (marks >= 40) 
            grade = "D+";
        else if (marks >= 35) 
            grade = "D";
        else if (marks >= 30) 
            grade = "D-";
        else 
            grade = "E";

        // Save data
        studentNames[studentCount] = name;
        studentScores[studentCount] = marks;
        studentGrades[studentCount] = grade;
        studentGPA[studentCount] = 0.0;
       
        studentCount++;
        currentstudentCount++;

        cout << "Marks: " << fixed << setprecision(2) << marks << " | " << "Grade: " << grade << endl;
    }
}


    void GPACalculator() {
        if (studentCount == 0 || currentstudentCount == 0) {
            cout << "\nNo students available. Go to option 1 first." << endl;
            return;
        }

        float grades[100] = { 0 }; //stored grade points for each subject
		int credits[100] = { 0 }; //stored credit hours for each subject
        int subjects;
		float* g = grades; // pointer to grades array
		int* c = credits; // pointer to credits array

        while (true) {
            cout << "\nAvailable Students:" << endl;
            
            int lastIndex = studentCount - currentstudentCount; //to get the current student
            int displayCurrent = 1;
            for (int i = lastIndex; i < studentCount; i++) {
                cout << displayCurrent << ". " << studentNames[i] << endl;
				displayCurrent++;
            }

            int choice;
            cout << "Select student by number: ";
            cin >> choice;
            cin.ignore();

            if (choice < 1 || choice > studentCount) {
                cout << "Invalid selection. Try again.\n";
            }

            int studentIndex = choice - 1; //  to show correct index in array

            cout << "\nNumber of subjects: ";
            cin >> subjects;
            if (subjects <= 0) {
                cout << "Number of subjects must be greater than 0.\n";
                return;
            }
            if (subjects > 50) {
                cout << "Maximum subjects is 50. Try again.\n";
                return;
            }

            for (int i = 0; i < subjects; i++) {
                cout << "\nSubject " << i + 1 << endl;
                cout << "Grade point: ";
                cin >> *(g + i);
                cout << "Credit hours: ";
                cin >> *(c + i);
            }

            float total = 0;
            int totalCredits = 0;
            for (int i = 0; i < subjects; i++) {
                total += (*(g + i)) * (*(c + i)); // Calculate total grade points
                totalCredits += *(c + i); // Calculate total credit hours
            }

            if (totalCredits == 0) {
                cout << "Total credit hours is 0. Cannot calculate GPA.\n";
                return;
            }

            float gpa = total / totalCredits;
            studentGPA[studentIndex] = gpa; // This is to store GPA for the selected student

            cout << fixed << setprecision(2);
            cout << "\nGPA: " << gpa << endl;

            if (gpa >= 3.5) cout << "Excellent work!" << endl;
            else if (gpa >= 3.0) cout << "Very good!" << endl;
            else if (gpa >= 2.0) cout << "Keep working hard!" << endl;
            else cout << "Need to study more!" << endl;

            char again;
            cout << "\nCalculate GPA for another student? (y/n): ";
            cin >> again;
            cin.ignore();
            
            if (again == 'n' || again == 'N') 
                break;
        }
    }


void showDataSummary() {
    cout << "\n=== CURRENT DATA SUMMARY ===" << endl;

	// Check if there is any data
    if (studentCount == 0 || currentstudentCount == 0) { 
        cout << "No data available." << endl;
    }
    else {
        cout << left
            << setw(20) << "Name"
            << setw(10) << "Score"
            << setw(10) << "Grade"
            << setw(10) << "GPA" << endl;

		int lastIndex = studentCount - currentstudentCount; //to get the current students only

        for (int i = lastIndex; i < studentCount; i++) {

            cout << left
                << setw(20) << studentNames[i]
                << setw(10) << fixed << setprecision(2) 
                << studentScores[i]
                << setw(10) << studentGrades[i] 
                << setw(10) << fixed << setprecision(2) 
                << studentGPA[i] << endl;
        }
    }
}

void studyReminder() {
    cout << "\nStudy Reminder" << endl; 
    int days;
	cout << "Days Until Exam? "; //get number of days until exam
    cin >> days;

    if (days > 7) {
        cout << days << " Days Left. Plenty of Time!" << endl;
    }
    else if (days > 3) {
        cout << days << " Days Left. Study Hard!" << endl;
    }
    else if (days > 0) {
        cout << "Only " << days << " Days Left. Final Push!" << endl;
    }
    else {
        cout << "Exam is over!" << endl;
    }
}

void saveFile() {

    fstream file;
	file.open("students.txt", ios::out); // Open file for writing
	
    // Check if file opened successfully
    if (!file) {
        cout << "Error: Could not create save file.\n";
        return;
    }

    // Save the count first
    file << studentCount << endl;

    for (int i = 0; i < studentCount; i++) {
        
		// Save each student's data
        file << studentNames[i] << endl; 
        file << studentScores[i] << endl;
        file << studentGrades[i] << endl;
        file << studentGPA[i] << endl;
    }

    file.close();
    if (studentCount > 0)
        cout << "Data saved successfully!\n";
}

void loadFile() {
	fstream file;
	file.open("students.txt", ios::in); // Open file for reading
	if (!file) return; // no file to load

    int countFromFile = 0;
    currentstudentCount = 0;

	if (!(file >> countFromFile)) return; // Read count of students 
    file.ignore(); 

    studentCount = 0; // Reset count before loading
    for (int i = 0; i < countFromFile && i < MAX_STUDENTS; i++) {
        getline(file, studentNames[i]);

        file >> studentScores[i];
        file.ignore(); 

        getline(file, studentGrades[i]);

        file >> studentGPA[i];
        file.ignore(); 

        studentCount++; 
    }

    file.close();
}
