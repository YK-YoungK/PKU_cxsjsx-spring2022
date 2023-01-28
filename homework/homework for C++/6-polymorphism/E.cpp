#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <vector> //双方分别放各自所有的武士
#include <map>    //每个武士所有的武器
using namespace std;

//以下全局变量可用于武士类和司令部类的初始化
int hero_life[5] = {0};                                    //记录五种武士的初始生命值
int hero_energy[5] = {0};                                  //记录五种武士的初始攻击力
int make_round[2][5] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}}; //make_round[0]:红方制造武士的顺序,make_round[1]:蓝方制造武士的顺序
int begin_life = 0;                                        //初始司令部生命元
int num_cities = 0;                                        //城市数目(red_place:0;blue_place:num_cities+1)
int minus_loyalty = 0;                                     //lion每前进一步减少的生命值
int time_need = 0;                                         //要求的时间，单位：min分钟

//以下string类信息用于输出
char city_name[2][5] = {"red", "blue"};
char hero_name[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};

//武士类
class hero
{
public:
    int owner; //red=0,blue=1
    int idnum; //该方第几个武士
    int name;  //0-dragon,1-ninja,2-iceman,3-lion,4-wolf
    int place; //当前位于的城市

    int life;    //生命值
    int energy;  //攻击力
    int loyalty; //忠诚度，lion为具体数值，其余默认设置为-200(注意数据范围lion走一步最多降低loyalty:100)

    int num_arms;            //武器数目
    multimap<int, int> arms; //所有武器，first-武器编号(sword-0,bomb-1,arrow-2)，second-武器可以使用次数（如果是sword初始化为-1）

    hero(int o, int i, int n, int l) : owner(o), idnum(i), name(n)
    {
        if (owner == 0)
            place = 0;
        else
            place = num_cities + 1;
        life = hero_life[name];
        energy = hero_energy[name];
        if (name == 3)
            loyalty = l;
        else
            loyalty = -200;
        num_arms = 0;

        //输出制造英雄的信息
        cout << city_name[owner] << " " << hero_name[name] << " " << idnum << " born" << endl;
        if (name == 3) //lion
            cout << "Its loyalty is " << loyalty << endl;

        //配置武器
        //second含义：还能使用的次数;sword初始为-1,不受影响
        if (name == 0) //dragon
        {
            num_arms = 1;
            if (idnum % 3 == 0) //得到sword
                arms.insert(make_pair(0, -1));
            else
                arms.insert(make_pair(idnum % 3, idnum % 3));
        }
        else if (name == 1) //ninja
        {
            num_arms = 2;
            if (idnum % 3 == 0)
            {
                arms.insert(make_pair(0, -1));
                arms.insert(make_pair(1, 1));
            }
            else if (idnum % 3 == 1)
            {
                arms.insert(make_pair(1, 1));
                arms.insert(make_pair(2, 2));
            }
            else if (idnum % 3 == 2)
            {
                arms.insert(make_pair(2, 2));
                arms.insert(make_pair(0, -1));
            }
        }
        else if (name == 2) //iceman
        {
            num_arms = 1;
            if (idnum % 3 == 0) //得到sword
                arms.insert(make_pair(0, -1));
            else
                arms.insert(make_pair(idnum % 3, idnum % 3));
        }
        else if (name == 3) //lion
        {
            num_arms = 1;
            if (idnum % 3 == 0) //得到sword
                arms.insert(make_pair(0, -1));
            else
                arms.insert(make_pair(idnum % 3, idnum % 3));
        }
    }
};

//司令部类
class city
{
public:
    int side;                 //red=0,blue=1
    int lives;                //生命元
    int stop_making;          //是否停止制造武士，是1否0，初始值0
    int win;                  //是否攻占敌方司令部，是1否0，初始值0
    int now;                  //下一个应当尝试造的英雄，模5循环，结合round[2][5]数组使用
    int total;                //总制造英雄数，用于编号
    vector<hero> city_heroes; //所有英雄，按照制造出来的先后顺序排队，先制造出来的若仍然在战场上，则距离司令部一定越远

    city(int s, int l) : side(s), lives(l), stop_making(0), win(0), now(0), total(0) {}
    void make_hero(int hour)
    {
        if (stop_making == 1)
            return;

        if (lives < hero_life[make_round[side][now]])
        {
            stop_making = 1;
            return;
        }
        else //制造now对应的hero并放到vector容器内
        {
            //先输出时间
            cout << setw(3) << setfill('0') << hour << ":00 ";

            total++;
            lives = lives - hero_life[make_round[side][now]];
            //cout<<"   "<<lives<<endl;
            city_heroes.push_back(hero(side, total, make_round[side][now], lives)); //构造武士对象并放到vector内
            now = (now + 1) % 5;
            return;
        }
    }

