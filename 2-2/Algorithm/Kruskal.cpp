#include <iostream>
#include <algorithm>
using namespace std;
const int n = 5;
struct edge
{
	int vertix1;
	int vertix2;
	int weight;
}typedef edge;
typedef vector<edge> set_of_edges;
typedef int index;
typedef index set_pointer;
struct notetype
{
	index parent;
	int depth;
}typedef universe[n+1];
universe U;
void makeset(index i)
{
	U[i].parent = i;
	U[i].depth = 0;
}
set_pointer find(index i){
	index j; j = i;
	while(U[j].parent != j)
		j=U[j].parent;
	return j;
}
void merge(set_pointer p, set_pointer q){
	if(U[p].depth == U[q].depth){
	U[p].depth =+ 1;
	U[q].parent=p;
	}
	else if(U[p].depth < U[q].depth)
		U[p].parent = q;
	else
		U[q].parent = p;
}
bool equal(set_pointer p, set_pointer q){
	if(p==q) return true; else return false;}
void initial(int n){ index i;
	for(i = 1 ; i <= n ; i++) makeset(i);}


bool compare(edge e1, edge e2);
void kruscal(int n, int m, set_of_edges E, set_of_edges& F);

int main()
{
	set_of_edges E1 = { {1,2,1}, {3,5,2}, {1,3,3}, {2,3,3}, {3,4,4}, {4,5,5}, {2,4,6} };
	set_of_edges F1;
	
	kruscal(5,E1.size(),E1,F1);
	
	cout << "교안 데이터\n";
	for (int i = 0; i < F1.size(); i++)
	{
		cout << "V"<< F1[i].vertix1 << "--V" << F1[i].vertix2<< ", weight : " << F1[i].weight<< endl;
	}
	
	set_of_edges made_E = { {1,2,2},{2,3,1},{1,5,3},{3,4,4},{2,5,5},{2,4,7},{4,5,10} };
	set_of_edges made_F;
	
	kruscal(5,made_E.size(),made_E,made_F);
	
	cout << "자작 데이터\n";
	for(int i = 0 ; i < made_F.size() ; i++)
	{
		cout << "V"<< made_F[i].vertix1 << "--V" << made_F[i].vertix2<< ", weight : " << made_F[i].weight<< endl;
	}
	
	return 0;
}

void kruscal(int n, int m, set_of_edges E, set_of_edges& F)
{
	index i, j;
	set_pointer p, q;
	edge e;
	
	int cnt = 0;
	
	sort(E.begin(),E.end(),compare);
	
	initial(n);
	
	while(F.size() < n-1)
	{
		e = E[cnt];
		i = E[cnt].vertix1;
		j = E[cnt].vertix2;
		p = find(i);
		q = find(j);
		if(!equal(p,q))
		{
			merge(p,q);
			F.push_back(e);
		}
		cnt++;
	}
}
bool compare(edge e1, edge e2)
{
	if(e1.weight < e2.weight)
	{
		return true;
	}
	else
	{
		return false;
	}
}
