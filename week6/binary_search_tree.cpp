#include <iostream>
#include <vector>

using namespace std;

typedef struct node{
	int val;
	int lindex;
	int rindex;
}node_t;


void in_order_traversal(vector<node_t> &a, int key,vector<int> &sorted_array, bool &yes_tree){
	if(key == -1)
		return;
	else{
		in_order_traversal(a,a[key].lindex,sorted_array,yes_tree);
		if(!yes_tree)
			return;
		if(sorted_array.size() == 0)
			sorted_array.push_back(a[key].val);
		else if(a[key].val > sorted_array.back())
			sorted_array.push_back(a[key].val);
		else{
			yes_tree = false;
			return;
		}
		in_order_traversal(a,a[key].rindex,sorted_array,yes_tree);
	}
}

int main(){
	int n;
	cin>>n;
	vector<node_t> a;
	int key,l,r;
	for(int i = 0; i < n; i++){
		cin>>key>>l>>r;
		node_t temp_node;
		temp_node.val = key;
		temp_node.lindex = l;
		temp_node.rindex = r;
		a.push_back(temp_node);
	}
	bool yes_tree = true;
	vector<int> sorted_array;
	if(a.size() != 0)
		in_order_traversal(a,0,sorted_array,yes_tree);
	if(yes_tree)
		cout<<"CORRECT";
	else
		cout<<"INCORRECT";
	return 0;
}