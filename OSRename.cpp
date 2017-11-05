#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <io.h>
#include <dir.h>
#include <direct.h>
#include <fcntl.h>
#include <string.h>
#define MAX 10000
//第几次实验的报告 这里就改成实验几
#define LAB "实验二"
using namespace std;
int count=0;
int mark[32]={0};
string list[32][2]={
"赵云朋","201426010101",
"胡泽宇","201426010102",
"韩润莹","201426010103",
"刘东淼","201426010104",
"宜文","201426010105",
"苏辉江","201426010106",
"王子枫","201426010107",
"李孟超","201426010108",
"黄建超","201426010109",
"张汉至","201426010110",
"胡莹","201426010111",
"肖尧","201426010112",
"谢锋","201426010114",
"梁锦思","201426010115",
"李忠耿","201426010116",
"李昊峰","201426010117",
"谢晓琨","201426010118",
"刘文武","201426010119",
"沈涛","201426010120",
"陈仁妮","201426010121",
"颜菁","201426010122",
"刘欢","201426010123",
"宗玉芬","201426010124",
"任晨熙","201426010125",
"丁帆","201426010126",
"张航","201426010127",
"郑瑞雪","201426010128",
"阿尔曼","201426010129",
"唐加丽克","201426010130",
"王思雄","201411010219",
"叶茂臻","201412010213",
"安琪","L2014042"
};
bool reName(char* name,char* dest,char* lab){
	count++;
	string temp=(string)name;
	string suffix=temp.substr(temp.find_last_of("."),temp.size());
	for(int i=0;i<32;i++)
    {
        std::size_t found = temp.find(list[i][0]);
        std::size_t found2 = temp.find(list[i][1]);
        std::size_t found3 = temp.find(" ");

        if((found!=std::string::npos)or(found2!=std::string::npos))
        {
            mark[i]++;
            //学号_姓名_实验二

            string newname=list[i][1]+"-"+list[i][0]+"-"+(string)lab+suffix;
            //检查空格
            string command;
            if(found3!=std::string::npos)
            {
                cout<<temp<<"  文件名含有空格"<<endl;
                rename(name,newname.data());
                command="copy "+(string)dest+"\\"+newname+" "+(string)dest+"\\result\\"+newname;
                cout<<"问题已经解决"<<endl;
            }
            else
                command="copy "+(string)dest+"\\"+temp+" "+(string)dest+"\\result\\"+newname;
            system(command.data());
        }
    }
	return 1;
}
int main()
{
	char lab[MAX]=LAB;
	char dest[MAX],src[MAX],name[MAX];
	getcwd(dest, MAX);
	strcpy(src,dest);
	printf("The current directory is: %s\n", dest);
	strcat(src,"\\result");
	// mkdir
	mkdir(src);
	getcwd(src, MAX);
	strcat(dest,"\\*.doc");
	//maintain
	//doc
	 {
        long handle;                                                //用于查找的句柄
        struct _finddata_t fileinfo;                          //文件信息的结构体
        handle=_findfirst(dest,&fileinfo);         //第一次查找
        if(-1==handle)return -1;
        reName(fileinfo.name,src,lab) ;                      //打印出找到的文件的文件名
        while(!_findnext(handle,&fileinfo))               //循环查找其他符合的文件，知道找不到其他的为止
        {
         reName(fileinfo.name,src,lab) ;                      //打印出找到的文件的文件名
        }
        _findclose(handle);                                      //别忘了关闭句柄
	 }
	//docx
	strcat(dest,"x");
	 {
        long handle;                                                //用于查找的句柄
        struct _finddata_t fileinfo;                          //文件信息的结构体
        handle=_findfirst(dest,&fileinfo);         //第一次查找
        if(-1==handle)return -1;
        reName(fileinfo.name,src,lab) ;                      //打印出找到的文件的文件名
        while(!_findnext(handle,&fileinfo))               //循环查找其他符合的文件，知道找不到其他的为止
        {
         reName(fileinfo.name,src,lab) ;                      //打印出找到的文件的文件名
        }
        _findclose(handle);                                      //别忘了关闭句柄
	 }
    cout<<"统计有"<<count<<"个人上交作业"<<endl;
    cout<<"----------------------------------"<<endl;
    int i=0;
    for(int j=0;j<32;j++)
    {
        if(mark[j]==0)
        {
            i++;
            cout<<"学号"<<list[j][1]<<"    姓名："<<list[j][0]<<"    没交！！"<<endl;
        }
        else if(mark[j]>1)
            cout<<"统计有错误,仔细核对情况"<<endl;
    }
    if(count!=(32-i))
            cout<<"有人出现附加说明的情况,仔细核对"<<endl;
    {
        cout<<"----------------------------------"<<endl;
        cout<<"应交32人  实际交"<<count<<"人  "<<32-count<<"人没交  "<<i-32+count<<"人命名异常"<<endl;
        cout<<"没交名单如上\n规范后的文档放置在result目录下，请查验"<<endl;
        cout<<"\n附加说明：只针对doc和docx文档进行整理，其他格式会显示没交  如果名字和学号都写错（really?）也会显示没交"<<endl;
    }
    system("pause");
	return 1;
}
