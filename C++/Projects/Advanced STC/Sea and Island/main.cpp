#include <iostream>
#include <conio.h>

#include "Point.h"

using namespace std;

int N, M;
int **data;
bool **visit;

point *head, *tail, *tmp;
point2 *list;

struct Anwser
{
	int sum_sea;
	int sum_island;
	Anwser();
	Anwser(int sum_sea, int sum_island);
} *anwser;

void Print();
void Init();
void Input();
void Free();
void BFS(int xx, int yy);

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		cin >> N >> M;
		Init();
		Input();
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if ( !visit[i][j])
				{
					BFS(i,j);
				}
			}
		}

		cout << "Case #" << tc + 1 << endl;
		cout << anwser->sum_sea << " " << anwser->sum_island << endl;
		Free();
	}

	getch();
	return 0;
}

void BFS(int xx, int yy)
{
	if (data[xx][yy])
	{
		anwser->sum_island++;
	}else
	{
		anwser->sum_sea++;
	}
	Free(head);
	head = nullptr;

	AddQueue(new point(xx,yy));

	while (head != nullptr)
	{
		int l = Length(head);
		for (int i = 0; i < l; i++)
		{
			int x = head->x;
			int y = head->y;

			if (x - 1 >= 0 && !visit[x-1][y] && data[x-1][y] == data[x][y])
			{
				visit[x-1][y] = true;
				AddQueue(new point(x-1,y));
			}

			if (x + 1 < N && !visit[x+1][y] && data[x+1][y] == data[x][y])
			{
				visit[x+1][y] = true;
				AddQueue(new point(x+1,y));
			}

			if (y - 1 >= 0 && !visit[x][y-1] && data[x][y-1] == data[x][y])
			{
				visit[x][y-1] = true;
				AddQueue(new point(x,y-1));
			}

			if (y + 1 < M && !visit[x][y+1] && data[x][y+1] == data[x][y])
			{
				visit[x][y+1] = true;
				AddQueue(new point(x,y+1));
			}
			DeQueue();
		}

	}
}

Anwser::Anwser()
{
	this->sum_island = this->sum_sea = 0;
}

Anwser::Anwser(int sum_sea, int sum_island)
{
	this->sum_island = sum_island;
	this->sum_sea = sum_sea;
}

void Init()
{
	anwser = new Anwser();
	data = new int*[N];
	visit = new bool*[N];
	for (int i = 0; i < N; i++)
	{
		data[i] = new int[M];
		visit[i] = new bool[M];
	}
	head = NULL;
	tail = NULL;
}

void Input()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> data[i][j];
			visit[i][j] = false;
		}
	}
}

void Free()
{
	delete anwser;
	for (int i = 0; i < N; i++)
	{
		delete[] data[i];
		delete[] visit[i];
	}
	delete[] data; 
	delete[] visit;
	Free(head);
}

void Print()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
}

point::point(int x, int y)
{
	this->x = x;
	this->y = y;
	this->next = NULL;
}

point::point()
{
	this->x = 0;
	this->y = 0;
	this->next = NULL;
}

point2::point2()
{
	this->x = 0;
	this->y = 0;
}

point2::point2(int x, int y)
{
	this->x = x;
	this->y = y;
}

void AddQueue(point *add)
{
	if (head == NULL)
	{
		head = add;
		tail = add;
		head->next = tail;
		tail->next = NULL;
	}else
	{
		tail->next = add;
		tail = add;
	}
}

void DeQueue()
{
	if (head != NULL)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

void Free(point *head)
{
	if (head == NULL)
	{
		return;
	}
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

int Length(point *head)
{
	if (head == NULL)
	{
		return 0;
	}else
	{
		int sum = 1;
		tmp = head->next;
		while (tmp != NULL)
		{
			tmp = tmp->next;
			sum++;
		}
		return sum;
	}

}

