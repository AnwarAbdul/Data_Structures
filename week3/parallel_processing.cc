#include <iostream>
#include <climits>

using std::cin;
using std::cout;

typedef struct thread{
	long long int idx;
	long long int avl_time;
}thread;

long long int lchild(long long int i)
{
	return 2*i + 1;
}

long long int rchild(long long int i)
{
	return 2*i + 2;
}

void swap(thread &x, thread &y)
{
	long long int temp_idx;
	long long int temp_avl_time;
	temp_idx = x.idx;
	temp_avl_time = x.avl_time;
	x.idx = y.idx;
	x.avl_time = y.avl_time;
	y.idx = temp_idx;
	y.avl_time = temp_avl_time;
}

void SiftDown(thread *threads, long long int i, long long int n)
{
	long long int minpos = i;
	long long int l = lchild(i);
	long long int r = rchild(i);
	if(l < n && threads[l].avl_time <= threads[minpos].avl_time)
	{
		if(threads[l].avl_time == threads[minpos].avl_time)
		{
			if(threads[l].idx < threads[minpos].idx)
				minpos = l;		
		}
		else
			minpos = l;
	}
	if(r < n && threads[r].avl_time <= threads[minpos].avl_time)
	{
		if(threads[r].avl_time == threads[minpos].avl_time)
		{
			if(threads[r].idx < threads[minpos].idx)
				minpos = r;
		}
		else
			minpos = r;
	}
	if(i != minpos)
	{
		swap(threads[i], threads[minpos]);
		SiftDown(threads,minpos,n);
	}
}


int main()
{
	long long int n,m;
	cin>>n>>m;
	thread *threads = (struct thread*)malloc(sizeof(struct thread) * n);
	long long int *job_time = (long long int *)malloc(sizeof(long long int) * m);
	long long int i;
	for(i = 0; i < m; i++)
		cin>>job_time[i];
	for(i = 0; i < n; i++)
	{
		threads[i].idx = i;
		threads[i].avl_time = 0;
	}	
	long long int priority_thread = 0;
	for(i = 0; i < m; i++)
	{
		cout<<threads[priority_thread].idx<<" "<<threads[priority_thread].avl_time<<"\n";
		threads[priority_thread].avl_time += job_time[i];
		if(n <= 2)
		{
			if(n == 2)
				if(threads[1].avl_time <= threads[priority_thread].avl_time)
					SiftDown(threads,0,n);
		}
		else 
		{
			if(threads[1].avl_time <= threads[priority_thread].avl_time || threads[2].avl_time <= threads[priority_thread].avl_time)
				SiftDown(threads,0,n);
		}
	}
	return 0;
}