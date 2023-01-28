#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <vector> //双方分别存放各自的武士,以及用于存储城市的信息
#include <algorithm>
using namespace std;

//以下全局变量可用于武士类和司令部类的初始化
int hero_life[5] = {0};                                    //记录五种武士的初始生命值
int hero_energy[5] = {0};                                  //记录五种武士的初始攻击力
int make_round[2][5] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}}; //make_round[0]:红方制造武士的顺序,make_round[1]:蓝方制造武士的顺序
int begin_life = 0;                                        //初始司令部生命元
int num_cities = 0;                                        //城市数目(red_place:0;blue_place:num_cities+1)
int arrow_hurt = 0;                                        //arrow的攻击力
int minus_loyalty = 0;                                     //lion每经过一场未能杀死敌人的战斗，降低的忠诚度
int time_need = 0;                                         //要求的时间，单位：min分钟

//以下string类信息用于输出
char headquarter_name[2][5] = {"red", "blue"};
char hero_name[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};

//武士类
class hero
{
public:
    int owner; //red=0,blue=1
    int idnum; //该方第几个武士
    int name;  //0-dragon,1-ninja,2-iceman,3-lion,4-wolf
    int place; //当前位于的城市

    int life;     //生命值
    int energy;   //攻击力
    double morale; //士气(仅dragon有，其余的默认设置为-200)
    int loyalty;  //忠诚度，lion为具体数值，其余默认设置为-200

    int killed_by_arrow; //当前回合是否被arrow射死，初始值为0，被射死为1
    int killer;          //当前回合是否通过主动进攻或者反击杀死敌人，用于统计奖励，初始值为0(注意：每一小时最开始都要重置)

    int arms[3][3]; //用于存放武器信息的数组(注意每种武器最多一个)
    //第0,1,2行分别存放sword,bomb,arrow的信息
    //第0列存放是否有该武器(有1无0),第1列存放这种武器的攻击力(仅sword,arrow有效),第2列存放这种武器的可用次数(仅arrow有效)

    hero(int o, int i, int n, int rest) : owner(o), idnum(i), name(n) //rest代表当前司令部剩余的生命元
    {
        if (owner == 0)
            place = 0;
        else if (owner == 1)
            place = num_cities + 1;
        life = hero_life[name];
        energy = hero_energy[name];

        if (name == 0)
            morale = (double)rest / (double)hero_life[0];
        else
            morale = -200;
        if (name == 3)
            loyalty = rest;
        else
            loyalty = -200;

        //输出制造英雄的信息
        cout << headquarter_name[owner] << " " << hero_name[name] << " " << idnum << " born" << endl;
        if (name == 0) //dragon
            cout << "Its morale is " << fixed << setprecision(2) << morale << endl;
        if (name == 3) //lion
            cout << "Its loyalty is " << loyalty << endl;

        //战斗数据设置
        killed_by_arrow = 0;
        killer = 0;

        //配置武器
        //step0:初始化为0
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
                arms[x][y] = 0;
        }
        //step1:设置第0列数值
        switch (name)
        {
        case 0: //dragon
            arms[idnum % 3][0] = 1;
            break;
        case 1: //ninja
            arms[idnum % 3][0] = 1;
            arms[(idnum + 1) % 3][0] = 1;
            break;
        case 2: //iceman
            arms[idnum % 3][0] = 1;
            break;
        default:
            break;
        }
        //step2:设置武器具体信息
        if (arms[0][0] == 1) //sword
        {
            arms[0][1] = energy * 2 / 10;
            if (arms[0][1] == 0)
                arms[0][0] = 0;
        }
        if (arms[2][0] == 1) //arrow
        {
            arms[2][1] = arrow_hurt;
            arms[2][2] = 3;
        }
    }

    //运算符重载==(判等号),在find()时需要用到
    bool operator==(const hero &tmp) const
    {
        return place == tmp.place;
    }

    //攻击对方
    void attack(hero &attacked, int place, int hour)
    {
        attacked.life -= energy;
        if (arms[0][0] == 1)
        {
            attacked.life -= arms[0][1];
            //sword钝化
            arms[0][1] = arms[0][1] * 8 / 10;
            if (arms[0][1] == 0)
                arms[0][0] = 0; //失去sword
        }

        //输出信息
        cout << setw(3) << setfill('0') << hour << ":40 " << headquarter_name[owner] << " " << hero_name[name] << " " << idnum;
        cout << " attacked " << headquarter_name[attacked.owner] << " " << hero_name[attacked.name] << " " << attacked.idnum;
        cout << " in city " << place << " with " << life << " elements and force " << energy << endl;
        return;
    }
    //反击
    void re_attack(hero &attacked, int place, int hour)
    {
        attacked.life -= energy / 2;
        if (arms[0][0] == 1)
        {
            attacked.life -= arms[0][1];
            //sword钝化
            arms[0][1] = arms[0][1] * 8 / 10;
            if (arms[0][1] == 0)
                arms[0][0] = 0; //失去sword
        }

        //输出信息
        cout << setw(3) << setfill('0') << hour << ":40 " << headquarter_name[owner] << " " << hero_name[name] << " " << idnum;
        cout << " fought back against " << headquarter_name[attacked.owner] << " " << hero_name[attacked.name] << " " << attacked.idnum;
        cout << " in city " << place << endl;
        return;
    }
};

