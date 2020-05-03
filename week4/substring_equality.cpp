#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <ctime>
#include <cmath>


#define DEBUG 0

using namespace std;

long long int polyhash(string s, long long int P, long long int X){
	long long int hash = 0;
	for(int i = s.length() - 1; i >= 0; i--){
		hash = (hash*X + (long long int)s[i])%P;
	}
	return hash;
}

void PrecomputeHashes(string T,int P_length, long long int prime, long long int X, long long int *H){
	string s = T.substr(T.length() - P_length,P_length);
	H[T.length()-P_length] = polyhash(s,prime,X);
	long long int y = (long long int)1;
	for(int i = 0; i < P_length; i++ )
		y = (y*X)%prime;
	for(int i = T.length() - P_length - 1; i >= 0; i--)
		H[i] = (X*H[i+1] + (long long int)T[i] - (y*(long long int)T[i+P_length])%prime+prime)%prime;	
}

void compute_hash_arrays_substrings(long long int *h,long long int m,string s,int k, int l,long long int X){
	h[0] = 0;
	for(int i = 1; i <= l; i++)
		h[i] = (X*h[i-1] + (long long int)s[k+i-1])%m;
}

void normalize(long long int *y, int l, int m,long long int X){
	y[0] = (long long int)1;
	for(int i = 1; i <= l; i++){
		y[i] = (y[i-1]*X)%m;
	}
}

int main(){
	string T;
	cin>>T;
	int q;
	int a,b,l;
	cin>>q;
	long long int m1,m2;
	m1 = pow(10,9) + 7;
	m2 = pow(10,9) + 9;
	srand(time(NULL));
	long long int X = rand() %((long long int)pow(10,9) - 1) + 1;
	vector<string> output;
	long long int* h1 = (long long int *)malloc(sizeof(long long int)*(T.length()+1));		
	long long int* h2 = (long long int *)malloc(sizeof(long long int)*(T.length()+1));		
	compute_hash_arrays_substrings(h1,m1,T,0,T.length(),X);
	compute_hash_arrays_substrings(h2,m2,T,0,T.length(),X);
	#if DEBUG
		for(int i = 0; i <= T.length(); i++){
			cout<<h1[i]<<" "<<h2[i]<<"\n";
		}	
		cout<<endl;
	#endif
	long long int *y1 = (long long int *)malloc(sizeof(long long int)*(T.length()+1));
	long long int *y2 = (long long int *)malloc(sizeof(long long int)*(T.length()+1));
	normalize(y1,T.length(),m1,X);
	normalize(y2,T.length(),m2,X);	
	for(int i = 0; i < q; i++){
		cin>>a>>b>>l;
		long long int ha_hash,hb_hash;
		ha_hash = (h1[a+l] - (y1[l]*h1[a])%m1 + m1)%m1;
		hb_hash = (h1[b+l] - (y1[l]*h1[b])%m1 + m1)%m1;
		#if DEBUG
			cout<<"ha_hash = "<<ha_hash<<"hb_hash = "<<hb_hash<<"\n";
		#endif
		if(ha_hash == hb_hash){
			ha_hash = (h2[a+l] - (y2[l]*h2[a])%m2 + m2)%m2;
			hb_hash = (h2[b+l] - (y2[l]*h2[b])%m2 + m2)%m2;
			#if DEBUG
				cout<<"ha2_hash = "<<ha_hash<<"hb2_hash = "<<hb_hash<<"\n";
			#endif
			if(ha_hash == hb_hash)
				output.push_back("Yes");
			else
				output.push_back("No");
		}
		else
			output.push_back("No");
	}
	free(h1);
	free(h2);
	free(y1);
	free(y2);
	for(int i = 0; i < output.size(); i++)
		cout<<output[i]<<"\n";
	return 0;
}