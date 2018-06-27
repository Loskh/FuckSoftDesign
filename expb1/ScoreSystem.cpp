/*
 * @Author: B15020411
 * @Date: 2018-06-21 18:30:35
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-27 17:59:12
 * @Description: この素晴らしい世界に爆焔を！
 */
#include <curses.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Student.hpp"
#define CLEAR() printf("\033[2J")
using namespace std;
void Save2File(vector<Student>& stu, int N) {
  streambuf* coutBuf = cout.rdbuf();

  ofstream of("out.dat");  // 获取文件out.dat流缓冲区指针
  streambuf* fileBuf =
      of.rdbuf();  // 设置cout流缓冲区指针为out.txt的流缓冲区指针
  cout.rdbuf(fileBuf);
  for (int i = 0; i < N; i++) {
    stu[i].print();
  }
  of.flush();
  of.close();  // 恢复cout原来的流缓冲区指针
  cout.rdbuf(coutBuf);
}
void DisplayClassAvg(vector<Student>& stu, int N) {
  float count = 0;
  for (int i = 0; i < N; i++) {
    count += stu[i].GetZP();
  }
  cout << "该班级本课程的总平均成绩为" << count / N << endl;
}
void DisplayResult(vector<Student>& stu, int N) {
  float count = 0;
  for (int i = 0; i < N; i++) {
    stu[i].print();
  }
}

void DisplayLevels(vector<Student>& stu, int N) {
  int num[5] = {0};
  for (int i = 0; i < N; i++) {
    num[stu[i].GetDJ() - 'A']++;
  }
  for (int i = 0; i < 5; i++) {
    cout << "等级为" << (char)('A' + i) << "的人数为" << num[i] << endl;
  }
}

bool compare(Student a, Student b) {
  return a.GetDJ() < b.GetDJ();  //升序排列，如果改为return a>b，则为降序
}

void DisplayLevelList(vector<Student>& stu, int N) {
  vector<Student> v0;
  v0 = stu;
  char level = 'F';
  sort(v0.begin(), v0.end(), compare);
  for (int i = 0; i < N; i++) {
    if (level != v0[i].GetDJ()) {
      level = v0[i].GetDJ();
      cout << "等级" << level << "的名单:" << endl;
    }
    v0[i].print();
  }
}
int main() {
  database tmp;
  ifstream in("./note.dat");
  if (!in) {
    cout << "打开文件失败！" << endl;
    return -1;
  }
  int N;
  in >> N;
  // cout << N << endl;
  vector<Student> stu(N);
  for (int i = 0; i < N; i++) {
    in >> tmp.NO >> tmp.regular >> tmp.midterm >> tmp.finalexam;
    // cout << tmp.NO << " " << tmp.regular << " " << tmp.midterm << " "
    //      << tmp.finalexam << endl;
    stu[i].Init(tmp);
    // stu[i].print();
  }
  in.close();
  Save2File(stu, N);
  int j = 1;
  char i[10];
  int n;
  do {
    cout << "1.显示总体结果" << endl
         << "2.显示总平均成绩" << endl
         << "3.显示各等级统计" << endl
         << "4.显示各等级名单" << endl
         << "5.退出" << endl;
    cin >> i;
    if ((i[0] < 49) || (i[0] > 57)) {
      cout << "Input error!!" << endl;
      goto end;
    } else
      n = i[0] - 48;
    CLEAR();
    switch (n) {
      case 1:
        DisplayResult(stu, N);
        break;
      case 2:
        DisplayClassAvg(stu, N);
        break;
      case 3:
        DisplayLevels(stu, N);
        break;
      case 4:
        DisplayLevelList(stu, N);
        break;
      case 5:
        exit(0);
      default:
        cout << "输入错误!" << endl;
    }
  end:;
  } while (j == 1);
  return 0;
}