//司令部类
class headquarter
{
public:
    int side;                 //red=0,blue=1
    int lives;                //生命元
    int win;                  //本方成功到达对方司令部的武士个数，初始为0，到达2战争结束
    int now;                  //下一个应当尝试造的英雄，模5循环，结合round[2][5]数组使用
    int total;                //总制造英雄数，用于编号
    vector<hero> city_heroes; //所有英雄，按照制造出来的先后顺序排队，先制造出来的若仍然在战场上，则距离司令部一定越远

    headquarter(int s, int l) : side(s), lives(l), win(0), now(0), total(0) {}

    void set_killer() //每个小时一开始，重置每个武士的killer数值为0
    {
        vector<hero>::iterator start = city_heroes.begin(), end = city_heroes.end();
        for (; start != end; start++)
            (*start).killer = 0;
    }

    void make_hero(int hour)
    {
        if (lives < hero_life[make_round[side][now]])
            return;
        //else,制造英雄
        cout << setw(3) << setfill('0') << hour << ":00 ";
        total++;
        lives = lives - hero_life[make_round[side][now]];
        city_heroes.push_back(hero(side, total, make_round[side][now], lives)); //构造武士并放到容器内
        now = (now + 1) % 5;
        return;
    }

    void march()
    {
        //城市位置变化：-2*side+1
        vector<hero>::iterator start = city_heroes.begin(), end = city_heroes.end();
        for (; start != end; start++)
        {
            //if ((*start).place != (1 - side) * (num_cities + 1) &&
            //    (*start).place != (1 - side) * (num_cities + 1) + (-2) * side + 1) //该武士不在对方司令部或者对方司令部后方的位置
            //{
            (*start).place += (-2) * side + 1;

            //iceman每前进两步，生命值和攻击力要发生变化
            if ((*start).name == 2) //iceman
            {
                if (((*start).place - side * (num_cities + 1)) % 2 == 0) //走的步数是2的倍数，此时需要修改生命值和攻击力
                {
                    (*start).life -= 9;
                    (*start).energy += 20;
                    if ((*start).life <= 0)
                        (*start).life = 1;
                }
            }

            //如果到达对方司令部
            if ((*start).place == (1 - side) * (num_cities + 1))
                win++;
            //}
        }
        return;
    }

    void reward_hero(int tmp_lives_num) //奖励获胜武士
    {
        vector<hero>::iterator start = city_heroes.begin(), end = city_heroes.end();
        for (; start != end; start++)
        {
            if ((*start).killer == 1 && tmp_lives_num >= 8) //杀死了对方且有足够的生命元进行奖励
            {
                tmp_lives_num -= 8;
                lives -= 8;
                (*start).life += 8;
            }
        }
        return;
    }

    void report_lives(int hour) //报告生命元数量
    {
        cout << setw(3) << setfill('0') << hour << ":50 " << lives << " elements in " << headquarter_name[side] << " headquarter" << endl;
        return;
    }
};

//城市类
class city
{
public:
    int place;                  //城市编号，从1-(num_cities)
    int flag;                   //旗子：未插旗-1,red0,blue1
    int life_num;               //生命元数目
    hero *red_hero, *blue_hero; //指向当前位于此城市的双方的武士，如果不存在则重置为nullptr

    int winner;    //当前回合胜者（平局2,red0,blue1）
    int win_times; //连胜次数

    city(int p) : place(p), flag(-1), life_num(0), red_hero(nullptr), blue_hero(nullptr), winner(2), win_times(0) {}
};

