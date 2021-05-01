/*Модуль робота шо ходит-бродит ебать для транспортной залупы ебать ее в рот
версия 1.0.1.до.пизды
маде бу димасек */

#include <iostream>
#include <conio.h>
#include <cmath>
#include <vector>
#include <ctime>
#include "var_main.h"

using namespace std;

/*bool checkCell(Cell **CELLS_TABLE, vector <WayCell> WAY, int *i, int *j, int iteration) {
	if (!CELLS_TABLE[*i][*j].isCheckedAlready || !CELLS_TABLE[*i][*j].isUsedOnCycle) { //если ячейка нигде никак не задействована
		if (!isnan(CELLS_TABLE[*i][*j].Value)) { //и еще имеет в себе значение, то
			iteration++; //прибавляем шаг итерации
			CELLS_TABLE[*i][*j].isCheckedAlready = true; //выдаем флаг проверки ячейки
			CELLS_TABLE[*i][*j].isUsedOnCycle = true; //выдаем флаг вершины цикла
			WAY.push_back(WayCell(*i, *j, iteration)); //запоминаем
			if (iteration % 2 == 0) //если четная
				CELLS_TABLE[*i][*j].isMinus_PT = false; //то плюс на грань
			else
				CELLS_TABLE[*i][*j].isMinus_PT = true; //иначе - минус
			return true;
		}
		else { //если грань поставить нельзя, то
			CELLS_TABLE[*i][*j].isCheckedAlready = true; //то просто выдем флаг проверки чтобы игнорировать ячейку
			return false;
		}
	}
	else
		return false; //если уже проверяли ранее - скип клетки
}*/

void findCell(Cell **CELLS_TABLE, int i, int j) {
	cout << "doRobot\tAlien" << ": find cell A[" << i << ", " << j << "] is " << CELLS_TABLE[i][j].Value << ", PT is " << CELLS_TABLE[i][j].PT << endl;
}

void isCheckedAlready(Cell **CELLS_TABLE, int i, int j) {
	cout << "doRobot\tAlien: is cell A[" << i << ", " << j << "] already checked by me?";
	if (CELLS_TABLE[i][j].isCheckedAlready) cout << "\tyes" << endl;
	else cout << "\tno" << endl;
}

void isUsedOnCycle(Cell **CELLS_TABLE, int i, int j) {
	cout << "doRobot\tAlien: is cell A[" << i << ", " << j << "] already used on cycle?";
	if (CELLS_TABLE[i][j].isUsedOnCycle) cout << "\tyes" << endl;
	else cout << "\tno" << endl;
}

void isMinusDropped(Cell **CELLS_TABLE, int i, int j) {
	cout << "doRobot\tAlien: is cell A[" << i << ", " << j << "] has minus point?";
	if (CELLS_TABLE[i][j].isMinus_PT) cout << "\tyes" << endl;
	else cout << "\tno" << endl;
}

void showStep(int iteration) {
	cout << "doRobot\tAlien: do the evolution on the " << iteration << " step" << endl;
}

void showVectorWAY(vector <WayCell> WAY) {
	cout << "doRobot\tAlien: i'll show you the WAY vector, look at this:" << endl;
	cout << "|-----------------|" << endl;
	cout << "| N | i | j | itr |" << endl;
	cout << "|-----------------|" << endl;
	for (int i = 0; i < WAY.size(); i++) {
		cout << "| " << i << " | " << WAY[i].i << " | " << WAY[i].j << " |  " << WAY[i].iteration << "  |" << endl;
	}
	cout << "|-----------------|" << endl;
}

void changeChecked(Cell **CELLS_TABLE, int i, int j) {
	cout << "doRobot\tAlien: bool isCheckedAlready for cell A[" << i << ", " << j << "] are changed, now";
	if (CELLS_TABLE[i][j].isCheckedAlready) cout << "\ttrue" << endl;
	else cout << "\tfalse" << endl;
}

void changeUsed(Cell **CELLS_TABLE, int i, int j) {
	cout << "doRobot\tAlien: bool isUsedOnCycle for cell A[" << i << ", " << j << "] are changed, now";
	if (CELLS_TABLE[i][j].isUsedOnCycle) cout << "\ttrue" << endl;
	else cout << "\tfalse" << endl;
}

void changeMinus(Cell **CELLS_TABLE, int i, int j) {
	cout << "doRobot\tAlien: bool isMinus_PT for cell A[" << i << ", " << j << "] are changed, now";
	if (CELLS_TABLE[i][j].isMinus_PT) cout << "\ttrue" << endl;
	else cout << "\tfalse" << endl;
}

void A_change() {
	cout << "doRobot\tAlien" << ": identity cell A is change successful" << endl;
}

void thereAreWe(bool isVerticalSearch) {
	cout << "doRobot\tAlien" << ": now we lookin' vertex from";
	if (isVerticalSearch)
		cout << " vertical axis" << endl;
	else
		cout << " horizontal axis" << endl;
}

void deleteWAY() {
	cout << "doRobot\tAlien" << ": previous cell from WAY is deleted now" << endl;;
}


