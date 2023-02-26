#include <iostream>
#include <vector>
#define INF 999
using namespace std;

struct edge
{
	int depart;
	int arrive;
	int weight;
}typedef edge;
typedef vector<edge> set_of_edges;

void dijkstra(int n, const vector<vector<int>> W, set_of_edges& F);

int main(void)
{
	vector<vector<int>> W = {{0,},{0,0,7,4,6,1},{0,INF,0,INF,INF,INF},{0,INF,2,0,5,INF},{0,INF,3,INF,0,INF},{0,INF,INF,INF,1,0}};
	
	vector<vector<int>> made = {{0,},{0,0,2,INF,INF,3},{0,INF,0,5,2,INF},{0,INF,INF,0,10,3},{0,INF,INF,INF,0,INF},{0,INF,INF,INF,7,0}};
	
	set_of_edges F;
	set_of_edges F_made;
	
	dijkstra(5,W,F);
	dijkstra(5,made,F_made);
	
	cout << "교안 데이터\n";
	
	for(int i = 0 ; i < F.size() ; i++)
	{
		cout << F[i].depart << " -> " << F[i].arrive << ", weight : " << F[i].weight << endl;
	}
	
	cout << "\n자작 데이터\n";
	
	for(int i = 0 ; i < F_made.size() ; i++)
	{
		cout << F_made[i].depart << " -> " << F_made[i].arrive << ", weight : " << F_made[i].weight << endl;
	}
	
	return 0;
}

void dijkstra(int n, const vector<vector<int>> W, set_of_edges& F)
{
	int i, vnear, min; edge e;
	vector<int> touch(n+1); vector<int> length(n+1);
	for(i = 2 ; i <= n ; i++)
	{
		touch[i] = 1;
		length[i] = W[1][i];
	}
	int repeat = n-1;
	while(repeat--)
	{
		min = INF;
		for(i = 2 ; i <= n ; i++)
		{
			if((length[i] >= 0) && (length[i] <= min))
			{
				min = length[i];
				vnear = i;
			}
		}
		
		e.depart = touch[vnear];
		e.arrive = vnear;
		e.weight = W[touch[vnear]][vnear];
		F.push_back(e);
		for(i = 2 ; i <= n ; i++)
		{
			if(length[vnear] + W[vnear][i] < length[i])
			{
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear;
			}		
		}
		length[vnear] = -1;
	}
}
