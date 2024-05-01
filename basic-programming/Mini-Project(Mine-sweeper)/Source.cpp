#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include<conio.h>
#include<Windows.h>
#pragma execution_character_set( "utf-8" )
#pragma warning(disable:4996)
#define maxmine 50
#define maxzamin 20
int side;
int miness;
int flag;
int wins = 0;
int lose = 0;
char name[100];
void enteringprofile() {
    printf("\033[0;36m");
    printf("Enter your name:");
    printf("\033[0m");
}
int mohit() {
    char m[100];
    char act[100];
    printf("\033[0;31m");
    printf("\t\t\t\t\t\t  1.Change name\n");
    printf("\t\t\t\t\t\t    2.Profile\n");
    printf("\t\t\t\t\t\t      3.Play\n");
    printf("\033[0;33m");
    printf("\t\t\t\t\t     Enter the action you want:");
    printf("\033[0m");
    while (1) {
        gets_s(m);
        if (m[0] != '1' && m[0] != '2' && m[0] != '3') {
            printf("\033[0;35m");
            printf("                                                      invalid\n                                                  enter 1, 2 or 3");
            _sleep(2000);
            system("cls");
            printf("\033[0;31m");
            printf("\t\t\t\t\t\t  1.Change name\n");
            printf("\t\t\t\t\t\t    2.Profile\n");
            printf("\t\t\t\t\t\t      3.Play\n");
            printf("\033[0;33m");
            printf("\t\t\t\t\t     Enter the action you want:");
            printf("\033[0m");
            continue;
        }
        if (m[1] != NULL) {
            printf("\033[0;35m");
            printf("                                                      invalid\n                                                  enter 1, 2 or 3");
            _sleep(2000);
            system("cls");
            printf("\033[0;31m");
            printf("\t\t\t\t\t\t  1.Change name\n");
            printf("\t\t\t\t\t\t    2.Profile\n");
            printf("\t\t\t\t\t\t      3.Play\n");
            printf("\033[0;33m");
            printf("\t\t\t\t\t     Enter the action you want:");
            printf("\033[0m");
            continue;
        }
        if (m[0] == '1') {
            system("cls");
            printf("\033[0;35m");
            printf("Enter your new name:");
            printf("\033[0m");
            gets_s(name);
            return 1;
        }
        else {
            if (m[0] == '2') {
                system("cls");
                printf("\033[0;36m");
                printf("Your name:%s\n", name);
                printf("The number of your wins:%d\n", wins);
                printf("The number of your loses:%d\n", lose);
                printf("\033[0;32m");
                printf("to get back press b or B:");
                printf("\033[0m");
                while (1) {
                    gets_s(act);
                    if (act[0] != 'b' && act[0] != 'B') {
                        printf("invalid,press b or B");
                        _sleep(2000);
                        system("cls");
                        printf("\033[0;36m");
                        printf("Your name:%s\n", name);
                        printf("The number of your wins:%d\n", wins);
                        printf("The number of your loses:%d\n", lose);
                        printf("\033[0;32m");
                        printf("to get back press b or B:");
                        printf("\033[0m");
                        continue;
                    }
                    if (act[1] != NULL) {
                        printf("invalid,press b or B");
                        _sleep(2000);
                        system("cls");
                        printf("\033[0;36m");
                        printf("Your name:%s\n", name);
                        printf("The number of your wins:%d\n", wins);
                        printf("The number of your loses:%d\n", lose);
                        printf("\033[0;32m");
                        printf("to get back press b or B:");
                        printf("\033[0m");
                        continue;
                    }
                    if (act[0] == 'b' || act[0] == 'B')
                        return 2;
                }
            }
            else {
                if (m[0] == '3') {
                    return 3;
                }


            }

        }

    }
}







