#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
using namespace std;
//�ýṹ���Ų����� 
struct Digit{
    int x;
    int y;
};  
char ss[4]={'+','-','x','%'}; //������
//���ز����������ȼ�
int mPriority(char op){
    if(op=='+') return 1;
    else if(op=='-') return 1;
    else if(op=='x') return 2;
    else if(op=='%') return 2;
} 
//�����Լ��
int gcd(int a,int b)
{
    if(b==0) return a;
    else return gcd(b,a%b);    
}  
//���ݲ�������������������
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
    //�����ĸΪ������ȡ��
    if(res.y<0){
        res.x=-res.x;
        res.y=-res.y;
    } 
    return res;
} 
//�������1������������ӡ 
Digit getNum()
{
    int i,j,f;
    Digit res;
    if(rand()%3==1)
    {
        i=rand()%11+1;
        j=rand()%11+1;
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
//�������һ������������ӡ
char getOperator(){
    char op=ss[rand()%4];
    if(op=='%') 
        printf("��");
    else if(op=='x')
        printf("��");
    else printf("%c",op);
    return op;
} 

int main()
{
    srand((unsigned)time(NULL));  //ÿ�����н��г�ʼ�� 
    int times; //����������Ŀ�ĸ��� 
    float score=100; //��Ŀ�÷� 
    printf("��������Ŀ����(��������:-n 5,������5����Ŀ)��");
    scanf("-n %d",&times);
    printf("���ι�%d�⣬����100��\n",times);
    //��һ��forѭ����ÿ������һ����Ŀ 
    for(int j=0;j<times;j++){
        printf("%d: ",j+1);
        int t=0,q=0,p=0,top=0;
        Digit opNum[10],numStack[10];
        char op,operatorStack[10],expQueue[20];
        opNum[q++]=getNum();
        expQueue[p++]=q-1+'0';
        //���븽�ӹ��ܣ�����������������
		int op_Num=rand()%5+1; 
		//���ӹ��ܣ��������ŵ�����
		int braket_Max=2,braket=0,flag=0;//�ֱ�����������ŵĸ����͵�ǰ�����Ÿ��� 
        //�õ���׺���ʽ 
        for(t=0;t<op_Num;t++)
        {
            op=getOperator();  //���������  
            if(t==0){
                operatorStack[top++]=op;
                 //��������Ƿ�����������
	            if(rand()%3==1&&t<op_Num-1){
	            	printf("(");//��ӡ���� 
	            	braket_Max--;
	            	braket++;
					operatorStack[top++]='('; //��������ջ 
	            }
				opNum[q++]=getNum();
                expQueue[p++]=q-1+'0';
                continue;
            }
           
            //������ջ�����������ţ��������ȼ��жϳ�ջ 
            if(operatorStack[top-1]!='('){
            	while(mPriority(op)<=mPriority(operatorStack[top-1])&&top>0&&operatorStack[top-1]!='('){
	                top--;
	                expQueue[p++]=operatorStack[top];
	            }
            }
            operatorStack[top++]=op;
             //��������Ƿ�����������
            if(rand()%3==1&&t<op_Num-1){
            	if(braket_Max<0) break;//����Ѿ������������ţ��Ͳ������� 
            	printf("(");//��ӡ���� 
            	flag=t;
            	braket_Max--;
            	braket++;
				operatorStack[top++]='('; //��������ջ 
            }
            opNum[q++]=getNum();//����һ������� 
            expQueue[p++]=q-1+'0';
            //��������Ƿ�����������
            if(flag!=t&&rand()%3==1){
            
            	if(braket<=0) break; 
            	printf(")");//��ӡ������
				braket--;
				//һֱ��ջֱ������������
				while(operatorStack[top-1]!='(') {
					top--;
					expQueue[p++]=operatorStack[top];
				}
				top--;
            }
        } 
        //������������Ż�δƥ��
		while(braket>0){
			braket--;
			printf(")");
			while(operatorStack[top-1]!='(') {
					top--;
					expQueue[p++]=operatorStack[top];
			}
			top--;
		} 
        while(top>0){
            top--;
            expQueue[p++]=operatorStack[top];
        }
       
        //���ݺ�׺���ʽ������ 
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
        //�û����������
        char userAns[100],rightAns[100];
//        printf("%d/%d\n",numStack[top-1].x,numStack[top-1].y);
        cin>>userAns;
        int c=getchar();
        //�õ�����ȷ��� 
        if(numStack[top-1].y!=1){
            sprintf(rightAns,"%d%s",numStack[top-1].x,"/");
            sprintf(rightAns,"%s%d",rightAns,numStack[top-1].y);
        }    
        else 
            sprintf(rightAns,"%d",numStack[top-1].x);
        //printf("%s\n",rightAns);
        //�ж϶Դ� 
        if(strcmp(userAns,rightAns)==0)
            printf("��ȷ��\n");
        else {
            printf("����ȷ����ȷ��= %s\n",rightAns);
            //�۷�
            score-=100*1.0/times; 
        }
        
    }
    printf("���ε÷�%.2f",score);    
    return 0;    
}
