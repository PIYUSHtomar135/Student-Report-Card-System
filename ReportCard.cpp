#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class Student {
public:
    int roll;
    string name;
    vector<int> marks;
    int total;
    char grade;

    void input();
    void calculateGrade();
    void display();
    int getRoll() { return roll; }
    string getName() { return name; }
};

void Student::input() {
    cout << "Enter Roll Number: ";
    cin >> roll;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);

    int n;
    cout << "Enter number of subjects: ";
    cin >> n;

    marks.clear();
    total = 0;
    for (int i = 0; i < n; i++) {
        int m;
        cout << "Subject " << i + 1 << " marks (out of 50): ";
        cin >> m;
        marks.push_back(m);
        total += m;
    }

    calculateGrade();
}

void Student::calculateGrade() {
    float percentage = (total / (float)(marks.size() * 50)) * 100;

    if (percentage >= 90) grade = 'A';
    else if (percentage >= 75) grade = 'B';
    else if (percentage >= 60) grade = 'C';
    else if (percentage >= 45) grade = 'D';
    else grade = 'F';
}

void Student::display() {
    cout << "\nRoll No: " << roll;
    cout << "\nName: " << name;
    cout << "\nMarks: ";
    for (int m : marks) cout << m << " ";
    cout << "\nTotal: " << total;
    float percentage = (total / (float)(marks.size() * 50)) * 100;
    cout << "\nPercentage: " << percentage << "%";
    cout << "\nGrade: " << grade << endl;
}



void saveToFile(vector<Student>& list) {
    ofstream out("students.txt");
    for (Student& s : list) {
        out << s.roll << " " << s.name << " " << s.marks.size() << " ";
        for (int m : s.marks) out << m << " ";
        out << s.total << " " << s.grade << "\n";
    }
    out.close();
}

vector<Student> loadFromFile() {
    ifstream in("students.txt");
    vector<Student> list;
    Student s;
    int num;

    while (in >> s.roll >> s.name >> num) {
        s.marks.clear();
        s.total = 0;
        for (int i = 0; i < num; i++) {
            int m;
            in >> m;
            s.marks.push_back(m);
            s.total += m;
        }
        in >> s.total >> s.grade;
        list.push_back(s);
    }
    in.close();
    return list;
}

void addStudent() {
    Student s;
    s.input();

    ofstream out("students.txt", ios::app);
    out << s.roll << " " << s.name << " " << s.marks.size() << " ";
    for (int m : s.marks) out << m << " ";
    out << s.total << " " << s.grade << "\n";
    out.close();

    cout << "Student added successfully.\n";
}

void updateStudent() {
    int roll;
    cout << "Enter roll number to update: ";
    cin >> roll;
    vector<Student> list = loadFromFile();
    bool found = false;

    for (Student& s : list) {
        if (s.getRoll() == roll) {
            cout << "Editing record for " << s.getName() << endl;
            s.input();  // re-input everything
            found = true;
            break;
        }
    }

    if (found) {
        saveToFile(list);
        cout << "Student updated successfully.\n";
    } else {
        cout << "Roll number not found.\n";
    }
}

void deleteStudent() {
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;

    vector<Student> list = loadFromFile();
    vector<Student> updated;
    bool found = false;

    for (Student& s : list) {
        if (s.getRoll() != roll)
            updated.push_back(s);
        else
            found = true;
    }

    if (found) {
        saveToFile(updated);
        cout << "Student deleted successfully.\n";
    } else {
        cout << "Roll number not found.\n";
    }
}

void viewAll() {
    vector<Student> list = loadFromFile();
    if (list.empty()) {
        cout << "No records available.\n";
        return;
    }

    for (Student& s : list) {
        s.display();
        cout << "-------------------------\n";
    }
}

// ---------------- Student View Access ----------------

void viewByRoll() {
    int roll;
    cout << "Enter roll number: ";
    cin >> roll;

    vector<Student> list = loadFromFile();
    bool found = false;

    for (Student& s : list) {
        if (s.getRoll() == roll) {
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";
}

void viewByName() {
    string name;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    vector<Student> list = loadFromFile();
    bool found = false;

    for (Student& s : list) {
        if (s.getName() == name) {
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";
}

// ---------------- Main Menu ----------------

void teacherMenu() {
    int ch;
    do {
        cout << "\n---  Teacher Menu ---";
        cout << "\n1. Add Student";
        cout << "\n2. Update Student";
        cout << "\n3. Delete Student";
        cout << "\n4. View All Students";
        cout << "\n5. Back to Main Menu";
        cout << "\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: addStudent(); break;
            case 2: updateStudent(); break;
            case 3: deleteStudent(); break;
            case 4: viewAll(); break;
        }
    } while (ch != 5);
}

void studentMenu() {
    int ch;
    do {
        cout << "\n---  Student Menu ---";
        cout << "\n1. View by Roll Number";
        cout << "\n2. View by Name";
        cout << "\n3. Back to Main Menu";
        cout << "\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: viewByRoll(); break;
            case 2: viewByName(); break;
        }
    } while (ch != 3);
}


int main() {
    int choice;
    while (true) {
        cout << "\n===============================";
        cout << "\n    Student Report Card System";
        cout << "\n===============================\n";
        cout << "1. Teacher Login\n";
        cout << "2. Student View\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: teacherMenu(); break;
            case 2: studentMenu(); break;
            case 3: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
