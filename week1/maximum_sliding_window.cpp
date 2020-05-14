#include <iostream>
#include <vector>
#include <list>
#include <vector>

int main(){
	int n;
	std::cin>>n;
	std::vector<int> a;
	int num;
	for(int i = 0; i < n; i++){
		std::cin>>num;
		a.push_back(num);
	}
	int m;
	std::cin>>m;
	std::vector<int> out;
	std::list<int> dq;
	dq.push_back(0);
	for(int i = 1; i < m; i++){
		if(dq.size() != 0){
			while(a[i] > a[dq.front()]){
				dq.pop_front();
				if(dq.size() == 0)
					break;
			}
		}
		if(dq.size() != 0){
			while(a[i] > a[dq.back()]){
				dq.pop_back();
				if(dq.size() == 0)
					break;
			}
		}
		dq.push_back(i);
	}
	out.push_back(dq.front());
	for(int i = m; i < a.size(); i++){
		while(dq.front() < (i-m+1)){
			dq.pop_front();
			if(dq.size() == 0)
				break;
		}
		if(dq.size() != 0){
			while(a[i] > a[dq.front()]){
				dq.pop_front();
				if(dq.size() == 0)
					break;
			}
		}
		if(dq.size() != 0){
			while(a[i] > a[dq.back()]){
				dq.pop_back();
				if(dq.size() == 0)
					break;
			}
		}
		dq.push_back(i);
		out.push_back(dq.front());
	}
	for(int i = 0; i < out.size(); i++)
		std::cout<<a[out[i]]<<" ";
	return 0;
}
