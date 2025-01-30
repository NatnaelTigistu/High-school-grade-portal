#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Marks {
    float English = 0;
    float Maths = 0;
    float Physics = 0;
    float Chemistry = 0;
    float Biology = 0;
    float Civics = 0;
    float Amharic = 0;
    float TD = 0;
    float IT = 0;
    float HPE = 0;
    float average = 0;
    float total = 0;
};

struct Section {
    int SectionCode;
    string SectionName;
    string password;
};

struct Student {
    int id;
    string name;
    string password;
    string academicYear;
    string semester;
    int section;
    Marks Marks;
    float average = 0;

};

Student* students = NULL;
int numStudents = 0;

Section* Sections = NULL;
int numSections = 0;


void saveData();
void loadData();
void studentPortal();
void teacherPortal();
void adminPortal();
void addStudent();
void removeStudent();
void addSection();
void removeSection();
void calculateAverage(Student& student);


int main() {
    loadData();

    int choice;
    do {
        cout << "\n--- Grade Portal System ---\n";
        cout << "1. Student\n";
        cout << "2. Teacher\n";
        cout << "3. Staff (Admin)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                studentPortal();
                break;
            case 2:
                teacherPortal();
                break;
            case 3:
                adminPortal();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    saveData();

    delete[] students;
    delete[] Sections;
    return 0;
}


//function to save data into "student.dat" and "Section.dat" files
void saveData() {

    ofstream studentFile("student.dat", ios::out | ios::binary);
    if(!studentFile){cerr<<"file not open"; return;}
    studentFile.write(reinterpret_cast<char*>(&numStudents), sizeof(numStudents));
    for (int i = 0; i < numStudents; i++) {
        size_t nameSize = students[i].name.size();
        size_t passwordSize = students[i].password.size();
        size_t academicYearSize = students[i].academicYear.size();
        size_t semesterSize = students[i].semester.size();

        studentFile.write(reinterpret_cast<char*>(&students[i].id), sizeof(students[i].id));
        studentFile.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        studentFile.write(students[i].name.c_str(), nameSize);
        studentFile.write(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
        studentFile.write(students[i].password.c_str(), passwordSize);
        studentFile.write(reinterpret_cast<char*>(&academicYearSize), sizeof(academicYearSize));
        studentFile.write(students[i].academicYear.c_str(), academicYearSize);
        studentFile.write(reinterpret_cast<char*>(&semesterSize), sizeof(semesterSize));
        studentFile.write(students[i].semester.c_str(), semesterSize);
        studentFile.write(reinterpret_cast<char*>(&students[i].section), sizeof(students[i].section));
        studentFile.write(reinterpret_cast<char*>(&students[i].Marks), sizeof(students[i].Marks));
        studentFile.write(reinterpret_cast<char*>(&students[i].average), sizeof(students[i].average));
    }
    studentFile.close();


    ofstream SectionFile("Section.dat", ios::out | ios::binary);
    if(!SectionFile){cerr<<"file not open"; return;}
    SectionFile.write(reinterpret_cast<char*>(&numSections), sizeof(numSections));
    for (int i = 0; i < numSections; i++) {
        size_t SectionNameSize = Sections[i].SectionName.size();
        size_t passwordSize = Sections[i].password.size();

        SectionFile.write(reinterpret_cast<char*>(&Sections[i].SectionCode), sizeof(Sections[i].SectionCode));
        SectionFile.write(reinterpret_cast<char*>(&SectionNameSize), sizeof(SectionNameSize));
        SectionFile.write(Sections[i].SectionName.c_str(), SectionNameSize);
        SectionFile.write(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
        SectionFile.write(Sections[i].password.c_str(), passwordSize);
    }
    SectionFile.close();
}

//function to read from "student.dat" and "Section.dat" files and then load the data to the working memory
void loadData() {

    ifstream studentFile("student.dat", ios::binary);
    if (studentFile) {
        studentFile.read(reinterpret_cast<char*>(&numStudents), sizeof(numStudents));
        students = new Student[numStudents];
        for (int i = 0; i < numStudents; i++) {
            size_t nameSize, passwordSize, academicYearSize, semesterSize;

            studentFile.read(reinterpret_cast<char*>(&students[i].id), sizeof(students[i].id));
            studentFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
            students[i].name.resize(nameSize);
            studentFile.read(&students[i].name[0], nameSize);
            studentFile.read(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
            students[i].password.resize(passwordSize);
            studentFile.read(&students[i].password[0], passwordSize);
            studentFile.read(reinterpret_cast<char*>(&academicYearSize), sizeof(academicYearSize));
            students[i].academicYear.resize(academicYearSize);
            studentFile.read(&students[i].academicYear[0], academicYearSize);
            studentFile.read(reinterpret_cast<char*>(&semesterSize), sizeof(semesterSize));
            students[i].semester.resize(semesterSize);
            studentFile.read(&students[i].semester[0], semesterSize);
            studentFile.read(reinterpret_cast<char*>(&students[i].section), sizeof(students[i].section));
            studentFile.read(reinterpret_cast<char*>(&students[i].Marks), sizeof(students[i].Marks));
            studentFile.read(reinterpret_cast<char*>(&students[i].average), sizeof(students[i].average));
        }
        studentFile.close();
    }else{cerr<<"File not open";}


    ifstream SectionFile("Section.dat", ios::binary);
    if (SectionFile) {
        SectionFile.read(reinterpret_cast<char*>(&numSections), sizeof(numSections));
        Sections = new Section[numSections];
        for (int i = 0; i < numSections; i++) {
            size_t SectionNameSize, passwordSize;

            SectionFile.read(reinterpret_cast<char*>(&Sections[i].SectionCode), sizeof(Sections[i].SectionCode));
            SectionFile.read(reinterpret_cast<char*>(&SectionNameSize), sizeof(SectionNameSize));
            Sections[i].SectionName.resize(SectionNameSize);
            SectionFile.read(&Sections[i].SectionName[0], SectionNameSize);
            SectionFile.read(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
            Sections[i].password.resize(passwordSize);
            SectionFile.read(&Sections[i].password[0], passwordSize);
        }
        SectionFile.close();
    }else{cerr<<"File not open";}
}

//function called when the student enters the portal
void studentPortal() {
    int id;
    string password;

    cout << "\n--- Student Portal ---\n";
    cout << "Enter your ID: ";
    cin >> id;
    cout << "Enter your password: ";
    cin >> password;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id && students[i].password == password) {
            cout << "Welcome, " << students[i].name << "!\n";
            cout << "Academic Year: " << students[i].academicYear << "\n";
            cout << "Semester: " << students[i].semester << "\n";
            cout << "Section: " << students[i].section << "\n";
            cout << "English: " << students[i].Marks.English << "\n";
            cout << "Maths: " << students[i].Marks.Maths << "\n";
            cout << "Physics: " << students[i].Marks.Physics << "\n";
            cout << "Chemistry: " << students[i].Marks.Chemistry << "\n";
            cout << "Biology: " << students[i].Marks.Biology << "\n";
            cout << "Civics: " << students[i].Marks.Civics << "\n";
            cout << "Amharic: " << students[i].Marks.Amharic << "\n";
            cout << "TD: " << students[i].Marks.TD << "\n";
            cout << "IT: " << students[i].Marks.IT << "\n";
            cout << "HPE: " << students[i].Marks.HPE << "\n";
            cout << "Average: " << students[i].average << "\n";
            cout << "Total: " << students[i].Marks.total << "\n";
            return;
        }
    }

    cout << "Invalid ID or password!\n";
}

//function called when then teacher enters the portal
void teacherPortal() {
    int SectionCode;
    string SectionPassword;

    cout << "\n--- Teacher Portal ---\n";
    cout << "Enter Section code: ";
    cin >> SectionCode;
    cout << "Enter Section password: ";
    cin >> SectionPassword;

    for (int i = 0; i < numSections; i++) {
        if (Sections[i].SectionCode == SectionCode && Sections[i].password == SectionPassword) {
            cout << "Welcome to " << Sections[i].SectionName << " portal.\n";


            for (int j = 0; j < numStudents; j++) {
                if (students[j].section == SectionCode) {
                    cout << "\n--- Student: " << students[j].name << " ---\n";
                    cout << "ID: " << students[j].id << "\n";

                    cout << "Enter English Marks: ";
                    cin >> students[j].Marks.English;

                    cout << "Enter Maths Marks: ";
                    cin >> students[j].Marks.Maths;

                    cout << "Enter Physics Marks: ";
                    cin >> students[j].Marks.Physics;

                    cout << "Enter Chemistry Marks: ";
                    cin >> students[j].Marks.Chemistry;

                    cout << "Enter Biology Marks: ";
                    cin >> students[j].Marks.Biology;

                    cout << "Enter Civics Marks: ";
                    cin >> students[j].Marks.Civics;

                    cout << "Enter Amharic Marks: ";
                    cin >> students[j].Marks.Amharic;

                    cout << "Enter TD Marks: ";
                    cin >> students[j].Marks.TD;

                    cout << "Enter IT Marks: ";
                    cin >> students[j].Marks.IT;

                    cout << "Enter HPE Marks: ";
                    cin >> students[j].Marks.HPE;

                    calculateAverage(students[j]);
                }
            }
            return;
        }
    }

    cout << "Invalid Section code or password!\n";
}

//function called when the staff(admin) enters the portal
void adminPortal() {
    int choice;
    string pass;
    do{
        cout<<"Enter Password: ";
        cin>>pass;
        if(pass=="112233"){
        do {
        cout << "\n--- Admin Portal ---\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Add Section\n";
        cout << "4. Remove Section\n";
        cout << "5. View All Students\n";
        cout << "6. View All Sections\n";
        cout << "7. Exit Admin Portal\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                removeStudent();
                break;
            case 3:
                addSection();
                break;
            case 4:
                removeSection();
                break;
            case 5:
                for (int i = 0; i < numStudents; i++) {
                    cout << "\n--- Student " << i + 1 << " ---\n";
                    cout << "ID: " << students[i].id << "\n";
                    cout << "Name: " << students[i].name << "\n";
                    cout << "Academic Year: " << students[i].academicYear << "\n";
                    cout << "Semester: " << students[i].semester << "\n";
                    cout << "Section: " << students[i].section << "\n";
                }
                break;
            case 6:
                for (int i = 0; i < numSections; i++) {
                    cout << "\n--- Section " << i + 1 << " ---\n";
                    cout << "Code: " << Sections[i].SectionCode << "\n";
                    cout << "Name: " << Sections[i].SectionName << "\n";
                }
                break;
            case 7:
                cout << "Exiting Admin Portal...\n";
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);}
    else if(pass != "0") {cout << "Incorrect password, Enter again or Press 0 to exit." << endl;}
    }while((pass!="0"));


}

//function called by staff(admin) to add new student to the file "student.dat"
void addStudent() {
    cout << "\n--- Add Student ---\n";

    Student* temp = new Student[numStudents + 1];
    for (int i = 0; i < numStudents; i++) {
        temp[i] = students[i];
    }

    cout << "Enter ID: ";
    cin >> temp[numStudents].id;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, temp[numStudents].name);
    cout << "Enter password: ";
    getline(cin, temp[numStudents].password);
    cout << "Enter academic year: ";
    getline(cin, temp[numStudents].academicYear);
    string input;
    cout << "Enter semester 1 or 2: ";
    while (true) {
        getline(cin, input);

        if (input == "1" || input == "2") {
            temp[numStudents].semester = input;
            break;
        } else {
            cout << "Invalid input. Please enter 1 or 2: ";
        }
    }
    cout << "Enter section: ";
    cin >> temp[numStudents].section;

    delete[] students;
    students = temp;
    numStudents++;

    cout << "Student added successfully!\n";
}

//function called by staff(admin) to remove a student from the file "student.dat"
void removeStudent() {
    cout << "\n--- Remove Student ---\n";
    if (numStudents == 0) {
        cout << "No students to remove!\n";
        return;
    }

    int id;
    cout << "Enter the ID of the student to remove: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    Student* temp = new Student[numStudents - 1];
    for (int i = 0, j = 0; i < numStudents; i++) {
        if (i != index) {
            temp[j++] = students[i];
        }
    }

    delete[] students;
    students = temp;
    numStudents--;

    cout << "Student removed successfully!\n";
}

//function called by staff(admin) to add a section to the file "Section.dat"
void addSection() {
    cout << "\n--- Add Section (1 - 4)---\n";

    Section* temp = new Section[numSections + 1];
    for (int i = 0; i < numSections; i++) {
        temp[i] = Sections[i];
    }

    cout << "Enter Section code: ";
    cin >> temp[numSections].SectionCode;
    cin.ignore();
    cout << "Enter Section name: ";
    getline(cin, temp[numSections].SectionName);
    cout << "Enter Section password: ";
    getline(cin, temp[numSections].password);

    delete[] Sections;
    Sections = temp;
    numSections++;

    cout << "Section added successfully!\n";
}

//function called by staff(admin) to remove section from the file "Section.dat"
void removeSection() {
    cout << "\n--- Remove Section ---\n";
    if (numSections == 0) {
        cout << "No Sections to remove!\n";
        return;
    }

    int SectionCode;
    cout << "Enter the Section code to remove: ";
    cin >> SectionCode;

    int index = -1;
    for (int i = 0; i < numSections; i++) {
        if (Sections[i].SectionCode == SectionCode) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Section not found!\n";
        return;
    }

    Section* temp = new Section[numSections - 1];
    for (int i = 0, j = 0; i < numSections; i++) {
        if (i != index) {
            temp[j++] = Sections[i];
        }
    }

    delete[] Sections;
    Sections = temp;
    numSections--;

    cout << "Section removed successfully!\n";
}

//function to calculate the average mark
void calculateAverage(Student& student) {
    student.Marks.total = student.Marks.English + student.Marks.Maths + student.Marks.Physics + student.Marks.Chemistry + student.Marks.Biology + student.Marks.Civics + student.Marks.Amharic + student.Marks.TD + student.Marks.IT + student.Marks.HPE;
    student.average = student.Marks.total/10.0;

}


/*

This C++ program implements a Grade Portal System that allows students, teachers, and staffs(admins) to manage academic records. The system includes features for storing student marks, managing sections, and handling authentication.

Key Features:
1.Student Management:

	Students have attributes like ID(integer only), name, password, academic year, semester(ONLY 1 OR 2), and section.
	Their marks in various subjects are stored, and an average is calculated.
2.Teacher Portal:

	Teachers can access section data by entering section credentials given by admin.
	They can update student marks.
3.Admin Portal:

	Admins can add/remove students and sections.
	They can view all registered students and sections.
	The credentials for section codes and student password are given by the admin.
	The password  for the admin is "112233".
	The section codes - Section code 01 , section password 01A
                      - Section code 02 , section password 02B
                      - Section code 03 , section password 03C
                      - Section code 04 , section password 04D
4.File Persistence:

	Student and section data are saved to binary files (student.dat and Section.dat).
	The system loads this data when the program starts.
5.Main Menu:

	Users can select to log in as a student, teacher, or admin.
	Exiting the program saves all data before termination.



Section 03
Group members         ID
1) Melkamu Tsegaye  UGR/5993/16
2) Natnael Tigstu   UGR/2732/16
3) Kalab Assefa     UGR/1231/16
4) Habtamu Asmamaw  UGR/7879/16
5) Yadelew Zemene   UGR/5025/16

*/