    void march(int hour)
    {
        //城市位置变化：-2*side+1
        vector<hero>::iterator start = city_heroes.begin(), end = city_heroes.end();
        for (; start != end; start++)
        {
            if ((*start).place != (1 - side) * (num_cities + 1)) //该武士不在对方司令部
            {
                (*start).place += (-2) * side + 1;

                //iceman每前进一步，生命值减少10%(减少的量要去尾取整)
                if ((*start).name == 2) //iceman
                    (*start).life -= (*start).life / 10;
                //lion每前进一步忠诚度就降低K
                if ((*start).name == 3) //lion
                    (*start).loyalty -= minus_loyalty;

                //如果到达对方司令部
                if ((*start).place == (1 - side) * (num_cities + 1))
                    win = 1;

                /*//输出信息
                //不是到达对方司令部的情况
                if ((*start).place != (1 - side) * (num_cities + 1))
                {
                    cout << setw(3) << setfill('0') << hour << ":10 ";
                    cout << city_name[side] << " " << hero_name[(*start).name] << " " << (*start).idnum << " marched to city ";
                    cout << (*start).place << " with " << (*start).life << " elements and force " << (*start).energy << endl;
                }
                else //是到达对方司令部的情况
                {
                    win = 1; //到达了对方司令部
                    cout << setw(3) << setfill('0') << hour << ":10 ";
                    cout << city_name[side] << " " << hero_name[(*start).name] << " " << (*start).idnum << " reached ";
                    cout << city_name[1 - side] << " headquarter ";
                    cout << " with " << (*start).life << " elements and force " << (*start).energy << endl;
                }*/
            }
        }
    }

    int arrive(int hour)
    {
        /*if (win == 1)
        {
            cout << setw(3) << setfill('0') << hour << ":10 ";
            cout << city_name[1 - side] << " headquarter was taken" << endl;
        }*/
        return win;
    }

    void report(int hour)
    {
        cout << setw(3) << setfill('0') << hour << ":50 " << lives << " elements in " << city_name[side] << " headquarter" << endl;
        return;
    }
};