//lion逃跑
void lion_runaway(headquarter &red, headquarter &blue, int hour)
{
    //按照城市搜索，用一个反向迭代器指向红方的武士，用一个正向迭代器指向蓝方的武士
    vector<hero>::reverse_iterator red_search = red.city_heroes.rbegin(), red_search_end = red.city_heroes.rend();
    vector<hero>::iterator blue_search = blue.city_heroes.begin(), blue_search_end = blue.city_heroes.end();

    //检查红方司令部lion逃跑情况
    if (red_search != red_search_end && (*red_search).place == 0 && (*red_search).name == 3 && (*red_search).loyalty <= 0)
    {
        //四个条件：存在武士，位于本方司令部，是lion，loyalty<=0
        //先输出逃跑信息
        cout << setw(3) << setfill('0') << hour << ":05 ";
        cout << "red lion " << (*red_search).idnum << " ran away" << endl;
        //然后删除该lion
        vector<hero>::reverse_iterator tmp = red_search;
        red_search++;
        tmp++;
        red.city_heroes.erase(tmp.base());
    }
    else if (red_search != red_search_end && (*red_search).place == 0)
        red_search++;

    //检查中间每个城市
    for (int i = 1; i <= num_cities; i++)
    {
        if (red_search != red_search_end && (*red_search).place == i && (*red_search).name == 3 && (*red_search).loyalty <= 0)
        {
            //四个条件：存在武士，位于城市i，是lion，loyalty<=0
            //先输出逃跑信息
            cout << setw(3) << setfill('0') << hour << ":05 ";
            cout << "red lion " << (*red_search).idnum << " ran away" << endl;
            //然后删除该lion
            vector<hero>::reverse_iterator tmp = red_search;
            red_search++;
            tmp++;
            red.city_heroes.erase(tmp.base());
        }
        else if (red_search != red_search_end && (*red_search).place == i)
            red_search++;

        if (blue_search != blue_search_end && (*blue_search).place == i && (*blue_search).name == 3 && (*blue_search).loyalty <= 0)
        {
            //四个条件：存在武士，位于城市i，是lion，loyalty<=0
            //先输出逃跑信息
            cout << setw(3) << setfill('0') << hour << ":05 ";
            cout << "blue lion " << (*blue_search).idnum << " ran away" << endl;
            //然后删除该lion
            blue.city_heroes.erase(blue_search);
        }
        else if (blue_search != blue_search_end && (*blue_search).place == i)
            blue_search++;
    }

    //检查蓝方司令部lion逃跑情况
    if (blue_search != blue_search_end && (*blue_search).place == num_cities + 1 && (*blue_search).name == 3 && (*blue_search).loyalty <= 0)
    {
        //四个条件：存在武士，位于城市i，是lion，loyalty<=0
        //先输出逃跑信息
        cout << setw(3) << setfill('0') << hour << ":05 ";
        cout << "blue lion " << (*blue_search).idnum << " ran away" << endl;
        //然后删除该lion
        blue.city_heroes.erase(blue_search);
    }
}
//输出武士前进，赋值每个城市类中的两个指针
void cout_march(headquarter &red, headquarter &blue, vector<city> &all_cities, int hour)
{
    //按照城市搜索，用一个反向迭代器指向红方的武士，用一个正向迭代器指向蓝方的武士
    vector<hero>::reverse_iterator red_search = red.city_heroes.rbegin(), red_search_end = red.city_heroes.rend();
    vector<hero>::iterator blue_search = blue.city_heroes.begin(), blue_search_end = blue.city_heroes.end();

    if (blue_search != blue_search_end && (*blue_search).place <0)//已经走过红方司令部了
        blue_search++;
    if (blue_search != blue_search_end && (*blue_search).place == 0)
    {
        cout << setw(3) << setfill('0') << hour << ":10 ";
        cout << "blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum << " reached red headquarter";
        cout << " with " << (*blue_search).life << " elements and force " << (*blue_search).energy << endl;

        //输出过一次之后，将该蓝武士的place设置成-1，防止下一轮输出搜索时再次搜索到
        //(*blue_search).place = -1;

        if (blue.win == 2) //两个武士到达
            cout << setw(3) << setfill('0') << hour << ":10 red headquarter was taken" << endl;
        blue_search++;
    }
    for (int i = 1; i <= num_cities; i++)
    {
        if (red_search != red_search_end && (*red_search).place == i)
        {
            cout << setw(3) << setfill('0') << hour << ":10 ";
            cout << "red " << hero_name[(*red_search).name] << " " << (*red_search).idnum << " marched to city " << i;
            cout << " with " << (*red_search).life << " elements and force " << (*red_search).energy << endl;
            all_cities[i].red_hero = &(*red_search); //修改city[i]中的red_hero指针，使其指向当前位于这个城市的红方武士
            red_search++;
        }
        if (blue_search != blue_search_end && (*blue_search).place == i)
        {
            cout << setw(3) << setfill('0') << hour << ":10 ";
            cout << "blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum << " marched to city " << i;
            cout << " with " << (*blue_search).life << " elements and force " << (*blue_search).energy << endl;
            all_cities[i].blue_hero = &(*blue_search); //修改city[i]中的blue_hero指针，使其指向当前位于这个城市的蓝方武士
            blue_search++;
        }
    }
    if (red_search != red_search_end && (*red_search).place == num_cities + 1)
    {
        cout << setw(3) << setfill('0') << hour << ":10 ";
        cout << "red " << hero_name[(*red_search).name] << " " << (*red_search).idnum << " reached blue headquarter";
        cout << " with " << (*red_search).life << " elements and force " << (*red_search).energy << endl;

        //输出过一次之后，将该红武士的place++，防止下一次输出搜索到
        //(*red_search).place++;

        if (red.win == 2) //两个武士到达
            cout << setw(3) << setfill('0') << hour << ":10 blue headquarter was taken" << endl;
        red_search++;
    }
    return;
}
//武士放箭攻击
void put_arrow(vector<city> &all_cities, int hour)
{
    for (int i = 1; i <= num_cities; i++)
    {
        //先红武士检查放箭
        if (i < num_cities && all_cities[i + 1].blue_hero != nullptr &&
            all_cities[i].red_hero != nullptr && all_cities[i].red_hero->arms[2][0] == 1)
        //条件：下一个城市有敌人，这个城市有红武士且自身有arrow
        {
            //敌人生命值修改
            all_cities[i + 1].blue_hero->life -= all_cities[i].red_hero->arms[2][1];
            if (all_cities[i + 1].blue_hero->life <= 0)
            {
                cout << setw(3) << setfill('0') << hour << ":35 red " << hero_name[all_cities[i].red_hero->name] << " ";
                cout << all_cities[i].red_hero->idnum << " shot and killed blue ";
                cout << hero_name[all_cities[i + 1].blue_hero->name] << " " << all_cities[i + 1].blue_hero->idnum << endl;
                all_cities[i + 1].blue_hero->killed_by_arrow = 1;
            }
            else
            {
                cout << setw(3) << setfill('0') << hour << ":35 red " << hero_name[all_cities[i].red_hero->name] << " ";
                cout << all_cities[i].red_hero->idnum << " shot" << endl;
            }

            //武士arrow性质修改
            all_cities[i].red_hero->arms[2][2]--;
            if (all_cities[i].red_hero->arms[2][2] == 0)
            {
                all_cities[i].red_hero->arms[2][0] = 0;
                all_cities[i].red_hero->arms[2][1] = 0;
            }
        }

        //后蓝武士检查放箭
        if (i > 1 && all_cities[i - 1].red_hero != nullptr &&
            all_cities[i].blue_hero != nullptr && all_cities[i].blue_hero->arms[2][0] == 1)
        //条件：下一个城市有敌人，这个城市有蓝武士且自身有arrow
        {
            //敌人生命值修改
            all_cities[i - 1].red_hero->life -= all_cities[i].blue_hero->arms[2][1];
            if (all_cities[i - 1].red_hero->life <= 0)
            {
                cout << setw(3) << setfill('0') << hour << ":35 blue " << hero_name[all_cities[i].blue_hero->name] << " ";
                cout << all_cities[i].blue_hero->idnum << " shot and killed red ";
                cout << hero_name[all_cities[i - 1].red_hero->name] << " " << all_cities[i - 1].red_hero->idnum << endl;
                all_cities[i - 1].red_hero->killed_by_arrow = 1;
            }
            else
            {
                cout << setw(3) << setfill('0') << hour << ":35 blue " << hero_name[all_cities[i].blue_hero->name] << " ";
                cout << all_cities[i].blue_hero->idnum << " shot" << endl;
            }

            //武士arrow性质修改
            all_cities[i].blue_hero->arms[2][2]--;
            if (all_cities[i].blue_hero->arms[2][2] == 0)
            {
                all_cities[i].blue_hero->arms[2][0] = 0;
                all_cities[i].blue_hero->arms[2][1] = 0;
            }
        }
    }
    return;
}
//拥有bomb的武士评估是否应该使用bomb
void use_bomb(headquarter &red, headquarter &blue, vector<city> &all_cities, int hour)
{
    for (int i = 1; i <= num_cities; i++)
    {
        if (all_cities[i].red_hero == nullptr || all_cities[i].blue_hero == nullptr) //不会发生战斗，更不会发生同归于尽
            continue;
        if (all_cities[i].red_hero->killed_by_arrow == 1 || all_cities[i].blue_hero->killed_by_arrow == 1)
            //如果已经有一方被arrow射死
            continue;

        //先行模拟战斗结果
        int result = -1; //模拟结果，红死0，蓝死1，都不会死2
        int tmp_redlife = all_cities[i].red_hero->life, tmp_bluelife = all_cities[i].blue_hero->life;
        if (all_cities[i].flag == 0 || (all_cities[i].flag == -1 && i % 2 == 1)) //red先进攻
        {
            tmp_bluelife -= all_cities[i].red_hero->energy;
            if (all_cities[i].red_hero->arms[0][0] == 1)
                tmp_bluelife -= all_cities[i].red_hero->arms[0][1];
            if (tmp_bluelife <= 0) //blue died
                result = 1;
            else if (tmp_bluelife > 0 && all_cities[i].blue_hero->name != 1) //blue不是ninja,则会反击
            {
                tmp_redlife -= all_cities[i].blue_hero->energy / 2;
                if (all_cities[i].blue_hero->arms[0][0] == 1)
                    tmp_redlife -= all_cities[i].blue_hero->arms[0][1];
                if (tmp_redlife <= 0)
                    result = 0;
            }
        }
        else if (all_cities[i].flag == 1 || (all_cities[i].flag == -1 && i % 2 == 0)) //blue先进攻
        {
            tmp_redlife -= all_cities[i].blue_hero->energy;
            if (all_cities[i].blue_hero->arms[0][0] == 1)
                tmp_redlife -= all_cities[i].blue_hero->arms[0][1];
            if (tmp_redlife <= 0)
                result = 0;
            else if (tmp_redlife > 0 && all_cities[i].red_hero->name != 1) //red不是ninja,则会反击
            {
                tmp_bluelife -= all_cities[i].red_hero->energy / 2;
                if (all_cities[i].red_hero->arms[0][0] == 1)
                    tmp_bluelife -= all_cities[i].red_hero->arms[0][1];
                if (tmp_bluelife <= 0) //blue died
                    result = 1;
            }
        }

        //根据模拟结果，考虑要死的一方
        if (result == 0) //red将死
        {
            if (all_cities[i].red_hero->arms[1][0] == 1) //red有bomb，同归于尽
            {
                //输出信息
                cout << setw(3) << setfill('0') << hour << ":38 red " << hero_name[all_cities[i].red_hero->name] << " ";
                cout << all_cities[i].red_hero->idnum << " used a bomb and killed blue ";
                cout << hero_name[all_cities[i].blue_hero->name] << " " << all_cities[i].blue_hero->idnum << endl;

                /*
                //从red,blue的武士库中删除这两个武士(使用find函数)
                vector<hero>::iterator tmp_red = find(red.city_heroes.begin(), red.city_heroes.end(), *(all_cities[i].red_hero));
                red.city_heroes.erase(tmp_red);
                vector<hero>::iterator tmp_blue = find(blue.city_heroes.begin(), blue.city_heroes.end(), *(all_cities[i].blue_hero));
                blue.city_heroes.erase(tmp_blue);*/

                //标记这两个英雄的生命值为0，便于后续war函数中删除
                all_cities[i].red_hero->life = 0;
                all_cities[i].blue_hero->life = 0;

                //将该城市的hero指针重置为空指针
                all_cities[i].red_hero = nullptr;
                all_cities[i].blue_hero = nullptr;
            }
        }
        else if (result == 1) //blue将死
        {
            if (all_cities[i].blue_hero->arms[1][0] == 1) //blue有bomb，同归于尽
            {
                //输出信息
                cout << setw(3) << setfill('0') << hour << ":38 blue " << hero_name[all_cities[i].blue_hero->name] << " ";
                cout << all_cities[i].blue_hero->idnum << " used a bomb and killed red ";
                cout << hero_name[all_cities[i].red_hero->name] << " " << all_cities[i].red_hero->idnum << endl;

                /*
                //从red,blue的武士库中删除这两个武士(使用find函数)
                vector<hero>::iterator tmp_red = find(red.city_heroes.begin(), red.city_heroes.end(), *(all_cities[i].red_hero));
                red.city_heroes.erase(tmp_red);
                vector<hero>::iterator tmp_blue = find(blue.city_heroes.begin(), blue.city_heroes.end(), *(all_cities[i].blue_hero));
                blue.city_heroes.erase(tmp_blue);*/

                //标记这两个英雄的生命值为0，便于后续war函数中删除
                all_cities[i].red_hero->life = 0;
                all_cities[i].blue_hero->life = 0;

                //将该城市的hero指针重置为空指针
                all_cities[i].red_hero = nullptr;
                all_cities[i].blue_hero = nullptr;
            }
        }
    }
    return;
}
//发生战斗
void war(headquarter &red, headquarter &blue, vector<city> &all_cities, int hour)
{
    //记载双方司令部当前生命元，以便后续分发奖励需要
    int red_life_now = red.lives, blue_life_now = blue.lives;

    int result[25] = {0}; //记录每个城市的战斗结果：red0,blue1,双方均活2,双方均死3

    //每个城市进行处理
    for (int city_check = 1; city_check <= num_cities; city_check++)
    {
        if (all_cities[city_check].red_hero == nullptr || all_cities[city_check].blue_hero == nullptr)
            //不会发生战斗，更不会发生战斗之后的事情
            //备注：被arrow射死的放在后面进行处理
            continue;

        //int result = -1; //red0,blue1,双方均活2,双方均死3
        int red_hero_life = all_cities[city_check].red_hero->life, blue_hero_life = all_cities[city_check].blue_hero->life;
        //存储战斗前双方的生命值

        //step1:进行战斗，输出攻击、反击、战死信息
        if (all_cities[city_check].red_hero->killed_by_arrow == 1 && all_cities[city_check].blue_hero->killed_by_arrow == 1)
        //双方都被箭射死，无事发生
        {
            result[city_check] = 3;
        }
        else if (all_cities[city_check].red_hero->killed_by_arrow != 1 && all_cities[city_check].blue_hero->killed_by_arrow == 1)
        //red胜利
        {
            all_cities[city_check].red_hero->killer = 1;
            result[city_check] = 0;
        }
        else if (all_cities[city_check].red_hero->killed_by_arrow == 1 && all_cities[city_check].blue_hero->killed_by_arrow != 1)
        //blue胜利
        {
            all_cities[city_check].blue_hero->killer = 1;
            result[city_check] = 1;
        }
        else if (all_cities[city_check].red_hero->killed_by_arrow != 1 && all_cities[city_check].blue_hero->killed_by_arrow != 1)
        //双方都仍然存活，发生战斗
        {
            if (all_cities[city_check].flag == 0 || (all_cities[city_check].flag == -1 && city_check % 2 == 1)) //red先手
            {
                all_cities[city_check].red_hero->attack(*(all_cities[city_check].blue_hero), city_check, hour);
                if (all_cities[city_check].blue_hero->life <= 0)
                {
                    result[city_check] = 0;
                    all_cities[city_check].red_hero->killer = 1;

                    //输出战死信息
                    cout << setw(3) << setfill('0') << hour << ":40 blue " << hero_name[all_cities[city_check].blue_hero->name];
                    cout << " " << all_cities[city_check].blue_hero->idnum << " was killed in city " << city_check << endl;
                }
                else
                {
                    if (all_cities[city_check].blue_hero->name != 1) //不是ninja，反击
                    {
                        all_cities[city_check].blue_hero->re_attack(*(all_cities[city_check].red_hero), city_check, hour);
                        if (all_cities[city_check].red_hero->life <= 0)
                        {
                            result[city_check] = 1;
                            all_cities[city_check].blue_hero->killer = 1;

                            //输出战死信息
                            cout << setw(3) << setfill('0') << hour << ":40 red " << hero_name[all_cities[city_check].red_hero->name];
                            cout << " " << all_cities[city_check].red_hero->idnum << " was killed in city " << city_check << endl;
                        }
                        else
                            result[city_check] = 2;
                    }
                    else //是ninja,不进行反击,由于此时ninja未死亡，因此平局
                        result[city_check] = 2;
                }
            }
            else if (all_cities[city_check].flag == 1 || (all_cities[city_check].flag == -1 && city_check % 2 == 0)) //blue先手
            {
                all_cities[city_check].blue_hero->attack(*(all_cities[city_check].red_hero), city_check, hour);
                if (all_cities[city_check].red_hero->life <= 0)
                {
                    result[city_check] = 1;
                    all_cities[city_check].blue_hero->killer = 1;

                    //输出战死信息
                    cout << setw(3) << setfill('0') << hour << ":40 red " << hero_name[all_cities[city_check].red_hero->name];
                    cout << " " << all_cities[city_check].red_hero->idnum << " was killed in city " << city_check << endl;
                }
                else
                {
                    if (all_cities[city_check].red_hero->name != 1) //不是ninja，反击
                    {
                        all_cities[city_check].red_hero->re_attack(*(all_cities[city_check].blue_hero), city_check, hour);
                        if (all_cities[city_check].blue_hero->life <= 0)
                        {
                            result[city_check] = 0;
                            all_cities[city_check].red_hero->killer = 1;

                            //输出战死信息
                            cout << setw(3) << setfill('0') << hour << ":40 blue " << hero_name[all_cities[city_check].blue_hero->name];
                            cout << " " << all_cities[city_check].blue_hero->idnum << " was killed in city " << city_check << endl;
                        }
                        else
                            result[city_check] = 2;
                    }
                    else //是ninja,不进行反击,由于此时ninja未死亡，因此平局
                        result[city_check] = 2;
                }
            }
        }

        //step2:战后缴获武器、生命值、改变忠诚度和士气（此过程无输出）
        if (result[city_check] == 0) //red胜利，几种情况：缴获、获取生命值、改变士气
        {
            if (all_cities[city_check].red_hero->name == 4) //wolf,缴获
            {
                for (int x = 0; x < 3; x++)
                {
                    if (all_cities[city_check].red_hero->arms[x][0] == 0)
                    {
                        for (int y = 0; y < 3; y++)
                            all_cities[city_check].red_hero->arms[x][y] = all_cities[city_check].blue_hero->arms[x][y];
                    }
                }
            }
            if (all_cities[city_check].blue_hero->name == 3)                     //对方是lion，获取生命值
                all_cities[city_check].red_hero->life += max(0, blue_hero_life); //有可能是被射死的，此时不增加生命值
            if (all_cities[city_check].red_hero->name == 0)                      //dragon,改变士气值
                all_cities[city_check].red_hero->morale += 0.2;
        }
        else if (result[city_check] == 1) //blue胜利，情况同上
        {
            if (all_cities[city_check].blue_hero->name == 4) //wolf,缴获
            {
                for (int x = 0; x < 3; x++)
                {
                    if (all_cities[city_check].blue_hero->arms[x][0] == 0)
                    {
                        for (int y = 0; y < 3; y++)
                            all_cities[city_check].blue_hero->arms[x][y] = all_cities[city_check].red_hero->arms[x][y];
                    }
                }
            }
            if (all_cities[city_check].red_hero->name == 3)                      //对方是lion，获取生命值
                all_cities[city_check].blue_hero->life += max(0, red_hero_life); //有可能是被射死的，此时不增加生命值
            if (all_cities[city_check].blue_hero->name == 0)                     //dragon,改变士气值
                all_cities[city_check].blue_hero->morale += 0.2;
        }
        else if (result[city_check] == 2) //双方均存活，仅进行该改变忠诚度和士气的操作
        {
            if (all_cities[city_check].red_hero->name == 0)
                all_cities[city_check].red_hero->morale -= 0.2;
            if (all_cities[city_check].blue_hero->name == 0)
                all_cities[city_check].blue_hero->morale -= 0.2;
            if (all_cities[city_check].red_hero->name == 3)
                all_cities[city_check].red_hero->loyalty -= minus_loyalty;
            if (all_cities[city_check].blue_hero->name == 3)
                all_cities[city_check].blue_hero->loyalty -= minus_loyalty;
        }

        //step3:dragon欢呼，输出对应信息
        if (all_cities[city_check].red_hero->name == 0 && all_cities[city_check].red_hero->life > 0 &&
            all_cities[city_check].red_hero->morale > 0.8 &&
            (all_cities[city_check].flag == 0 || (all_cities[city_check].flag == -1 && city_check % 2 == 1)))
        //red先手，存活且red dragon yelled
        {
            cout << setw(3) << setfill('0') << hour << ":40 red dragon " << all_cities[city_check].red_hero->idnum;
            cout << " yelled in city " << city_check << endl;
        }
        if (all_cities[city_check].blue_hero->name == 0 && all_cities[city_check].blue_hero->life > 0 &&
            all_cities[city_check].blue_hero->morale > 0.8 &&
            (all_cities[city_check].flag == 1 || (all_cities[city_check].flag == -1 && city_check % 2 == 0)))
        //blue先手且blue dragon yelled
        {
            cout << setw(3) << setfill('0') << hour << ":40 blue dragon " << all_cities[city_check].blue_hero->idnum;
            cout << " yelled in city " << city_check << endl;
        }
        /*
        //step4:处理死者（此过程无输出）
        if (result == 0) //blue died
        {
            vector<hero>::iterator tmp_blue = find(blue.city_heroes.begin(), blue.city_heroes.end(), *(all_cities[city_check].blue_hero));
            blue.city_heroes.erase(tmp_blue);
            all_cities[city_check].blue_hero = nullptr;
        }
        else if (result == 1) //red died
        {
            vector<hero>::iterator tmp_red = find(red.city_heroes.begin(), red.city_heroes.end(), *(all_cities[city_check].red_hero));
            red.city_heroes.erase(tmp_red);
            all_cities[city_check].red_hero = nullptr;
        }
        else if (result == 3) //both died
        {
            vector<hero>::iterator tmp_red = find(red.city_heroes.begin(), red.city_heroes.end(), *(all_cities[city_check].red_hero));
            red.city_heroes.erase(tmp_red);
            all_cities[city_check].red_hero = nullptr;

            vector<hero>::iterator tmp_blue = find(blue.city_heroes.begin(), blue.city_heroes.end(), *(all_cities[city_check].blue_hero));
            blue.city_heroes.erase(tmp_blue);
            all_cities[city_check].blue_hero = nullptr;
        }*/

        //step5:武士获取生命元
        //只有result为0,1的情况才能发生这个事件
        if (result[city_check] == 0) //red win
        {
            //修改司令部生命元
            red.lives += all_cities[city_check].life_num;
            //输出
            cout << setw(3) << setfill('0') << hour << ":40 red " << hero_name[all_cities[city_check].red_hero->name];
            cout << " " << all_cities[city_check].red_hero->idnum << " earned " << all_cities[city_check].life_num;
            cout << " elements for his headquarter" << endl;
            //修改城市生命元
            all_cities[city_check].life_num = 0;
        }
        else if (result[city_check] == 1) //blue win
        {
            //修改司令部生命元
            blue.lives += all_cities[city_check].life_num;
            //输出
            cout << setw(3) << setfill('0') << hour << ":40 blue " << hero_name[all_cities[city_check].blue_hero->name];
            cout << " " << all_cities[city_check].blue_hero->idnum << " earned " << all_cities[city_check].life_num;
            cout << " elements for his headquarter" << endl;
            //修改城市生命元
            all_cities[city_check].life_num = 0;
        }

        //step6:修改胜平负情况（此过程无输出）
        //重置连胜场数
        if (result[city_check] != 3) //不是双方均被射死的情况，才算有战争事件发生
        {
            if (all_cities[city_check].winner == result[city_check])
                all_cities[city_check].win_times++;
            else
            {
                all_cities[city_check].winner = result[city_check];
                all_cities[city_check].win_times = 1;
            }
        }

        //step7:升旗
        //升旗情况：当前连胜>=2且连胜方!=当前旗子的数值且当前连胜是0或1
        if (all_cities[city_check].win_times >= 2 && all_cities[city_check].winner != all_cities[city_check].flag &&
            (all_cities[city_check].winner == 0 || all_cities[city_check].winner == 1))
        {
            all_cities[city_check].flag = all_cities[city_check].winner;

            //输出
            cout << setw(3) << setfill('0') << hour << ":40 " << headquarter_name[all_cities[city_check].flag];
            cout << " flag raised in city " << city_check << endl;
        }
    }

    for (int city_check = 1; city_check <= num_cities; city_check++)
    {
        //step4:处理死者（此过程无输出）
        //用迭代器遍历
        vector<hero>::iterator red_start = red.city_heroes.begin();   //, red_end = red.city_heroes.end();
        vector<hero>::iterator blue_start = blue.city_heroes.begin(); //, blue_end = blue.city_heroes.end();
        for (; red_start != red.city_heroes.end();)
        {
            if ((*red_start).life <= 0)
                red.city_heroes.erase(red_start);
            else
                red_start++;
        }
        for (; blue_start != blue.city_heroes.end();)
        {
            if ((*blue_start).life <= 0)
                blue.city_heroes.erase(blue_start);
            else
                blue_start++;
        }
    }
    //按照战斗前司令部拥有的生命元数目，分发奖励
    //如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利
    //每一方都按照迭代器顺序从前到后进行奖励，直到奖励到战斗前的生命元数目不够使用或者到达终点为止
    red.reward_hero(red_life_now);
    blue.reward_hero(blue_life_now);
    return;
}
//武士报告武器情况
void report_arms(headquarter &red, headquarter &blue, int hour)
{
    vector<hero>::reverse_iterator red_start = red.city_heroes.rbegin(), red_end = red.city_heroes.rend();
    for (; red_start != red_end; red_start++)
    {
        cout << setw(3) << setfill('0') << hour << ":55 red " << hero_name[(*red_start).name] << " " << (*red_start).idnum << " has ";
        int num_arms = (*red_start).arms[0][0] + (*red_start).arms[1][0] + (*red_start).arms[2][0];
        if (num_arms == 0)
            cout << "no weapon" << endl;
        else
        {
            if ((*red_start).arms[2][0] == 1)
            {
                cout << "arrow(" << (*red_start).arms[2][2] << ")";
                num_arms--;
                if (num_arms > 0)
                    cout << ",";
                else
                    cout << endl;
            }
            if ((*red_start).arms[1][0] == 1)
            {
                cout << "bomb";
                num_arms--;
                if (num_arms > 0)
                    cout << ",";
                else
                    cout << endl;
            }
            if ((*red_start).arms[0][0] == 1)
            {
                cout << "sword(" << (*red_start).arms[0][1] << ")";
                num_arms--;
                if (num_arms > 0)
                    cout << ",";
                else
                    cout << endl;
            }
        }
    }

    vector<hero>::iterator blue_start = blue.city_heroes.begin(), blue_end = blue.city_heroes.end();
    for (; blue_start != blue_end; blue_start++)
    {
        cout << setw(3) << setfill('0') << hour << ":55 blue " << hero_name[(*blue_start).name] << " " << (*blue_start).idnum << " has ";
        int num_arms = (*blue_start).arms[0][0] + (*blue_start).arms[1][0] + (*blue_start).arms[2][0];
        if (num_arms == 0)
            cout << "no weapon" << endl;
        else
        {
            if ((*blue_start).arms[2][0] == 1)
            {
                cout << "arrow(" << (*blue_start).arms[2][2] << ")";
                num_arms--;
                if (num_arms > 0)
                    cout << ",";
                else
                    cout << endl;
            }
            if ((*blue_start).arms[1][0] == 1)
            {
                cout << "bomb";
                num_arms--;
                if (num_arms > 0)
                    cout << ",";
                else
                    cout << endl;
            }
            if ((*blue_start).arms[0][0] == 1)
            {
                cout << "sword(" << (*blue_start).arms[0][1] << ")";
                num_arms--;
                if (num_arms > 0)
                    cout << ",";
                else
                    cout << endl;
            }
        }
    }
    return;
}

