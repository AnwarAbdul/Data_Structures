#include<iostream>

typedef struct node{
	int arr_time;
	int proc_time;
	int arr_proc_time;
	int getting_processed_time;
	struct node *next;
}node;

node *head,*tail;
int size = 0;

node *node_create(int a, int p)
{
	node *np = (struct node *)malloc(sizeof(struct node));
	np->arr_time = a;
	np->proc_time = p;
	np->getting_processed_time = -1;
	np->arr_proc_time = a + p;
	np->next = NULL;
	return np;
}

void queue(node *np,int capacity)
{
	if(head == tail)
	{
		head->next = np;
		tail = np;
		np->getting_processed_time = np->arr_time;
		size++;
	}
	else 
	{
		if(size == capacity && np->arr_time < head->next->arr_proc_time)
			return;
		else
		{
			while(np->arr_time >= head->next->arr_proc_time)
			{

				head = head->next;
				size--;
				if(head == tail)
				{
					head->next =  np;
					tail = np;
					np->getting_processed_time = np->arr_time;
					size++;
					break;
				}
			}
			if(head->next != np)
			{
				if(np->arr_time >= tail->arr_proc_time)
					np->getting_processed_time = np->arr_time;
				else
				{
					np->getting_processed_time = tail->arr_proc_time;
					np->arr_proc_time = np->getting_processed_time + np->proc_time;
				}
				tail->next = np;
				tail = np;
				size++;
			}
			
		}
	}	
}

int main()
{
	int n, capacity;
	std::cin>>capacity>>n;
	size = 0;
	head = (struct node *)malloc(sizeof(struct node));
	tail = (struct node *)malloc(sizeof(struct node));
	head->next = NULL;
	tail->next = NULL;
	head = tail;
	node *np;
	node *nodes = (struct node *)malloc(sizeof(struct node) * n);
	int *A = (int *)malloc(sizeof(int) * n);
	int *P = (int *)malloc(sizeof(int) * n);
	int i;
	if(n == 0 || n==1)
	{
		if(n == 0)
			return 0;
		else
		{
			std::cin>>A[0]>>P[0];
			std::cout<<A[0];
			return 0;
		}
	}
	else
	{
		for(i = 0; i < n ; i++)
		{	
			std::cin>>A[i]>>P[i];
			np = node_create(A[i],P[i]);
			queue(np,capacity);
			nodes[i] = *np;
		}
		for(i = 0; i < n ; i++)
		{	
			std::cout<<nodes[i].getting_processed_time<<"\n";
		}
	}
	return 0;
}
