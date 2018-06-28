#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
map<string, double> ChargeRate;
class Call {
 public:
  void Init(string F, string T, int ToPh, int ti);
  string From;
  string To;
  int time;
  int costtime;
  int ToPhone;
  bool isRemote;
  double Cost;
  double GetCost();
  void isRe();
  void CalTime();
  void CalCost();
};
void Call::Init(string F, string T, int ToPh, int ti) {
  From = F;
  To = T;
  ToPhone = ToPh;
  time = ti;
  Call::isRe();
  Call::CalTime();
  Call::CalCost();
}
void Call::CalTime() { costtime = ceil((double)time / 60); }
void Call::CalCost() {
  if (isRemote)
    Cost = ChargeRate[To] * costtime;
  else if (costtime < 4)
    Cost = 0.5;
  else
    Cost = (double)costtime / 3 * 0.2 + 0.3;
}
void Call::isRe() {
  if (From == To)
    isRemote = false;
  else
    isRemote = true;
}
double Call::GetCost() { return Cost; }