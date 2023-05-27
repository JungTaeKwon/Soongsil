#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
typedef int index;

void knapsack(index i, int profit, int weight);
bool promising(index i,int,int);
void myqsort(vector<float> v, index start, index end);
const int n = 4;
const int W = 16;
vector<string> include(n+1);
vector<string> bestset(n+1);
int maxprofit = 0;
int numbest = 0;

//교안 데이터 
//vector<float> p = {40, 30, 50, 10};
//vector<float> w = {2, 5, 10, 5};
//자작 데이터 
vector<float> p = {40,16,24,15};
vector<float> w = {5,4,12,3};

vector<float> pdivw;
int main()
{
	for(int i = 0 ; i < p.size() ; i++)
	{
		pdivw.push_back(p[i]/w[i]);
	}
	
	myqsort(pdivw,0,pdivw.size()-1);
	
	p.insert(p.begin(),0);
	w.insert(w.begin(),0);

	knapsack(0, 0, 0);
	
	for(int i = 1 ; i <= numbest ; i++)
		cout << "w" << i  << ":" << bestset[i] << endl;
	cout << "maxprofit : " << maxprofit << endl;
	return 0;
}

void knapsack(index i, int profit, int weight)
{
	if(weight <= W && profit > maxprofit)
	{
		maxprofit = profit;
		numbest = i;
		bestset = include;
	}
	
	if(promising(i,profit,weight))
	{
		include[i+1] = "YES";
		knapsack(i+1, profit+p[i+1], weight+w[i+1]);
		include[i+1] = "NO";
		knapsack(i+1, profit, weight);
	}
}

bool promising(index i, int profit, int weight)
{
	index j, k;
	int totweight;
	float bound;
	
	if(weight >= W)	return false;
	else
	{
		j = i+1;
		bound = profit;
		totweight = weight;
		while((j <= n) && (totweight + w[j] <= W))
		{
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		 }
		k = j;
		if(k <= n)
			bound = bound + (W-totweight) * (p[k]/w[k]);
			
	 	return bound > maxprofit;
	}
}

void myqsort(vector<float> v, index start, index end)
{
	if(start >= end)
		return;
	
	index pivot = start;
	index i = start + 1;
	index j  = end;
	float temp;
	float wtemp;
	float ptemp;
	while(i <= j)
	{
		while(i <= end && v[i] >= v[pivot])
			i++;
		while(j > start && v[j] <= v[pivot])
			j--;
		if(i > j)
		{
			temp = v[j];
			v[j] = v[pivot];
			v[pivot] = temp;
			
			wtemp = w[j];
			w[j] = w[pivot];
			w[pivot] = wtemp;
			
			ptemp = p[j];
			p[j] = p[pivot];
			p[pivot] = ptemp;
		}
		else
		{
			temp = v[j];
			v[j] = v[i];
			v[i] = temp;
			
			wtemp = w[j];
			w[j] = w[i];
			w[i] = wtemp;
			
			ptemp = p[j];
			p[j] = p[i];
			p[i] = ptemp;
		}
	}
	myqsort(v,start,j-1);
	myqsort(v,j+1,end);
}
