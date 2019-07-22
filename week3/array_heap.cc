#include <iostream>


using std::cin;
using std::cout;



int lchild(int i)
{
	return 2*i + 1;
}

int rchild(int i)
{
	return 2*i + 2;
}

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void SiftDown(int *a,int n, int i, int &swap_counter, int *swap_val_list)
{
	int minpos = i;
	int l = lchild(i);
	int r = rchild(i);
	if(l < n && a[l] < a[minpos])
		minpos = l;
	if(r < n && a[r] < a[minpos])
		minpos = r;
	if(i != minpos){
		swap(a[i],a[minpos]);
		swap_val_list[swap_counter*2] = i;
		swap_val_list[swap_counter*2 + 1] = minpos;
		swap_counter++;
		SiftDown(a,n,minpos,swap_counter,swap_val_list);
	}
}

int main()
{
	int n;
	cin>>n;
	int *a = (int *)malloc(sizeof(int) *n);
	int i;
	int *swap_val_list = (int *)malloc(sizeof(int) * 4 *n );
	int swap_counter = 0;
	for(i = 0; i < n; i++)
		cin>>a[i];
	for(i = n/2; i >= 0; i--)
		SiftDown(a,n,i,swap_counter,swap_val_list);
	/*for(i = 0; i < n; i++)
		cout<<a[i]<<" ";
	cout<<"\n";*/
	cout<<swap_counter;
	for(i = 0; i < swap_counter; i++)
		cout<<"\n"<<swap_val_list[i*2]<<" "<<swap_val_list[i*2 + 1];
	cout<<"\n";
	return 0;
}