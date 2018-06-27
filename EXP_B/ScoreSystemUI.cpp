/*
 * @Author: B15020411
 * @Date: 2018-06-27 16:19:21
 * @LastEditors: B15020411
 * @LastEditTime: 2018-06-27 19:07:13
 * @Description: この素晴らしい世界に爆焔を！
 */

#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Student.hpp"
#define ENTER 10
#define ESCAPE 27
using namespace std;
void Save2File(vector<Student> &stu, int N) {
  streambuf *coutBuf = cout.rdbuf();

  ofstream of("out.dat");  // 获取文件out.dat流缓冲区指针
  streambuf *fileBuf =
      of.rdbuf();  // 设置cout流缓冲区指针为out.txt的流缓冲区指针
  cout.rdbuf(fileBuf);
  for (int i = 0; i < N; i++) {
    stu[i].print();
  }
  of.flush();
  of.close();  // 恢复cout原来的流缓冲区指针
  cout.rdbuf(coutBuf);
}
void DisplayClassAvg(vector<Student> &stu, int N) {
  float count = 0;
  for (int i = 0; i < N; i++) {
    count += stu[i].GetZP();
  }
  //   cout << "该班级本课程的总平均成绩为" << count / N << endl;
  //   printw("The average score in this class is:\n");
  //   printw("%f", count / N);
  stringstream ss;
  ss << "The average score in this class is " << count / N << endl;
  string s = ss.str();
  mvprintw(LINES / 2, (COLS - s.length()) / 2, s.c_str());
  refresh();
}
void DisplayResult(vector<Student> &stu, int N) {
  float count = 0;
  stringstream ss;
  ss << "----------------------------" << endl;
  string s = ss.str();
  int x = (COLS - s.length()) / 2;
  int y = 2;
  mvprintw(y++, x, s.c_str());
  ss.str("");
  ss << "|    ID    |  Socre  |Grade|" << endl;
  //   ss << "|  994203  |    78   |  C  |";
  s = ss.str();
  mvprintw(y++, x, s.c_str());
  for (int i = 0; i < N; i++) {
    ss.str("");
    ss << "|  " << stu[i].GetId() << "  |    " << stu[i].GetZP() << "   |  "
       << stu[i].GetDJ() << "  |";
    s = ss.str();
    mvprintw(y++, x, s.c_str());
  }
  ss.str("");
  ss << "----------------------------" << endl;
  s = ss.str();
  mvprintw(y++, x, s.c_str());
  refresh();
}

void DisplayLevels(vector<Student> &stu, int N) {
  int num[5] = {0};
  for (int i = 0; i < N; i++) {
    num[stu[i].GetDJ() - 'A']++;
  }
  stringstream ss;
  ss << "----------------------------" << endl;
  string s = ss.str();
  int x = (COLS - s.length()) / 2;
  int y = 8;
  mvprintw(y++, x, s.c_str());
  ss.str("");
  ss << "|    Level    |    Number  |" << endl;
  s = ss.str();
  mvprintw(y++, x, s.c_str());
  for (int i = 0; i < 5; i++) {
    ss.str("");
    ss << "|      " << (char)('A' + i) << "      |      " << num[i] << "     |"
       << endl;
    s = ss.str();
    mvprintw(y++, x, s.c_str());
  }
  ss.str("");
  ss << "----------------------------" << endl;
  s = ss.str();
  mvprintw(y++, x, s.c_str());
  refresh();
}

bool compare(Student a, Student b) {
  return a.GetDJ() < b.GetDJ();  //升序排列，如果改为return a>b，则为降序
}

void DisplayLevelList(vector<Student> &stu, int N) {
  stringstream ss;
  ss << "----------------------------" << endl;
  string s = ss.str();
  int x = (COLS - s.length()) / 2;
  int y = 2;
  mvprintw(y++, x, s.c_str());
  ss.str("");
  ss << "|    ID    |  Socre  |Grade|" << endl;
  //   ss << "|  994203  |    78   |  C  |";
  s = ss.str();
  mvprintw(y++, x, s.c_str());
  vector<Student> v0;
  v0 = stu;
  char level = 'F';
  sort(v0.begin(), v0.end(), compare);
  for (int i = 0; i < N; i++) {
    // if (level != v0[i].GetDJ()) {
    //   level = v0[i].GetDJ();
    //   cout << "等级" << level << "的名单:" << endl;
    // }
    ss.str("");
    ss << "|  " << stu[i].GetId() << "  |    " << stu[i].GetZP() << "   |  "
       << stu[i].GetDJ() << "  |";
    //   ss << "|  994203  |    78   |  C  |";
    s = ss.str();
    mvprintw(y++, x, s.c_str());
  }
  ss.str("");
  ss << "----------------------------" << endl;
  s = ss.str();
  mvprintw(y++, x, s.c_str());
  refresh();
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
  items[4] = subwin(items[0], 1, 17, 5, start_col + 1);
  wprintw(items[1], "Total Socres");
  wprintw(items[2], "Average Socres");
  wprintw(items[3], "Levels");
  wprintw(items[4], "Levels List");
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
int main() {
  int key;
  WINDOW *menubar, *messagebar;

  init_curses();

  bkgd(COLOR_PAIR(1));
  menubar = subwin(stdscr, 1, 80, 0, 0);
  messagebar = subwin(stdscr, 1, 79, 23, 1);
  draw_menubar(menubar);
  werase(messagebar);
  wrefresh(messagebar);
  database tmp;
  ifstream in("note.dat");
  if (!in) {
    wprintw(messagebar, "File Open Filure.");
    return -1;
  } else {
    wprintw(messagebar, "File Open Success.");
  }
  touchwin(stdscr);
  refresh();
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