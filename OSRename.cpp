#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <io.h>
#include <dir.h>
#include <direct.h>
#include <fcntl.h>
#include <string.h>
#define MAX 10000
//�ڼ���ʵ��ı��� ����͸ĳ�ʵ�鼸
#define LAB "ʵ���"
using namespace std;
int count=0;
int mark[32]={0};
string list[32][2]={
"������","201426010101",
"������","201426010102",
"����Ө","201426010103",
"�����","201426010104",
"����","201426010105",
"�ջԽ�","201426010106",
"���ӷ�","201426010107",
"���ϳ�","201426010108",
"�ƽ���","201426010109",
"�ź���","201426010110",
"��Ө","201426010111",
"ФҢ","201426010112",
"л��","201426010114",
"����˼","201426010115",
"���ҹ�","201426010116",
"��껷�","201426010117",
"л����","201426010118",
"������","201426010119",
"����","201426010120",
"������","201426010121",
"��ݼ","201426010122",
"����","201426010123",
"�����","201426010124",
"�γ���","201426010125",
"����","201426010126",
"�ź�","201426010127",
"֣��ѩ","201426010128",
"������","201426010129",
"�Ƽ�����","201426010130",
"��˼��","201411010219",
"Ҷï��","201412010213",
"����","L2014042"
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
            //ѧ��_����_ʵ���

            string newname=list[i][1]+"-"+list[i][0]+"-"+(string)lab+suffix;
            //���ո�
            string command;
            if(found3!=std::string::npos)
            {
                cout<<temp<<"  �ļ������пո�"<<endl;
                rename(name,newname.data());
                command="copy "+(string)dest+"\\"+newname+" "+(string)dest+"\\result\\"+newname;
                cout<<"�����Ѿ����"<<endl;
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
        long handle;                                                //���ڲ��ҵľ��
        struct _finddata_t fileinfo;                          //�ļ���Ϣ�Ľṹ��
        handle=_findfirst(dest,&fileinfo);         //��һ�β���
        if(-1==handle)return -1;
        reName(fileinfo.name,src,lab) ;                      //��ӡ���ҵ����ļ����ļ���
        while(!_findnext(handle,&fileinfo))               //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
        {
         reName(fileinfo.name,src,lab) ;                      //��ӡ���ҵ����ļ����ļ���
        }
        _findclose(handle);                                      //�����˹رվ��
	 }
	//docx
	strcat(dest,"x");
	 {
        long handle;                                                //���ڲ��ҵľ��
        struct _finddata_t fileinfo;                          //�ļ���Ϣ�Ľṹ��
        handle=_findfirst(dest,&fileinfo);         //��һ�β���
        if(-1==handle)return -1;
        reName(fileinfo.name,src,lab) ;                      //��ӡ���ҵ����ļ����ļ���
        while(!_findnext(handle,&fileinfo))               //ѭ�������������ϵ��ļ���֪���Ҳ���������Ϊֹ
        {
         reName(fileinfo.name,src,lab) ;                      //��ӡ���ҵ����ļ����ļ���
        }
        _findclose(handle);                                      //�����˹رվ��
	 }
    cout<<"ͳ����"<<count<<"�����Ͻ���ҵ"<<endl;
    cout<<"----------------------------------"<<endl;
    int i=0;
    for(int j=0;j<32;j++)
    {
        if(mark[j]==0)
        {
            i++;
            cout<<"ѧ��"<<list[j][1]<<"    ������"<<list[j][0]<<"    û������"<<endl;
        }
        else if(mark[j]>1)
            cout<<"ͳ���д���,��ϸ�˶����"<<endl;
    }
    if(count!=(32-i))
            cout<<"���˳��ָ���˵�������,��ϸ�˶�"<<endl;
    {
        cout<<"----------------------------------"<<endl;
        cout<<"Ӧ��32��  ʵ�ʽ�"<<count<<"��  "<<32-count<<"��û��  "<<i-32+count<<"�������쳣"<<endl;
        cout<<"û����������\n�淶����ĵ�������resultĿ¼�£������"<<endl;
        cout<<"\n����˵����ֻ���doc��docx�ĵ���������������ʽ����ʾû��  ������ֺ�ѧ�Ŷ�д��really?��Ҳ����ʾû��"<<endl;
    }
    system("pause");
	return 1;
}