int menu(int help) {
    int l;
    char action[100];
    printf("\033[0;36m");
    printf("************************************************************************************************************************\n*");
    printf("\033[0;31m");
    printf("\t\t\t\t    HELLO,WELCOME TO THE MINESWEEPER!                                                  ");
    printf("\033[0m");
    printf("\033[0;36m");
    printf("*\n");
    printf("************************************************************************************************************************\n");
    printf("\033[0m");
    printf("\033[0;33m");
    _sleep(1000);
    printf("\033[0m");
    printf("\033[0;32m");
    printf("\t\t\t\t\t\t 1.ENTER\n");
    printf("\t\t\t\t\t\t  2.EXIT\n");
    printf("\033[0m");
    while (1) {
        printf("\033[0;33m");
        printf("\t\t\t \t        Select the action you want:");
        printf("\033[0m");
        gets_s(action);
        if (action[0] != '1' && action[0] != '2') {
            printf("\033[0;35m");
            printf("                                                 invalid\n                                              enter 1 or 2");
            printf("\033[0m");
            _sleep(2000);
            system("cls");
            printf("\033[0;36m");
            printf("************************************************************************************************************************\n*");
            printf("\033[0;31m");
            printf("\t\t\t\t    HELLO,WELCOME TO THE MINESWEEPER!                                                  ");
            printf("\033[0m");
            printf("\033[0;36m");
            printf("*\n");
            printf("************************************************************************************************************************\n");
            printf("\033[0m");
            printf("\033[0;33m");
            printf("\033[0m");
            printf("\033[0;32m");
            printf("\t\t\t\t\t\t 1.ENTER\n");
            printf("\t\t\t\t\t\t  2.EXIT\n");
            printf("\033[0m");

            continue;
        }
        if (action[1] != NULL) {
            printf("\033[0;35m");
            printf("                                                 invalid\n                                              enter 1 or 2");
            printf("\033[0m");
            _sleep(2000);
            system("cls");
            printf("\033[0;36m");
            printf("************************************************************************************************************************\n*");
            printf("\033[0;31m");
            printf("\t\t\t\t    HELLO,WELCOME TO THE MINESWEEPER!                                                  ");
            printf("\033[0m");
            printf("\033[0;36m");
            printf("*\n");
            printf("************************************************************************************************************************\n");
            printf("\033[0m");
            printf("\033[0;33m");
            printf("\033[0m");
            printf("\033[0;32m");
            printf("\t\t\t\t\t\t 1.ENTER\n");
            printf("\t\t\t\t\t\t  2.EXIT\n");
            printf("\033[0m");

            continue;
        }
        if (action[0] == '1') {
            help = 1;
            return help;
        }
        else {
            if (action[0] == '2') {
                help = 2;
                return help;
            }

        }

    }


}
int playagain(char c) {
    while (1) {
        if (c == 'y' || c == 'Y')
            return 1;
        else {
            if (c == 'n' || c == 'N')
                return 0;
            else
                return 5;
        }
    }
}
void difficulty() {
    char acti[100];
    int level;
    int arz, tool;
    printf("\033[0;33m");
    printf("press 1 for easy mode\n");
    printf("press 2 for medium mode\n");
    printf("press 3 for hard mode\n");
    printf("choose difficulty:");
    printf("\033[0m");
    for (int i = 0;; i++) {
        while (1) {
            gets_s(acti);
            if (acti[0] != '1' && acti[0] != '2' && acti[0] != '3') {
                printf("invalid,press 1 or 2 or 3");
                _sleep(2000);
                system("cls");
                printf("\033[0;33m");
                printf("press 1 for easy mode\n");
                printf("press 2 for medium mode\n");
                printf("press 3 for hard mode\n");
                printf("choose difficulty:");
                printf("\033[0m");
                continue;
            }
            if (acti[1] != NULL) {
                printf("invalid,press 1 or 2 or 3");
                _sleep(2000);
                system("cls");
                printf("\033[0;33m");
                printf("press 1 for easy mode\n");
                printf("press 2 for medium mode\n");
                printf("press 3 for hard mode\n");
                printf("choose difficulty:");
                printf("\033[0m");
                continue;

            }

            if (acti[0] == '1') {
                side = 9;
                miness = 10;
                flag = 10;
                return;
            }
            else {
                if (acti[0] == '2') {
                    side = 12;
                    miness = 30;
                    flag = 30;
                    return;
                }
                else {
                    if (acti[0] == '3') {
                        side = 20;
                        miness = 50;
                        flag = 50;
                        return;
                    }

                }
            }
        }
    }
    printf("\033[0m");
}
int ismine(char mainboard[maxzamin][maxzamin], int x, int y) {
    if (mainboard[x][y] == '*') {
        return 1;
    }
    return 0;
}
int wrongnum(int x, int y) {
    if ((char)x == '1' || 'b')
        return 1;
}
int istrue(int x, int y) {
    if (x < side && x >= 0 && y < side && y >= 0) {
        return 1;
    }
    else
        return 0;
}
int checkflag(int x, int y, char gameboard[][maxzamin]) {
    if (gameboard[x][y] == 'f')
        return 0;
    else
        return 1;
}
int ischar(int z) {
    if (z == 'L' || z == 'l') {
        return 1;
    }
    if (z == 'r' || z == 'R') {
        return 2;
    }
    else return 0;
}
int isback(char gameboard[maxzamin][maxzamin], int x, int y) {
    if (gameboard[x][y] != '-' && gameboard[x][y] != 'f')
        return 0;
    else
        return 1;
}

