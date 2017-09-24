#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
using namespace std;
struct Digit{
	int x;
	int y;
};  
char ss[4]={'+','-','x','%'}; //操作符
//返回操作符的优先级
int mPriority(char op){
	if(op=='+') return 1;
	else if(op=='-') return 1;
	else if(op=='x') return 2;
	else if(op=='%') return 2;
} 
//求最大公约数
int gcd(int a,int b)
{
	if(b==0) return a;
	else return gcd(b,a%b);	
}  
//根据操作符计算两个操作数
Digit Calculate(Digit num1,Digit num2,char op){
	Digit res;
	int f;
	switch(op){
		case '+':{
			res.x=num1.x*num2.y+num1.y*num2.x;
			res.y=num1.y*num2.y;
			break;
		}
		case '-':{
			res.x=num1.x*num2.y-num1.y*num2.x;
			res.y=num1.y*num2.y;
			break;
		}
		case 'x':{
			res.x=num1.x*num2.x;
			res.y=num1.y*num2.y;
			break;
		}
		case '%':{
			res.x=num1.x*num2.y;
			res.y=num1.y*num2.x;
			break;
		}
		default:{
			res.x=0;
			res.y=1;
		}
	}
	if(res.x<res.y) 
		f=gcd(res.y,res.x);
	else 
		f=gcd(res.x,res.y);
	res.x=res.x/f;res.y=res.y/f;
	//如果分母为负数，取反
	if(res.y<0){
		res.x=-res.x;
		res.y=-res.y;
	} 
	return res;
} 
//随机生成1个操作数并打印 
Digit getNum()
{
	int i,j,f;
	Digit res;
	if(rand()%3==1)
	{
		i=rand()%101+1;
		j=rand()%101+1;
		if(i>j) {int temp=i;i=j;j=temp;}
		f=gcd(j,i);
		i=i/f;j=j/f;
		printf("%d/%d",i,j);
	}else{
		i=rand()%101+1;
		j=1;
		printf("%d",i);
	}
	res.x=i;
	res.y=j;
	return res;
}
//随机生成一个操作符并打印
char getOperator(){
	char op=ss[rand()%4];
	if(op=='%') 
		printf("÷");
	else if(op=='x')
		printf("×");
	else printf("%c",op);
	return op;
} 

int main()
{
	srand((unsigned)time(NULL));  //每次运行进行初始化 
	int times; //控制生成题目的个数 
	float score=100; //题目得分 
	printf("请输入生成题目个数："); 
	scanf("-n %d",&times);
	printf("本次共%d题，满分100分\n",times);
	for(int j=0;j<times;j++){
		printf("%d: ",j+1);
		int t=0,q=0,p=0,top=0;
		Digit opNum[10],numStack[10];
		char op,operatorStack[10],expQueue[20];
		opNum[q++]=getNum();
		expQueue[p++]=q-1+'0';
		for(t=0;t<3;t++)
		{
			op=getOperator();	
			if(t==0){
				operatorStack[top++]=op;
				opNum[q++]=getNum();
				expQueue[p++]=q-1+'0';
				continue;
			}
			while(mPriority(op)<=mPriority(operatorStack[top-1])&&top>0){
				top--;
				expQueue[p++]=operatorStack[top];
			}
			opNum[q++]=getNum();
			expQueue[p++]=q-1+'0';
			operatorStack[top++]=op;
		} 
		while(top>0){
			top--;
			expQueue[p++]=operatorStack[top];
		}
		
//		printf(" top=%d q=%d p=%d\n",top,q,p);
//		for(int i=0;i<p;i++)
//			printf("%c ",expQueue[i]);
//			printf("\n");
//			
//		for(int i=0;i<q;i++)
//			printf("%d/%d ",opNum[i].x,opNum[i].y);
//		printf("\n");
		//根据后缀表达式计算结果 
		top=0;
		for(int i=0;i<p;i++){
			if(expQueue[i]>='0'&&expQueue[i]<='9')
				{
					int ch=expQueue[i]-'0';
					numStack[top].x=opNum[ch].x;
					numStack[top].y=opNum[ch].y;
					top++;
				}else{
					top--;
					numStack[top-1]=Calculate(numStack[top-1],numStack[top],expQueue[i]);
				}
		}
		printf("=");
		//用户输入计算结果
		char userAns[100],rightAns[100];
//		printf("%d/%d\n",numStack[top-1].x,numStack[top-1].y);
		cin>>userAns;
		int c=getchar();
		//得到的正确结果 
		if(numStack[top-1].y!=1){
			sprintf(rightAns,"%d%s",numStack[top-1].x,"/");
			sprintf(rightAns,"%s%d",rightAns,numStack[top-1].y);
		}	
		else 
			sprintf(rightAns,"%d",numStack[top-1].x);
		//printf("%s\n",rightAns);
		//判断对错 
		if(strcmp(userAns,rightAns)==0)
			printf("正确！\n");
		else {
			printf("不正确！正确答案= %s\n",rightAns);
			//扣分
			score-=100*1.0/times; 
		}
		
	}
	printf("本次得分%.2f",score);	
	return 0;	
} 


















