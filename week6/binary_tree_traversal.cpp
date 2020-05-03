#include <iostream>
#include <vector>

typedef struct node{
	int val;
	int lindex;
	int rindex;
}node_t;

void in_order_traversal(std::vector<node_t> &a, int key){
	if(key == -1)
		return;
	else{
		in_order_traversal(a,a[key].lindex);
		std::cout<<a[key].val<<" ";
		in_order_traversal(a,a[key].rindex);
	}
}

void pre_order_traversal(std::vector<node_t> &a, int key){
	if(key == -1)
		return;
	else{
		std::cout<<a[key].val<<" ";
		pre_order_traversal(a,a[key].lindex);
		pre_order_traversal(a,a[key].rindex);
	}
}

void post_order_traversal(std::vector<node_t> &a, int key){
	if(key == -1)
		return;
	else{
		post_order_traversal(a,a[key].lindex);
		post_order_traversal(a,a[key].rindex);
		std::cout<<a[key].val<<" ";
	}
}

int main(){
	int n;
	std::cin>>n;
	std::vector<node_t> a;
	int num,l,r;
	for(int i = 0; i < n; i++){
		std::cin>>num>>l>>r;
		node_t in_node;
		in_node.val = num;
		in_node.lindex = l;
		in_node.rindex = r;
		a.push_back(in_node);
	}
	in_order_traversal(a,0);
	std::cout<<"\n";
	pre_order_traversal(a,0);
	std::cout<<"\n";
	post_order_traversal(a,0);
	return 0;
}