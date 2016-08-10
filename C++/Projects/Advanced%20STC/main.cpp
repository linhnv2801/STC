/////////////////////////////////////////////////////////////////////////////////////////////
// You can edit all or part of the default code for your purpose
// Please refer to the following input/output example when you need
// Standard Input Examples
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // Example of input one int variable
// cin >> b >> c;                       // Example of input two float variables 
// cin >> d >> e >> f;                  // Example of input three double varaibles
// cin >> g;                            // Example of input one char variable
// cin >> var;                          // Example of input one string into one char array
// cin >> AB;                           // Exmaple of input one long long variable
/////////////////////////////////////////////////////////////////////////////////////////////
// Standard Output Examples
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // Example of output one int variable
// cout << b << " " << c;               // Example of output two float variables
// cout << d << " " << e << " " << f;   // Example of output three double varaibles
// cout << g;                           // Example of output one char variable
// cout << var;                         // Example of output one string from one char array
// cout << AB;                          // Exmaple of output one long long variable
/////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS	// Ignore build errors when using unsafe functions in Visual Studio.
#include <iostream>

#include <conio.h>

#define GET_MIN(x,y) ( x > y ? x = y : x)
#define INT_MAX 1e9

using namespace std;

int answer, N, g[3],  n[3], s[3];

int Abs(int x);
void Init();
void Print();
void Swap(int i, int j);
void Sort();
int Calculator();
void Solve();


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
		//cout << Abs(-1) << endl << Abs(2) << endl;
		/*Print();
		Sort();
		Print();*/

		Sort();
		Solve();


		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << answer << endl;
	}

	getch();
	return 0; // Your program should return 0 on normal termination.
}

void Init()
{
	cin >> N >> g[0] >> n[0] >> g[1] >> n[1] >> g[2] >> n[2];
	g[0]--;
	g[1]--;
	g[2]--;
	answer = INT_MAX;
}

void Swap(int i, int j)
{
	int tmp = g[i];
	g[i] = g[j];
	g[j] = tmp;

	int tmp2 = n[i];
	n[i] = n[j];
	n[j] = tmp2;
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

void Solve()
{
	for (int i = 0; i <= (N - n[0] - n[1] - n[2]); i++)
	{
		for (int j = n[0]; j <= (N - n[1] - n[2] ); j++)
		{
			for (int t = n[0] + n[1] ; t <= (N - n[2] ); t++)
			{
				if ((i <= (j - n[0])) && (j <= (t - n[1])))
				{
					s[0] = i;
					s[1] = j;
					s[2] = t;
					int tmp = Calculator();
					GET_MIN(answer,tmp);
				}
			}
		}
	}
}

int Calculator()
{
	int sum = 0;
	for (int i = s[0]; i < (s[0] + n[0]); i++)
	{
		sum += Abs(g[0] - i) + 1;
	}
	for (int i = s[1]; i < (s[1] + n[1]); i++)
	{
		sum += Abs(g[1] - i) + 1;
	}
	for (int i = s[2]; i < (s[2] + n[2]); i++)
	{
		sum += Abs(g[2] - i) + 1;
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