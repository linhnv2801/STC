#define _CRT_SECURE_NO_WARNINGS	// Ignore build errors when using unsafe functions in Visual Studio.
#include <iostream>

#include <conio.h>

#define G 3 // sum of gates

#define GET_MIN(x,y) ( x > y ? x = y : x)
#define INT_MAX 1e9

using namespace std;

int answer, N, g[G],  n[G], s[G], l, r, sum, sums[G][2];
int  a[G]; // [123] gate 1 -> gate 2 -> gate 3
int *spot; // spot[N] : da co fisherman hay chua

int ToLeft(int i); // return index left of i can insert
int ToRight(int i); // return index right of i can insert
int Abs(int x);
void Reset();
void Init();
void Print();
void Print(int *arrs, int length);
void Swap(int &i, int &j);
void Per(int i);
void Sort();
int Calculator(int i); // Tinh tong quang duong tai cong thu i
int Calculator();
void Solve(int i);
void Free();


int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	The freopen function below opens sample_input.txt in read only mode and
	sets your standard input to work with the opened file.
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/
	freopen("sample_input.txt", "r", stdin);

	/*
	The following code is inserted for increasing input/output processing performance.
	If the following code is activated, using both of scanf and cin command may cause malfucntion on input process.
	*/
	std::ios::sync_with_stdio(false);

	/*
	Read each test case from standard input.
	*/
	cin >> T;
	for (test_case = 1; test_case <= T; test_case++)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Please, implement your algorithm from this section.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////

		Init();

		Per(0);

		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << answer << endl;
		Free();
	}

	getch();
	return 0; // Your program should return 0 on normal termination.
}

void Init()
{
	cin >> N >> g[0] >> n[0] >> g[1] >> n[1] >> g[2] >> n[2];
	spot = new int[N];
	for (int i = 0; i < N; i++)
	{
		spot[i] = -1;
	}
	for (int i = 0; i < G; i++)
	{
		a[i] = i;
	}
	g[0]--;
	g[1]--;
	g[2]--;
	answer = INT_MAX;
	sum = 0;
}

void Swap(int &i, int &j)
{
	int tmp = i;
	i = j;
	j = tmp;
}

void Sort()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i; j < 3; j++)
		{
			if (g[i] > g[j])
			{
				Swap(i,j);
			}
		}
	}
}

void Print()
{
	cout << N << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << g[i] << "\t" << n[i] << endl;
	}
	cout << endl;
}

void Solve(int i) // goi lan luot tu cua a[0] -> a[1] -> a[2]
{
	if (i == G)
	{
		GET_MIN(answer, Calculator());
		return;
	}
	Reset();
	// Gate : a[0] -> a[1] -> a[2]
	//  Gate a[0] : g[a[0]]

	int nums = n[a[i]];
	while (nums) // put others fisherman of gate a[i]
	{
		l = ToLeft(g[a[i]]);
		r = ToRight(g[a[i]]);
		if (l == -1)
		{
			// only case right != -1, then put fisherman to index right
			spot[r] = a[i]; // dien vi tri cong a[i] vao vi tri right
			nums--;
		}else // left != -1
		{
			if (r == -1)
			{
				// dien vao vi tri left
				spot[l] = a[i];
				nums--;
			}else
			{
				if (Abs(a[i] - l) == Abs(a[i] - r))
				{
					// dien 1 trong 2 cho
					if (nums == 1) // thang cuoi cung thi se co 2 lua chon dien 2 cho khac nhau
					{
						for (int j = 0; j < 2; j++)
						{
							if (j)
							{
								spot[l] = a[i];
								Solve(i + 1);
								spot[l] = -1;
							}else
							{
								spot[r] = a[i];
								Solve(i + 1);
								spot[r] = -1;
							}
						}
						spot[l] = a[i];
						spot[r] = 0;
						Solve(i + 1);
						spot[l] = 0;
						spot[r] = a[i];
						nums--;
					}else // chua phai thang cuoi thi dien ben nao cung nhu nhau, vi du chon dien ben trai
					{
						// put in left
						spot[l] = a[i];
						nums--;
					}
				}if (Abs(a[i] - l) < Abs(a[i] - r))
				{
					// put in left
					spot[l] = a[i];
					nums--;
				}else // Abs(a[i] - l) > Abs(a[i] - r)
				{
					// put in right
					spot[r] = a[i]; // dien vi tri cong a[i] vao vi tri right
					nums--;
				}
			}
		}
	}


}

int Calculator(int i) // i = 0,1,2, g[i]
{
	int sum = 0;
	for (int j = 0; j < N; j++)
	{
		if (spot[j] == a[i])
		{
			sum += Abs(g[i] - j) + 1;
		}
	}
	return sum;
}

int Abs(int x)
{
	if (x < 0)
	{
		return -x;
	}
	return x;
}

void Print(int *arrs, int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << arrs[i] << "\t";
	}
	cout << endl;
}

void Free()
{
	delete[] spot;
}

void Per(int i)
{
	if (i == G)
	{
		Print(a, G);
		Solve(0);
		//Print(spot, N);
		return;
	}
	for (int j = i; j < G; j++)
	{
		Swap(a[i], a[j]);
		Per(i + 1);
		Swap(a[i], a[j]);
	}
}

void Reset()
{
	for (int i = 0; i < N; i++)
	{
		spot[i] = -1;
	}
}

int ToLeft(int i)
{
	for (int j= i; j >= 0; j--)
	{
		if (spot[j] == -1)
		{
			return j;
		}
	}
	return -1;
}

int ToRight(int i)
{
	for (int j = i; j < N; j++)
	{
		if (spot[j] == -1)
		{
			return j;
		}
	}
	return -1;
}

int Calculator()
{
	int sum = 0;
	for (int i = 0; i < G; i++)
	{
		sum += Calculator(a[i]);
	}
	return sum;
}