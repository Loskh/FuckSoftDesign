/*
 * @Author: B15020411
 * @Date: 2018-06-21 17:48:15
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-21 18:35:27
 * @Description: この素晴らしい世界に爆焔を！
 */

#include "Student.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
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