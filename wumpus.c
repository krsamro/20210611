#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Need for srand(time(NULL))
#include <math.h>

#define NOROWS 4 // Number Of rows
#define NOCOLS 4 // Number Of columns

#define NOWUMPUS 1 // Number Of wumpus creatures
#define NOPIT 3    // Number Of pit
#define NOGOLD 1   // Number Of gold


struct coord
{
    int x;
    int y;
};

struct grid
{
    int agent;

    bool wumpus;
    bool gold;
    bool pit;

    bool strench;
    bool breeze;
    bool glitter;

    bool scream;

    bool visit;
    bool safe; 
};

struct player
{
    int x;
    int y;

    int d; //0오른쪽 1아래쪽 2왼쪽 3위쪽
};

int main()
{
    int i, j, k;

    int realWorld[NOCOLS][NOROWS];
    int agentWorld[NOCOLS][NOROWS];
    int x, y;
    int status = 0;
    
    char c;

    srand((unsigned int)time(0));

    struct grid myWumpus[4][4] = {0};

    //초기 위치
    struct player myPlayer = {0};

    //임의의 위치에 배치해둠
    struct coord wumpusSet = {2, 2};
    struct coord goldSet = {2, 3};
    struct coord pitSet[3] = {{0, 3}, {1, 1}, {3, 2}};

    //맵 세팅
    for (i = 0; i < NOCOLS; i++)
    {
        for (j = 0; j < NOROWS; j++)
        {
            if (i == wumpusSet.x && j == wumpusSet.y)
            {
                myWumpus[i][j].wumpus = true; //wumpus 배치

                //strench 위치
                if (i >= 1 && i <= 2 && j >= 1 && j <= 2)
                {
                    myWumpus[i - 1][j].strench = true;
                    myWumpus[i][j - 1].strench = true;
                    myWumpus[i + 1][j].strench = true;
                    myWumpus[i][j + 1].strench = true;
                }

                else if (i == 3 && j >= 1 && j <= 2)
                {
                    myWumpus[i - 1][j].strench = true;
                    myWumpus[i][j - 1].strench = true;
                    myWumpus[i + 1][j].strench = true;
                }
                else if (i == 0 && j >= 1 && j <= 2)
                {
                    myWumpus[i][j - 1].strench = true;
                    myWumpus[i + 1][j].strench = true;
                    myWumpus[i][j + 1].strench = true;
                }
                else if (i >= 1 && i <= 2 && j == 0)
                {
                    myWumpus[i - 1][j].strench = true;
                    myWumpus[i + 1][j].strench = true;
                    myWumpus[i][j + 1].strench = true;
                }
                else if (i >= 1 && i <= 2 && j == 3)
                {
                    myWumpus[i - 1][j].strench = true;
                    myWumpus[i][j - 1].strench = true;
                    myWumpus[i + 1][j].strench = true;
                }
                else if (i == 0 && j == 3)
                {
                    myWumpus[i][j - 1].strench = true;
                    myWumpus[i + 1][j].strench = true;
                }
                else if (i == 3 && j == 3)
                {
                    myWumpus[i][j - 1].strench = true;
                    myWumpus[i - 1][j].strench = true;
                }
                else if (i == 3 && j == 0)
                {
                    myWumpus[i][j - 1].strench = true;
                    myWumpus[i - 1][j].strench = true;
                }
            }

            //gold 배치+glitter
            else if (i == goldSet.x && j == goldSet.y)
            {
                myWumpus[i][j].gold = true;
                myWumpus[i][j].glitter = true;
            }

            //pit 배치+breeze
            for (k = 0; k < NOPIT; k++)
            {
                if (i == pitSet[k].x && j == pitSet[k].y)
                {
                    myWumpus[i][j].pit = true;

                    if (i >= 1 && i <= 2 && j >= 1 && j <= 2)
                    {
                        myWumpus[i - 1][j].breeze = true;
                        myWumpus[i][j - 1].breeze = true;
                        myWumpus[i + 1][j].breeze = true;
                        myWumpus[i][j + 1].breeze = true;
                    }

                    else if (i == 3 && j >= 1 && j <= 2)
                    {
                        myWumpus[i - 1][j].breeze = true;
                        myWumpus[i][j - 1].breeze = true;
                        myWumpus[i + 1][j].breeze = true;
                    }
                    else if (i == 0 && j >= 1 && j <= 2)
                    {
                        myWumpus[i][j - 1].breeze = true;
                        myWumpus[i + 1][j].breeze = true;
                        myWumpus[i][j + 1].breeze = true;
                    }
                    else if (i >= 1 && i <= 2 && j == 0)
                    {
                        myWumpus[i - 1][j].breeze = true;
                        myWumpus[i + 1][j].breeze = true;
                        myWumpus[i][j + 1].breeze = true;
                    }
                    else if (i >= 1 && i <= 2 && j == 3)
                    {
                        myWumpus[i - 1][j].breeze = true;
                        myWumpus[i][j - 1].breeze = true;
                        myWumpus[i + 1][j].breeze = true;
                    }
                    else if (i == 0 && j == 3)
                    {
                        myWumpus[i][j - 1].breeze = true;
                        myWumpus[i + 1][j].breeze = true;
                    }
                    else if (i == 3 && j == 3)
                    {
                        myWumpus[i][j - 1].breeze = true;
                        myWumpus[i - 1][j].breeze = true;
                    }
                    else if (i == 3 && j == 0)
                    {
                        myWumpus[i][j - 1].breeze = true;
                        myWumpus[i - 1][j].breeze = true;
                    }
                }
            }
        }
    }

    //진행
    int n, m;
    while (status == 0)
    {

        switch (c)
        {

        /*
        case 'f': //go forward
                  //0오른쪽 1아래쪽 2왼쪽 3위쪽
            switch (myPlayer.d)
            {
            case 0: //오른쪽
                myPlayer.y++;
                break;

            case 1: //아래쪽
                myPlayer.x--;
                break;

            case 2: //왼쪽
                myPlayer.y--;
                break;

            case 3: //위쪽
                myPlayer.x++;
                break;
            }
            */

            break;

        default:

            break;
        }
    }

    {
        /*
        for (n = 3; n >= 0; n--)
        {
            printf("──────────────────────────\n");
            for (m = 0; m < NOROWS; m++)
            {
                printf("│%d%d%d│", myWumpus[n][m].wumpus, myWumpus[n][m].strench, myWumpus[n][m].breeze);
            }
            printf("\n");
            for (m = 0; m < NOROWS; m++)
            {
                if (myPlayer.x == n && myPlayer.y == m)
                {
                    myWumpus[n][m].agent = 1;
                }

                printf("│%d%d%d│", myWumpus[n][m].agent, myWumpus[n][m].glitter, myWumpus[n][m].pit);
            }
            printf("\n");
        }
*/
    }

    return 0;
}