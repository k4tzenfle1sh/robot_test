/*ћодуль робота шо ходит-бродит ебать дл€ транспортной залупы ебать ее в рот
верси€ 1.0.1.до.пизды
маде бу димасек */

#include <iostream>
#include <conio.h>
#include <cmath>
#include <vector>
#include <ctime>
#include "var_main.h"

using namespace std;

bool checkCell(Cell **CELLS_TABLE, vector <WayCell> WAY, int *i, int *j, int iteration) {
	if (!CELLS_TABLE[*i][*j].isCheckedAlready || !CELLS_TABLE[*i][*j].isUsedOnCycle) { //если €чейка нигде никак не задействована
		if (!isnan(CELLS_TABLE[*i][*j].Value)) { //и еще имеет в себе значение, то
			iteration++; //прибавл€ем шаг итерации
			CELLS_TABLE[*i][*j].isCheckedAlready = true; //выдаем флаг проверки €чейки
			CELLS_TABLE[*i][*j].isUsedOnCycle = true; //выдаем флаг вершины цикла
			WAY.push_back(WayCell(*i, *j, iteration)); //запоминаем
			if (iteration % 2 == 0) //если четна€
				CELLS_TABLE[*i][*j].isMinus_PT = false; //то плюс на грань
			else
				CELLS_TABLE[*i][*j].isMinus_PT = true; //иначе - минус
			return true;
		}
		else { //если грань поставить нельз€, то
			CELLS_TABLE[*i][*j].isCheckedAlready = true; //то просто выдем флаг проверки чтобы игнорировать €чейку
		}
	}
	else
		return false; //если уже провер€ли ранее - скип клетки
}

bool findway(Cell **CELLS_TABLE, vector <WayCell> WAY, int VERT_M, int HORZ_M, int A_i, int A_j, int A_BASIC_i, int A_BASIC_j, int iteration, bool isCycleIsOver, bool isVerticalSearch) {
	int *i_ptr, int *j_ptr; //указатели на i-e, j-e
	int *A_Find; //указатель на предыдущее значение точки, либо пойдем по i, либо по j
	int *LIMIT; //указатель на размерность массива строки/столбца
	int A; //это индекс
	int *A_state, *A_state_from; //указатель на проверку текущего индекса i/j с базисным
	int *A_check_valid; //указатель на проверку найденного индекса с базисныи
	bool ifCheckedisTrue = false; //

	if (isVerticalSearch) { //если ищем по вертикали, то
		A_Find = &A_i; //предыдущее значение есть i-e
		LIMIT = &HORZ_M; // ограничиваем по вертикали (написано, что горизонт, но мне лень править код из-за одной хуйни

		i_ptr = &A; //указатель на поиск точки по i-му есть найденный индекс
		j_ptr = &A_j; //тогда указатель на j-й есть текущий индекс j-го

		A_check_valid = &A_BASIC_i; //провер€ем по i-му базису

		A_state = &A_j; //и реализуем проверку по j-му, там мы ничего не мен€ем
		A_state_from = &A_BASIC_j;

	}
	//по j-му все также работает, только наоборот, лень писать все заново
	else {
		A_Find = &A_j;
		LIMIT = &VERT_M;

		i_ptr = &A_i;
		j_ptr = &A;

		A_check_valid = &A_BASIC_j;

		A_state = &A_i;
		A_state_from = &A_BASIC_i;
	}


	for (A = *A_Find - 1;; A--) { //идем по методу северо-западного угла, идем в точку [0;0]
		if (A == *A_check_valid && *A_state == *A_state_from) { //если координаты текущей €чейки и базовой совпали
			if (iteration > 0) { //и если итераци€ не нулева€ есесна
				isCycleIsOver = true; //то цикл завершен, флаг выдан
				return true;
			}
			else { //иначе грань ставить некуда, все хуйн€ давай по новой, ћиш
				isCycleIsOver = true;
				return false;
			}
		}
		else if (A == *A_Find) { //если мы вернулись в точку поиска, но не базовую
			return false;
		}
		else {
				ifCheckedisTrue = checkCell(CELLS_TABLE, WAY, i_ptr, j_ptr, iteration);
				if (ifCheckedisTrue)
					return true;
				else;
		}
		if (A - 1 < 0)
			A = *LIMIT;
	}

}
void doRobot(Cell **CELLS_TABLE, vector <WayCell> WAY, int VERT_M, int HORZ_M, int A_BASIC_i, int A_BASIC_j) {
	int A_i, A_j; //внутренние координаты точки
	int iteration = 0; //внутренний счетчик итераций
	bool isCycleIsOver = false;
	bool isVerticalSearch;

	//нулева€ итераци€ пошла
	A_i = A_BASIC_i;
	A_j = A_BASIC_j;

	WAY.push_back(WayCell(A_i, A_j, iteration)); //вносим в путь первый шаг
	CELLS_TABLE[A_i][A_j].isCheckedAlready = true;
	CELLS_TABLE[A_i][A_j].isUsedOnCycle = true;
	CELLS_TABLE[A_i][A_j].isMinus_PT = false;
	bool first_check_cycle = findway(CELLS_TABLE, WAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);

	if (first_check_cycle && !isCycleIsOver) {
		while (1) {
			if (iteration % 2 != 0) {
				isVerticalSearch = true;
				findway(CELLS_TABLE, WAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);
			}
			else {
				isVerticalSearch = false;
				//findwayHORZ(CELLS_TABLE, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);
			}
		}
	}
	else
		cout << "You cannot do anything else there. Go find another way" << endl;
}

