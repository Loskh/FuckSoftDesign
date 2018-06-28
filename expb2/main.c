#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>
#define amount 20

struct s1 {
  char aera1[5];
  char calling[10];
  char aera2[5];
  char called[10];
  int time;
};

struct s2 {
  char aera[5];
  double rate;
};

struct s3 {
  char num[10];
  char name[10];
};

struct s4 {
  char calling[10];
  char type[10];
  double money;
};

void readfile(struct s1 *list1, struct s2 *list2, struct s3 *list3) {
  int i;
  FILE *fp;
  fp = fopen("hd.dat", "r");
  for (i = 0; i < amount; i++) {
    fscanf(fp, "%s %s %s %s %d", list1[i].aera1, list1[i].calling,
           list1[i].aera2, list1[i].called, &list1[i].time);
  }
  fclose(fp);

  fp = fopen("fl.dat", "r");
  for (i = 0; i < 4; i++) {
    fscanf(fp, "%s %lf", list2[i].aera, &list2[i].rate);
  }
  fclose(fp);

  fp = fopen("yh.dat", "r");
  for (i = 0; i < 5; i++) {
    fscanf(fp, "%s %s", list3[i].num, list3[i].name);
  }
  fclose(fp);
}

void savefile(struct s4 *list4) {
  int i;
  FILE *fp;
  fp = fopen("fy.dat", "w");
  fprintf(fp, "%s\n", "主叫电话号码   通话类型   话费金额（元）");
  for (i = 0; i < amount; i++) {
    fprintf(fp, "%10s   %10s   %6.2lf\n", list4[i].calling, list4[i].type,
            list4[i].money);
  }
  fclose(fp);
  printf("      \n\n【信息已输出至费用文件fy.dat,请查看!按任意键返回!】\n");
  getchar();
}

void calculate(struct s1 *list1, struct s2 *list2, struct s4 *list4)  //计费功能
{
  int i;
  int flag = 1;
  double sum = 0;
  double bill;
  int j;
  int k;
  double rate;
  for (i = 0; i < amount; i++) {
    flag = strcmp(list1[i].aera1, list1[i].aera2);  //全部相等flag为0
    if (flag == 0)                                  // flag=0时为本地话费
    {
      strcpy(list4[i].type, "本地通话");
      strcpy(list4[i].calling, list1[i].calling);
      if (list1[i].time < 180)
        bill = 0.3;
      else {
        k = list1[i].time - 180;
        if (k % 60 == 0)
          bill = 0.5 + (k / 60) * 0.2;
        else
          bill = 0.5 + (k / 60 + 1) * 0.2;
      }
      list4[i].money = bill;
      sum = sum + bill;

    } else  // flag不为零时为长途话费
    {
      strcpy(list4[i].type, "长途通话");
      strcpy(list4[i].calling, list1[i].calling);
      for (j = 0; j < 4; j++) {
        if (strcmp(list1[i].aera2, list2[j].aera) == 0) rate = list2[j].rate;
      }
      if (list1[i].time % 60 == 0) {
        k = list1[i].time - 180;
        bill = rate * (list1[i].time / 60);
      } else {
        k = list1[i].time - 180;
        bill = rate * (list1[i].time / 60 + 1);
      }
      list4[i].money = bill;
      sum = sum + bill;
    }
  }
  printf("      ┌───────┬───────┬──────┐\n");
  printf("      │ 主叫电话号码 │    通话类型  │   通话费用 │\n");
  printf("      ├───────┼───────┼──────┤\n");
  for (i = 0; i < amount; i++)
    printf("      │ %s      │    %s  │   %5.2lf    │\n", list4[i].calling,
           list4[i].type, list4[i].money);
  printf("      └───────┴───────┴──────┘\n");
  printf("      话费总额为:%.2lf\n\n", sum);
  printf("      请按任意键继续:");
  getchar();
}

void searchmoney(struct s3 *list3, struct s4 *list4)  //查询话费
{
  char ch[10];
  double sum1 = 0;
  double sum2 = 0;
  double sum = 0;
  int i;
  int j;
  int flag;
  int flag1;
  int flag2 = 1;
  do {
    flag2 = 1;
    printf("      请输入电话号码：");
    scanf("%s", ch);
    for (i = 0; i < 5; i++)  //从用户信息中根据电话号码查询用户名
    {
      flag = strcmp(ch, list3[i].num);
      if (flag == 0) {
        flag2 = 0;
        break;
      }
    }
    if (flag2 == 1) printf("      您输入的电话号码不存在,请重新输入!\n");
  } while (flag2);
  for (j = 0; j < amount; j++)  //从话费文件中查询通话类型及相应话费
  {
    flag = strcmp(ch, list4[j].calling);
    if (flag == 0) {
      flag1 = strcmp(list4[j].type, "本地通话");
      if (flag1 == 0)
        sum1 = sum1 + list4[j].money;
      else
        sum2 = sum2 + list4[j].money;
    }
  }
  sum = sum1 + sum2;
  printf("      ┌─────┬──────┬──────┬──────┬────┐\n");
  printf(
      "      │  用户名  │主叫电话号码│本地通话费用│长途通话费用│  总费用│\n");
  printf("      ├─────┼──────┼──────┼──────┼────┤\n");
  printf("      │   %s   │  %s   │   %4.2lf     │   %4.2lf     │  %4.2lf  │\n",
         list3[i].name, ch, sum1, sum2, sum);
  printf("      └─────┴──────┴──────┴──────┴────┘\n");
  printf("\n      按任意键返回!");
  getchar();
}

