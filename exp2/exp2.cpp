/*
 * @Author: B15020411
 * @Date: 2018-06-19 09:59:26
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-19 12:48:11
 * @Description: この素晴らしい世界に爆焔を！
 */
// 二、打字程序（10）
//     要求：（1）随即产生一字符串，每次产生的字符串内容、长度都不同；
//          （2）根据（1）的结果，输入字符串，判断输入是否正确，输出正确率；
//          （3）具有输入输出界面。
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
// 65~90 97~122
using namespace std;
char dic[26 + 26 + 10];
void rand_str(string& str) {
  int len = rand() % 31 + 1;
  str.assign(len, '\0');
  for (int i = 0; i < len; i++) str[i] = dic[rand() % 62];
}
char init_dic() {
  int i, j, k, n;
  for (i = 0; i < 26; i++) dic[i] = 'A' + i;
  for (j = 0; j < 26; i++, j++) dic[i] = 'a' + j;
  for (k = 0; k < 10; i++, k++) dic[i] = '0' + k;
}
int main() {
  init_dic();
  srand((unsigned)time(NULL));
  string words;
  string input;
  int count = 0;
  int right = 0;
  double right_rate;
  while (1) {
    rand_str(words);
    cout << words << endl;
    cin >> input;
    count++;
    if (input == words) {
      cout << "right";
      right++;
    } else
      cout << "wrong";
    right_rate = (double)(right * 1.0 / count * 1.0);
    cout << "  正确率" << fixed << setprecision(2) << right_rate << endl;
  }

  return 0;
}