int main() {
	//cin >> VERT_M >> HORZ_M; нахуй надо
	srand(time(0));
	VERT_M = 3;
	HORZ_M = 4;
	CELLS_TABLE = new Cell *[HORZ_M];
	for (int i = 0; i < HORZ_M; i++) {
		CELLS_TABLE[i] = new Cell[VERT_M];
	}
	
	for (int i = 0; i < HORZ_M; i++) {
		for (int j = 0; j < VERT_M; j++) {
			if ((i == 0 && j == 0) || (i == 1 && j == 0) || (i == 1 && j == 1) || (i == 2 && j == 1) || (i == 2 && j == 2) || (i == 2 && j == 3))
				CELLS_TABLE[i][j].Value = double(1 + rand() % 99);
			else
				CELLS_TABLE[i][j].Value = NAN;
			CELLS_TABLE[i][j].PT = double(1+ rand() % 9);
		}
	}
	U = new int[HORZ_M];
	V = new int[VERT_M];
	U[0] = 0;
	V[0] = CELLS_TABLE[0][0].PT - U[0];
	U[1] = CELLS_TABLE[1][0].PT - V[0];
	V[1] = CELLS_TABLE[1][1].PT - U[1];
	U[2] = CELLS_TABLE[2][1].PT - V[1];
	V[2] = CELLS_TABLE[2][2].PT - U[2];
	U[3] = CELLS_TABLE[2][3].PT - V[2];

	cout << "|------------------------------------|" << endl;
	for (int i = 0; i < HORZ_M; i++) {
		for (int j = 0; j < VERT_M; j++) {
			if (isnan(CELLS_TABLE[i][j].Value))
				cout << "| NN | "<< CELLS_TABLE[i][j].PT<<" |";
			else
				cout << "| "<< CELLS_TABLE[i][j].Value <<" | " << CELLS_TABLE[i][j].PT << " |";
			if (j+1>= VERT_M)
				cout << "| "<< U[i]<<" |";
		}
		cout << endl;
	}
	cout << "|------------------------------------|" << endl;
	for (int j = 0; j < VERT_M; j++) {
		cout << "| " << V[j] << " |";
	}
	cout << endl << "|------------------------------------|" << endl;
	

	for (int i = 0; i < HORZ_M; i++) {
		for (int j = 0; j < VERT_M; j++) {
			if (isnan(CELLS_TABLE[i][j].Value)) {
				if (U[i] + V[j] > CELLS_TABLE[i][j].PT && (U[i] + V[j] - CELLS_TABLE[i][j].PT) > min) {
					min = U[i] + V[j] - CELLS_TABLE[i][j].PT;
					A_BASIC_j = j;
					A_BASIC_i = i;
				}

			}
			else;
		}
	}

	cout << min << "\t x = " << A_BASIC_i << " y = " << A_BASIC_j << endl;

	doRobot(CELLS_TABLE, WAY, VERT_M, HORZ_M, A_BASIC_i, A_BASIC_j);
	_getch();
	return 0;
}