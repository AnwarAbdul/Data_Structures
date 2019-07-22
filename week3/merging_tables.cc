#include <iostream>

using std::cin;
using std::cout;

typedef struct table_format{
	long long int row_count;
	long long int symlink;
}table_format;

long long int find(table_format *tables, long long int id) //Normal find() for disjolong long int set using trees w/o path compression
{
	while(id != tables[id-1].symlink)
		id = tables[id-1].symlink;
	return id;
}

long long int find_path_compression(table_format *tables,long long int id)
{
	if(id != tables[id-1].symlink)
		tables[id-1].symlink = find_path_compression(tables,tables[id-1].symlink);
	return tables[id-1].symlink;
}

void Union(table_format *tables,long long int dest_table, long long int source_table, long long int *rank,long long int n, long long int &max_table_size)
{
	if(dest_table == source_table)
		return;
	long long int dest_id = find_path_compression(tables,dest_table) - 1;
	long long int source_id = find_path_compression(tables,source_table) - 1;
	if(dest_id == source_id)
		return;
	//cout<<"\nsource_id = "<<source_id+1<<" : "<<"dest_id = "<<dest_id+1<<"\n";
	if(rank[source_id] < rank[dest_id])
	{
		//cout<<"\nsource table row count = "<<tables[source_table-1].row_count<<" : "<<"dest table row count = "<<tables[dest_table-1].row_count<<"\n";
		tables[dest_id].row_count += tables[source_id].row_count;
		tables[source_id].symlink = dest_id+1;
		tables[source_id].row_count = 0;
		tables[dest_id].symlink = dest_id+1;
		if(tables[dest_id].row_count > max_table_size)
			max_table_size = tables[dest_id].row_count;
	}
	else
	{
		//cout<<"\nsource table row count = "<<tables[source_table-1].row_count<<" : "<<"dest table row count = "<<tables[dest_table-1].row_count<<"\n";
		tables[source_id].row_count += tables[dest_id].row_count;
		tables[dest_id].symlink = source_id+1;
		tables[dest_id].row_count = 0;
		if(rank[dest_id] == rank[source_id])
			rank[source_id] += 1;
		tables[source_id].symlink = source_id+1;
		if(tables[source_id].row_count > max_table_size)
			max_table_size	= tables[source_id].row_count;
	}
}

void dis(table_format *tables, long long int n, long long int *rank)
{
	long long int i;
	for(i = 0; i < n; i++)
	{
		cout<<"Table "<<i+1<<" root = "<<tables[i].symlink<<" : "<<" row_count = "<<tables[i].row_count<<" : rank = "<<rank[i]<<"\n";
	}
}

int main()
{
	long long int n,m;
	cin>>n>>m;
	long long int dest_table,source_table;
	long long int i;
	long long int *rank = (long long int *)malloc(sizeof(long long int)* n);
	table_format *tables = (struct table_format*)malloc(sizeof(struct table_format) * n);
	long long int max_table_size = 0;
	long long int max_table_size_array[m];
	for(i = 0; i <n ; i++)
	{
		cin>>tables[i].row_count;
		tables[i].symlink = i+1;
		rank[i] = 0;
		if(tables[i].row_count > max_table_size)
			max_table_size = tables[i].row_count;
	}
	//dis(tables,n,rank);
	for(i = 0; i < m; i++)
	{
		cin>>dest_table>>source_table;
		Union(tables,dest_table,source_table,rank,n,max_table_size);
		max_table_size_array[i] = max_table_size;
		/*cout<<"\nHere\n";
		dis(tables,n,rank);
		cout<<"\nHere\n"; */
	}
	for(i = 0; i < m; i++)
		cout<<max_table_size_array[i]<<"\n";
	return 0;
}