#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
class city;
class hero
{
public:
    int life;
    char name[10];
    //city *owner; //记录是哪一方的英雄，魔兽3再补
    hero(int x) : life(x) {}
    hero() : life(0) {}
};

hero all_heroes[5];                                      //5种武士，建立一个类数组，记录他们的基本信息（这些基本信息不随着战争进行而改变）
const char name[2][5] = {"red", "blue"};                 //司令部双方的名字
const char arms_name[3][6] = {"sword", "bomb", "arrow"}; //所有的武器名称
int stop[2] = {0};                                       //双方，若停止制造武士则修改为1

//5种英雄，分别继承自hero
class dragon : public hero
{
public:
    int arms;      //1件武器
    double morale; //士气
    dragon(int x, double y, int z) : arms(x), morale(y), hero(z) {}
};
class ninja : public hero
{
public:
    int arms1, arms2; //2件武器
    ninja(int x, int y, int z) : arms1(x), arms2(y), hero(z) {}
};
class iceman : public hero
{
public:
    int arms; //1件武器
    iceman(int x, int y) : arms(x), hero(y) {}
};
class lion : public hero
{
public:
    int loyalty; //忠诚度
    lion(int x, int y) : loyalty(x), hero(y) {}
};
class wolf : public hero
{
public:
    wolf(int x) : hero(x) {}
};

class city
{
private:
    int all, lives, num[5], now, heroes[5], side;
    //all代表总英雄数，lives代表生命力，num数组记录各种英雄数目，now代表当前应该制造哪个英雄，side代表是哪一方（red=0,blue=1）
    //hero数组记录下标为i的时候应当造的英雄

    //分别存储该方所有的英雄的信息
    vector<dragon> city_dragon;
    vector<ninja> city_ninja;
    vector<iceman> city_iceman;
    vector<lion> city_lion;
    vector<wolf> city_wolf;

public:
    static int minlife; //5种英雄最小生命力
    //static int stopnum;                                                       //双方停止制造武士的数目（0，1，2）
    city(int x, int a, int b, int c, int d, int e, int y) : lives(x), all(0), now(0), side(y) //列表初始化不能初始化数组！
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
    void makehero(int time) //private-side:red=0,blue=1
    {
        if (lives < minlife)
        {
            cout << setw(3) << setfill('0') << time << " " << name[side] << " headquarter stops making warriors" << endl;
            stop[side] = 1;
            return;
        }

        if (lives < all_heroes[heroes[now]].life)
        {
            now = (now + 1) % 5;
            makehero(time);
            return;
        }
        else
        {
            lives = lives - all_heroes[heroes[now]].life;
            all++;
            num[now]++;
            cout << setw(3) << setfill('0') << time << " " << name[side] << " " << all_heroes[heroes[now]].name << " " << all << " born with strength " << all_heroes[heroes[now]].life << ",";
            cout << num[now] << " " << all_heroes[heroes[now]].name << " in " << name[side] << " headquarter" << endl;

            //存储并输出该英雄的信息
            switch (heroes[now])//注：由于每个case里面涉及变量的定义，因此采用{}用明确块包装声明新定义变量的作用范围
            {
            case 0:
            {
                dragon tmp_dragon(all % 3, (double)lives / (double)all_heroes[0].life, all_heroes[0].life);
                city_dragon.push_back(tmp_dragon);
                cout << "It has a " << arms_name[all % 3] << ",and it's morale is " << fixed << setprecision(2) << tmp_dragon.morale << endl;
                break;
            }
            case 1:
            {
                ninja tmp_ninja(all % 3, (all + 1) % 3, all_heroes[1].life);
                city_ninja.push_back(tmp_ninja);
                cout << "It has a " << arms_name[all % 3] << " and a " << arms_name[(all + 1) % 3] << endl;
                break;
            }
            case 2:
            {
                iceman tmp_iceman(all % 3, all_heroes[2].life);
                city_iceman.push_back(tmp_iceman);
                cout << "It has a " << arms_name[all % 3] << endl;
                break;
            }
            case 3:
            {
                lion tmp_lion(lives, all_heroes[3].life);
                city_lion.push_back(tmp_lion);
                cout << "It's loyalty is " << lives << endl;
                break;
            }
            case 4:
            {
                wolf tmp_wolf(all_heroes[4].life);
                city_wolf.push_back(tmp_wolf);
                break;
            }
            }

            now = (now + 1) % 5;
            return;
        }
    }
};
int city::minlife = 1 << 30;
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
        city::minlife = 1 << 30;

        cout << "Case:" << i << endl;
        int m = 0;
        cin >> m;
        for (int j = 0; j < 5; j++)
        {
            cin >> all_heroes[j].life;
            city::minlife = min(city::minlife, all_heroes[j].life);
        }

        city red(m, 2, 3, 4, 1, 0, 0);
        city blue(m, 3, 0, 1, 2, 4, 1);
        for (int time = 0; stop[0] + stop[1] != 2; time++)
        {
            if (stop[0] == 0)
                red.makehero(time);
            if (stop[1] == 0)
                blue.makehero(time);
        }
    }

    return 0;
}