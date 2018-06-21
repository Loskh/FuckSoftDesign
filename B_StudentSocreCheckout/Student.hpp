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
  int regular;
  int midterm;
  int finalexam;
  int total;
  char grade;
};
void Student::Init(database db) {
  Student::DataIn(db);
  Student::ComputeZP();
  Student::ComputeDJ();
};
long Student::GetId() { return ID; };
float Student::GetZP() { return total; };
char Student::GetDJ() { return grade; };
void Student::print() {
  cout << ID << " " << GetZP() << " " << GetDJ() << endl;
};
void Student::DataIn(database db) {
  Student::SetId(db.NO);
  regular = db.regular;
  midterm = db.midterm;
  finalexam = db.finalexam;
};
void Student::SetId(long NO) { ID = NO; };
void Student::ComputeZP() {
  total = 0.3 * regular + 0.3 * midterm + 0.4 * finalexam;
};
void Student::ComputeDJ() {
  if (total < 60)
    grade = 'E';
  else if (total < 70)
    grade = 'D';
  else if (total < 80)
    grade = 'C';
  else if (total < 90)
    grade = 'B';
  else
    grade = 'A';
};