void printzamin(char gameboard[][maxzamin]) {
    SetConsoleOutputCP(CP_UTF8);

    printf("mines: %d  flags:  %d\n", miness, flag);
    printf("   1 ");
    for (int i = 2; i <= side; i++) {
        printf("  %d ", i);
    }
    printf("\n");
    for (int i = 0; i < side; i++) {
        if (i + 1 < 10) {
            printf("%d|", i + 1);
        }
        else {
            printf("%d|", i + 1);
        }

        for (int j = 0; j < side; j++) {
            if (gameboard[i][j] == '*') {
                printf("\033[5;101;30m Ơ ");
                printf("\033[0m");
                printf("|");
                continue;
            }
            else {
                if (gameboard[i][j] == 'f') {
                    printf("\033[5;104;30m ♠ ");
                    printf("\033[0m");
                    printf("|");
                    continue;
                }
                else {
                    if (gameboard[i][j] == '-') {
                        printf("\033[5;103;30| %c |", gameboard[i][j]);
                        printf("\033[0m");
                    }
                    else {
                        printf(" %c |", gameboard[i][j]);
                    }
                }
            }

        }

        printf("\n");
    }

}
void firstround(char mainboard[maxzamin][maxzamin], char gameboard[maxzamin][maxzamin]) {
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            gameboard[i][j] = mainboard[i][j] = '-';
        }
    }
}
int movment(char z) {
    if (z == 'L' || z == 'l') {
        return 1;
    }
    if (z == 'r' || z == 'R') {
        return 2;
    }
}

void createmines(char mainboard[maxzamin][maxzamin], int mine[maxmine][2]) {
    srand(time(NULL));
    bool mark[maxzamin * maxzamin];
    int count1, count2;
    count1 = 0;
    count2 = 0;
    memset(mark, false, sizeof(mark));

    for (int i = 0; i < miness; i++)
    {
        int random = rand() % (side * side);
        int x = random / side;
        int y = random % side;
        if (mark[random] == false)
        {
            for (int j = 0; j < side; j++) {
                if (mainboard[x][j] == '*')
                    count1++;
            }
            for (int j = 0; j < side; j++) {
                if (mainboard[j][y] == '*')
                    count2++;
            }
            if (count1 < 3 && count2 < 3) {
                mine[i][0] = x;
                mine[i][1] = y;
                mainboard[x][y] = '*';
                mark[random] = true;
                count2 = 0;
                count1 = 0;
                continue;
            }
            else {
                count2 = 0;
                count1 = 0;
                i--;
                continue;
            }

        }
        else {
            i--;
            continue;

        }
    }
    return;
}

