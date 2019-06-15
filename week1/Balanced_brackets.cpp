#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void push(char *a,int *sp,char value)
{
	a[*sp] = value;
	*sp = *sp + 1;;
}

char top_return(char *a,int *sp,int *b)
{
	if(*sp == 0)
		return 0;
	else
	{
		--*sp;
		b[*sp] = 0;
		return a[*sp];
	}
}

int main()
{
	string str;
	cin>>str;
	int str_length = str.length();
	char a[str_length];
	int sp = 0;
	int i;
	char temp;
	int close_bracket_mis = 0;
	int opening_brackets_tracker[str_length];
	for(i = 0; i < str_length; i++)
	{
		if(str[i] == '(' || str[i] == '{' || str[i] == '[')
		{
			opening_brackets_tracker[sp] = i+1;
			push(a,&sp,str[i]);
		}	
		else if(str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			temp = top_return(a,&sp,opening_brackets_tracker);
			if((temp == '(' && str[i] == ')') || (temp == '[' && str[i] == ']') || (temp =='{' && str[i] == '}'))
				continue;
			else 
			{
				close_bracket_mis = 1;
				break;
			}
		}
		else
			continue;
	}
	//cout<<"i = "<<i<<" "<<"sp = "<<sp<<"\n";
	
	if(i == str_length && sp == 0)
		cout<<"Success";
	else
	{
		if(close_bracket_mis)
			cout<<i+1;
		else
		{
			for(i = 0; i < str_length; i++)
			{
				if(opening_brackets_tracker[i] != 0)
				{
					cout<<opening_brackets_tracker[i];
					break;
				}
			}
		}	

	}	
	return 0;

}