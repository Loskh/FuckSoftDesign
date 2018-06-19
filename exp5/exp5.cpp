/*
 * @Author: B15020411
 * @Date: 2018-06-19 14:25:31
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-19 14:51:04
 * @Description: この素晴らしい世界に爆焔を！
 */
// 五、进制转换器（10）
// 要求：
// （1）可输入二进制、八进制、十进制、十六进制数；
// （2）将已输入的数转换成其余进制的数；
// （3）具有输入输出界面。
#include <bitset>
#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void SplitString(const string& s, vector<string>& v, const string& c) {
  string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while (string::npos != pos2) {
    v.push_back(s.substr(pos1, pos2 - pos1));
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if (pos1 != s.length()) v.push_back(s.substr(pos1));
}

int main() {
  cout << "输入待转换的数字，进制与数字用`分隔" << endl
       << "如2`101,16`1A2B" << endl;
  string buffer;
  cin >> buffer;
  char* stop;
  vector<string> v;
  SplitString(buffer, v, "`");
  //   cout << v[0] << endl;
  //   cout << v[1] << endl;
  const char* nptr_base = v[0].c_str();
  const char* nptr = v[1].c_str();
  int result = strtol(nptr, &stop, strtol(nptr_base, &stop, 10));
  cout << "2进制: " << bitset<8>(result) << endl;
  cout << "8进制:" << std::oct << result << endl;
  cout << "10进制" << std::dec << result << endl;
  cout << "16进制:" << std::hex << result << endl;
  return 0;
}