#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ifstream input;

  // Open a file
  input.open("scores.txt");

  if (input.fail())
  {
    cout << "File does not exist" << endl;
    cout << "Exit program" << endl;
    return 0;
  }

  // Read data
  char firstName[80];
  char mi;
  char lastName[80];
  int score;
  input >> firstName >> mi >> lastName >> score;
  cout << firstName << " " << mi << " " << lastName << " "
    << score << endl;

  input >> firstName >> mi >> lastName >> score;
  cout << firstName << " " << mi << " " << lastName << " "
    << score << endl;

  input.close();

  cout << "Done" << endl;
  return 0;
}
