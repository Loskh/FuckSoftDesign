/*
 * @Author: B15020411
 * @Date: 2018-06-21 18:30:44
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-21 18:36:56
 * @Description: この素晴らしい世界に爆焔を！
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct database {
  long NO;
  float regular;
  float midterm;
  float finalexam;
};
class Student {
 public:
  // Student(database db);
  void Init(database db);
  long GetId();
  float GetZP();
  char GetDJ();
  void print();
  void DataIn(database db);
  void SetId(long NO);
  void ComputeZP();
  void ComputeDJ();

 private:
  long ID;
  string major;
  string name;
  class Score {
   public:
    int regular;
    int midterm;
    int finalexam;
    int total;
    char grade;
  } score;
};
void Student::Init(database db) {
  Student::DataIn(db);
  Student::ComputeZP();
  Student::ComputeDJ();
};
long Student::GetId() { return ID; };
float Student::GetZP() { return score.total; };
char Student::GetDJ() { return score.grade; };
void Student::print() {
  cout << ID << " " << GetZP() << " " << GetDJ() << endl;
};
void Student::DataIn(database db) {
  Student::SetId(db.NO);
  score.regular = db.regular;
  score.midterm = db.midterm;
  score.finalexam = db.finalexam;
};
void Student::SetId(long NO) { ID = NO; };
void Student::ComputeZP() {
  score.total =
      (float)0.3 * score.regular + 0.3 * score.midterm + 0.4 * score.finalexam;
};
void Student::ComputeDJ() {
  if (score.total < 60)
    score.grade = 'E';
  else if (score.total < 70)
    score.grade = 'D';
  else if (score.total < 80)
    score.grade = 'C';
  else if (score.total < 90)
    score.grade = 'B';
  else
    score.grade = 'A';
};