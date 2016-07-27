#include <iostream>

#include <conio.h>

#define GET_MAX(x,y) ( x < y) ? (x = y) : (x)

using namespace std;

int DD[12];
int LL[] = { 0, -1, -1, 0, 0, 1, 1, 1, 1, 0, 1, -1 }; // x, y deu le    : 1
int LC[] = { -1, -1, -1, 0, -1, 1, 0, 1, 1, 0, 0, -1 }; // x le, y chan  : 2
int CL[] = { 0, -1, -1, 0, 0, 1, 1, 1, 1, 0, 1, -1 }; // x chan, y le   : 3
int CC[] = { -1, -1, -1, 0, -1, 1, 0, 1, 1, 0, 0, -1 }; // x,y deu chan : 4
int data[15][15], result[8], re_max[8];
bool visited[15][15], visited2[15][15];
int n, m, anwser, nums, sum, C;

inline int Type(int x, int y);
inline bool Is_Safe(int x, int y);
inline void Copy_Arr(int a[], int b[], int length);
inline void Copy_DD(int i);
void Init();
void Print();
void Print(int *arr, int length);
void Print_Results(int *arr, int length);
void Mark(int nums, int x, int y);
void Try_Cell(int xx, int yy);
void Solve();
void Reset();

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		Init();
		//Print();
		Solve();
		//cout << C << endl;
		Print_Results(re_max, 8);
		cout << "#" << tc + 1 << " " << anwser << endl;
	}

	//cout << "done" << endl;
	getch();
	return 0;
}

void Try_Cell(int xx, int yy)
{
	if (nums == 4)
	{
		C++;
		//GET_MAX(anwser, sum * sum);
		if (anwser < sum * sum)
		{
			Copy_Arr(re_max, result, 8);
			anwser = sum * sum;
		}
		return;
	}
	Copy_DD(Type(xx, yy));

	for (int i = 0; i < 12; i += 2)
	{
		int x = xx + DD[i];
		int y = yy + DD[i + 1];
		if (Is_Safe(x, y))
		{
			visited[x][y] = true;
			nums++;
			Mark(nums, x, y);
			sum += data[x][y];
			Try_Cell(x, y);
			visited[x][y] = false;
			nums--;
			sum -= data[x][y];
		}
	}
}

void Solve()
{
	int c = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			c++;
			if (c > n *m - 3)
			{
				return;
			}
			visited[i][j] = true;
			visited2[i][j] = true;
			sum += data[i][j];
			result[0] = i;
			result[1] = j;
			Try_Cell(i, j);
			Reset();
		}
	}
}

void Mark(int nums, int x, int y)
{
	switch (nums)
	{
	case 2:
		result[2] = x;
		result[3] = y;
		break;
	case 3:
		result[4] = x;
		result[5] = y;
		break;
	case 4:
		result[6] = x;
		result[7] = y;
		break;
	default:
		break;
	}
}

inline int Type(int x, int y)
{
	int ans = 0;
	if (x % 2)
	{
		if (y % 2)
		{
			// LL
			ans = 1;
		}
		else
		{
			// LC
			ans = 2;
		}
	}
	else
	{
		if (y % 2)
		{
			// CL
			ans = 3;
		}
		else
		{
			// CC
			ans = 4;
		}
	}
	return ans;
}

void Print(int *arr, int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void Print_Results(int *arr, int length)
{
	for (int i = 0; i < length; i += 2)
	{
		cout << data[re_max[i]][re_max[i + 1]] << "\t";
	}
	cout << endl;
}

inline void Copy_DD(int i)
{
	switch (i)
	{
	case 1:
		Copy_Arr(DD, LL, 12);
		break;
	case 2:
		Copy_Arr(DD, LC, 12);
		break;
	case 3:
		Copy_Arr(DD, CL, 12);
		break;
	case 4:
		Copy_Arr(DD, CC, 12);
		break;
	default:
		break;
	}
}

inline void Copy_Arr(int a[], int b[], int length)
{
	for (int i = 0; i < length; i++)
	{
		a[i] = b[i];
	}
}

inline bool Is_Safe(int x, int y)
{
	if (x < 0 || y < 0 || x > n || y > m || visited[x][y] )
	{
		return false;
	}
	return true;
}

void Init()
{
	cin >> m >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> data[i][j];
			visited[i][j] = false;
			visited2[i][j] = false;
		}
	}
	anwser = 0;
	nums = 1;
	sum = 0;
	C = 0;
}

void Reset()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			visited[i][j] = false;
		}
	}
	nums = 1;
	sum = 0;
}

void Print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
}