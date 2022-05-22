// Kosaraj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define CMAX 10000

vector< int > components[CMAX];
vector< int > v[CMAX];
vector< int > vrev[CMAX];
bool arr[CMAX];
stack< int > st;
int n, numComponents, m;
ofstream fout;

void dfs(int x)
{
	arr[x] = true;
	for (int i = 0; i < v[x].size(); i++)
	{
		if (!arr[v[x][i]])
		{
			dfs(v[x][i]);
		}
	}
	st.push(x);
}

void dfsrev(int x)
{
	fout << x << ' ';
	arr[x] = true;

	for (int i = 0; i < vrev[x].size(); i++)
	{
		if (!arr[vrev[x][i]])
		{
			dfsrev(vrev[x][i]);
		}
	}
}

void kosaraju()
{
	for (int i = 0; i < n; i++)
	{
		if (!arr[i])
		{
			dfs(i);
		}
	}

	memset(arr, false, CMAX);

	while (!st.empty())
	{
		int v = st.top();
		st.pop();

		if (!arr[v])
		{
			fout << "Componenta " << numComponents << ": ";
			dfsrev(v);
			numComponents++;
			fout << endl;
		}
		
	}
}

void clear(vector<int> v[CMAX])
{
	for (int i = 0; i < CMAX; i++)
	{
		v[i].clear();
	}
	v->clear();
}


int main()
{
	
	for (int i = 1; i <= 10; i++)
	{
		memset(arr, false, CMAX);
		char nume[40], numeOutput[40];
		sprintf_s(numeOutput, "../../Data/output%d.txt", i);
		sprintf_s(nume,"../../Data/input%d.txt", i);
		ifstream fin(nume);
		fout.open(numeOutput,ios::out);

		fin >> n >> m;
		cout << n << " " << m << endl;
		int nr = 0;
		int a, b;

		while (fin >> a >> b)
		{
			nr++;
			//fout << a << " " << b << " " << nr << endl;
			v[a].push_back(b);
			vrev[b].push_back(a);
		}
		auto start = chrono::steady_clock::now();
		kosaraju();
		auto end = chrono::steady_clock::now();

		fout << "Elapsed time in seconds: "
			<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
			<< " milliseconds";

		clear(v);
		clear(vrev);

		fin.close();
		fout.close();

	}
	
}