bool checkCell(Cell **CELLS_TABLE, int *i, int *j) {
	if ((!CELLS_TABLE[*i][*j].isCheckedAlready && !CELLS_TABLE[*i][*j].isUsedOnCycle) && !isnan(CELLS_TABLE[*i][*j].Value)) //если ячейка нигде никак не задействована
		return true;
	else
		return false; //если уже проверяли ранее - скип клетки
}

bool findway(Cell **CELLS_TABLE, WayCell *SAVETHEWAY, int VERT_M, int HORZ_M, int A_i, int A_j, int A_BASIC_i, int A_BASIC_j, int iteration, bool isCycleIsOver[], bool isVerticalSearch) {
	int *i_ptr;
	int *j_ptr; //указатели на i-e, j-e
	int *A_Find; //указатель на предыдущее значение точки, либо пойдем по i, либо по j
	int *LIMIT; //указатель на размерность массива строки/столбца
	int A; //это индекс
	int *A_state, *A_state_from; //указатель на проверку текущего индекса i/j с базисным
	int *A_check_valid; //указатель на проверку найденного индекса с базисныи
	bool ifCheckedisTrue = false; //

	if (isVerticalSearch) { //если ищем по вертикали, то
		A_Find = &A_i; //предыдущее значение есть i-e
		LIMIT = &HORZ_M; // ограничиваем по вертикали (написано, что горизонт, но мне лень править код из-за одной хуйни

		A_check_valid = &A_BASIC_i; //проверяем по i-му базису

		A_state = &A_j; //и реализуем проверку по j-му, там мы ничего не меняем
		A_state_from = &A_BASIC_j;

	}
	//по j-му все также работает, только наоборот, лень писать все заново
	else {
		A_Find = &A_j;
		LIMIT = &VERT_M;

		A_check_valid = &A_BASIC_j;

		A_state = &A_i;
		A_state_from = &A_BASIC_i;
	}


	for (A = *A_Find - 1;; A--) { //идем по методу северо-западного угла, идем в точку [0;0]
		if (A < 0) {
			A = *LIMIT - 1; //если точка прямо сходу ушла в никуда 
		}
		if (A == *A_check_valid && *A_state == *A_state_from) { //если координаты текущей ячейки и базовой совпали
			if ((iteration+1) >= 4 && (iteration + 1)%2==0) { //и если итерация не нулевая есесна
				isCycleIsOver[0] = true; //то цикл завершен, флаг выдан
				return true;
			}
			else { //иначе грань ставить некуда, все хуйня давай по новой, Миш
				isCycleIsOver[0] = true;
				return false;
			}
		}
		else if (A == *A_Find) { //если мы вернулись в точку поиска, но не базовую
			return false;
		}
		else {
			if (isVerticalSearch) {
				i_ptr = &A; //указатель на поиск точки по i-му есть найденный индекс
				j_ptr = &A_j; //тогда указатель на j-й есть текущий индекс j-го
			}
			else {
				i_ptr = &A_i;
				j_ptr = &A;
			}
			if (checkCell(CELLS_TABLE, i_ptr, j_ptr)) {
				SAVETHEWAY[0].i = *i_ptr;
				SAVETHEWAY[0].j = *j_ptr;
				SAVETHEWAY[0].iteration = 1;

				CELLS_TABLE[*i_ptr][*j_ptr].isCheckedAlready = true; //выдаем флаг проверки ячейки
				CELLS_TABLE[*i_ptr][*j_ptr].isUsedOnCycle = true; //выдаем флаг вершины цикла

				
				if (iteration % 2 == 0) //если четная
					CELLS_TABLE[*i_ptr][*j_ptr].isMinus_PT = false; //то плюс на грань
				else
					CELLS_TABLE[*i_ptr][*j_ptr].isMinus_PT = true; //иначе - минус
				return true;
			}
			else {
				CELLS_TABLE[*i_ptr][*j_ptr].isCheckedAlready = true;
			}
		}
		if (A - 1 < 0)
			A = *LIMIT;
	}

}

