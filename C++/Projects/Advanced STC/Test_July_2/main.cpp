#include <iostream>

#include <conio.h>
#include <time.h>

#define GET_MAX(x,y) ( x < y) ? (x = y) : (x)

using namespace std;

struct Point
{
	int x, y;
	Point();
	Point(int x, int y);
	bool Equal(Point p);
	void Set(int x, int y);
};

struct Max2 // include maxtric max 2
{
	Point p1;
	int v; // value
	Max2();
	Max2(Point p1, int v);
	void Set_Value(Point p1, int v);
};

struct Max3
{
	Point p1, p2;
	int v;
	Max3();
	Max3(Point p1, Point p2, int v);
	void Set_Value(Point p1, Point p2, int v);
};

struct Max4
{
	Point p1, p2, p3;
	int v;
	Max4();
	Max4(Point p1, Point p2, Point p3, int v);
	void Set_Value(Point p1, Point p2, Point p3, int v);
};

Max2 **max2;
Max3 **max3;
Max4 **max4;

int DD[12];
int LL[] = { 0, -1, -1, 0, 0, 1, 1, 1, 1, 0, 1, -1 }; // x, y deu le    : 1
int LC[] = { -1, -1, -1, 0, -1, 1, 0, 1, 1, 0, 0, -1 }; // x le, y chan  : 2
int CL[] = { 0, -1, -1, 0, 0, 1, 1, 1, 1, 0, 1, -1 }; // x chan, y le   : 3
int CC[] = { -1, -1, -1, 0, -1, 1, 0, 1, 1, 0, 0, -1 }; // x,y deu chan : 4
int **data, result[8], result_max[8];
bool **visited;
int n, m, anwser, nums, sum, C;

inline int Type(int x, int y);
inline bool Is_Safe(int x, int y);
inline bool Is_Safe2(int x, int y);
inline void Copy_Arr(int a[], int b[], int length);
inline void Copy_DD(int i);

void Init();
void Free();
void Print();
void Print(int *arr, int length);
void Print_Result(int *arr, int length);
inline void Set_Result(int x0, int y0,int x1, int y1,int x2, int y2,int x3, int y3);
void Mark(int nums, int x, int y);
void Try_Cell(int xx, int yy);
void Try_Cell2(int xx, int yy);
void Solve();
void Reset();

void Print_Max2();
void Print_Max3();
void Print_Max4();
void Dynamic_Max2();
void Dynamic_Max3();
void Dynamic_Max4();
void Dynamic_Max();

int main()
{
	clock_t tStart = clock();
	freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		Init();
		//Print();

		//Solve();
		Dynamic_Max();
		//cout << C << endl;
		//Print_Result(result_max, 8);
		//Print_Max3();
		cout << "#" << tc + 1 << " " << anwser << endl;
		Free();
	}

	//cout << "done" << endl;
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) /CLOCKS_PER_SEC);
	getch();
	return 0;
}

void Try_Cell(int xx, int yy)
{
	if (nums == 4)
	{
		C++;
		//GET_MAX(anwser, sum * sum);
		//Print_Result(result, 8);
		if (anwser < sum * sum)
		{
			Copy_Arr(result_max, result, 8);
			anwser = sum * sum;
		}
		return;
	}

	//DFS
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

			Copy_DD(Type(xx, yy));
			visited[x][y] = false;
			nums--;
			sum -= data[x][y];
		}
	}
}

void Solve()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			visited[i][j] = true;
			sum += data[i][j];
			result[0] = i;
			result[1] = j;
			Try_Cell(i, j);
			Try_Cell2(i,j);
			Reset();
		}
	}
}