void isflag(int x, int y, char gameboard[maxzamin][maxzamin], char mainboard[maxzamin][maxzamin]) {

    if (gameboard[x][y] == '-') {
        gameboard[x][y] = 'f';
        flag--;
        if (mainboard[x][y] == '*') {
            miness--;
            return;
        }
        return;
    }
    if (gameboard[x][y] == 'f') {
        gameboard[x][y] = '-';
        flag++;
        if (mainboard[x][y] == '*') {
            miness++;
            return;
        }
        return;
    }

}
int minecounter(int x, int y, int mine[maxmine][2], char mainboard[maxzamin][maxzamin]) {
    int i;
    int counter = 0;
    if (istrue(x + 1, y) == 1)
    {
        if (ismine(mainboard, x + 1, y) == 1)
            counter++;
    }
    if (istrue(x - 1, y) == 1)
    {
        if (ismine(mainboard, x - 1, y) == 1)
            counter++;
    }
    if (istrue(x, y - 1) == 1)
    {
        if (ismine(mainboard, x, y - 1) == 1)
            counter++;
    }
    if (istrue(x, y + 1) == 1)
    {
        if (ismine(mainboard, x, y + 1) == 1)
            counter++;
    }
    if (istrue(x - 1, y + 1) == 1)
    {
        if (ismine(mainboard, x - 1, y + 1) == 1)
            counter++;
    }
    if (istrue(x - 1, y - 1) == 1)
    {
        if (ismine(mainboard, x - 1, y - 1) == 1)
            counter++;
    }
    if (istrue(x + 1, y + 1) == 1)
    {
        if (ismine(mainboard, x + 1, y + 1) == 1)
            counter++;
    }
    if (istrue(x + 1, y - 1) == 1)
    {
        if (ismine(mainboard, x + 1, y - 1) == 1)
            counter++;
    }

    return counter;
}
void cheatMinesweeper(char realBoard[][maxzamin])
{
    printf("The mines locations are-\n");
    printzamin(realBoard);
    return;
}
int bazgashti(char gameboard[][maxzamin], char mainboard[][maxzamin], int mine[][2], int x, int y) {
    if (gameboard[x][y] != '-')
        return 0;
    int i, j;
    char c;
    if (mainboard[x][y] == '*')
    {

        gameboard[x][y] = '*';

        for (i = 0; i < miness; i++)
            gameboard[mine[i][0]][mine[i][1]] = '*';
        system("cls");
        printzamin(gameboard);
        printf("\nYou lost!\n");
        lose++;

        return 1;

    }
    else
    {
        int count = minecounter(x, y, mine, mainboard);

        if (count == 0)
        {
            gameboard[x][y] = count + '0';
            if (istrue(x - 1, y) == 1) {
                if (checkflag(x - 1, y, gameboard) == 1) {
                    if (ismine(mainboard, x - 1, y) == 0)
                        bazgashti(gameboard, mainboard, mine, x - 1, y);
                }
            }
            if (istrue(x + 1, y) == 1) {
                if (checkflag(x + 1, y, gameboard) == 1) {
                    if (ismine(mainboard, x + 1, y) == 0)
                        bazgashti(gameboard, mainboard, mine, x + 1, y);
                }
            }
            if (istrue(x, y - 1) == 1) {
                if (checkflag(x, y - 1, gameboard) == 1) {
                    if (ismine(mainboard, x, y - 1) == 0)
                        bazgashti(gameboard, mainboard, mine, x, y - 1);
                }
            }
            if (istrue(x, y + 1) == 1) {
                if (checkflag(x, y + 1, gameboard) == 1) {
                    if (ismine(mainboard, x, y + 1) == 0)
                        bazgashti(gameboard, mainboard, mine, x, y + 1);
                }
            }


        }

        return 0;
    }
}
int hi(char gameboard[][maxzamin], char mainboard[][maxzamin], int mine[][2], int x, int y) {
    int i, j;
    char c;
    if (mainboard[x][y] == '*')
    {


        gameboard[x][y] = '*';

        for (i = 0; i < miness; i++)
            gameboard[mine[i][0]][mine[i][1]] = '*';

        system("cls");
        printzamin(gameboard);
        printf("\nYou lost!\n");
        lose++;
        return 1;

    }
    else {
        int count = minecounter(x, y, mine, mainboard);
        gameboard[x][y] = count + '0';
        return 0;
    }



}