void doRobot(Cell **CELLS_TABLE, WayCell *SAVETHEWAY, vector <WayCell> WAY, int VERT_M, int HORZ_M, int A_BASIC_i, int A_BASIC_j) {
	int A_i, A_j; //внутренние координаты точки
	int iteration = 0; //внутренний счетчик итераций
	bool isVerticalSearch = true;
	bool check_cycle;

	bool isCycleIsOver[1];
	isCycleIsOver[0] = false;
	
	//нулевая итерация пошла
	A_i = A_BASIC_i;
	A_j = A_BASIC_j;
	showStep(iteration);
	findCell(CELLS_TABLE, A_i, A_j);
	isCheckedAlready(CELLS_TABLE, A_i, A_j);
	isUsedOnCycle(CELLS_TABLE, A_i, A_j);
	isMinusDropped(CELLS_TABLE, A_i, A_j);


	WAY.push_back(WayCell(A_i, A_j, iteration)); //вносим в путь первый шаг
	showStep(iteration);
	showVectorWAY(WAY);
	CELLS_TABLE[A_i][A_j].isCheckedAlready = true;
	changeChecked(CELLS_TABLE, A_i, A_j);
	CELLS_TABLE[A_i][A_j].isUsedOnCycle = true;
	changeUsed(CELLS_TABLE, A_i, A_j);
	CELLS_TABLE[A_i][A_j].isMinus_PT = false;
	changeMinus(CELLS_TABLE, A_i, A_j);

	SAVETHEWAY = new WayCell[1];
	
	
	check_cycle = findway(CELLS_TABLE, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);
	WAY.push_back(WayCell(SAVETHEWAY[0].i, SAVETHEWAY[0].j, SAVETHEWAY[0].iteration));
	showStep(iteration);
	showVectorWAY(WAY);

	A_i = WAY[WAY.size() - 1].i;
	A_j = WAY[WAY.size() - 1].j;
	A_change();
	findCell(CELLS_TABLE, A_i, A_j);
	isCheckedAlready(CELLS_TABLE, A_i, A_j);
	isUsedOnCycle(CELLS_TABLE, A_i, A_j);
	isMinusDropped(CELLS_TABLE, A_i, A_j);

	iteration = WAY.size() - 1;
	
	if (check_cycle && !isCycleIsOver[0]) {
		while (1) {
			showStep(iteration);
			if (iteration % 2 == 0) {
				isVerticalSearch = true;
				thereAreWe(isVerticalSearch);
				check_cycle = findway(CELLS_TABLE, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);
			}
			else {
				isVerticalSearch = false;
				thereAreWe(isVerticalSearch);
				check_cycle = findway(CELLS_TABLE, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);	
			}

			if (check_cycle && !isCycleIsOver[0]) {
				WAY.push_back(WayCell(SAVETHEWAY[0].i, SAVETHEWAY[0].j, SAVETHEWAY[0].iteration));
				showVectorWAY(WAY);
				A_i = WAY[WAY.size() - 1].i;
				A_j = WAY[WAY.size() - 1].j;
				A_change();
				findCell(CELLS_TABLE, A_i, A_j);
				isCheckedAlready(CELLS_TABLE, A_i, A_j);
				isUsedOnCycle(CELLS_TABLE, A_i, A_j);
				isMinusDropped(CELLS_TABLE, A_i, A_j);

				iteration = WAY.size() - 1;
				//iteration = iteration + SAVETHEWAY[0].iteration;
				continue;
			}
			//if (WAY[WAY.size() - 1].iteration == iteration || (!check_cycle && (isCycleIsOver[0] || !isCycleIsOver[0]))) {
			if (!check_cycle && (isCycleIsOver[0] || !isCycleIsOver[0])) {
				//if (!check_cycle && !isCycleIsOver) {
				isCheckedAlready(CELLS_TABLE, A_i, A_j);
				CELLS_TABLE[A_i][A_j].isCheckedAlready = true;
				changeChecked(CELLS_TABLE, A_i, A_j);

				isUsedOnCycle(CELLS_TABLE, A_i, A_j);
				if (CELLS_TABLE[A_i][A_j].isUsedOnCycle)
					CELLS_TABLE[A_i][A_j].isUsedOnCycle = false;
				changeUsed(CELLS_TABLE, A_i, A_j);

				WAY.pop_back();
				deleteWAY();
				showVectorWAY(WAY);

				if (WAY.size() > 0) {
					A_i = WAY[WAY.size() - 1].i;
					A_j = WAY[WAY.size() - 1].j;

					A_change();
					findCell(CELLS_TABLE, A_i, A_j);
					isCheckedAlready(CELLS_TABLE, A_i, A_j);
					isUsedOnCycle(CELLS_TABLE, A_i, A_j);
					isMinusDropped(CELLS_TABLE, A_i, A_j);

					iteration = WAY.size() - 1;
					continue;
				}

				else {
					cout << "You cannot do anything else there. Go find another way, stalker" << endl;
					break;
				}
				
			}
			if (check_cycle && isCycleIsOver[0]) {
				SAVETHEWAY[0].i = A_BASIC_i;
				SAVETHEWAY[0].j = A_BASIC_j;
				SAVETHEWAY[0].iteration = 1;
				WAY.push_back(WayCell(SAVETHEWAY[0].i, SAVETHEWAY[0].j, SAVETHEWAY[0].iteration));
				showVectorWAY(WAY);
				cout << "cycle is done. great job. \nit's wednesday my dudes." << endl;
				break;
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

	cout << min << "\t i = " << A_BASIC_i << " j = " << A_BASIC_j << endl;
	cout << "| " << CELLS_TABLE[A_BASIC_i][A_BASIC_j].Value << " | " << CELLS_TABLE[A_BASIC_i][A_BASIC_j].PT << " |" << endl;

	doRobot(CELLS_TABLE, SAVETHEWAY, WAY, VERT_M, HORZ_M, A_BASIC_i, A_BASIC_j);
	_getch();
	return 0;
}