// GeneratorDate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <bits/stdc++.h>
using namespace std;

int main()
{
	srand(time(NULL));

	for (int i = 1; i <= 10; i++)
	{
		char nume[40];
		sprintf_s(nume, "../../Data/input%d.txt", i);
		ofstream fout(nume);

		cout << "FISIERUL " << i << endl;

		int n, m, laturi = 0;
		n = (i * 100);
		fout << n << ' ';
		set<pair<int, int >> s;
		for (int i = 0; i < n; i++)
		{
			//genereaza laturile pentru fiecare nod
			//nr de laturi posibile este rand()%(n - (i + 1)) + 1,
			//pt noduri mai mici decat n - 1

			m = 1 + (std::rand() % ((n - 1) - 1 + 1));
			//cout << m << endl;
			while (m)
			{
				int latura = 0 + (std::rand() % ((n - 1) + 1));
				auto pos = s.find(pair<int, int>(i, latura));
				if (pos == s.end() && latura != i)
				{
					s.insert(make_pair(i, latura));
					m--;
				}
			}
		}
		fout << s.size() << '\n';

		int nr = 0;
		for (const auto& pr : s)
		{
			nr++;
			fout << pr.first << ' ' << pr.second << '\n';
		}

		fout.close();

	}
	
}