void searchbill(struct s1 *list1, struct s3 *list3,
                struct s4 *list4)  //话单查询
{
  char ch[10];
  char user[10];
  int i;
  int j;
  int flag2;
  int flag;
  int sum1 = 0, sum2 = 0;
  int sum = 0;
  do {
    flag2 = 1;
    printf("      请输入电话号码：");
    scanf("%s", ch);
    for (i = 0; i < 5; i++)  //从用户信息中根据电话号码查询用户名
    {
      flag = strcmp(ch, list3[i].num);
      if (flag == 0) {
        flag2 = 0;
        break;
      }
    }
    if (flag2 == 1) printf("      您输入的电话号码不存在,请重新输入!\n");
  } while (flag2);
  strcpy(user, list3[i].name);
  printf("      ┌─────┬──────┬──────┬─────┐\n");
  printf("      │   用户名 │  主叫号码  │  被叫号码  │  通话时长│\n");
  printf("      ├─────┼──────┼──────┼─────┤\n");
  for (i = 0; i < amount; i++) {
    if (!(strcmp(ch, list4[i].calling))) {
      printf("      │   %s   │  %s   │ %8s   │ %5d    │\n", user,
             list4[i].calling, list1[i].called, list1[i].time);
      if (!(strcmp(list1[i].aera1, list1[i].aera2)))
        sum1 = sum1 + list1[i].time;
      else
        sum2 = sum2 + list1[i].time;
    }
  }
  printf("      └─────┴──────┴──────┴─────┘\n");
  sum = sum1 + sum2;
  printf("\n");
  printf(
      "      您的总通话时长为%d秒,期中本地通话时长为%d秒,长途通话时长为%d秒\n",
      sum1 + sum2, sum1, sum2);
  printf("      按任意键返回!");
  getchar();
}

void menu() {
  printf("\n\n");
  printf(
      "        *********  **********  电信计费系统  **********  ********\n\n");
  printf("             >>>>>>>>        1、读取话费文件         <<<<<<<<\n");
  printf("             >>>>>>>>        2、计算通话费用         <<<<<<<<\n");
  printf("             >>>>>>>>        3、个人话费查询         <<<<<<<<\n");
  printf("             >>>>>>>>        4、个人详单查询         <<<<<<<<\n");
  printf("             >>>>>>>>        5、输出至文件           <<<<<<<<\n");
  printf("             >>>>>>>>        0、退出系统             <<<<<<<<\n\n");
  printf(
      "        *********  ********  *******  *******  *******  *********\n\n");
}

void menu1() {
  printf("\n\n\t\t   **********  读取话费文件  **********\n\n");
  printf("              ********      1、显示源数据文件       ********\n");
  printf("              ********      2、显示长话费率文件     ********\n");
  printf("              ********      3、显示用户信息文件     ********\n");
  printf("              ********      0、返回主菜单           ********\n");
  printf("\n\t\t**********  **********  ********  *********\n\n");
}

void output1(struct s1 *list1) {
  printf("\n\n\t┌────┬──────┬────┬──────┬────┐\n");
  printf("\t│主叫区号│主叫电话号码│被叫区号│被叫电话号码│通话时长│\n");
  printf("\t├────┼──────┼────┼──────┼────┤\n");
  int i;
  for (i = 0; i < amount; i++)
    printf("\t│   %s  │  %s   │ %5s  │  %8s  │ %6d │ \n", list1[i].aera1,
           list1[i].calling, list1[i].aera2, list1[i].called, list1[i].time);
  printf("\t└────────────────────────────┘\n");
}

void output2(struct s2 *list2) {
  int i;
  printf("                      ┌────┬──────┐\n");
  printf("                      │  区号  │    费率    │\n");
  printf("                      ├────┴──────┤\n");
  for (i = 0; i < 4; i++)
    printf("                      │ %4s   │   %.2lf     │ \n", list2[i].aera,
           list2[i].rate);
  printf("                      └───────────┘\n");
}

void output3(struct s3 *list3) {
  int i;
  printf("                      ┌──────┬───────┐\n");
  printf("                      │  电话号码  │    用户姓名  │\n");
  printf("                      ├──────┴───────┤\n");
  for (i = 0; i < 5; i++)
    printf("                      │  %s   │   %8s   │\n", list3[i].num,
           list3[i].name);
  printf("                      └──────────────┘\n");
}

int main() {
  system("color 81");
  int choice;
  int choice2;
  struct s1 list1[20];
  struct s2 list2[5];
  struct s3 list3[5];
  struct s4 list4[20];
  while (1) {
    system("cls");
    menu();
    printf("      请选择：");
    scanf("%d", &choice);
    switch (choice) {
      case 1: {
        readfile(list1, list2, list3);
        do {
          menu1();
          printf("      请选择您要查询的文件：");
          scanf("%d", &choice2);
          if (choice2 == 1) {
            printf("\n");
            output1(list1);
          } else if (choice2 == 2) {
            printf("\n");
            output2(list2);
          } else if (choice2 == 3) {
            printf("\n");
            output3(list3);
          } else if (choice2 == 0)
            break;
          else
            printf("\n      您的输入有误，请重新输入!\n");
        } while (choice2);
      } break;
      case 2:
        calculate(list1, list2, list4);
        getchar();
        break;
      case 3:
        searchmoney(list3, list4);
        break;
      case 4:
        searchbill(list1, list3, list4);
        break;
      case 5:
        savefile(list4);
        break;
      case 0:
        system("cls");
        printf(
            "\n\n\n\n\n\n\n\n\n\n                        ******  谢谢使用!  "
            "******");
        getchar();
        break;
      default:
        printf("      您的输入有误，请重新输入!\n");
        getchar();
    }
  }
  return 0;
}
