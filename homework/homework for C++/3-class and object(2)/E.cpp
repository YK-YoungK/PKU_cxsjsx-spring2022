#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;
class hero
{
public:
    int life;
    char name[10];
    hero(int x) : life(x) {}
    hero() : life(0) {}
};

//5种武士，建立一个类数组
hero all_heroes[5];
const char name[2][5] = {"red", "blue"}; //双方的名字
int stop[2] = {0};                       //双方，若停止制造武士则修改为1

class city
{
private:
    int all, lives, num[5], now, heroes[5];
    //all代表总英雄数，lives代表生命力，num数组记录各种英雄数目，now代表当前应该制造哪个英雄
    //hero数组记录下标为i的时候应当造的武士
public:
    static int minlife; //5种英雄最大生命力
    //static int stopnum;                                                       //双方停止制造武士的数目（0，1，2）
    city(int x, int a, int b, int c, int d, int e) : lives(x), all(0), now(0) //列表初始化不能初始化数组！
    {
        for (int i = 0; i < 5; i++)
            num[i] = 0;
        heroes[0] = a;
        heroes[1] = b;
        heroes[2] = c;
        heroes[3] = d;
        heroes[4] = e;
        //注：abcde为0-4的全排列
    }
    void makehero(int side, int time) //red=0,blue=1
    {
        if (lives < minlife)
        {
            cout << setw(3) << setfill('0') << time << " " << name[side] << " headquarter stops making warriors" << endl;
            stop[side] = 1;
            return;
        }

        if (lives < all_heroes[heroes[now]].life)
        {
            now=(now+1)%5;
            makehero(side, time);
            return;
        }
        else
        {
            lives = lives - all_heroes[heroes[now]].life;
            all++;
            num[now]++;
            cout << setw(3) << setfill('0') << time << " " << name[side] << " " << all_heroes[heroes[now]].name << " " << all << " born with strength " << all_heroes[heroes[now]].life << ",";
            cout << num[now] << " " << all_heroes[heroes[now]].name << " in " << name[side] << " headquarter" << endl;
            now=(now+1)%5;
            return;
        }
    }
};
int city::minlife = 1<<30;
//int city::stopnum = 0;
int main()
{
    //设定英雄名
    strcpy(all_heroes[0].name, "dragon");
    strcpy(all_heroes[1].name, "ninja");
    strcpy(all_heroes[2].name, "iceman");
    strcpy(all_heroes[3].name, "lion");
    strcpy(all_heroes[4].name, "wolf");

    //循环
    int n = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        //重置stop数组与minlife
        stop[0] = 0;
        stop[1] = 0;
        city::minlife = 1<<30;

        cout << "Case:" << i << endl;
        int m = 0;
        cin >> m;
        for (int j = 0; j < 5; j++)
        {
            cin >> all_heroes[j].life;
            city::minlife = min(city::minlife, all_heroes[j].life);
        }

        city red(m, 2, 3, 4, 1, 0);
        city blue(m, 3, 0, 1, 2, 4);
        for (int time = 0; stop[0] + stop[1] != 2; time++)
        {

            if (stop[0] == 0)
                red.makehero(0, time);
            if (stop[1] == 0)
                blue.makehero(1, time);
        }
    }

    return 0;
}