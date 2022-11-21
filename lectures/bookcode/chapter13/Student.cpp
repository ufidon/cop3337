#include "Student.h"
#include <cstring>

// Construct a default student
Student::Student()
{
}

// Construct a Student object with specified data
Student::Student(const string& firstName, char mi, 
  const string& lastName, int score)
{
  setFirstName(firstName);
  setMi(mi);
  setLastName(lastName);
  setScore(score);
}

void Student::setFirstName(const string& s)
{
  strcpy(firstName, s.c_str());
}

void Student::setMi(char mi)
{
  this->mi = mi;
}

void Student::setLastName(const string& s)
{
   strcpy(lastName, s.c_str());
}

void Student::setScore(int score)
{
  this->score = score;
}

string Student::getFirstName() const
{
  return string(firstName);
}

char Student::getMi() const
{
  return mi;
}

string Student::getLastName() const
{
  return string(lastName);
}

int Student::getScore() const
{
  return score;
}
