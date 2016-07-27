/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/
#include <conio.h>
//#include <time.h>
 
#include <iostream>

using namespace std;

#define getMin(x, y) if(x > y) (x = y)
#define isSafe(x,y) ( x < 0 | y < 0 | x > 7 | y > 7) ? (false) : (true)
int Answer, N, startX, startY, minValue;
int dd[16] = { -2, -1, -2, 1, -1, -2, -1, 2, 1, -2, 1, 2, 2, -1, 2, 1 };
int arr[8][8]; //
bool visited[8][8]; // chessboard 8x8

void Recursive(int x, int y, int currCost, int horse);

int main(int argc, char** argv)
{
	int T, test_case;
	//clock_t start = clock();
	/*
	The freopen function below opens input.txt file in read only mode, and afterward,
	the program will read from input.txt file instead of standard(keyboard) input.
	To test your program, you may save input data in input.txt file,
	and use freopen function to read from the file when using cin function.
	You may remove the comment symbols(//) in the below statement and use it.
	Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	But before submission, you must remove the freopen function or rewrite comment symbols(//).
	*/	

	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Implement your algorithm here.
		The answer to the case will be stored in variable Answer.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		Answer = 0;
		cin >> startX >> startY >> N;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				arr[i][j] = 0;
				visited[i][j] = false;
			}
		}

		for (int i = 0; i < N; i++)
		{
			int tmpX, tmpY;
			cin >> tmpX >> tmpY;

			arr[tmpX-1][tmpY-1] = 1;
		}

		arr[startX-1][startY-1] = 2;
		minValue = 25;
		Recursive(startX - 1, startY - 1, 0, 0);

		Answer = minValue;
		// Print the answer to standard output(screen).
		std::cout << "Case #" << test_case+1 << endl ;
		std::cout << Answer << endl;
	}

	//cout << "Time run : "<< (float)(clock() - start) / CLOCKS_PER_SEC << endl;
	getch();
	return 0;//Your program should return 0 on normal termination.
}

void Recursive(int x, int y, int currCost, int horse) {
	if (horse == 3) {
		getMin(minValue,currCost);
		return;
	}
	if (currCost >= minValue) {
		return;
	}
	// 1
	if (x >= 1 && y >= 2) {
		if (!visited[x - 1][y - 2])
		{
			visited[x - 1][y - 2] = true;
			if (arr[x - 1][y - 2] == 1)
			{
				Recursive(x - 1, y - 2, currCost + 1, horse + 1);
			}else
			{
				Recursive(x - 1, y - 2, currCost + 1, horse);
			}
			visited[x - 1][y - 2] = false;
		}
	}
	// 2
	if (x >= 1 && y < 6) {
		if (!visited[x - 1][y + 2])
		{
			visited[x - 1][y + 2] = true;
			if (arr[x - 1][y + 2] == 1)
			{
				Recursive(x - 1, y + 2, currCost + 1, horse + 1);
			}else
			{
				Recursive(x - 1, y + 2, currCost + 1, horse);
			}
			visited[x - 1][y + 2] = false;
		}
	}
	// 3
	if (x >= 2 && y >= 1) {
		if (!visited[x - 2][y - 1])
		{
			visited[x - 2][y - 1] = true;
			if (arr[x - 2][y - 1] == 1)
			{
				Recursive(x - 2, y - 1, currCost + 1, horse + 1);
			}else
			{
				Recursive(x - 2, y - 1, currCost + 1, horse);
			}
			visited[x - 2][y - 1] = false;
		}
	}
	// 4
	if (x >= 2 && y < 7) {
		if (!visited[x - 2][y + 1])
		{
			visited[x - 2][y + 1] = true;
			if (arr[x - 2][y + 1] == 1)
			{
				Recursive(x - 2, y + 1, currCost + 1, horse + 1);
			}else
			{
				Recursive(x - 2, y + 1, currCost + 1, horse);
			}
			visited[x - 2][y + 1] = false;
		}

	}
	// 5
	if (x < 7 && y < 6) {
		if (!visited[x + 1][y + 2])
		{
			visited[x + 1][y + 2] = true;
			if (arr[x + 1][y + 2] == 1)
			{
				Recursive(x + 1, y + 2, currCost + 1, horse + 1);
			}else
			{
				Recursive(x + 1, y + 2, currCost + 1, horse);
			}
			visited[x + 1][y + 2] = false;
		}
	}
	// 6
	if (x < 7 && y >= 2) {
		if (!visited[x + 1][y - 2])
		{
			visited[x + 1][y - 2] = true;
			if (arr[x + 1][y - 2] == 1)
			{
				Recursive(x + 1, y - 2, currCost + 1, horse + 1);
			}else
			{
				Recursive(x + 1, y - 2, currCost + 1, horse);
			}
			visited[x + 1][y - 2] = false;
		}
	}
	// 7
	if (x < 6 && y < 7) {
		if (!visited[x + 2][y + 1])
		{
			visited[x + 2][y + 1] = true;
			if (arr[x + 2][y + 1] == 1)
			{
				Recursive(x + 2, y + 1, currCost + 1, horse + 1);
			}else
			{
				Recursive(x + 2, y + 1, currCost + 1, horse);
			}
			visited[x + 2][y + 1] = false;
		}
	}
	// 8
	if (x < 6 && y >= 1) {
		if (!visited[x + 2][y - 1])
		{
			visited[x + 2][y - 1] = true;
			if (arr[x + 2][y - 1] == 1)
			{
				Recursive(x + 2, y - 1, currCost + 1, horse + 1);
			}else
			{
				Recursive(x + 2, y - 1, currCost + 1, horse);
			}
			visited[x + 2][y - 1] = false;
		}
	}
}