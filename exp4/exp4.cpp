/*
 * @Author: B15020411
 * @Date: 2018-06-19 13:18:20
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-19 14:22:14
 * @Description: この素晴らしい世界に爆焔を！
 */

// 四、加密（10）
// 要求：
// （1）输入任意一段明文M，以及密钥K;
// （2）根据以下公式将其转换为密文C。 Ci = Mi + K, 其中i = 0, 1,……n - 1,K为密钥
// （3）具有输入输出界面。
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
char getCharByValue(int value) {
  if (value >= 0 && value <= 9)
    return '0' + value;
  else if (value >= 10 && value <= 35)
    return 'A' + (value - 10);
  else
    return 'a' + (value - 36);
}
string toHex(string str) {
  string hex = "";
  for (int i = 0; i < str.length(); i++) {
    int low = str[i] % 16;
    int hight = str[i] / 16;
    hex += string(1, getCharByValue(hight)) + string(1, getCharByValue(low));
  }
  return hex;
}
int main() {
  string origin;
  int key;
  cout << "输入要加密的文字" << endl;
  cin >> origin;
  cout << "输入密钥" << endl;
  cin >> key;
  int len = origin.length();
  string encrypted;
  encrypted.assign(len, '\0');
  for (int i = 0; i < len; i++) {
    encrypted[i] = origin[i] + key;
  }
  cout << "ASCII显示密文：" << endl << encrypted << endl;
  cout << "16进制显示密文：" << endl << hex << toHex(encrypted) << endl;
  return 0;
}