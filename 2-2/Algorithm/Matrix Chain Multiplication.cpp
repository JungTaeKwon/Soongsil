#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int minmult(int n, const vector<int> d, vector<vector<int>>& p);
void order(int i, int j, vector<vector<int>> p);
void print(const vector<vector<int>> v);

int main()
{
	//교안 데이터
	vector<int> d = {5,2,3,4,6,7,8};
	//자작 데이터
	vector<int> made = {4,5,3,2,7,3,8};
	
	vector<int> empty(d.size()); //empty vector를 p vector 초기화에 이용 
	vector<vector<int>> p(d.size(), empty); //최적곱셈순서 출력 도와줄 p 
	cout << "최소 곱셈 횟수 : " << minmult(p.size() - 1, d, p) << endl;
	cout << "최소 곱셈 양식 : "; order(1,6,p); cout << endl << endl;

	cout << "p\n";
	print(p);
	
	vector<int> made_empty(made.size()); //made_empty vector를 made vector 초기화에 이용
	vector<vector<int>> made_p(made.size(), empty);  //최적곱셈순서 출력 도와줄 made_p
	cout << "최소 곱셈 횟수 : " << minmult(made_p.size() - 1, made, made_p) << endl;
	cout << "최소 곱셈 양식 : "; order(1,6,made_p); cout << endl << endl;
	cout << "made_p\n";
	print(made_p);
	
	
	return 0;
}

int minmult(int n, const vector<int> d, vector<vector<int>>& p)
{
	int i, j, k, diagonal,minnum;
	vector<int> empty(n+1);	//pesudo code에 충실하고자 0행 0열 인덱스 이용하지 않음 
	vector<vector<int>> M(n+1, empty);
	//임의의 M vector 생성 후 구하고자 하는 최소곱셈횟수 값인 [1][n] 반환예정 
	
	for(i = 1 ; i <= n ; i++)
	{
		for(k = 1 ; k <= n ; k++)
		{
			M[i][k] = INT_MAX;
		}
	}
	
	for(i = 1 ; i<= n ; i++)
		M[i][i] = 0;
		
	for(diagonal = 1; diagonal <= n-1; diagonal++) //대각 
	{
		for(i = 1 ; i <= n-diagonal ; i++) //대각과 열의 인덱스 합은 항상 n인점 이용 
		{
			j = i + diagonal;
			for(k = i ; k <= j-1 ; k++)	//후보들 계속 비교 
			{
				if(M[i][j] > (M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j]))
				{
					M[i][j] = (M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j]);
					minnum = k;
					cout << "M[i][j] : " << M[i][j] << endl;
				}
				p[i][j] = minnum;
			}
		}
	}
	print(M);
	return M[1][n];
}

void order(int i, int j, vector<vector<int>> p)
{//재귀 호출로 최소곱셈 양식 출력  
	int k;
	if(i == j) cout << "A" << i;
	else
	{
		k = p[i][j];
		cout << "(";
		order(i,k,p);
		order(k+1,j,p);
		cout << ")";
	}
} 

void print(const vector<vector<int>> v)
{
	for(int i = 0 ; i < v.size() ; i++)
	{
		for(int k = 0 ; k < v[i].size() ; k++)
		{
			if(i == 0 || k == 0)
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