//lion逃跑
void lion_runaway(city &red, city &blue, int hour)
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
            vector<hero>::iterator tmp = blue_search;
            //blue_search++;
            blue.city_heroes.erase(tmp); //将反向迭代器转为正向迭代器
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
        vector<hero>::iterator tmp = blue_search;
        //blue_search++;
        blue.city_heroes.erase(tmp); //将反向迭代器转为正向迭代器
    }
    /*
    for (vector<hero>::iterator tmp = start; tmp != end;)
    {
        if ((*tmp).name == 3 && (*tmp).place != (1 - side) * (num_cities + 1) && (*tmp).loyalty <= 0)
        {
            //三个条件：是lion，不在对方司令部，loyalty<=0
            //先输出逃跑信息
            cout << setw(3) << setfill('0') << hour << ":05 ";
            cout << city_name[side] << " lion " << (*tmp).idnum << " ran away" << endl;
            //再删除该lion
            vector<hero>::iterator tmp1 = tmp; //临时的迭代器，指向即将被删除的武士对象
            tmp++;
            city_heroes.erase(tmp1); //返回值指向下一个迭代器
        }
        else
            tmp++; //若未删除，则手动将start移至下一个迭代器
    }*/
}
//输出武士前进
void cout_march(city &red, city &blue, int hour)
{
    //按照城市搜索，用一个反向迭代器指向红方的武士，用一个正向迭代器指向蓝方的武士
    vector<hero>::reverse_iterator red_search = red.city_heroes.rbegin(), red_search_end = red.city_heroes.rend();
    vector<hero>::iterator blue_search = blue.city_heroes.begin(), blue_search_end = blue.city_heroes.end();

    if (blue_search != blue_search_end && (*blue_search).place == 0)
    {
        cout << setw(3) << setfill('0') << hour << ":10 ";
        cout << "blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum << " reached red headquarter";
        cout << " with " << (*blue_search).life << " elements and force " << (*blue_search).energy << endl;
        cout << setw(3) << setfill('0') << hour << ":10 red headquarter was taken"<<endl;
        blue_search++;
    }
    for (int i = 1; i <= num_cities; i++)
    {
        if (red_search != red_search_end && (*red_search).place == i)
        {
            cout << setw(3) << setfill('0') << hour << ":10 ";
            cout << "red " << hero_name[(*red_search).name] << " " << (*red_search).idnum << " marched to city " << i;
            cout << " with " << (*red_search).life << " elements and force " << (*red_search).energy << endl;
            red_search++;
        }
        if (blue_search != blue_search_end && (*blue_search).place == i)
        {
            cout << setw(3) << setfill('0') << hour << ":10 ";
            cout << "blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum << " marched to city " << i;
            cout << " with " << (*blue_search).life << " elements and force " << (*blue_search).energy << endl;
            blue_search++;
        }
    }
    if (red_search != red_search_end && (*red_search).place == num_cities + 1)
    {
        cout << setw(3) << setfill('0') << hour << ":10 ";
        cout << "red " << hero_name[(*red_search).name] << " " << (*red_search).idnum << " reached blue headquarter";
        cout << " with " << (*red_search).life << " elements and force " << (*red_search).energy << endl;
        cout << setw(3) << setfill('0') << hour << ":10 blue headquarter was taken"<<endl;
        red_search++;
    }
    return;
}
//wolf抢武器
void wolf_get_arms(city &red, city &blue, int hour)
{
    //按照城市搜索，用一个反向迭代器指向红方的武士，用一个正向迭代器指向蓝方的武士
    vector<hero>::reverse_iterator red_search = red.city_heroes.rbegin(), red_search_end = red.city_heroes.rend();
    vector<hero>::iterator blue_search = blue.city_heroes.begin(), blue_search_end = blue.city_heroes.end();
    for (int i = 1; i <= num_cities; i++)
    {
        //三种情况：(1)红蓝相同，(2)红在该城市，蓝在该城市之后，(3)情形(2)反过来
        //注意检查越界情况
        //情形(1)
        if (red_search != red_search_end && blue_search != blue_search_end && (*red_search).place == (*blue_search).place)
        {
            if ((*red_search).name == 4 && (*blue_search).name != 4) //red抢blue
            {
                //检查red武器，blue编号最小武器(武器用multimap排序，只需获取第一个)
                if ((*blue_search).num_arms != 0) //检查blue武器个数是否为0
                {
                    multimap<int, int>::iterator blue_arm_start = (*blue_search).arms.begin(), blue_arm_end = (*blue_search).arms.end();
                    int blue_min = blue_arm_start->first; //获取blue编号最小武器
                    if (blue_min == 0)                    //sword
                    {
                        int get_num = min((int)(*blue_search).arms.count(0), 10 - (*red_search).num_arms); //所抢该种武器的个数
                        (*red_search).num_arms += get_num;
                        (*blue_search).num_arms -= get_num;
                        multimap<int, int>::iterator tmp = (*blue_search).arms.begin();
                        for (int i = 0; i < get_num; i++)
                        {
                            multimap<int, int>::iterator tmp1 = tmp;
                            (*red_search).arms.insert(make_pair(0, -1));
                            tmp++;
                            (*blue_search).arms.erase(tmp1);
                        }

                        //输出抢武器结果
                        cout << setw(3) << setfill('0') << hour << ":35 red wolf " << (*red_search).idnum;
                        cout << " took " << get_num << " sword from blue " << hero_name[(*blue_search).name] << " ";
                        cout << (*blue_search).idnum << " in city " << i << endl;
                    }
                    else if (blue_min == 1) //bomb
                    {
                        int get_num = min((int)(*blue_search).arms.count(1), 10 - (*red_search).num_arms); //所抢该种武器的个数
                        (*red_search).num_arms += get_num;
                        (*blue_search).num_arms -= get_num;
                        multimap<int, int>::iterator tmp = (*blue_search).arms.begin();
                        for (int i = 0; i < get_num; i++)
                        {
                            multimap<int, int>::iterator tmp1 = tmp;
                            (*red_search).arms.insert(make_pair(1, 1));
                            tmp++;
                            (*blue_search).arms.erase(tmp1);
                        }

                        //输出抢武器结果
                        cout << setw(3) << setfill('0') << hour << ":35 red wolf " << (*red_search).idnum;
                        cout << " took " << get_num << " bomb from blue " << hero_name[(*blue_search).name] << " ";
                        cout << (*blue_search).idnum << " in city " << i << endl;
                    }
                    else if (blue_min == 2) //arrow，此时所有武器均为arrow
                    {
                        //统计没用过的和用过的数目
                        int used_num = 0, unused_num = 0;
                        for (multimap<int, int>::iterator t = blue_arm_start; t != blue_arm_end; t++)
                        {
                            if (t->second == 2)
                                unused_num++;
                            else if (t->second == 1)
                                used_num++;
                        }
                        //重新排序，把没用过的放在前面
                        multimap<int, int>::iterator tmp2 = blue_arm_start;
                        for (int i = 0; i < used_num + unused_num; i++, tmp2++)
                        {
                            if (i < unused_num)
                                tmp2->second = 2;
                            else
                                tmp2->second = 1;
                        }
                        //wolf开始抢武器
                        int get_num = min(used_num + unused_num, 10 - (*red_search).num_arms);
                        (*red_search).num_arms += get_num;
                        (*blue_search).num_arms -= get_num;
                        multimap<int, int>::iterator tmp = (*blue_search).arms.begin();
                        for (int i = 0; i < get_num; i++)
                        {
                            multimap<int, int>::iterator tmp1 = tmp;
                            if (i < unused_num)
                                (*red_search).arms.insert(make_pair(2, 2));
                            else
                                (*red_search).arms.insert(make_pair(2, 1));
                            tmp++;
                            (*blue_search).arms.erase(tmp1);
                        }

                        //输出抢武器结果
                        cout << setw(3) << setfill('0') << hour << ":35 red wolf " << (*red_search).idnum;
                        cout << " took " << get_num << " arrow from blue " << hero_name[(*blue_search).name] << " ";
                        cout << (*blue_search).idnum << " in city " << i << endl;
                    }
                }
            }
            else if ((*blue_search).name == 4 && (*red_search).name != 4) //blue抢red
            {
                //检查blue武器，red编号最小武器(武器用multimap排序，只需获取第一个)
                if ((*red_search).num_arms != 0) //检查red武器个数是否为0
                {
                    multimap<int, int>::iterator red_arm_start = (*red_search).arms.begin(), red_arm_end = (*red_search).arms.end();
                    int red_min = red_arm_start->first; //获取red编号最小武器
                    if (red_min == 0)                   //sword
                    {
                        int get_num = min((int)(*red_search).arms.count(0), 10 - (*blue_search).num_arms); //所抢该种武器的个数
                        (*blue_search).num_arms += get_num;
                        (*red_search).num_arms -= get_num;
                        multimap<int, int>::iterator tmp = (*red_search).arms.begin();
                        for (int i = 0; i < get_num; i++)
                        {
                            multimap<int, int>::iterator tmp1 = tmp;
                            (*blue_search).arms.insert(make_pair(0, -1));
                            tmp++;
                            (*red_search).arms.erase(tmp1);
                        }

                        //输出抢武器结果
                        cout << setw(3) << setfill('0') << hour << ":35 blue wolf " << (*blue_search).idnum;
                        cout << " took " << get_num << " sword from red " << hero_name[(*red_search).name] << " ";
                        cout << (*red_search).idnum << " in city " << i << endl;
                    }
                    else if (red_min == 1) //bomb
                    {
                        int get_num = min((int)(*red_search).arms.count(1), 10 - (*blue_search).num_arms); //所抢该种武器的个数
                        (*blue_search).num_arms += get_num;
                        (*red_search).num_arms -= get_num;
                        multimap<int, int>::iterator tmp = (*red_search).arms.begin();
                        for (int i = 0; i < get_num; i++)
                        {
                            multimap<int, int>::iterator tmp1 = tmp;
                            (*blue_search).arms.insert(make_pair(1, 1));
                            tmp++;
                            (*red_search).arms.erase(tmp1);
                        }

                        //输出抢武器结果
                        cout << setw(3) << setfill('0') << hour << ":35 blue wolf " << (*blue_search).idnum;
                        cout << " took " << get_num << " bomb from red " << hero_name[(*red_search).name] << " ";
                        cout << (*red_search).idnum << " in city " << i << endl;
                    }
                    else if (red_min == 2) //arrow，此时所有武器均为arrow
                    {
                        //统计没用过的和用过的数目
                        int used_num = 0, unused_num = 0;
                        for (multimap<int, int>::iterator t = red_arm_start; t != red_arm_end; t++)
                        {
                            if (t->second == 2)
                                unused_num++;
                            else if (t->second == 1)
                                used_num++;
                        }
                        //重新排序，把没用过的放在前面
                        multimap<int, int>::iterator tmp2 = red_arm_start;
                        for (int i = 0; i < used_num + unused_num; i++, tmp2++)
                        {
                            if (i < unused_num)
                                tmp2->second = 2;
                            else
                                tmp2->second = 1;
                        }
                        //wolf开始抢武器
                        int get_num = min(used_num + unused_num, 10 - (*blue_search).num_arms);
                        (*blue_search).num_arms += get_num;
                        (*red_search).num_arms -= get_num;
                        multimap<int, int>::iterator tmp = (*red_search).arms.begin();
                        for (int i = 0; i < get_num; i++)
                        {
                            multimap<int, int>::iterator tmp1 = tmp;
                            if (i < unused_num)
                                (*blue_search).arms.insert(make_pair(2, 2));
                            else
                                (*blue_search).arms.insert(make_pair(2, 1));
                            tmp++;
                            (*red_search).arms.erase(tmp1);
                        }

                        //输出抢武器结果
                        cout << setw(3) << setfill('0') << hour << ":35 blue wolf " << (*blue_search).idnum;
                        cout << " took " << get_num << " arrow from red " << hero_name[(*red_search).name] << " ";
                        cout << (*red_search).idnum << " in city " << i << endl;
                    }
                }
            }
            red_search++;
            blue_search++;
        }
        //情形(2)
        else if (red_search != red_search_end && (*red_search).place == i)
        {
            red_search++;
        }
        //情形(3)
        else if (blue_search != blue_search_end && (*blue_search).place == i)
        {
            blue_search++;
        }
    }
    return;
}
//一方用武器攻击另外一方
multimap<int, int>::iterator attack(hero &attacker, hero &attacked, multimap<int, int>::iterator &now)
{
    if (now->first == 0) //sword
    {
        attacked.life -= attacker.energy * 2 / 10;
        now++;
        if (now == attacker.arms.end())
            now = attacker.arms.begin();
    }
    else if (now->first == 1) //bomb
    {
        int hurt = attacker.energy * 4 / 10;
        attacked.life -= hurt;
        if (attacker.name != 1)
        {
            hurt = hurt / 2;
            attacker.life -= hurt;
        }
        //删除bomb武器
        attacker.num_arms--;
        multimap<int, int>::iterator tmp_delete = now;
        now++;
        if (now == attacker.arms.end())
            now = attacker.arms.begin();
        attacker.arms.erase(tmp_delete);
    }
    else if (now->first == 2) //arrow
    {
        attacked.life -= attacker.energy * 3 / 10;
        now->second--;
        if (now->second == 0) //删除arrow
        {
            attacker.num_arms--;
            multimap<int, int>::iterator tmp_delete = now;
            now++;
            if (now == attacker.arms.end())
                now = attacker.arms.begin();
            attacker.arms.erase(tmp_delete);
        }
        else
        {
            now++;
            if (now == attacker.arms.end())
                now = attacker.arms.begin();
        }
    }
    return now;
}
//判断当场战斗是否结束
pair<int, int> judge_over(hero &red, hero &blue)
{
    //分出胜负的方法：单方死去
    //平局情况：(1)双方武器都用完了且都活着(2)双方都死了(3)战斗中双方的生命值和武器的状态都不再发生变化(只可能是两方都只有sword)
    //情形(3)补充说明:这种情况只有可能出现在双方的武器均只有sword且双方的攻击力都<=4
    //结束的几种情况：有死亡，双方的状态均为(无武器)或(只有sword(这个用迭代器检索进行检查)且攻击力<=4)
    //winner-pair.first:未结束-(-1),red-0,blue-1,平局(双方均死亡)-2,平局(双方均存活)-3
    //war_status-pair.second:正在进行:0,胜负已分:1,平局(双方均死亡):-1,平局(双方均存活):-2
    if (red.life <= 0 && blue.life > 0)
        return make_pair(1, 1);
    else if (blue.life <= 0 && red.life > 0)
        return make_pair(0, 1);
    else if (red.life <= 0 && blue.life <= 0)
        return make_pair(2, -1);
    else
    {
        int r = 0, b = 0;
        if (red.num_arms == 0)
            r = 1;
        else
        {
            multimap<int, int>::iterator r_tmp = red.arms.end();
            r_tmp--;
            if (r_tmp->first == 0 && red.energy <= 4)
                r = 1;
        }
        if (blue.num_arms == 0)
            b = 1;
        else
        {
            multimap<int, int>::iterator b_tmp = blue.arms.end();
            b_tmp--;
            if (b_tmp->first == 0 && blue.energy <= 4)
                b = 1;
        }

        if (r == 1 && b == 1)
            return make_pair(3, -2);
        else
            return make_pair(-1, 0);
    }
}
//战后缴获武器
void get_arms_after_war(hero &winner, hero &loser)
{
    //检查loser武器数量
    if (loser.num_arms == 0)
        return;

    //loser武器排序
    multimap<int, int>::iterator loser_arrow_begin = loser.arms.lower_bound(2), loser_arrow_end = loser.arms.end();
    if (loser_arrow_begin != loser_arrow_end) //存在arrow,需要计数与排序
    {
        int used = 0, unused = 0;
        for (multimap<int, int>::iterator tmp1 = loser_arrow_begin; tmp1 != loser_arrow_end; tmp1++)
        {
            if (tmp1->second == 1)
                used++;
            else if (tmp1->second == 2)
                unused++;
        }
        multimap<int, int>::iterator tmp = loser_arrow_begin;
        for (int i = 0; tmp != loser_arrow_end; tmp++, ++i)
        {
            if (i < unused)
                tmp->second = 2;
            else
                tmp->second = 1;
        }
    }

    //开始缴获
    int get_num = min(loser.num_arms, 10 - winner.num_arms);
    multimap<int, int>::iterator tmp_get = loser.arms.begin();
    for (int i = 0; i < get_num; tmp_get++, ++i)
    {
        winner.arms.insert(*tmp_get);
    }
    winner.num_arms+=get_num;

    return;
}
//双方武士战斗
void war(city &red, city &blue, int hour)
{
    //按照城市搜索，用一个反向迭代器指向红方的武士，用一个正向迭代器指向蓝方的武士
    vector<hero>::reverse_iterator red_search = red.city_heroes.rbegin(), red_search_end = red.city_heroes.rend();
    vector<hero>::iterator blue_search = blue.city_heroes.begin(), blue_search_end = blue.city_heroes.end();
    for (int city_check = 1; city_check <= num_cities; city_check++)
    {
        //三种情况：(1)红蓝相同，(2)红在该城市，蓝在该城市之后，(3)情形(2)反过来
        //注意检查越界情况
        //情形(1),发生战斗
        if (red_search != red_search_end && blue_search != blue_search_end && (*red_search).place == (*blue_search).place)
        {
            //step1:双方排序武器,只需排序arrow,将用过的放在没用过的前面
            int red_used_arrow = 0, red_unused_arrow = 0, blue_used_arrow = 0, blue_unused_arrow = 0;
            multimap<int, int>::iterator red_arrow_start = (*red_search).arms.lower_bound(2), red_arrow_end = (*red_search).arms.end();
            multimap<int, int>::iterator blue_arrow_start = (*blue_search).arms.lower_bound(2), blue_arrow_end = (*blue_search).arms.end();
            //red
            for (multimap<int, int>::iterator tmp = red_arrow_start; tmp != red_arrow_end; tmp++)
            {
                if (tmp->second == 1)
                    red_used_arrow++;
                else if (tmp->second == 2)
                    red_unused_arrow++;
            }
            multimap<int, int>::iterator tmp_red_arrow = red_arrow_start;
            for (int i = 0; tmp_red_arrow != red_arrow_end; tmp_red_arrow++, ++i)
            {
                if (i < red_used_arrow)
                    tmp_red_arrow->second = 1;
                else
                    tmp_red_arrow->second = 2;
            }
            //blue
            for (multimap<int, int>::iterator tmp = blue_arrow_start; tmp != blue_arrow_end; tmp++)
            {
                if (tmp->second == 1)
                    blue_used_arrow++;
                else if (tmp->second == 2)
                    blue_unused_arrow++;
            }
            multimap<int, int>::iterator tmp_blue_arrow = blue_arrow_start;
            for (int i = 0; tmp_blue_arrow != blue_arrow_end; tmp_blue_arrow++, ++i)
            {
                if (i < blue_used_arrow)
                    tmp_blue_arrow->second = 1;
                else
                    tmp_blue_arrow->second = 2;
            }

            //step2:双方开始战斗
            //分出胜负的方法：单方死去
            //平局情况：(1)双方武器都用完了且都活着(2)双方都死了(3)战斗中双方的生命值和武器的状态都不再发生变化(只可能是两方都只有sword)
            //情形(3)补充说明:这种情况只有可能出现在双方的武器均只有sword且双方的攻击力都<=4
            int winner = -1;         //未结束-(-1),red-0,blue-1,平局(双方均死亡)-2,平局(双方均存活)-3
            int war_status = 0;      //正在进行:0,胜负已分:1,平局(双方均死亡):-1,平局(双方均存活):-2
            if (city_check % 2 == 1) //红武士先手
            {
                multimap<int, int>::iterator red_now = (*red_search).arms.begin();
                multimap<int, int>::iterator blue_now = (*blue_search).arms.begin();

                //先判断战争是否会直接不进行
                winner = judge_over(*red_search, *blue_search).first;
                war_status = judge_over(*red_search, *blue_search).second;

                while (war_status == 0)
                {
                    //红武士出击
                    //先判断其是否有武器
                    if ((*red_search).num_arms != 0)
                        red_now = attack(*red_search, *blue_search, red_now); //返回的下一个武器对应的迭代器赋值给red_now
                    //更新winner,war_status,并判断战斗是否结束
                    winner = judge_over(*red_search, *blue_search).first;
                    war_status = judge_over(*red_search, *blue_search).second;
                    if (war_status != 0)
                        break;

                    //蓝武士出击
                    //先判断其是否有武器
                    if ((*blue_search).num_arms != 0)
                        blue_now = attack(*blue_search, *red_search, blue_now);
                    //更新winner,war_status,并判断战斗是否结束
                    winner = judge_over(*red_search, *blue_search).first;
                    war_status = judge_over(*red_search, *blue_search).second;
                    if (war_status != 0)
                        break;
                }
            }
            else //蓝武士先手
            {
                multimap<int, int>::iterator red_now = (*red_search).arms.begin();
                multimap<int, int>::iterator blue_now = (*blue_search).arms.begin();

                //先判断战争是否会直接不进行
                winner = judge_over(*red_search, *blue_search).first;
                war_status = judge_over(*red_search, *blue_search).second;

                while (war_status == 0)
                {
                    //蓝武士出击
                    //先判断其是否有武器
                    if ((*blue_search).num_arms != 0)
                        blue_now = attack(*blue_search, *red_search, blue_now);
                    //更新winner,war_status,并判断战斗是否结束
                    winner = judge_over(*red_search, *blue_search).first;
                    war_status = judge_over(*red_search, *blue_search).second;
                    if (war_status != 0)
                        break;

                    //红武士出击
                    //先判断其是否有武器
                    if ((*red_search).num_arms != 0)
                        red_now = attack(*red_search, *blue_search, red_now); //返回的下一个武器对应的迭代器赋值给red_now
                    //更新winner,war_status,并判断战斗是否结束
                    winner = judge_over(*red_search, *blue_search).first;
                    war_status = judge_over(*red_search, *blue_search).second;
                    if (war_status != 0)
                        break;
                }
            }

            //战斗结束：(1)缴获武器(2)输出战斗信息(3)处理死亡及迭代器处理
            //(1)
            if (winner == 0)
                get_arms_after_war(*red_search, *blue_search);
            else if (winner == 1)
                get_arms_after_war(*blue_search, *red_search);

            //(2)
            if (winner == 0)
            {
                cout << setw(3) << setfill('0') << hour << ":40 red " << hero_name[(*red_search).name] << " " << (*red_search).idnum;
                cout << " killed blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum << " in city " << city_check;
                cout << " remaining " << (*red_search).life << " elements" << endl;
                //yelled
                if ((*red_search).name == 0)
                    cout << setw(3) << setfill('0') << hour << ":40 red dragon " << (*red_search).idnum << " yelled in city " << city_check << endl;
            }
            else if (winner == 1)
            {
                cout << setw(3) << setfill('0') << hour << ":40 blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum;
                cout << " killed red " << hero_name[(*red_search).name] << " " << (*red_search).idnum << " in city " << city_check;
                cout << " remaining " << (*blue_search).life << " elements" << endl;
                //yelled
                if ((*blue_search).name == 0)
                    cout << setw(3) << setfill('0') << hour << ":40 blue dragon " << (*blue_search).idnum << " yelled in city " << city_check << endl;
            }
            else if (winner == 2)
            {
                cout << setw(3) << setfill('0') << hour << ":40 both red " << hero_name[(*red_search).name] << " " << (*red_search).idnum;
                cout << " and blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum;
                cout << " died in city " << city_check << endl;
            }
            else if (winner == 3)
            {
                cout << setw(3) << setfill('0') << hour << ":40 both red " << hero_name[(*red_search).name] << " " << (*red_search).idnum;
                cout << " and blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum;
                cout << " were alive in city " << city_check << endl;
                //yelled
                if ((*red_search).name == 0)
                    cout << setw(3) << setfill('0') << hour << ":40 red dragon " << (*red_search).idnum << " yelled in city " << city_check << endl;
                if ((*blue_search).name == 0)
                    cout << setw(3) << setfill('0') << hour << ":40 blue dragon " << (*blue_search).idnum << " yelled in city " << city_check << endl;
            }

            //(3)
            if (winner == 0) //blue died
            {
                blue.city_heroes.erase(blue_search);
                red_search++;
            }
            else if (winner == 1) //red died
            {
                vector<hero>::reverse_iterator tmp_delete_red = red_search;
                tmp_delete_red++;
                red.city_heroes.erase(tmp_delete_red.base());
                red_search++;
                blue_search++;
            }
            else if (winner == 2) //both died
            {
                vector<hero>::reverse_iterator tmp_delete_red = red_search;
                tmp_delete_red++;
                red.city_heroes.erase(tmp_delete_red.base());
                red_search++;
                blue.city_heroes.erase(blue_search);
            }
            else if (winner == 3) //both alive
            {
                red_search++;
                blue_search++;
            }
        }
        //情形(2)
        else if (red_search != red_search_end && (*red_search).place == city_check)
            red_search++;
        //情形(3)
        else if (blue_search != blue_search_end && (*blue_search).place == city_check)
            blue_search++;

        //debug:case1 第5小时，战斗情况错误
    }
}
//武士报告情况
void hero_report(city &red, city &blue, int hour)
{
    //按照城市搜索，用一个反向迭代器指向红方的武士，用一个正向迭代器指向蓝方的武士
    vector<hero>::reverse_iterator red_search = red.city_heroes.rbegin(), red_search_end = red.city_heroes.rend();
    vector<hero>::iterator blue_search = blue.city_heroes.begin(), blue_search_end = blue.city_heroes.end();
    for (int i = 1; i <= num_cities; i++)
    {
        //三种情况：(1)红蓝相同，(2)红在该城市，蓝在该城市之后，(3)情形(2)反过来
        //注意检查越界情况
        if (red_search != red_search_end && blue_search != blue_search_end && (*red_search).place == (*blue_search).place)
        {
            //red
            int red_sword = 0, red_bomb = 0, red_arrow = 0;
            for (multimap<int, int>::iterator tmp_red = (*red_search).arms.begin(); tmp_red != (*red_search).arms.end(); tmp_red++)
            {
                if (tmp_red->first == 0)
                    red_sword++;
                else if (tmp_red->first == 1)
                    red_bomb++;
                else if (tmp_red->first == 2)
                    red_arrow++;
            }
            cout << setw(3) << setfill('0') <<hour<< ":55 red " << hero_name[(*red_search).name] << " " << (*red_search).idnum << " has ";
            cout << red_sword << " sword " << red_bomb << " bomb " << red_arrow << " arrow and " << (*red_search).life << " elements" << endl;
            red_search++;

            //blue
            int blue_sword = 0, blue_bomb = 0, blue_arrow = 0;
            for (multimap<int, int>::iterator tmp_blue = (*blue_search).arms.begin(); tmp_blue != (*blue_search).arms.end(); tmp_blue++)
            {
                if (tmp_blue->first == 0)
                    blue_sword++;
                else if (tmp_blue->first == 1)
                    blue_bomb++;
                else if (tmp_blue->first == 2)
                    blue_arrow++;
            }
            cout << setw(3) << setfill('0') <<hour<< ":55 blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum << " has ";
            cout << blue_sword << " sword " << blue_bomb << " bomb " << blue_arrow << " arrow and " << (*blue_search).life << " elements" << endl;
            blue_search++;
        }
        else if (red_search != red_search_end && (*red_search).place == i)
        {
            //red
            int red_sword = 0, red_bomb = 0, red_arrow = 0;
            for (multimap<int, int>::iterator tmp_red = (*red_search).arms.begin(); tmp_red != (*red_search).arms.end(); tmp_red++)
            {
                if (tmp_red->first == 0)
                    red_sword++;
                else if (tmp_red->first == 1)
                    red_bomb++;
                else if (tmp_red->first == 2)
                    red_arrow++;
            }
            cout << setw(3) << setfill('0') <<hour<< ":55 red " << hero_name[(*red_search).name] << " " << (*red_search).idnum << " has ";
            cout << red_sword << " sword " << red_bomb << " bomb " << red_arrow << " arrow and " << (*red_search).life << " elements" << endl;
            red_search++;
        }
        else if (blue_search != blue_search_end && (*blue_search).place == i)
        {
            //blue
            int blue_sword = 0, blue_bomb = 0, blue_arrow = 0;
            for (multimap<int, int>::iterator tmp_blue = (*blue_search).arms.begin(); tmp_blue != (*blue_search).arms.end(); tmp_blue++)
            {
                if (tmp_blue->first == 0)
                    blue_sword++;
                else if (tmp_blue->first == 1)
                    blue_bomb++;
                else if (tmp_blue->first == 2)
                    blue_arrow++;
            }
            cout << setw(3) << setfill('0') <<hour<< ":55 blue " << hero_name[(*blue_search).name] << " " << (*blue_search).idnum << " has ";
            cout << blue_sword << " sword " << blue_bomb << " bomb " << blue_arrow << " arrow and " << (*blue_search).life << " elements" << endl;
            blue_search++;
        }
    }
}