int gmaeplay() {
    int x;
    int y;
    int a;
    int b;
    char mainboard[maxzamin][maxzamin], gameboard[maxzamin][maxzamin];
    char z, c;
    int mines[maxmine][2];
    firstround(mainboard, gameboard);
    createmines(mainboard, mines);
    //cheatMinesweeper(mainboard);
    while (1)
    {
        printf("Current Status of Board : \n");
        printzamin(gameboard);
        while (1) {
            printf("put your x , y,and your action(L as left that means clicking the cell,R as right click means putting falg) ");
            scanf("%d %d\n", &a, &b);
            scanf("%c", &z);
            x = a - 1;
            y = b - 1;
            if (istrue(x, y) == 0 || ischar(z) == 0) {
                printf("Invalid movment\n");
                _sleep(2000);
                system("cls");
                printzamin(gameboard);
                continue;
            }
            if (isback(gameboard, x, y) == 0) {
                printf("khane ghablan por shode ast\n");
                _sleep(2000);
                system("cls");
                printzamin(gameboard);
                continue;
            }
            if (flag == 0 && movment(z) == 2) {
                printf("you dont have any flag!!\n");
                _sleep(2000);
                system("cls");
                printzamin(gameboard);
                continue;
            }
            break;
        }
        if (movment(z) == 2) {
            isflag(x, y, gameboard, mainboard);
            if (miness == 0) {
                printzamin(gameboard);
                printf("you won!!!!\n");
                wins++;
                return 3;
            }
            system("cls");
        }
        else {
            if (checkflag(x, y, gameboard) == 0) {
                printf("you should first remove the flag!!\n");
                _sleep(2000);
                system("cls");
                printzamin(gameboard);
                continue;
            }
            else {
                if (minecounter(x, y, mines, mainboard) == 0) {
                    if (bazgashti(gameboard, mainboard, mines, x, y) == 1) {

                        return 3;
                    }
                }
                else {
                    if (hi(gameboard, mainboard, mines, x, y) == 1)

                        return 3;


                }


                system("cls");
            }

        }
    }

}

int main() {
    char temp;
    char finish[100];
    SetConsoleOutputCP(CP_UTF8);
    char d[100];
    char f[100];
    char harekat[100];
    char cont;
    char cont1, cont2;
    int help = 0;
    while (1) {
        help = menu(help);
        if (help == 1) {

            system("cls");
            enteringprofile();
            gets_s(name);
            system("cls");
            while (1) {
                if (mohit() == 3) {
                    break;
                }
                else {
                    system("cls");
                    continue;
                }
            }
            printf("\033[0m");
            while (1) {
                system("cls");
                difficulty();
                system("cls");
                gmaeplay();
                printf("press any key and press enter to continue:");
                scanf("%c", &temp);
                gets_s(finish);
                if (finish[0] != NULL) {
                    system("cls");
                    printf("if u want to continue press y else n\n");
                    while (1) {
                        gets_s(harekat);
                        if (harekat[0] != 'y' && harekat[0] != 'Y' && harekat[0] != 'n' && harekat[0] != 'N') {
                            printf("invalid.\n");
                            _sleep(2000);
                            system("cls");
                            printf("if u want to continue press y else n\n");
                            continue;
                        }
                        if (harekat[1] != NULL) {
                            printf("invalid.\n");
                            _sleep(2000);
                            system("cls");
                            printf("if u want to continue press y else n\n");
                            continue;
                        }
                        if (harekat[0] == 'n' || harekat[0] == 'N') {
                            system("cls");
                            break;
                        }
                        if (harekat[0] == 'y' || harekat[0] == 'Y')
                            break;
                    }
                    if (harekat[0] == 'N' || harekat[0] == 'n') {
                        system("cls");
                        while (1) {
                            if (mohit() == 3) {
                                break;
                            }
                            
                        }
                        break;
                    }
                    if (harekat[0] == 'y' || harekat[0] == 'Y') {
                        system("cls");
                        continue;
                    }
                }
            }

        }
        if (help == 2) {
            printf("bye");
            return 0;
        }
    }


    return 0;
}