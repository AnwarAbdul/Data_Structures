#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <ctime>


#define DEBUG 0

using namespace std;

long long int polyhash(string s, long long int P, long long int X){
	long long int hash = 0;
	for(int i = s.length() - 1; i >= 0; i--){
		hash = ((hash * X) + (long long int)s[i])%P;
	}
	return hash;
}

void PrecomputeHashes(string T,int P_length, long long int prime, long long int X, long long int *H){
	string s = T.substr(T.length() - P_length,P_length);
	H[T.length()-P_length] = polyhash(s,prime,X);
	long long int y = (long long int)1;
	for(int i = 0; i < P_length; i++ )
		y = (y * X)%prime;
	for(int i = T.length() - P_length - 1; i >= 0; i--)
		H[i] = ((X * H[i+1]) + (long long int)T[i] - (y*(long long int)T[i+P_length])%prime+prime)%prime;	
}

int main(){
	string P,T;
	cin>>P>>T;
	long long int prime = 1000000007;
	long long int m = 1000;
	srand(time(NULL));
	long long int X = rand() %(prime - 1 - 1) + 1;
	//long long int X = 263;
	long long int pHash = polyhash(P,prime,X);
	#if DEBUG
		cout<<"\npHash = "<<pHash<<"\n";
	#endif
	vector<int> index_list;
	long long int *H = (long long int *)malloc(sizeof(long long int)*(T.length() - P.length() + 1));
	PrecomputeHashes(T,P.length(),prime,X,H);
	for(int i = 0; i <= T.length() - P.length(); i++){
		#if DEBUG
			cout<<"\nH[i] = "<<H[i]<<"\n";
		#endif
		if(pHash != H[i])
			continue;
		int flag = 1;
		for(int j = 0; j < P.length(); j++){
			if(P[j] != T[i+j]){
				flag = 0;
				break;
			}
		}
		if(flag)
			index_list.push_back(i);
	}
	for(int i = 0; i < index_list.size(); i++)
		cout<<index_list[i]<<" ";
	free(H);
	return 0;
}