void Try_Cell2(int xx, int yy)
{
	Copy_DD(Type(xx, yy));
	for (int i = 0; i < 2; i++) // 2 chu Y
	{
		int sum = data[xx][yy];
		int c = 0;
		for (int j = i; j < 12; j += 4)
		{
			int x = xx + DD[j];
			int y = yy + DD[j + 1];
			if (Is_Safe2(x, y))
			{
				c++;
				sum += data[x][y];
			}
		}
		if (c == 3 && anwser < sum * sum)
		{
			anwser = sum * sum;
			Set_Result(xx,yy,xx + DD[i],yy + DD[i + 1],xx + DD[i + 4],yy + DD[i + 5],xx + DD[i + 8],yy + DD[i + 9]);
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

void Print_Result(int *arr, int length)
{
	for (int i = 0; i < length; i += 2)
	{
		cout << data[result_max[i]][result_max[i + 1]] << "\t";
	}
	cout << endl;
}

inline void Set_Result(int x0, int y0,int x1, int y1,int x2, int y2,int x3, int y3)
{
	result_max[0] = x0;
	result_max[1] = y0;
	result_max[2] = x1;
	result_max[3] = y1;
	result_max[4] = x2;
	result_max[5] = y2;
	result_max[6] = x3;
	result_max[7] = y3;
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
	if (x < 0 || y < 0 || x >= n || y >= m || visited[x][y] )
	{
		return false;
	}
	return true;
}

inline bool Is_Safe2(int x, int y)
{
	if (x < 0 || y < 0 || x >= n || y >= m )
	{
		return false;
	}
	return true;
}

void Init()
{
	cin >> m >> n;
	max2 = new Max2*[n];
	max3 = new Max3*[n];
	max4 = new Max4*[n];
	data = new int*[n];
	visited = new bool*[n];
	for (int i = 0; i < n; i++)
	{
		max2[i] = new Max2[m];
		max3[i] = new Max3[m];
		max4[i] = new Max4[m];
		data[i] = new int[m];
		visited[i] = new bool[m];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> data[i][j];
			visited[i][j] = false;
		}
	}

	anwser = 0;
	nums = 1;
	sum = 0;
	C = 0;
}

void Free()
{
	for (int i = 0; i < n; i++)
	{
		delete[] max2[i];
		delete[] max3[i];
		delete[] max4[i];
		delete[] data[i];
		delete[] visited[i];
	}
	delete[] max2;
	delete[] max3;
	delete[] max4;
	delete[] data;
	delete[] visited;
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

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool Point::Equal(Point p)
{
	if (this->x != p.x || this->y != p.y)
	{
		return false;
	}
	return true;
}

void Point::Set(int x, int y)
{
	this->x = x;
	this->y = y;
}

Max2::Max2()
{
	this->v = 0;
	this->p1 = Point();
}

Max2::Max2(Point p1, int v)
{
	this->p1 = p1;
	this->v = v;
}

Max3::Max3()
{
	this->v = 0;
	this->p1 = Point();
	this->p2 = Point();
}

Max3::Max3(Point p1, Point p2, int v)
{
	this->p1 = p1;
	this->p2 = p2;
	this->v = v;
}

Max4::Max4()
{
	this->v = 0;
	this->p1 = Point();
	this->p2 = Point();
	this->p3 = Point();
}

Max4::Max4(Point p1, Point p2, Point p3, int v)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->v = v;
}

void Max2::Set_Value(Point p1, int v)
{
	this->p1 = p1;
	this->v = v;
}

void Max3::Set_Value(Point p1, Point p2, int v)
{
	this->p1 = p1;
	this->p2 = p2;
	this->v = v;
}

void Max4::Set_Value(Point p1, Point p2, Point p3, int v)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->v = v;
}

void Dynamic_Max()
{
	Dynamic_Max2();
	Dynamic_Max3();
	Dynamic_Max4();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if(anwser < max4[i][j].v * max4[i][j].v)
			{
				anwser = max4[i][j].v * max4[i][j].v;
				Set_Result(i,j,max4[i][j].p3.x,max4[i][j].p3.y,max4[i][j].p2.x,max4[i][j].p2.y,max4[i][j].p1.x,max4[i][j].p1.y);
			}
		}
	}
}

void Dynamic_Max2()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			max2[i][j].v = data[i][j];
			Copy_DD(Type(i, j));
			for (int ii = 0; ii < 12; ii += 2)
			{
				int x = i + DD[ii];
				int y = j + DD[ii + 1];
				if (Is_Safe2(x,y))
				{
					if (max2[i][j].v < (data[i][j] + data[x][y]))
					{
						max2[i][j].Set_Value(Point(x,y),data[i][j] + data[x][y]);
					}
				}
			}
		}
	}
}

void Dynamic_Max3()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			max3[i][j].v = data[i][j];
			Copy_DD(Type(i, j));
			for (int ii = 0; ii < 12; ii += 2)
			{
				int x = i + DD[ii];
				int y = j + DD[ii + 1];
				if (Is_Safe2(x,y))
				{
					if (max3[i][j].v < (max2[x][y].v  + data[i][j]) && !max2[x][y].p1.Equal(Point(i,j)))
					{
						max3[i][j].Set_Value(Point(max2[x][y].p1.x,max2[x][y].p1.y), Point(x,y),max2[x][y].v + data[i][j]);
					}

					if (max3[i][j].v < (max2[i][j].v + data[x][y]) && !max2[i][j].p1.Equal(Point(x,y)))
					{
						max3[i][j].Set_Value(Point(max2[i][j].p1.x,max2[i][j].p1.y), Point(x,y),max2[i][j].v + data[x][y]);
					}
				}
			}
		}
	}
}

void Dynamic_Max4()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			max4[i][j].v = data[i][j];
			Copy_DD(Type(i, j));
			for (int ii = 0; ii < 12; ii += 2)
			{
				int x = i + DD[ii];
				int y = j + DD[ii + 1];
				if (Is_Safe2(x,y))
				{
					if (max4[i][j].v < data[i][j] + max3[x][y].v && !max3[x][y].p1.Equal(Point(i,j)) && !max3[x][y].p2.Equal(Point(i,j)))
					{
						max4[i][j].Set_Value(Point(max3[x][y].p1.x,max3[x][y].p1.y), Point(max3[x][y].p2.x,max3[x][y].p2.y), Point(x,y),data[i][j] + max3[x][y].v);
					}
					if (max4[i][j].v < data[x][y] + max3[i][j].v && !max3[i][j].p1.Equal(Point(x,y)) && !max3[i][j].p2.Equal(Point(x,y)))
					{
						max4[i][j].Set_Value(Point(max3[i][j].p1.x,max3[i][j].p1.y), Point(max3[i][j].p2.x,max3[i][j].p2.y), Point(x,y),data[i][j] + max3[x][y].v);
					}
				}
			}
		}
	}
}

void Print_Max2()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << max2[i][j].v << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Print_Max3()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << max3[i][j].v << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void Print_Max4()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << max4[i][j].v << "\t";
		}
		cout << endl;
	}
	cout << endl;
}