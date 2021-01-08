#include <iostream>
#include <string>
#include "Nod.h"

void Citire(int a[], int& n)
{
	std::cin >> n;
	for (int i = 0; i < n*n; i++)
	{
		std::cin >> a[i];
	}
}

bool determinareSolvabilitate(int StareInitiala[], int n)
{
	int nrInversiuni = 0, pozitieBlank = -1;
	for (int i = 0; i < n*n-1; i++)
	{
		for (int j = i+1; j < n*n; j++)
		{
			if (StareInitiala[i] > StareInitiala[j] && StareInitiala[i] != n*n && StareInitiala[j] != n*n)
			{
				nrInversiuni++;
			}
		}
		if (StareInitiala[i] == n)
		{
			pozitieBlank = i;
		}
	}
	if (pozitieBlank == -1)
	{
		pozitieBlank = n*n-1; //aflu pozitia in vectorul-joc scris ca row
	}
	pozitieBlank = (n - pozitieBlank / n) + 1; //randul pe care e spatiul de jos in sos
	if ((n % 2 == 1 && nrInversiuni % 2 == 0) || (n % 2 == 0 && (pozitieBlank % 2 == 1 == nrInversiuni % 2 == 0)))
	{
		return true;
	}
	return false;
}

int cost_recurent(int v[], int i) {
	if (i == 9)
		return 0;
	else
		if (v[i] == 9)
		{
			return cost_recurent(v, i + 1);
		}
		return abs((v[i]-1) / 3 - i / 3) + abs((v[i]-1) % 3 - i % 3) + cost_recurent(v, i + 1);
}

int cost_permutare(int v[], int t[], int k, int pos) {
	int aux;
	if ((pos%3 != (pos+k)%3) && (pos / 3 != (pos + k) / 3) || pos + k > 9 || pos + k < 0 )
		return 32000;
	else {
		aux = v[pos + k];
		v[pos + k] = v[pos];
		v[pos] = aux;
		int c = cost_recurent(v, 0);
		for (int i = 1; i <= 9; i++)
			v[i] = t[i];
		return c;
	}
}

int optimal_path(int a, int b, int c, int d) {
	if (a <= b && a <= c && a <= d)
		return 1; //right
	else
		if (b <= a && b <= c && b <= d)
			return -1; //left
		else
			if (c <= a && c <= b && c <= d)
				return 3; //down
			else
				return -3; //up
}

int A_star(int v[], int t[], int pos)
{
	for (int i = 0; i < 9; i++)
		t[i] = v[i];
	int c = cost_recurent(v, 0);
	if (c == 0)
		return 0;
	else {
		int optim = optimal_path(cost_permutare(v, t, 1, pos), cost_permutare(v, t, -1, pos), cost_permutare(v, t, 3, pos),
			cost_permutare(v, t, -3, pos));
		int aux;
		aux = v[pos + optim];
		v[pos + optim] = v[pos];
		v[pos] = aux;
		int cost = cost_recurent(v, 0);
		return cost + A_star(v, t, pos + optim);
	}
}

int main()
{
	int stareInitiala[1000], n, t[1000];
	Citire(stareInitiala, n);
	if (determinareSolvabilitate(stareInitiala, n))
	{
		std::cout << A_star(stareInitiala, t, 4);
	}
	else
	{
		std::cout << "No solution";
	}
	return 0;
}
