/* Yogesh Rana
CISC3142 HW#1*/
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

const int MAX_SIZE = 25; // arrays gonna be length of 25

// Create a Student type structure
struct Student {
  // members variables includes first name, last name and a grade
  string first_name;
  string last_name;
  int grade;
};
// prototype all the methods below main function
int readFromFile(ifstream &, Student[]);
void printStudInfo(ofstream &, Student[], int);
double meanGrade(Student[], int);
void classtopper(ofstream &, Student[], int);
double calcuateSD(Student[], double, int);
int main() {
  // Create a input file variable
  ifstream myfile("students.txt");
  // If file cannot be open,print Error message
  if (!myfile) {
    cerr << "Error! File doesn't exist " << endl;
    exit(1);
  }

  // define a and open output file
  ofstream outFile("output.txt");
  outFile << "Yogesh Rana CISC3142 HW#1 \nThis is output file Of HW#1.\n\n";

  // Creates an array of 25 length of Student Struct type
  Student student[MAX_SIZE];

  // Call the readFromFile function
  // gets the logical length of the student array since we have allocated_size >
  // logical_size
  int logical_array_length = readFromFile(myfile, student);
  // cout << "the logical length of the array student is: " <<
  // logical_array_length
  //      << endl;

  // Close the file
  myfile.close();

  // Print the students informations
  printStudInfo(outFile, student, logical_array_length);

  // print mean of the grades
  double mean = meanGrade(student, logical_array_length);
  outFile << "\n" << endl;
  outFile << "The mean of the grade in class is: " << mean << endl;

  // prin the class topper
  classtopper(outFile, student, logical_array_length);

  // Standard Deviation
  double sdOfGrade = calcuateSD(student, mean, logical_array_length);
  outFile << "The Standard Deviation of the gardes of the class is: "
          << sdOfGrade << endl;
  // Close output file
  outFile.close();
  return 0;
}
// Function to read file and store in the array
// As well as gets the actual size of array student
int readFromFile(ifstream &myFile, Student student[]) {
  int count = 0;
  // read the input myFile
  myFile >> student[count].first_name >> student[count].last_name >>
      student[count].grade;
  while (myFile) {
    count++;
    myFile >> student[count].first_name >> student[count].last_name >>
        student[count].grade;
  }
  return count;
}
// print all the students names and grades
void printStudInfo(ofstream &output, Student student[],
                   int logical_array_length) {

  for (int i = 0; i < logical_array_length; i++) {
    output << student[i].first_name << " ";
    output << student[i].last_name << " ";
    // cout << student[i].grade << " ";
    if (student[i].grade > 90) // Marks between 91-100: A
      output << "got grade: A" << endl;
    else if (student[i].grade > 80) // Marks between 81-90: B
      output << "got grade: B" << endl;
    else if (student[i].grade > 70) // Marks between 71-80: C
      output << "got grade: C" << endl;
    else if (student[i].grade > 60) // Marks between 61-70: D
      output << "got grade: D" << endl;
    else
      output << "got grade: F" << endl;
  }
}
// the Average grade of the class
double meanGrade(Student student[], int logical_array_length) {
  int sum = 0.0;
  for (int i = 0; i < logical_array_length; i++) {
    sum += student[i].grade;
  }
  return (sum * 1.0) / (logical_array_length * 1.0);
}
// Class topper
void classtopper(ofstream &output, Student student[], int length) {
  Student std;
  int highest_grade = 0; // Set highest grade to 0
  for (int i = 0; i < length; i++) {
    if (student[i].grade > highest_grade) {
      highest_grade = student[i].grade;
      std = student[i];
    }
  }
  output << "The student who got highest in the class is: " << std.first_name
         << " " << std.last_name << " with grade: " << std.grade << endl;
}

// Function to calculate the standard deviation
double calcuateSD(Student student[], double mean, int length) {
  double sd = 0.0;
  for (int i = 0; i < length; i++) {
    sd += pow((student[i].grade) * 1.0 - mean, 2);
  }
  return sqrt(sd / (length * 1.0));
}