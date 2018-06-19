/*
 * @Author: B15020411
 * @Date: 2018-06-19 09:14:14
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-19 13:19:44
 * @Description: この素晴らしい世界に爆焔を！
 */
// 一、分数统计（10）
// 要求：
// （1）输入某班级学生的姓名、分数；
// （2）对（1）的分数进行降幂排列并输出；
// （3）具有输入输出界面。

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef struct student {
  char name[20];
  int score;
} student;
bool compare(student a, student b) {
  return a.score < b.score;  //升序排列，如果改为return a>b，则为降序
}

int main() {
  int N;
  cout << "请输入学生数量" << endl;
  cin >> N;
  vector<student> array(N);
  cout << "请输入" << N << "个学生的姓名和分数" << endl;
  for (int i = 0; i < N; i++) {
    cin >> array[i].name >> array[i].score;
  }
  sort(array.begin(), array.end(), compare);
  cout << "姓名"
       << "分数" << endl;
  for (int i = 0; i < N; i++) {
    cout << array[i].name << " " << array[i].score << endl;
  }
  return 0;
}
