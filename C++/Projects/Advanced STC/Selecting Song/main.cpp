#include <iostream>
#include <conio.h>

#define GET_MAX(x,y) if ((x) < (y)) (x = y);
#define MIN(x,y) (x < y) ? (x) : (y)


using namespace std;

int n, sum, m;
int *data, *result;

void Init();
void Print();
int Sum(int *arr, int length);
void Swap(int *arr, int i, int j);
void Sort(int *arr, int length, int left, int right);
void Solve();
void Free();

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		Init();

		Solve();

		cout << "Case #" << tc + 1 << endl << result[m] << endl;
	}

	getch();
	return 0;
}

void Solve()
{
	m = MIN(sum, Sum(data,n));
	for (int i = 0; i < n; i++)
	{
		for (int j = data[i]; j <= m; j++)
		{
			GET_MAX(result[j], result[j-data[i]] + data[i]);
		}
	}
}

void Init()
{
	cin >> sum >> n;
	data = new int[n];
	result = new int[sum + 1];
	for (int i = 0; i < n; i++)
	{
		cin >> data[i];
	}
	for (int i = 0; i < sum + 1; i++)
	{
		result[i] = 0;
	}
}

int Sum(int *arr, int length)
{
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += arr[i];
	}
	return sum;
}

void Free()
{
	delete[] data;
	delete[] result;
}

void Sort(int *arr, int length, int left, int right)
{
	if (left < right)
	{
		int pivot = (left + right) / 2;
		int i = left, j = right;
		while (arr[i] < arr[pivot])
		{
			i++;
		}
		while (arr[j] > arr[pivot])
		{
			j--;
		}
		Swap(arr,i,j);
		Sort(arr, length, i, pivot);
		Sort(arr, length, pivot, j);
	}
}

void Swap(int *arr, int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void Print()
{
	for (int i = 0; i < n; i++)
	{
		cout << data[i] << "\t";
	}
	cout << endl;
}