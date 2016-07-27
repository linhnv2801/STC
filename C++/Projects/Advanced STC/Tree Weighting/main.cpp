#include <cstdio>
#include <conio.h>
#include <iostream>
#include <cstring>

using namespace std;

unsigned long freq[100005];
unsigned long weight[100005];
unsigned long array[100004][3];

const unsigned long MOD = 1000000007;

int main(int argc, char** argv)
{
	int tc, T;
	int N;

	freopen("sample_input.txt", "r", stdin);

	cin >> T;
	for(tc = 0; tc < T; tc++)
	{
		int i;
		int a,b,c;
		unsigned long sum = 0;

		cin >> N;
		memset(array,0,sizeof(array));
		memset(freq,0,sizeof(freq));
		memset(weight,0,sizeof(weight));

		for(i = 0; i < N-1; i++){
			cin >> a >> b >> c;
			array[i][0] = a;
			array[i][1] = b;
			array[i][2] = c;

			freq[a-1]++;
			freq[b-1]++;
		}
		for(i = 0; i < N; i++){
			weight[i] = 1;
		}
		while(1){
			int flag = 0;
			unsigned long temp = 0;
			for(i = 0; i < N-1; i++){
				if((freq[array[i][0]-1] == 1 && freq[array[i][1]-1] != 0)
					|| (freq[array[i][1]-1] == 1 && freq[array[i][0]-1] != 0)){
						if(freq[array[i][0]-1] == 1){
							temp = (weight[array[i][0]-1] * array[i][2] )%MOD;
							sum = (sum + temp*weight[array[i][1]-1])%MOD;
							weight[array[i][1]-1] = (weight[array[i][1]-1] + temp)%MOD;
						}else if(freq[array[i][1]-1] == 1){
							temp = (weight[array[i][1]-1] * array[i][2])%MOD;
							sum = (sum + temp * weight[array[i][0]-1])%MOD;
							weight[array[i][0]-1] = (temp + weight[array[i][0]-1])%MOD;
						}
						freq[array[i][0]-1]--;
						freq[array[i][1]-1]--;
						flag = 1;
				}
			}
			if(flag == 0){
				break;
			}
		}
		cout << sum <<endl;
	}

	getch();
	return 0;//Your program should return 0 on normal termination.
}
