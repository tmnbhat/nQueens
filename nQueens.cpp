#include <iostream>
#include <cstdlib>
#include <ctime>
// Goal is to have n queens placed in an nxn board

using namespace std;

int n = 10;
int queenPos[10];		//index represents column number, number stored represents row number. (each column has exactly one queen)

void qInit(int n){
	for (int idx = 0; idx < n; idx++) {
		queenPos[idx] = rand() % n;
		//cout << queenPos[i] << '\n';
	}
}

int calWeight(int N, int column) {	//only calculates weight corresponding to queen present in column 'c'. 
	int weight = 0, idx = 0;
	for (idx = 1; column - idx >= 0; idx++) {	//checks conflict on coresponding diagonals and rows ON THE LEFT.
		if (queenPos[column - idx] == queenPos[column] - idx)
			weight++;
		if (queenPos[column - idx] == queenPos[column] + idx)
			weight++;
		if (queenPos[column - idx] == queenPos[column])
			weight++;
	}
	for (idx = 1; column + idx < N; idx++) {	//checks conflict on coresponding diagonals and rows ON THE RIGHT.
		if (queenPos[column + idx] == queenPos[column] + idx)
			weight++;
		if (queenPos[column + idx] == queenPos[column] - idx)
			weight++;
		if (queenPos[column + idx] == queenPos[column])
			weight++;
	}
	return weight;
}

int minmizeWeight(int N) {
	int row, column, weightBuff = 10000, rowIdeal, iter, loopWeight = 0, innerLoopWeight, totalWeight = 1;
	for (iter = 0; ((iter < N) && (totalWeight > 0)) || iter < 5; iter++) {
		//cout << totalWeight << '\n';
		loopWeight = 0;
		for (column = 0; column < N; column++) {
			weightBuff = 10000;			//resets at the beg. of each column.
			for (row = 0; row < N; row++) {
				queenPos[column] = row;
				innerLoopWeight = calWeight(N, column);
				//cout << innerLoopWeight << '\n';
				if ((innerLoopWeight) <= weightBuff) {
					weightBuff = innerLoopWeight;
					rowIdeal = row;
				}
			}
			queenPos[column] = rowIdeal;
			loopWeight += weightBuff;
		}
		totalWeight = loopWeight;
	}
	return iter;
}

int nQueens(int n) {
	srand((unsigned)time(0));
	int iter = n;
	for (int i = 0; iter >= n; i++) {
		qInit(n);
		iter = minmizeWeight(n);
	}
	return iter;
}

int main(){
	int iter = nQueens(n);
	for (int idx = 0; idx < n; idx++)
		cout <<'\t'<< queenPos[idx] << '\n';
	return 0;
}