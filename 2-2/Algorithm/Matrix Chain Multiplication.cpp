#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int minmult(int n, const vector<int> d, vector<vector<int>>& p);
void order(int i, int j, vector<vector<int>> p);
void print(const vector<vector<int>> v);

int main()
{
	//���� ������
	vector<int> d = {5,2,3,4,6,7,8};
	//���� ������
	vector<int> made = {4,5,3,2,7,3,8};
	
	vector<int> empty(d.size()); //empty vector�� p vector �ʱ�ȭ�� �̿� 
	vector<vector<int>> p(d.size(), empty); //������������ ��� ������ p 
	cout << "�ּ� ���� Ƚ�� : " << minmult(p.size() - 1, d, p) << endl;
	cout << "�ּ� ���� ��� : "; order(1,6,p); cout << endl << endl;

	cout << "p\n";
	print(p);
	
	vector<int> made_empty(made.size()); //made_empty vector�� made vector �ʱ�ȭ�� �̿�
	vector<vector<int>> made_p(made.size(), empty);  //������������ ��� ������ made_p
	cout << "�ּ� ���� Ƚ�� : " << minmult(made_p.size() - 1, made, made_p) << endl;
	cout << "�ּ� ���� ��� : "; order(1,6,made_p); cout << endl << endl;
	cout << "made_p\n";
	print(made_p);
	
	
	return 0;
}

int minmult(int n, const vector<int> d, vector<vector<int>>& p)
{
	int i, j, k, diagonal,minnum;
	vector<int> empty(n+1);	//pesudo code�� ����ϰ��� 0�� 0�� �ε��� �̿����� ���� 
	vector<vector<int>> M(n+1, empty);
	//������ M vector ���� �� ���ϰ��� �ϴ� �ּҰ���Ƚ�� ���� [1][n] ��ȯ���� 
	
	for(i = 1 ; i <= n ; i++)
	{
		for(k = 1 ; k <= n ; k++)
		{
			M[i][k] = INT_MAX;
		}
	}
	
	for(i = 1 ; i<= n ; i++)
		M[i][i] = 0;
		
	for(diagonal = 1; diagonal <= n-1; diagonal++) //�밢 
	{
		for(i = 1 ; i <= n-diagonal ; i++) //�밢�� ���� �ε��� ���� �׻� n���� �̿� 
		{
			j = i + diagonal;
			for(k = i ; k <= j-1 ; k++)	//�ĺ��� ��� �� 
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
{//��� ȣ��� �ּҰ��� ��� ���  
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