//主函数
int main()
{
    int cases = 0;
    cin >> cases;
    //freopen("out.txt", "w", stdout); //将标准输出重定向到 out.txt文件
    for (int test = 1; test <= cases; test++)
    {
        cout << "Case " << test << ":" << endl;
        cin >> begin_life >> num_cities >> arrow_hurt >> minus_loyalty >> time_need;
        for (int i = 0; i < 5; i++)
            cin >> hero_life[i];
        for (int i = 0; i < 5; i++)
            cin >> hero_energy[i];

        //新建司令部
        headquarter red(0, begin_life);
        headquarter blue(1, begin_life);
        //新建城市，用类数组方式储存
        vector<city> all_cities;
        for (int i = 0; i <= num_cities; i++)
            all_cities.push_back(city(i)); //注:city(0)没用，只是为了以后下标为i就是第i个城市的访问方便

        //逐个小时模拟
        for (int hour = 0; 60 * hour <= time_need; hour++)
        {
            //每个小时一开始：将所有城市的hero指针重置为空指针
            for (int i = 0; i <= num_cities; i++)
            {
                all_cities[i].red_hero = nullptr;
                all_cities[i].blue_hero = nullptr;
            }
            //每个小时一开始：将所有武士的killer数值重置为0
            red.set_killer();
            blue.set_killer();

            //(1)每小时第0分：武士降生
            //先检查是否超时
            if (60 * hour > time_need)
                break;
            red.make_hero(hour);
            blue.make_hero(hour);

            //(2)每小时第5分：lion逃跑
            //先检查是否超时
            if (60 * hour + 5 > time_need)
                break;
            lion_runaway(red, blue, hour);

            //(3)每小时第10分：所有武士前进一步
            //先检查是否超时
            if (60 * hour + 10 > time_need)
                break;
            red.march();
            blue.march();
            //输出武士前进信息，并赋值每个城市对应的两个武士指针(如果某个城市没有某一方的武士，则由于循环开始的设置，保证其为nullptr)
            cout_march(red, blue, all_cities, hour);
            //检查是否战争结束
            if (red.win == 2 || blue.win == 2)
                break;

            //(4)每小时第20分：每个城市产出10个生命元
            //先检查是否超时
            if (60 * hour + 20 > time_need)
                break;
            for (int i = 1; i <= num_cities; i++)
                all_cities[i].life_num += 10;

            //(5)每个小时的第30分：仅有一个武士的城市，取走所有的生命元，并传送到司令部（注意：此步无输出）
            //先检查是否超时
            if (60 * hour + 30 > time_need)
                break;
            for (int i = 1; i <= num_cities; i++)
            {
                if (all_cities[i].red_hero == nullptr && all_cities[i].blue_hero != nullptr)
                {
                    blue.lives += all_cities[i].life_num;
                    //输出信息
                    cout << setw(3) << setfill('0') << hour << ":30 blue " << hero_name[all_cities[i].blue_hero->name];
                    cout << " " << all_cities[i].blue_hero->idnum << " earned " << all_cities[i].life_num << " elements for his headquarter" << endl;
                    all_cities[i].life_num = 0;
                }
                else if (all_cities[i].blue_hero == nullptr && all_cities[i].red_hero != nullptr)
                {
                    red.lives += all_cities[i].life_num;
                    //输出信息
                    cout << setw(3) << setfill('0') << hour << ":30 red " << hero_name[all_cities[i].red_hero->name];
                    cout << " " << all_cities[i].red_hero->idnum << " earned " << all_cities[i].life_num << " elements for his headquarter" << endl;
                    all_cities[i].life_num = 0;
                }
            }

            //(6)每个小时的第35分：拥有arrow的武士放箭，对敌人造成伤害
            //先检查是否超时
            if (60 * hour + 35 > time_need)
                break;
            put_arrow(all_cities, hour);

            //(7)每个小时的第38分：拥有bomb的武士评估是否应该使用bomb
            //先检查是否超时
            if (60 * hour + 38 > time_need)
                break;
            use_bomb(red, blue, all_cities, hour);

            //(8)每个小时的第40分：在有两个武士的城市，会发生战斗
            //先检查是否超时
            if (60 * hour + 40 > time_need)
                break;
            war(red, blue, all_cities, hour);

            //(9)每个小时的第50分：司令部报告生命元数量
            //先检查是否超时
            if (60 * hour + 50 > time_need)
                break;
            red.report_lives(hour);
            blue.report_lives(hour);

            //(10)每个小时的第55分：每个武士报告武器情况
            //先检查是否超时
            if (60 * hour + 55 > time_need)
                break;
            report_arms(red, blue, hour);
        }
    }
    return 0;
}