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


int pattern_match(long long int *h_t, long long int *h_p, long long int *h_1t, long long int *h_1p,int l, int k, int start, int end, int offset){
    
   int i;

   long long int hash1_t,hash2_t,hash1,hash2;
   hash1 = (h_p[offset+l] - (y_1[l]*h_p[offset])%M1 + M1)%M1;
   hash2 = (h_1p[offset+l] - (y_2[l]*h_1p[offset])%M2 + M2)%M2;
   hash1_t = (h_t[start+l] - (y_1[l]*h_t[start])%M1 + M1)%M1;
   hash2_t = (h_1t[start+l] - (y_2[l]*h_1t[start])%M2 + M2)%M2;
   
   if(hash1 == hash1_t && hash2 == hash2_t)
       return 1;
   else
      return 0;
                    
}

void find_max_subsequence_length(string t, string p, int k,vector<int> &index){
   long long int *h_t = (long long int*)malloc(sizeof(long long int)*(t.length() + 1));
   long long int *h_p = (long long int*)malloc(sizeof(long long int)*(p.length() + 1));
   long long int *h_1t = (long long int*)malloc(sizeof(long long int)*(t.length() + 1));
   long long int *h_1p = (long long int*)malloc(sizeof(long long int)*(p.length() + 1));
   
   h_t[0] = 0;
   h_p[0] = 0;
   h_1t[0] = 0;
   h_1p[0] = 0;
   int i;
   int high = maxi(t.length(),p.length());
   for(i = 1; i <= high; i++){
       if(i <= t.length()){
            h_t[i] = (X*h_t[i-1] + (long long int)t[i-1])%M1;
            h_1t[i] = (X*h_1t[i-1] + (long long int)t[i-1])%M2;
       }
        if(i <= p.length()){
            h_p[i] = (X*h_p[i-1] + (long long int)p[i-1])%M1;
            h_1p[i] = (X*h_1p[i-1] + (long long int)p[i-1])%M2;
        }
   }
   
    for(int i = 0; i < (t.length() - p.length() + 1); i++){
      int start = i;
      int end = start + p.length();
      int mism = 0;
      while(start < end && mism <= k){
        int low = 0;
        int high = end - start;
        while(low <= high){
          int mid = low + (high-low)/2;
          int res = pattern_match(h_t,h_p,h_1t,h_1p,mid,k,start,end,start - i);
          if(res)
              low = mid + 1;
          else
              high = mid - 1;
        }
        int l = low - 1;
        if(l == 0){
          mism++;
          start++;
        }
        else
          start = start + l;
      }
      if(mism <= k)
        index.push_back(i);
    }
   free(h_t);
   free(h_p);
   free(h_1t);
   free(h_1p);
   
}

int main(){
    string line;
    vector<vector<int>> output;
    
    y_1 = (long long int*)malloc(sizeof(long long int)*200001);
    y_2 = (long long int*)malloc(sizeof(long long int)*200001);
    y_1[0] = (long long int)1;
    y_2[0] = (long long int)1;
    for(int i = 1; i < 200001; i++){
        y_1[i] = (y_1[i-1]*X)%M1;
        y_2[i] = (y_2[i-1]*X)%M2;
    }
    string t,p;
    int k;
    vector<int> index;
    while(getline(cin,line)){
        if(line == "")
            break;
        istringstream mystream(line);
   	    mystream>>k;
        mystream>>t;
        mystream>>p;
        if(k >= p.length()){
          vector<int> row;
          for(int i = 0; i < (t.length() - p.length() + 1); i++){
              row.push_back(i);
          }
          output.push_back(row);
          continue;
        }
        index.clear();
        find_max_subsequence_length(t,p,k,index);
        if(index.size() == 0){
          output.push_back({-1});
          continue;
        }
        else{
          output.push_back(index);
        }

    } 
    
   for(int i = 0; i < output.size(); i++){
       if(output[i][0] == -1){
          cout<<0<<"\n";
          continue;
       }
       cout<<output[i].size()<<" ";
       for(int j = 0; j < output[i].size(); j++){
          cout<<output[i][j]<<" ";
       }
       cout<<"\n";
   }
   free(y_1);
   free(y_2);
   return 0;
}
