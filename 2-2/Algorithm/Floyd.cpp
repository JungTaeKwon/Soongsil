#include <iostream>
#include <vector>
using namespace std;

void print(const vector<vector<int>> arr)
{//vector 전체출력 함수. W,P1,D2,made,P2,D2 출력 보조  
	for(int i = 1 ; i < arr.size() ; i++)
	{
		for(int j = 1 ; j < arr.at(i).size() ; j++)
		{
			cout << arr.at(i).at(j) << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
}

void floyd2(int n, const vector<vector<int>> W, vector<vector<int>> &D, vector<vector<int>> &P) 
{//교안의 pseudo code에 충실히 작성. 본인은 c++ library vector를 이용하여 최단경로 알고리즘 구현  
	int i, j, k;
	for(i = 1 ; i < n ; i++)
	{
		for(j = 1 ; j < n ; j++)
		{
			P[i][j] = 0;
		}
	}
	D = W;
	for(k = 1 ; k < n ; k++)
	{
		for(i = 1 ; i < n ; i++)
		{
			for(j = 1 ; j < n ; j++)
			{
				if(D[i][k] + D[k][j] < D[i][j])
				{
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}

void path(const int q, const int r, const vector<vector<int>> P)
{//최단경로 출력 알고리즘  
	if(P[q][r] != 0)
	{
		path(q,P[q][r],P);
		cout << "v" << P[q][r] << "->";
		path(P[q][r],r,P);
	}
}

void pathPrinter(const int q, const int r, const vector<vector<int>> P)
{//교안 pseudo code에 충실하게 작성한 path() 의 출력을 간결하게 해줄 pathPrinter 함수  
	cout << "v" << q << "에서 v" << r << "까지 최단 경로 : v" << q << "->";
	path(q, r, P);
	cout << "v" << r << endl<<endl;
}

int main()
{
	//교재 데이터 
	vector<vector<int>> W = { {0,},{0,0,1,999,1,5},{0,9,0,3,2,999},{0,999,999,0,4,999},{0,999,999,2,0,3},{0,3,999,999,999,0} };
	//자작 데이터 
	vector<vector<int>> made = { {0,},{0,0,3,8,999,4},{0,999,0,999,1,7},{0,999,4,0,999,999},{0,2,999,5,0,999},{0,999,999,999,6,0} };
	//pseudo code에 최대한 충실하게 floyd2를 작성하기 위해 0행0열을 비워두고 사용하지 않음.
	//간선이 없음(INF)을 999로 표현
	 
	//빈 배열을 만들어서 D1,P1,D2,P2 초기화에 이용 
	vector<int> empty(W.size());
	
	vector<vector<int>> D1(W.size(), empty);
	vector<vector<int>> P1(W.size(), empty);
	vector<vector<int>> D2(made.size(), empty);
	vector<vector<int>> P2(made.size(), empty);
	
	cout << "W\n";
	print(W);
	floyd2(W.size() , W , D1 , P1);
	
	cout << "D1\n";
	print(D1);
	
	pathPrinter(5,3,P1); //교안에서 test했던 v5 -> v3 최단경로 출력.  
	
	cout << "P1\n";
	print(P1);
	
	cout << "--------------------------------\n";
	
	cout << "made\n";
	print(made);
	floyd2(made.size() , made , D2 , P2);
	
	cout << "D2\n";
	print(D2);
	
	pathPrinter(5,2,P2); //v5 에서 v2까지의 최단경로를 출력하라.  
	cout << "P2\n";
	print(P2);
	
	return 0;
}
