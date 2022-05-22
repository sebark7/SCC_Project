#include <bits/stdc++.h>
//#include "mpi.h"
#include <omp.h>
#include <execution>
#include <algorithm>
#include <mutex> 
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;
map<int, set<int>> vc;
set< int > sett[1000];
vector<vector<int>> v(10000);
vector< int > noduri, sirprelucrat;
map<int, int> colors;
vector<int> culoriunice;
map<int, int> mapp;
map<int, set<int>> scvv;
bool arr[10000];
int n, nr, index;

bool changedColors(int n)
{
	for (int i = 0; i < n; i++)
	{
		if (noduri[i] != -1)
		{
			return true;
		}
	}
	return false;
}

void dfs(int nod)
{
	if (!arr[nod])
	{
		arr[nod] = true;
		for (int i = 0; i < v[nod].size(); i++)
		{
			if (!arr[v[nod][i]])
			{
				if (colors[nod] > colors[v[nod][i]])
				{
					colors[v[nod][i]] = colors[nod];
				}
				dfs(v[nod][i]);
			}
		}
	}
}

void umplereculori(int nod)
{
	if (!arr[nod])
	{
		dfs(nod);
	}
}

bool bfs(int nod, int destinatie)
{
	if (nod == destinatie)
	{
		return false;
	}
	memset(arr, false, sizeof(arr));
	queue<int> q;
	q.push(nod);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (int i = 0; i < v[x].size(); i++)
		{
			if (v[x][i] == destinatie)
			{
				return true;
			}
			else if (!arr[v[x][i]])
			{
				q.push(v[x][i]);
			}
		}
	}
	return false;
}


void stergereLista(vector<vector<int>>& v, int nod)
{
	//cout << "Nodul sters " << nod << " " << omp_get_thread_num() << endl;
	v[nod].clear();
	noduri.erase(remove(noduri.begin(), noduri.end(), nod), noduri.end());
	for (int i = 0; i < n; i++)
	{
		v[i].erase(remove(v[i].begin(), v[i].end(), nod), v[i].end());
	}
}


void insereazaCulori(int ii)
{
	for (auto const& itr2 : colors)
	{
		if (ii == itr2.second)
		{
			vc[ii].insert(itr2.first);
		}
	}
}

void adaugaSet(int ii)
{
	sett[nr].insert(ii);
	for (auto const& itr3 : vc[ii])
	{
		if (bfs(itr3, ii))
		{
			sett[nr].insert(itr3);
		}
	}
}

void stergeLista()
{
	for (int i = 0; i <= nr; i++)
	{
		for (const auto& itr4 : sett[i])
		{
			stergereLista(v, itr4);
		}
	}
	nr++;
}


void resolve(int& i)
{
	insereazaCulori(i);
	adaugaSet(i);
	stergeLista();

}



int main()
{
	mutex mm, mm2;
	omp_set_num_threads(8);

	for (int c = 1; c <= 10; c++)
	{
		cout << "Testul " << c << endl;
		char nume[40], numeOutput[40];
		sprintf_s(numeOutput, "../../Data/output%d.txt", c);
		sprintf_s(nume, "../../Data/input%d.txt", c);
		ifstream fin(nume);
		ofstream fout(numeOutput);

		int m, a, b;
		fin >> n >> m;

		//#pragma omp parallel for
		for (int i = 0; i < n; i++)
		{
			noduri.push_back(i);
		}

		while (fin >> a >> b)
		{
			//cout << a << b << endl;

			v[a].push_back(b);
		}
		auto start = chrono::steady_clock::now();
		while (noduri.size())
		{
			for (int i = 0; i < noduri.size(); i++)
			{
				colors[noduri[i]] = noduri[i];
			}

			std::for_each(std::execution::par, std::begin(noduri), std::end(noduri),
				[&](auto i)
				{
					std::lock_guard lock(mm);
					umplereculori(i);
					memset(arr, false, sizeof(arr));
				});


			for (auto const& itr : colors)
			{
				cout << itr.first << " " << itr.second << endl;
			}

			memset(arr, false, sizeof(arr));

			//Culorile Unice
			for (auto const& itr : colors)
			{
				if (!mapp[itr.second])
				{
					mapp[itr.second] = 1;
					sirprelucrat.push_back(itr.second);
				}
			}

			//map<int, int>::iterator itr2;
			//map<int, set<int>>::iterator itr3;
			//set<int>::iterator itr4;
			std::for_each(std::execution::par, std::begin(sirprelucrat), std::end(sirprelucrat),
				[&](auto ii)
				{
					std::lock_guard lock(mm2);

					resolve(ii);

				});

			//////
			//-eliminarea din noduri-

			colors.clear();
			for (auto& itr : vc)
			{
				itr.second.clear();
			}
			mapp.clear();
			vc.clear();
			sirprelucrat.clear();	
		}
		auto end = chrono::steady_clock::now();

		for (int i = 0; i < 1000; i++)
		{
			v[i].clear();
		}


		for (int i = 0; i < nr; i++)
		{

			fout << "Componentele conexe: ";
			for (auto const& itr2 : sett[i])
			{
				fout << itr2 << " ";
			}
			fout << endl;
			nr = 0;
			for (auto& itr : sett)
			{
				itr.clear();
			}
		}
		fout << "Elapsed time in seconds: "
			<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
			<< " milliseconds";

		fin.close();
		fout.close();
	}
	
	return 0;
}


/*
13 19
0 0
1 4
1 10
2 1
3 2
4 3
4 5
5 1
6 7
6 10
7 12
8 11
9 6
9 12
10 8
10 6
10 9
11 10
12 7

*/