#include<iostream>
#include<cmath>


void cmd_parse(std::string s, int &num)
{
	int i = 0;
	num = 0;
	while(s[i++] != ' ');
	std::string temp = "";
	int count = 0;
	while(s[i] != '\0')
	{
		temp += s[i];
		i++;
		count++;
	}
	i = 0;
	//std::cout<<"count = "<<count<<"\n";
	while(count)
	{
		count--;
		num += pow(10,count) * (temp[i++] - 0x30);		
	}
}

int main()
{
	int n;
	std::string s;
	std::cin>>n;
	int num,max;
	int *a = (int *)malloc(sizeof(int) * n);
	int *max_arr = (int *)malloc(sizeof(int) * n);
	int *out = (int *)malloc(sizeof(int) * n);
	int i;
	int top = 0;
	max = -1; 
	std::cin.ignore();
	int k = 0;
	for(i = 0; i < n; i++)
	{
		getline(std::cin,s);
		if(s[1] == 'u')
		{
			cmd_parse(s,num);
			a[top] = num;
	//		std::cout<<"num = "<<num<<"\n";
			if(num > max)
			{
				max = num;
				max_arr[top] = max;
			}
			else
				max_arr[top] = max;
			top++;
		}
		else if(s[1] == 'o')
		{
			top--;
		}
		else
		{
			out[k] = max_arr[top-1];
			k++;
		}
	}
	for(i = 0; i < k ; i++)
		std::cout<<out[i]<<"\n";
	return 0;
}