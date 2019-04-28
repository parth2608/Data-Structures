#include<stdio.h>
#include<ctype.h>
#define MAX 100

float st[MAX];
int top=-1;

void push(float st[],float val);
float pop(float st[]);
float evaluate(char exp[]);

void main()
{
	char exp[100];
	float val;	
	printf("Enter Postfix Expression: ");
	scanf("%s",exp);
	val=evaluate(exp);
	printf("Evaluation Of Postfix Expression: %.2f",val);
}

void push(float st[],float val)
{
	if(top==MAX-1)
	{
		printf("\nStack Overflow");
	}
	else
	{
		top++;
		st[top]=val;
	}
}

float pop(float st[])
{
	float val=-1;	
	if(top==-1)
	{
		printf("\nStack Underflow");
	}
	else
	{
		val=st[top];
		top--;
	}
	return val;
}

float evaluate(char exp[])
{
	int i=0;
	float op1,op2,value;
	while(exp[i]!='\0')
	{
		if(isdigit(exp[i]))
		{
			push(st,(float)(exp[i]-'0'));
		}
		else
		{
			op2=pop(st);
			op1=pop(st);
			switch(exp[i])
			{
				case '+':
					value=op1+op2;
				break;
				case '-':
					value=op1-op2;
				break;
				case '*':
					value=op1*op2;
				break;
				case '/':
					value=op1/op2;
				break;
				case '%':
					value=(int)op1%(int)op2;
				break;
			}
			push(st,value);
		}
		i++;
	}	
	return (pop(st));
}
