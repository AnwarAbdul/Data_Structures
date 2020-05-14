#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <unordered_map>
   
using namespace std;

#define M1 1000000007
#define M2 1000000009


long long int *y_1;
long long int *y_2;
long long int X = rand() % (1000000000 - 1) + 1;

			
int mini(int a, int b){
    if(a < b)
        return a;
    else
		  return b;
}

int maxi(int a, int b){
    if(a > b)
        return a;
    else 
        return b;
}


int pattern_match(string s, string t,  int l, int &i, int &j){
   long long int *h_s = (long long int*)malloc(sizeof(long long int)*(s.length() + 1));
   long long int *h_t = (long long int*)malloc(sizeof(long long int)*(t.length() + 1));
   long long int *h_1s = (long long int*)malloc(sizeof(long long int)*(s.length() + 1));
   long long int *h_1t = (long long int*)malloc(sizeof(long long int)*(t.length() + 1));
   
   h_s[0] = 0;
   h_t[0] = 0;
   h_1s[0] = 0;
   h_1t[0] = 0;
   int k;
   int high = maxi(s.length(),t.length());
   for(k = 1; k <= high; k++){
       if(k <= s.length()){
            h_s[k] = (X*h_s[k-1] + (long long int)s[k-1])%M1;
            h_1s[k] = (X*h_1s[k-1] + (long long int)s[k-1])%M2;
       }
        if(k <= t.length()){
            h_t[k] = (X*h_t[k-1] + (long long int)t[k-1])%M1;
            h_1t[k] = (X*h_1t[k-1] + (long long int)t[k-1])%M2;
        }
   }
   unordered_map<long long int,int> substring_map1;
   unordered_map<long long int,int> substring_map2;
    

   for(k = 0; k < (s.length() - l + 1); k++){
       long long int hash1 = (h_s[k+l] - (y_1[l]*h_s[k])%M1 + M1)%M1;
       long long int hash2 = (h_1s[k+l] - (y_2[l]*h_1s[k])%M2 + M2)%M2;
       if(substring_map1.find(hash1) == substring_map1.end())
            substring_map1.insert({hash1,k});
        if(substring_map2.find(hash2) == substring_map2.end())
            substring_map2.insert({hash2,k});
	}
   for(k = 0; k < (t.length() - l + 1); k++){
       long long int hash1 = (h_t[k+l] - (y_1[l]*h_t[k])%M1 + M1)%M1;
       long long int hash2 = (h_1t[k+l] - (y_2[l]*h_1t[k])%M2 + M2)%M2;
	     if((substring_map1.find(hash1) != substring_map1.end()) && (substring_map2.find(hash2) != substring_map2.end())){
           if(substring_map1[hash1] != substring_map2[hash2])
                continue;
           i = substring_map1[hash1];
           j = k;
           free(h_s);
           free(h_t);
           free(h_1s);
           free(h_1t);
           return 1;
       }     
   }
   free(h_s);
   free(h_t);        
   free(h_1s);
   free(h_1t);
        
   return 0;
}

void find_max_subsequence_length(string s, string t, int &i, int &j, int &l){
    int low = 0;
    int high = mini(s.length(), t.length());
    while(low <= high){
        int mid = low + (high-low)/2;
        int res = pattern_match(s,t,mid,i,j);
        if(res)
            low = mid + 1;
        else
            high = mid - 1;
    }
    l = low - 1;
}

int main(){
    string line;
    vector<vector<int>> output;
    int i,j,l;

    y_1 = (long long int*)malloc(sizeof(long long int)*100001);
    y_2 = (long long int*)malloc(sizeof(long long int)*100001);
    y_1[0] = (long long int)1;
    y_2[0] = (long long int)1;
    for(i = 1; i < 100001; i++){
        y_1[i] = (y_1[i-1]*X)%M1;
        y_2[i] = (y_2[i-1]*X)%M2;
    }
    
    while(getline(cin,line)){
        if(line == "")
            break;
        string temp_s,temp_t;
   	    istringstream mystream(line);
   	    mystream>>temp_s; 
        mystream>>temp_t; 

        i = 0; j = 0; l = 0;
        find_max_subsequence_length(temp_s,temp_t,i,j,l);
        if(l == 0)
             output.push_back({0,1,0});
        else
            output.push_back({i,j,l});

    } 
    
   for(i = 0; i < output.size(); i++){
       cout<<output[i][0]<<" "<<output[i][1]<<" "<<output[i][2]<<"\n";
   }
   free(y_1);
   free(y_2);
   return 0;
}
