#include <conio.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include <iostream>

#define GET_MAX(x,y) if((x) < (y)) (x = y);

using namespace std;

int N, C, Answer;
int *W; // save weight of N elements
int *V; // save value of N elements
int *F; // save maximum value for array C element can save in knapsack

// Print array 
void PrintArr(int *arr, int length) ;
void Init();
void Solve();
void Free();

int main()
{
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	register int T, test_case;

	freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);

	cin >> T;
	for(test_case = 0; test_case < T; test_case++)
	{
		Init();

		Solve();

		// Print the answer to standard output(screen).
		cout << "Case #" << test_case + 1 << endl << F[C] << endl;
		Free();
	}

	getch();
	return 0;//Your program should return 0 on normal termination.
}

void Solve()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = W[i]; j <= C; j++)
		{
			GET_MAX(F[j], F[j-W[i]] + V[i]);
		}
	}
}

void Init()
{
	cin >> N;
	W = new int[N];
	V = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> W[i];
	}
	for (int i = 0; i < N; i++)
	{
		cin >> V[i];
	}
	cin >> C;
	F = new int[C+1];
	for (int i = 0; i < C + 1; i++)
	{
		F[i] = 0;
	}
}

void Free()
{
	delete[] F;
	delete[] V;
	delete[] W;
}

void PrintArr(int *arr, int length) 
{
	for (int i = 1; i < length; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}