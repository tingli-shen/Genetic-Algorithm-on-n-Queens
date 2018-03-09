#include <iostream>
#include <array>
#include<vector>
#include <cstdlib>
#include <ctime>
using namespace std;
#define N 8
#define K 4
void show(array<array<int, N>, N> a);
void show2(array<array<bool, N>, N> a);
class Nqueen
{
public:
	array<array<bool, N>, N> queen;
	array<int, N> A;
	int per;
	int collide;
	int y;
	int x;
};
Nqueen board[K],select[K],a,b;
int A[4][8] = { { 1,3,6,3,7,4,4,1 } ,{ 2,1,6,4,1,3,0,0 } ,{ 1,3,3,0,4,0,1,3 } ,{ 2,1,4,3,2,1,0,2 } };
vector<Nqueen> stop;
bool found;
int nodes;
int son;
int ans;
void boardNum();
void min();
int collide(Nqueen &board, int);
void clear(Nqueen &board, int);

int main()
{
	nodes = 0;
	found = false;
	srand(time(0));
	int i, j, k, sum = 0, times = 0, time = 0,diff,mu;
	double;
	for (j = 0; j < K; j++)
	{
		for (i = 0; i < N; i++)
		{
			board[j].A[i] = rand() % N;
			board[j].queen[i][board[j].A[i]] = true;
		}

		sum += 28 - collide(board[j], j);
		board[j].collide = sum;
		//cout << 28 - collide(board[j],j)<<endl;
	}
	while (!found) {
		sum = 0;
		nodes++;
		for (j = 0; j < K; j++)
		{
			sum += 28 - collide(board[j], j);
			board[j].collide = sum;
			//cout << 28 - collide(board[j],j)<<endl;
		}
		
		if (found)
		{
			for (i = 0; i < N; i++)
				cout << board[ans].A[i]+1<<" ";
			cout << " / total nodes=" << nodes;
			break;
		}
		for (j = 0; j < K; j++)
		{
			board[j].per = board[j].collide * 100 / sum;
		}
		for (j = 0; j < K; j++)
		{
			son = rand() % 100 + 1;
			//cout << son << endl;
			if (son <= board[0].per)
				select[j] = board[0];
			else if (son > board[0].per&&son <= board[1].per)
				select[j] = board[1];
			else if (son > board[1].per&&son <= board[2].per)
				select[j] = board[2];
			else if (son > board[2].per&&son <= 100)
				select[j] = board[3];

		}
		for (j = 0; j < 4; j += 2)
		{
			son = rand() % (N - 2) + 1;
			a = select[j];
			b = select[j + 1];
			for (i = son; i < N; i++)
			{
				select[j].queen[i][select[j].A[i]] = false;
				select[j].A[i] = b.A[i];
				select[j].queen[i][select[j].A[i]] = true;
			}
			for (i = son; i < N; i++)
			{
				select[j + 1].queen[i][select[j + 1].A[i]] = false;
				select[j + 1].A[i] = a.A[i];
				select[j + 1].queen[i][select[j + 1].A[i]] = true;
			}
		}
		for (j = 0; j < K; j++)
		{
			son = rand() % N;
			mu = rand() % N;
			select[j].queen[son][select[j].A[son]] = false;
			select[j].A[son] = mu;
			select[j].queen[son][select[j].A[son]] = true;

		}
		for (j = 0; j < K; j++)
		{
			board[j] = select[j];
		}/*
		for (j = 0; j < K; j++) {
			for (i = 0; i < N; i++)
				cout << select[j].A[i];
			cout << endl;
		}*/
	}
	

	return 0;	
}
void clear(Nqueen &board, int n)
{
	int i;
	//srand(time(0));

	for (i = 0; i < N; i++)
	{
		board.queen[i][A[n][i]] = false;
		A[n][i] = rand() % N;
		board.queen[i][A[n][i]] = true;
	}
	//stop[n].clear();
}

void show(array<array<int, N>, N> a)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			cout << a[j][i]<<" ";
		cout << endl;
	}
	cout << endl;
}
void show2(array<array<bool, N>, N> a)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			cout << a[j][i] << " ";
		cout << endl;
	}
	cout << endl;
}
int collide(Nqueen &board, int n)
{
	int i, j, sum = 0, x, y, locate = 1;
	for (i = 0; i < N; i++)
	{
		x = i;
		y = board.A[i];
		for (j = x + 1; j < N; j++)
		{
			if (board.queen[j][y])
				sum++;
		}
		for (j = x + 1; j < N; j++)
		{
			if (y + locate < N&&board.queen[j][y + locate] == true)
				sum++;
			if (y - locate >= 0 && board.queen[j][y - locate] == true)
				sum++;
			locate++;
		}
		locate = 1;
		//show(board.queen);
		//cout << sum;

	}
	if (sum == 0)
		found = true,ans=n;
	return sum;
}