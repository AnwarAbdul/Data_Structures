#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>
#include <cstring>

#define DEBUG 0

using namespace std;

#define X 263
#define P 1000000007

int polyhash(string s,int m){
	long int hash = 0;
	for(int i = s.length() - 1; i >=  0; i--){
		hash = ((hash*X + (long int)s[i])%P);
	}
	hash %= (long int) m;
	#if DEBUG
		cout<<"\nHash lookup index = "<<hash;
	#endif
	return (int) hash;
}


void add_processing(vector<vector<string>> &table, string s){
	int hash_lookup_index = polyhash(s,table.size());
	int j;
	std::vector<string>::iterator it;
	it = find(table[hash_lookup_index].begin()+1, table[hash_lookup_index].end(),s);
	if(it == table[hash_lookup_index].end())
		table[hash_lookup_index].insert(table[hash_lookup_index].begin()+1,s);	
}

void delete_processing(vector<vector<string>> &table, string s){
	int hash_lookup_index = polyhash(s,table.size());
	int j;
	std::vector<string>::iterator it;
	it = find(table[hash_lookup_index].begin()+1, table[hash_lookup_index].end(),s);
	if(it != table[hash_lookup_index].end())
		table[hash_lookup_index].erase(it);		
}

vector<string> find_processing(vector<vector<string>> &table, string s){
	int hash_lookup_index = polyhash(s,table.size());
	int j;
	std::vector<string>::iterator it;
	it = find(table[hash_lookup_index].begin()+1, table[hash_lookup_index].end(),s);
	vector<string> row;
	if(it != table[hash_lookup_index].end())
		row.push_back("yes");
	else
		row.push_back("no");
	return row;

}

vector<string> check_processing(vector<vector<string>> &table, int inum){
	int hash_lookup_index = inum;
	#if DEBUG
		cout<<"\nHash lookup index = "<<hash_lookup_index;
	#endif
	vector<string> row;
	if(table[hash_lookup_index].size() == 1)
		row.push_back("");
	else{
		for(int j = 1; j < table[hash_lookup_index].size();j++)
			row.push_back(table[hash_lookup_index][j]);
	}
	return row;
}

void table_init(vector<vector<string>> &table,int m){
	vector<string> row;
	for(int i = 0;i < m; i++)
		table.push_back({"None"});
}

void dis(vector<vector<string>> &table){
	for(int i = 0; i < table.size(); i++){
		cout<<"\n";
		for(int j = 0; j < table[i].size(); j++)
			cout<<table[i][j]<<" ";
	}
	cout<<"\n";
}

int main(){
	vector<vector<string>> table;
	int m,N;
	cin>>m;
	cin>>N;
	int i;
	table_init(table,m);
	#if DEBUG
		dis(table_init);
	#endif
	char temp[20];
	vector<vector<string>> output;
	cin.ignore();
	string line;
	char temp_line[50];
	int inum;
	vector<string> tokens;
	vector<string> out;
	for(i = 0; i < N; i++){
		out.clear();
		getline(cin,line);
		strcpy(temp_line,line.c_str());
		char *token = strtok(temp_line," ");
		tokens.clear();
		while(token != NULL){
			strcpy(temp,token);
			tokens.push_back(temp);
			token = strtok(NULL," ");
		}
		#if DEBUG
			std::cout<<"tokens[0] = "<<tokens[0]<<" tokens[1] "<<tokens[1]<<"\n";
		#endif
		if(tokens[0] == "check"){
			inum = atoi(tokens[1].c_str());
			out = check_processing(table,inum);
			output.push_back(out);
		}
		else if(tokens[0] == "find"){
			out = find_processing(table,tokens[1]);
			output.push_back(out);
		}
		else if(tokens[0] == "del")
			delete_processing(table,tokens[1]);
		else
			add_processing(table,tokens[1]);
		#if DEBUG
			dis(table);
		#endif
	}
	int j;
	for(i = 0; i < output.size(); i++){
		for(j = 0; j < output[i].size(); j++){
			cout<<output[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}