#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <vector>
using namespace std;
long width = 0, height = 0; //输入图像的宽度和高度
BITMAPFILEHEADER filehead;  //输入图像的bmp文件头
BITMAPINFOHEADER bmphead;   //输入图像的位图信息头
class pixel
{
public:
    char r, g, b;
};                             //每一个像素
vector<vector<pixel>> picture; //存储图片每一个像素信息的二维vector
void readbmp(char *filename)
{
    ifstream file;
    file.open(filename, ios::binary | ios::in); //二进制打开
    if (!file)                                  //检查是否正确打开
    {
        cout << "文件打开错误！" << endl;
        return;
    }

    file.read((char *)&filehead, sizeof(BITMAPFILEHEADER)); //读bmp文件头，作强制类型转换
    file.read((char *)&bmphead, sizeof(BITMAPINFOHEADER));  //读位图信息头，作强制类型转换
    width = bmphead.biWidth;                                //获取宽度
    height = bmphead.biHeight;                              //获取高度
    int byte_rest = (4 - (3 * width) % 4) % 4;              //计算每一行对齐所需的字节数
    //读取图像
    for (int i = 0; i < height; i++)
    {
        vector<pixel> row;
        for (int j = 0; j < width; j++)
        {
            pixel pi;
            //读入r,g,b
            file.read(&pi.r, sizeof(char));
            file.read(&pi.g, sizeof(char));
            file.read(&pi.b, sizeof(char));
            row.push_back(pi);
        }
        picture.push_back(row);
        char tmp;
        for (int j = 0; j < byte_rest; j++)
            file.read(&tmp, sizeof(char));
    }
    //关闭文件
    file.close();
    return;
}
void writebmp(char *filename)
{
    ofstream file;
    file.open(filename, ios::out | ios::binary);
    if (!file) //检查是否正确打开
    {
        cout << "文件写入错误！" << endl;
        return;
    }

    //重新计算图像所需空间并写入bmp文件头
    unsigned long rotation_size = 54 + width * ((3 * height + 3) / 4 * 4);
    filehead.bfSize = rotation_size;
    //对换位图信息头中的宽和高以及修改图像所需空间
    bmphead.biWidth = height;
    bmphead.biHeight = width;
    bmphead.biSizeImage = rotation_size;
    //交换水平垂直分辨率
    long tmp = bmphead.biXPelsPerMeter;
    bmphead.biXPelsPerMeter = bmphead.biYPelsPerMeter;
    bmphead.biYPelsPerMeter = tmp;

    //写入文件
    file.seekp(0, ios::beg);                                 //回到开头
    file.write((char *)&filehead, sizeof(BITMAPFILEHEADER)); //写bmp文件头，作强制类型转换
    file.write((char *)&bmphead, sizeof(BITMAPINFOHEADER));  //写位图信息头，作强制类型转换
    //写图像信息
    int byte_rest = (4 - (3 * height) % 4) % 4; //计算此时对齐所需的字节数
    char rest = 0;                              //用于对齐补0
    for (int i = width - 1; i >= 0; i--)
    {
        for (int j = 0; j < height; j++)
        {
            file.write(&picture[j][i].r, sizeof(char));
            file.write(&picture[j][i].g, sizeof(char));
            file.write(&picture[j][i].b, sizeof(char));
        }
        for (int j = 0; j < byte_rest; j++)
            file.write(&rest, sizeof(char));
    }
    //关闭文件
    file.close();
    return;
}
int main(int argc, char *argv[]) // argv[1]是输入图像名,argv[2]是输出图像名
{
    if (argc == 3) //命令行打开的正确情形
    {
        readbmp(argv[1]);
        writebmp(argv[2]);
    }
    else if (argc == 1) //.exe双击直接打开的情形
    {
        cout << "请输入待旋转的图片名及目标文件名，用空格间隔：" << endl;
        string s1, s2;
        cin >> s1 >> s2;
        int len1 = s1.length(), len2 = s2.length();
        char *str1 = new char[len1 + 1];
        char *str2 = new char[len2 + 1];
        strcpy(str1, s1.c_str());
        strcpy(str2, s2.c_str());
        readbmp(str1);
        writebmp(str2);
    }
    else
        cout << "输入格式错误，请按照rotatebmp src.bmp dest.bmp的格式输入！" << endl;
    return 0;
}