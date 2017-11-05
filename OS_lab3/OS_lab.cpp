#include<windows.h>
#include<process.h>
#include<stdio.h>

#define M 3
#define N 3
#define K 2
 int A[M][K]={{1,4},{2,5},{3,6}};
 int B[K][N]={{8,7,6},{5,4,3}};
 int C[M][N];

struct DOUB {
int row;
int col;
};

HANDLE hMutex[10][10];
DWORD WINAPI ThreadProc(LPVOID lpParameter ){
   DOUB* hCur=(DOUB*)lpParameter;
 //struct v*data=(struct v*)malloc(sizeof(struct v));
 //int x=hCur->row;
 //int y=hCur->col;
 int x=hCur->row;
 int y=hCur->col;

 hMutex[x][y]=CreateMutex(NULL,true,NULL);
 int r=0;
 for(int i=0;i<K;++i)
    r+=A[x][i]*B[i][y];
 C[x][y]=r;
 ReleaseMutex(hMutex[x][y]);
 return 0;
}
int main(){
	/*printf("¾ØÕóA:\n");
	for(int i=0;i<M;i++){
		for(int j=0;j<K;i++)
		printf("%d ",A[i][j]);
	}
	printf("¾ØÕóB:\n");
	for(int i=0;i<K;i++){
		for(int j=0;j<N;i++)
	       printf("%d ",B[i][j]);
	}*/
    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j){
            DOUB temp;
            DOUB* hTemp=&temp;
            hTemp->row=i;
            hTemp->col=j;
            HANDLE hThread=CreateThread(NULL,0,ThreadProc,hTemp,0,NULL);
            CloseHandle(hThread);
            Sleep(100);
        }
    }
    for(int i=0;i<M;++i)
        for(int j=0;j<N;++j)
        WaitForSingleObject(hMutex[i][j],INFINITE);
    printf("\n¾ØÕóÏà³Ë½á¹û:\n");
    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j)
            printf("%d ",C[i][j]);
        printf("\n");
    }
    return 0;
}


