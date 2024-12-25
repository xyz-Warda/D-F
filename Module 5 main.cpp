#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100; // Adjust as needed
const int MAX_FRIENDS = 50; // Adjust as needed

// Structure to represent a student
struct Student {
    string name;
    string friends[MAX_FRIENDS];
    int numFriends;
};

// Function to read student data from a file
void readStudents(Student students[], int& numStudents, const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    numStudents = 0;
    string line;

    // Read the first line (student name)
    if (getline(infile, students[numStudents].name)) {
        students[numStudents].numFriends = 0;

        // Read friends on the same line
        string friendName;
        for (int i = 0; i < MAX_FRIENDS && infile >> friendName; ++i) {
            students[numStudents].friends[i] = friendName;
            students[numStudents].numFriends++;
        }

        infile.ignore(1024, '\n'); // Ignore newline (using a large buffer)
        numStudents++;
    }

    // Read the remaining lines (if any)
    if (getline(infile, students[numStudents].name)) {
        students[numStudents].numFriends = 0;

        // Read friends on the same line
        string friendName;
        for (int i = 0; i < MAX_FRIENDS && infile >> friendName; ++i) {
            students[numStudents].friends[i] = friendName;
            students[numStudents].numFriends++;
        }

        infile.ignore(1024, '\n'); // Ignore newline (using a large buffer)
        numStudents++;
    }

    // ... (Repeat the above block for the remaining students, up to MAX_STUDENTS)

    infile.close();
}

// Function to calculate the weight of an edge (number of common friends)
int calculateWeight(const Student& student1, const Student& student2) {
    int weight = 0;
    for (int i = 0; i < student1.numFriends; ++i) {
        for (int j = 0; j < student2.numFriends; ++j) {
            if (student1.friends[i] == student2.friends[j]) {
                weight++;
            }
        }
    }
    return weight;
}

// Function to print the multiplicity graph (adjacency matrix)
void printGraph(const Student students[], int numStudents) {
    cout << "   ";
    for (int i = 0; i < numStudents; ++i) {
        cout << students[i].name << " ";
    }
    cout << endl;

    for (int i = 0; i < numStudents; ++i) {
        cout << students[i].name << " ";
        for (int j = 0; j < numStudents; ++j) {
            int weight = calculateWeight(students[i], students[j]);
            cout << weight << " ";
        }
        cout << endl;
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents;

    readStudents(students, numStudents, "D:\\BSCS 1st Sem\\Final\\Discrete project\\Friends Dataset.csv"); // Replace "students.txt" with your file name

    printGraph(students, numStudents);

    return 0;
}
