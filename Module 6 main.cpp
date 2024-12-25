#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;  // Maximum number of students
const int MAX_FRIENDS = 50;    // Maximum number of friends per student

// Structure to represent a student
struct Student {
    string name;                // Student's name
    string friends[MAX_FRIENDS]; // List of friends
    int numFriends = 0;         // Number of friends
};

// Function to read students and their friends from a file
void readStudents(Student students[], int &numStudents, const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    numStudents = 0;

    // Read each student's name and their friends
    while (getline(infile, students[numStudents].name)) {
        students[numStudents].numFriends = 0;
        string friendName;

        // Read friends for the student
        while (infile >> friendName) {
            students[numStudents].friends[students[numStudents].numFriends] = friendName;
            students[numStudents].numFriends++;
            if (infile.peek() == '\n') break; // Stop if we reach the end of the line
        }

        infile.ignore(); // Ignore the newline character at the end of the line
        numStudents++;
    }

    infile.close();
}

// Function to find potential friendships (not direct friends but have at least one common friend)
void findPotentialFriendships(const Student students[], int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        for (int j = i + 1; j < numStudents; ++j) {
            // Check if they are direct friends
            bool areDirectFriends = false;
            for (int k = 0; k < students[i].numFriends; ++k) {
                if (students[i].friends[k] == students[j].name) {
                    areDirectFriends = true;
                    break;
                }
            }

            // If not direct friends, check for common friends
            if (!areDirectFriends) {
                int commonFriends = 0;
                for (int m = 0; m < students[i].numFriends; ++m) {
                    for (int n = 0; n < students[j].numFriends; ++n) {
                        if (students[i].friends[m] == students[j].friends[n]) {
                            commonFriends++;
                        }
                    }
                }

                if (commonFriends > 0) { // If there is at least one common friend
                    cout << "Potential friendship between " << students[i].name << " and " << students[j].name
                         << " with " << commonFriends << " common friends." << endl;
                }
            }
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents;

    // Read data from the file "students.txt" (replace with your filename)
    readStudents(students, numStudents, "D:\\BSCS 1st Sem\\Final\\Discrete project\\Friends Dataset.csv");

    // Find and print potential friendships
    findPotentialFriendships(students, numStudents);

    return 0;
}
