#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;
void print(const vector<vector<float>> v);
void print(const vector<vector<int>> v);
void optsearchtree(int n, const vector<float> p, float& minavg, vector<vector<int>> R);

struct node{
	string key;
	node* left;
	node* right;
}typedef node;

int main()
{
	//최적의 경우 출력 도와줄 변수  
	float minavg; 
	//교안 데이터  
	vector<float> p = {0.0, 0.375, 0.375, 0.125, 0.125};
	//자작 데이터
	vector<float> made = {0.0,0.3,0.2,0.1,0.4};
	
	vector<int> empty (p.size()+1);
	vector<vector<int>> r(p.size()+1,empty);
	vector<vector<int>> r_made(made.size()+1,empty);
	 
	optsearchtree(4,p,minavg,r);
	cout << "optimal : " << minavg << endl;
	optsearchtree(4,made,minavg,r_made);
	cout << "optimal : " << minavg << endl;
	return 0;
}

void print(const vector<vector<float>> v)
{
	for(int i = 0 ; i < v.size() ; i++)
	{
		for(int k = 0 ; k < v[i].size()-1 ; k++)
		{
			if(i == 0)
				continue;
			if(v[i][k] == INT_MAX)
				cout << " INF  ";
			else if(v[i][k] == 0)
				cout << "0.000 ";
			else
				cout << v[i][k] << " ";	
		}
		cout << endl;
	}
	cout << endl;
 }
 
 void print(const vector<vector<int>> v)
{
	for(int i = 0 ; i < v.size() ; i++)
	{
		for(int k = 0 ; k < v[i].size()-1 ; k++)
		{
			if(i == 0)
				continue;
			if(v[i][k] == INT_MAX)
				cout << "  ";
			else
				cout << v[i][k] << " ";	
		}
		cout << endl;
	}
	cout << endl;
 }
 
void optsearchtree(int n, const vector<float> p, float& minavg, vector<vector<int>> R)
{
	int i, j, k, diagonal,minnum;
	vector<float> empty(n+2);
	vector<vector<float>> A(n+2,empty);

	for(i = 0 ; i <= n+1 ; i++)
	{
		for(k = 0 ; k <= n+1 ; k++)
		{
			A[i][k] = INT_MAX;
		}
	}
	
	for(i = 1 ; i <= n ; i++)
	{
		A[i][i] = p[i];
		A[i][i-1] = 0;
		R[i][i] = i;
		R[i][i-1] = 0;
	}
	
	
	A[n+1][n] = 0;
	R[n+1][n] = 0;
	
	for(diagonal = 1 ; diagonal <= n-1 ; diagonal++)
	{
		for(i = 1 ; i <= n-diagonal ; i++)
		{
			j = i + diagonal;
			for(k = i ; k <= j ; k++)
			{
				if(A[i][j] > A[i][k-1] + A[k+1][j])
				{
					A[i][j] = A[i][k-1] + A[k+1][j];
					minnum = k;
				}
			}
			for(k = i ; k <= j ; k++) A[i][j] += p[k];
			R[i][j] = minnum;
		}
		minavg = A[1][n];
	}
	print(A);
	print(R);
}
