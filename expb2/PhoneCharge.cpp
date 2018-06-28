/*
 * @Author: B15020411
 * @Date: 2018-06-27 20:47:04
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-28 03:07:57
 * @Description: この素晴らしい世界に爆焔を！
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Call.hpp"
// #include "User.hpp"
using namespace std;
typedef multimap<int, Call> CList;
CList CallList;
typedef CList::const_iterator CIT;
typedef pair<CIT, CIT> Range;
CIT it;
map<int, string> UserNumber;
map<int, double> UserCostList;
string GetType(bool isRemote) {
  if (isRemote)
    return "长途通话";
  else
    return "本地通话";
}
string GetUserName(int s) { return UserNumber[s]; }
void ReadChargeRate() {
  double rate;
  string code;
  ifstream infile;  //输入流
  infile.open("fl.dat", ios::in);
  if (!infile.is_open()) cout << "Open file failure" << endl;
  while (!infile.eof())  // 若未到文件结束一直循环
  {
    infile >> code >> rate;
    ChargeRate.insert(make_pair(code, rate));
  }
  infile.close();  //关闭文件
}
void ReadUserNumber() {
  int Phone;
  string Name;
  ifstream infile;  //输入流
  infile.open("yh.dat", ios::in);
  if (!infile.is_open()) cout << "Open file failure" << endl;
  while (!infile.eof())  // 若未到文件结束一直循环
  {
    infile >> Phone >> Name;
    UserNumber.insert(make_pair(Phone, Name));
  }
  infile.close();  //关闭文件
}
void ReadCallList() {
  string From;
  string To;
  int time;
  int ToPhone;
  int FromPhone;
  ifstream infile;   //输入流
  ofstream outfile;  //输出流
  infile.open("hd.dat", ios::in);
  outfile.open("fy.dat", ios::out);
  if (!infile.is_open()) cout << "Open file failure" << endl;
  while (!infile.eof())  // 若未到文件结束一直循环
  {
    infile >> From >> FromPhone >> To >> ToPhone >> time;
    Call Call;
    Call.Init(From, To, ToPhone, time);
    outfile << FromPhone << " " << GetType(Call.isRemote) << " "
            << Call.GetCost() << endl;
    CallList.insert(make_pair(FromPhone, Call));
  }
  infile.close();  //关闭文件
  outfile.close();
}
double CalUserCost(int s) {
  double totalcost = 0;
  Range range = CallList.equal_range(s);
  for (CIT i = range.first; i != range.second; i++) {
    totalcost += i->second.Cost;
  };
  return totalcost;
}
void CalAllUsersCost() {
  map<int, string>::iterator iter;
  iter = UserNumber.begin();
  while (iter != UserNumber.end()) {
    int UserPhone = iter->first;
    string UserName = iter->second;
    // cout << UserName << " : " << UserPhone << endl;
    // cout << CalUserCost(UserPhone) << endl;
    UserCostList.insert(make_pair(UserPhone, CalUserCost(UserPhone)));
    iter++;
  }
}
void CheckUserCost(int s) {
  Range range = CallList.equal_range(s);
  double RemoteCost = 0;
  double LocalCost = 0;
  for (CIT i = range.first; i != range.second; i++) {
    if (i->second.isRemote)
      RemoteCost += i->second.Cost;
    else
      LocalCost += i->second.Cost;
  };
  cout << "姓名   号码    本地通话    外地通话    总费用" << endl;
  cout << GetUserName(s) << "   " << s << "   " << LocalCost << "      "
       << RemoteCost << "      " << LocalCost + RemoteCost << endl;
}
void CheckUserList(int s) {
  string Name = GetUserName(s);
  Range range = CallList.equal_range(s);
  cout << "姓名       号码          被叫          通话时间" << endl;
  for (CIT i = range.first; i != range.second; i++) {
    cout << Name << "       " << s << "       " << i->second.ToPhone
         << "       " << i->second.time << endl;
  };
}
void CheckEveryOneCost() {
  map<int, string>::iterator iter;
  iter = UserNumber.begin();
  int y = 8;
  cout << "号码          话费" << endl;
  while (iter != UserNumber.end()) {
    int UserPhone = iter->first;
    string UserName = iter->second;
    // cout << UserName << " : " << UserPhone << endl;
    // cout << CalUserCost(UserPhone) << endl;
    cout << UserPhone << "       " << CalUserCost(UserPhone) << endl;
    iter++;
  }
}

int main(int argc, char const *argv[]) {
  ReadChargeRate();
  ReadUserNumber();
  ReadCallList();
  CalAllUsersCost();
  int j = 1;
  char i[10];
  int n;
  do {
    cout << "1.查看所有账单" << endl;
    cout << "2.查询个人账单" << endl;
    cout << "3.查询通话纪录" << endl;
    cout << "4.退出" << endl;
    cout << "请选择：";
    cin >> i;
    if ((i[0] < 49) || (i[0] > 51)) {
      cout << "Input error!!" << endl;
      goto end;
    } else
      n = i[0] - 48;
    switch (n) {
      case 1:
        CheckEveryOneCost();
        break;
      case 2:
        cout << "输入电话号码" << endl;
        int num;
        cin >> num;
        CheckUserCost(num);
        break;
      case 3:
        cout << "输入电话号码" << endl;
        int s;
        cin >> s;
        CheckUserList(s);
        break;
      case 4:
        exit(0);
      default:
        cout << "输入错误!" << endl;
    }
  end:;
  } while (j == 1);
  return 0;
  return 0;
}
