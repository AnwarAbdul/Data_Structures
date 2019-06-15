/* The height of a tree shall be 1 + number of edges between the root node and the lowest leaf
Level = 1 + number of edges of subnode with respect to its root
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef struct node
{
	int child_count;
	int *children;
	int assign;
}dummy;

node *nodes;

int height_calc(node parent)
{
	int height=0;
	if(parent.child_count == 0)
		return 0;
	else
	{
		int i,temp;
		for(i = 0; i < parent.child_count; i++)
		{
			temp = 1 + height_calc(nodes[parent.children[i]]);
			if(temp > height)
				height = temp;
		}
		return height;
	}
}

/*
void display_children(node parent)
{
	int i,j;
	for(i = 0; i < parent.child_count;i++)
	{
		cout<<parent.children[i]<<",";
	}
	cout<<"\n";
}
*/
int main()
{
	int n;
	cin>>n;
	int i;
	int root;
	int *parent;
	
	parent = (int *)malloc(sizeof(int) * n);
	nodes = (node *)malloc(sizeof(node) * n);
	for(i = 0; i < n; i++)
	{	
		nodes[i].child_count = 0;
		nodes[i].assign = 0;
	}
	for(i = 0; i < n; i++)
	{
		cin>>parent[i];
		if(parent[i] == -1)
		{	
			root = i;
			continue;
		}
		nodes[parent[i]].child_count += 1;
	}

	for(i = 0; i < n; i++)
	{
		if(nodes[i].child_count)
		{
			nodes[i].children = (int *)malloc(sizeof(int) * nodes[i].child_count);
		}
	}

	for(i = 0; i < n; i++)
	{
		if(parent[i] != -1)
		{
			nodes[parent[i]].children[nodes[parent[i]].assign++] = i;
		}
	}
	/*
	for(i = 0; i < n; i++)
	{	
		//cout<<parent[i]<<" ";
		cout<<nodes[i].child_count<<" ";
	}
	
	cout<<"\n";
	for(i = 0; i < n; i++)
	{
		cout<<"Children of node "<<i<<"-> ";
		display_children(nodes[i]);
	}
	*/
	int final_height;
	final_height = 1 + height_calc(nodes[root]);
	//cout<<"root = "<<root<<"\n";
	//cout<<"final_height = "<<final_height + 1<<"\n";
	cout<<final_height;
	//free(parent);
	free(nodes);
	return 0;
}