/*
 * @Author: B15020411
 * @Date: 2018-06-27 20:47:04
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-28 02:50:23
 * @Description: この素晴らしい世界に爆焔を！
 */

#include <locale.h>
#include <ncursesw/curses.h>
#include <stdlib.h>
#include <algorithm>
#include <bitset>
#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "Call.hpp"
#define ENTER 10
#define ESCAPE 27

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

void init() {
  ReadChargeRate();
  ReadUserNumber();
  ReadCallList();
  CalAllUsersCost();
}

void init_curses() {
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_BLUE, COLOR_WHITE);
  init_pair(3, COLOR_RED, COLOR_WHITE);
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
}
void draw_menubar(WINDOW *menubar) {
  wbkgd(menubar, COLOR_PAIR(2));
  waddstr(menubar, "Data");
  wattron(menubar, COLOR_PAIR(3));
  waddstr(menubar, "(F1)");
  wattroff(menubar, COLOR_PAIR(3));
  wmove(menubar, 0, 0);
}
WINDOW **draw_menu(int start_col) {
  int i;
  WINDOW **items;
  items = (WINDOW **)malloc(5 * sizeof(WINDOW *));

  items[0] = newwin(6, 18, 1, start_col);
  wbkgd(items[0], COLOR_PAIR(2));
  box(items[0], ACS_VLINE, ACS_HLINE);
  items[1] = subwin(items[0], 1, 17, 2, start_col + 1);
  items[2] = subwin(items[0], 1, 17, 3, start_col + 1);
  items[3] = subwin(items[0], 1, 17, 4, start_col + 1);
  wprintw(items[1], "Everyone's Bill");
  wprintw(items[2], "Check Cost");
  wprintw(items[3], "Check Records");
  wbkgd(items[1], COLOR_PAIR(1));
  wrefresh(items[0]);
  return items;
}
void delete_menu(WINDOW **items, int count) {
  int i;
  for (i = 0; i < count; i++) delwin(items[i]);
  free(items);
}
int scroll_menu(WINDOW **items, int count, int menu_start_col) {
  int key;
  int selected = 0;
  while (1) {
    key = getch();
    if (key == KEY_DOWN || key == KEY_UP) {
      wbkgd(items[selected + 1], COLOR_PAIR(2));
      wnoutrefresh(items[selected + 1]);
      if (key == KEY_DOWN) {
        selected = (selected + 1) % count;
      } else {
        selected = (selected + count - 1) % count;
      }
      wbkgd(items[selected + 1], COLOR_PAIR(1));
      wnoutrefresh(items[selected + 1]);
      doupdate();
    } else if (key == ESCAPE) {
      return -1;
    } else if (key == ENTER) {
      return selected;
    }
  }
}
int GetNumber() {
  string mesg = "Input A PhoneNumber:";
  char str[80];
  int row, col;
  getmaxyx(stdscr, row, col);
  mvprintw(row / 2, col - mesg.length() / 2, "%s", mesg.c_str());
  getstr(str);
  char *stop;
  int result = strtol(str, &stop, 10);
  clear();
  bkgd(COLOR_PAIR(1));
  menubar = subwin(stdscr, 1, COLS, 0, 0);
  messagebar = subwin(stdscr, 1, COLS - 1, LINES - 1, 1);
  draw_menubar(menubar);
  werase(messagebar);
  wrefresh(messagebar);
  touchwin(stdscr);
  refresh();
  return result;
}
void CheckUserCost() {
  int num = GetNumber();
  stringstream ss;
  ss.str("");
  ss << "------------------------" << endl;
  string s = ss.str();
  const int x = (COLS - s.length()) / 2;
  mvprintw(y++, x, s.c_str());
  ss.str("");
  ss << "   号码      费用      " << endl;
  s = ss.str();
  mvprintw(y++, x, s.c_str());
  Range range = CallList.equal_range(num);
  double RemoteCost = 0;
  double LocalCost = 0;
  for (CIT i = range.first; i != range.second; i++) {
    if (i->second.isRemote)
      RemoteCost += i->second.Cost;
    else
      LocalCost += i->second.Cost;
  };
  ss.str("");
  ss << GetUserName(num) << s << LocalCost << LocalCost << LocalCost + LocalCost
     << endl;
  s = ss.str();
  mvprintw(y++, x, s.c_str());
}
void CheckUserList(int s) {
  string Name = GetUserName(s);
  Range range = CallList.equal_range(s);
  for (CIT i = range.first; i != range.second; i++) {
    cout << Name << s << i->second.ToPhone << "  " << i->second.time << endl;
  };
}
void CheckEveryOneCost() {
  map<int, string>::iterator iter;
  iter = UserNumber.begin();
  int y = 8;
  stringstream ss;
  ss.str("");
  ss << "------------------------" << endl;
  string s = ss.str();
  const int x = (COLS - s.length()) / 2;
  mvprintw(y++, x, s.c_str());
  ss.str("");
  ss << "   号码      费用      " << endl;
  s = ss.str();
  mvprintw(y++, x, s.c_str());
  while (iter != UserNumber.end()) {
    int UserPhone = iter->first;
    string UserName = iter->second;
    // cout << UserName << " : " << UserPhone << endl;
    // cout << CalUserCost(UserPhone) << endl;
    ss.str("");
    ss << UserPhone << "      " << CalUserCost(UserPhone) << endl;
    s = ss.str();
    mvprintw(y++, x, s.c_str());
    iter++;
  }
}
int main() {
  init();
  int key;
  WINDOW *menubar, *messagebar;
  setlocale(LC_ALL, "");
  init_curses();

  bkgd(COLOR_PAIR(1));
  menubar = subwin(stdscr, 1, COLS, 0, 0);
  messagebar = subwin(stdscr, 1, COLS - 1, LINES - 1, 1);
  draw_menubar(menubar);
  werase(messagebar);
  wrefresh(messagebar);
  touchwin(stdscr);
  refresh();
  do {
    int selected_item;
    WINDOW **menu_items;
    key = getch();
    werase(messagebar);
    wrefresh(messagebar);
    if (key == KEY_F(1)) {
      menu_items = draw_menu(0);
      selected_item = scroll_menu(menu_items, 4, 0);
      delete_menu(menu_items, 5);
      if (selected_item < 0)
        wprintw(messagebar, "You haven't selected any item.");
      else {
        clear();
        draw_menubar(menubar);
        switch (selected_item + 1) {
          case 1:
            CheckEveryOneCost();
            break;
          case 2:
            CheckUserCost();
            break;
          case 3:
            break;
          case 4:
            break;
          case 5:
            break;
        }
        touchwin(stdscr);
        refresh();
      }
    }
  } while (key != ESCAPE);
  delwin(menubar);
  delwin(messagebar);
  endwin();
  return 0;
}
