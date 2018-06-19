/*
 * @Author: B15020411
 * @Date: 2018-06-19 12:37:39
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-19 13:06:01
 * @Description: この素晴らしい世界に爆焔を！
 */
// 三、文本编辑器（10）
// 要求：（1）编辑文本；
//      （2）保存、打开指定位置的文本文件；
//      （3）具有输入输出界面。
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void input() {
  char str[100];
  ofstream out("test.txt");
  if (!out) {
    cout << "Cannot open output file.\n";
  }
  cout << "please input:" << endl;
  cin >> str;
  out << str;
  cout << endl;
  out.close();
}
void output() {
  ifstream in("test.txt");
  if (!in) {
    cout << "Cannot open input file.\n";
  }
  char str;
  while (in.get(str)) {
    cout << str;
  }
  cout << endl;
  in.close();
}

int main() {
  int j = 1;
  char i[10];
  int n;
  do {
    cout << "1.写入文本" << endl;
    cout << "2.读文本" << endl;
    cout << "3.退出程序" << endl;
    cout << "请选择：";
    cin >> i;
    if ((i[0] < 49) || (i[0] > 51)) {
      cout << "Input error!!" << endl;
      goto end;
    } else
      n = i[0] - 48;
    switch (n) {
      case 1:
        input();
        break;
      case 2:
        output();
        break;
      case 3:
        exit(0);
      default:
        cout << "输入错误!" << endl;
    }
  end:;
  } while (j == 1);
  return 0;
}