//主函数
int main()
{
    int cases = 0;
    cin >> cases;
    for (int test = 1; test <= cases; test++)
    {
        //输入数据
        cout << "Case " << test << ":" << endl;
        cin >> begin_life >> num_cities >> minus_loyalty >> time_need;
        for (int i = 0; i < 5; i++)
            cin >> hero_life[i];
        for (int i = 0; i < 5; i++)
            cin >> hero_energy[i];

        //新建司令部
        city red(0, begin_life);
        city blue(1, begin_life);

        //开始模拟全过程，逐小时进行
        for (int hour = 0; 60 * hour <= time_need; hour++)
        {
            //(1)每小时0分：双方尝试制造武士
            red.make_hero(hour);
            blue.make_hero(hour);

            //(2)每小时5分：lion逃跑
            //先判断是否超时
            if (60 * hour + 5 > time_need)
                break;
            lion_runaway(red, blue, hour);

            //(3)每小时10分：双方武士分别前进一步，最后需要检查是否有武士到达对方司令部
            //先判断是否超时
            if (60 * hour + 10 > time_need)
                break;
            //武士前进
            red.march(hour);
            blue.march(hour);
            //输出武士前进信息
            cout_march(red, blue, hour);
            //判断是否到达对方司令部
            int blue_arrive = blue.arrive(hour), red_arrive = red.arrive(hour);
            if (red_arrive == 1 || blue_arrive == 1)
                break; //游戏结束
            //注意：需要修改输出顺序，按城市顺序输出！

            //(4)每小时第35分：在有wolf及其敌人的城市，wolf要抢夺对方的武器
            //先判断是否超时
            if (60 * hour + 35 > time_need)
                break;
            wolf_get_arms(red, blue, hour); //传参传的是红蓝双方城市的引用

            //(5)每小时第40分：在有两个武士的城市，会发生战斗
            //先判断是否超时
            if (60 * hour + 40 > time_need)
                break;
            war(red, blue, hour);

            //(6)每小时第50分：司令部报告生命元情况
            //先判断是否超时
            if (60 * hour + 50 > time_need)
                break;
            red.report(hour);
            blue.report(hour);

            //(7)每小时第55分：武士报告情况
            //先判断是否超时
            if (60 * hour + 55 > time_need)
                break;
            hero_report(red,blue,hour);
        }
    }
    return 0;
}