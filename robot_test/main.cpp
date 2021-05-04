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
		cout << "| " << i << " | " << WAY[i].i << " | " << WAY[i].j << " |" << endl;
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

void cleanMemory(Cell **CELLS_TABLE, WayCell *SAVETHEWAY, vector <WayCell> WAY, int HORZ_M, int VERT_M) {
	for (int i = 0; i < HORZ_M; i++) {
		for (int j = 0; j < VERT_M; j++) {
			if (CELLS_TABLE[i][j].isCheckedAlready == true) { //если ячейка как-то проверялась, то
				//затираем все к ебаной матери
				CELLS_TABLE[i][j].isCheckedAlready = false;
				CELLS_TABLE[i][j].isUsedOnCycle = false;
				CELLS_TABLE[i][j].isMinus_PT = true;
			}
		}
	}

	//удаляем массив памяти итерации
	delete [] SAVETHEWAY;

	//и затираем саму память цикла
	WAY.clear();

	/*
	Press
	F
	To
	Pay
	Respect
	*/
}
	

void replaceCycle(Cell **CELLS_TABLE, WayCell *SAVETHEWAY, vector <WayCell> WAY, int VERT_M, int HORZ_M) {
	int MIN = INT_MAX;
	//поиск минимального элемента
	for (int i = 0; i < WAY.size(); i++) { //зная точные i,j делаем явную подстановку в основную таблицу по каждому элементу 
		if (CELLS_TABLE[WAY[i].i][WAY[i].j].isUsedOnCycle && CELLS_TABLE[WAY[i].i][WAY[i].j].isMinus_PT == true) { //если ячейка действительна задействована и при этом минусовая, то
			if (CELLS_TABLE[WAY[i].i][WAY[i].j].Value <= MIN) //проверяем ее на маленькость
				MIN = CELLS_TABLE[WAY[i].i][WAY[i].j].Value; 
		}
	}

	//собсна, делаем перерасчет по минимальному элементу
	for (int i = 0; i < WAY.size(); i++) {
		if (CELLS_TABLE[WAY[i].i][WAY[i].j].isUsedOnCycle) {
			if (CELLS_TABLE[WAY[i].i][WAY[i].j].isMinus_PT == true) {
				CELLS_TABLE[WAY[i].i][WAY[i].j].Value = CELLS_TABLE[WAY[i].i][WAY[i].j].Value - MIN; //отрицательные нужно отнять
				if (CELLS_TABLE[WAY[i].i][WAY[i].j].Value == 0.0)
					CELLS_TABLE[WAY[i].i][WAY[i].j].Value = NAN;
			}
			else {
				if (!isnan(CELLS_TABLE[WAY[i].i][WAY[i].j].Value)) //главное, чтобы не NaN
					CELLS_TABLE[WAY[i].i][WAY[i].j].Value = CELLS_TABLE[WAY[i].i][WAY[i].j].Value + MIN; //а положительные, кто бы мог подумать, сложить
				else
					CELLS_TABLE[WAY[i].i][WAY[i].j].Value = 0.0 + MIN; //а иначе просто прибавим к нулю, как и должно быть
			}
		}
	}

	cleanMemory(CELLS_TABLE, SAVETHEWAY, WAY, HORZ_M, VERT_M); //цикл завершен, пора подчистить память и все флаги перерасчета
}

bool checkCell(Cell **CELLS_TABLE, int *i, int *j) {
	if ((!CELLS_TABLE[*i][*j].isCheckedAlready && !CELLS_TABLE[*i][*j].isUsedOnCycle) && !isnan(CELLS_TABLE[*i][*j].Value)) //если ячейка нигде никак не задействована
		return true; //то все гуд
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
			if ((iteration + 1) >= 4 && (iteration + 1) % 2 == 0) { //и если итерация не нулевая есесна
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
				SAVETHEWAY[0].i = *i_ptr; //сейвим i-e в массиве, шоб ниче никуда не съебнуло
				SAVETHEWAY[0].j = *j_ptr; //так же сейвим j-e

				CELLS_TABLE[*i_ptr][*j_ptr].isCheckedAlready = true; //выдаем флаг проверки ячейки
				CELLS_TABLE[*i_ptr][*j_ptr].isUsedOnCycle = true; //выдаем флаг вершины цикла

				
				if ((iteration+1) % 2 == 0) //если четная
					CELLS_TABLE[*i_ptr][*j_ptr].isMinus_PT = false; //то плюс на грань
				else
					CELLS_TABLE[*i_ptr][*j_ptr].isMinus_PT = true; //иначе - минус
				return true;
			}
			else {
				CELLS_TABLE[*i_ptr][*j_ptr].isCheckedAlready = true; //иначе просто выдаем флаг проверки ячейки
			}
		}
		if (A - 1 < 0) //если при попытке уйти на предыдущий элемент мы выйдем за пределы массива, то
			A = *LIMIT; //тупа присвоим пограничное значение оси
	}

}

void doRobot(Cell **CELLS_TABLE, WayCell *SAVETHEWAY, vector <WayCell> WAY, int VERT_M, int HORZ_M, int A_BASIC_i, int A_BASIC_j) {
	int A_i, A_j; //внутренние координаты точки
	int iteration = 0; //внутренний счетчик итераций
	bool isVerticalSearch = true; //на нулевой итерации будем идти всегда по вертикали
	bool check_cycle; //нужная хуйня

	bool isCycleIsOver[1]; //ебаный компилятор решил затирать все указатели после выполнения ф-ций, пришлось костылить
	isCycleIsOver[0] = false;

	//нулевая итерация пошла
	A_i = A_BASIC_i; //присваиваем коэффициенты i, j первой ячейки
	A_j = A_BASIC_j;
	showStep(iteration);
	findCell(CELLS_TABLE, A_i, A_j);
	isCheckedAlready(CELLS_TABLE, A_i, A_j);
	isUsedOnCycle(CELLS_TABLE, A_i, A_j);
	isMinusDropped(CELLS_TABLE, A_i, A_j);


	WAY.push_back(WayCell(A_i, A_j)); //вносим в путь первый шаг
	showStep(iteration);
	showVectorWAY(WAY);

	//выставляем все флаги
	CELLS_TABLE[A_i][A_j].isCheckedAlready = true;
	changeChecked(CELLS_TABLE, A_i, A_j);
	CELLS_TABLE[A_i][A_j].isUsedOnCycle = true;
	changeUsed(CELLS_TABLE, A_i, A_j);
	CELLS_TABLE[A_i][A_j].isMinus_PT = false;
	changeMinus(CELLS_TABLE, A_i, A_j);

	SAVETHEWAY = new WayCell[1]; //создаем единичный динам. массив, чтобы хранить значения после выполнения ф-ции

	//пошло говно по трубам
	check_cycle = findway(CELLS_TABLE, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);

	if (check_cycle && !isCycleIsOver[0]) { //если мы сразу же не обосрались, то 
		WAY.push_back(WayCell(SAVETHEWAY[0].i, SAVETHEWAY[0].j)); // вносим второй шаг
		iteration = WAY.size() - 1; //увеличиваем итерацию
		showStep(iteration);
		showVectorWAY(WAY);

		A_i = WAY[WAY.size() - 1].i; //присваиваем коэффициенты i, j найденной ячейки
		A_j = WAY[WAY.size() - 1].j;
		A_change();
		findCell(CELLS_TABLE, A_i, A_j);
		isCheckedAlready(CELLS_TABLE, A_i, A_j);
		isUsedOnCycle(CELLS_TABLE, A_i, A_j);
		isMinusDropped(CELLS_TABLE, A_i, A_j);

		while (1) { //пошли гонять лысого, эээ, то есть цикл
			showStep(iteration);
			if (iteration % 2 == 0) { //если итерация, то идем искать строго вверх
				isVerticalSearch = true;
				thereAreWe(isVerticalSearch);
				check_cycle = findway(CELLS_TABLE, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);
			}
			else { //иначе вдоль
				isVerticalSearch = false;
				thereAreWe(isVerticalSearch);
				check_cycle = findway(CELLS_TABLE, SAVETHEWAY, VERT_M, HORZ_M, A_i, A_j, A_BASIC_i, A_BASIC_j, iteration, isCycleIsOver, isVerticalSearch);
			}

			if (check_cycle && !isCycleIsOver[0]) { //если не обсер, то
				WAY.push_back(WayCell(SAVETHEWAY[0].i, SAVETHEWAY[0].j)); //вносим n-й	шаг
				showVectorWAY(WAY);
				A_i = WAY[WAY.size() - 1].i; //присваиваем коэффициенты i, j найденной ячейки
				A_j = WAY[WAY.size() - 1].j;
				A_change();
				findCell(CELLS_TABLE, A_i, A_j);
				isCheckedAlready(CELLS_TABLE, A_i, A_j);
				isUsedOnCycle(CELLS_TABLE, A_i, A_j);
				isMinusDropped(CELLS_TABLE, A_i, A_j);

				iteration = WAY.size() - 1; //увеличиваем итерацию
				continue;
			}
			if (!check_cycle && (isCycleIsOver[0] || !isCycleIsOver[0])) { //если по выбранной оси ничего нет, и при этом мы не вернулись к базисной точке 
				isCheckedAlready(CELLS_TABLE, A_i, A_j);
				CELLS_TABLE[A_i][A_j].isCheckedAlready = true; //даем флаг, что ячейка проверена и игнорим ее дальше
				changeChecked(CELLS_TABLE, A_i, A_j);

				isUsedOnCycle(CELLS_TABLE, A_i, A_j);
				if (CELLS_TABLE[A_i][A_j].isUsedOnCycle) //если мы уже успели ее включить в цикл, то затираем флаг цикла
					CELLS_TABLE[A_i][A_j].isUsedOnCycle = false;
				changeUsed(CELLS_TABLE, A_i, A_j);

				WAY.pop_back(); //удаляем неудавшийся элемент из памяти
				deleteWAY(); 
				showVectorWAY(WAY);

				if (WAY.size() > 0) { //если еще есть куда откатываться назад по вершинам, то 
					A_i = WAY[WAY.size() - 1].i; //таки возвращаемся
					A_j = WAY[WAY.size() - 1].j;

					A_change();
					findCell(CELLS_TABLE, A_i, A_j);
					isCheckedAlready(CELLS_TABLE, A_i, A_j);
					isUsedOnCycle(CELLS_TABLE, A_i, A_j);
					isMinusDropped(CELLS_TABLE, A_i, A_j);

					iteration = WAY.size() - 1; //свапаем итерацию на предыдующую
					continue;
				}

				else { //если некуда, то все, цикл для этой точки построить нельзя
					cout << "You cannot do anything else there. Go find another way, stalker" << endl;
					break;
				}

			}
			if (check_cycle && isCycleIsOver[0]) {
				/*SAVETHEWAY[0].i = A_BASIC_i;
				SAVETHEWAY[0].j = A_BASIC_j;
				WAY.push_back(WayCell(SAVETHEWAY[0].i, SAVETHEWAY[0].j));*/
				showVectorWAY(WAY);
				cout << "cycle is done. great job. \nit's wednesday my dudes." << endl;
				replaceCycle(CELLS_TABLE, SAVETHEWAY, WAY, VERT_M, HORZ_M);
				break;
			}
		}
	}
	else //иначе робот не нашел куда ставить вторую вершину по вертикали, скипаем
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
			if ((i == 0 && j == 0) || (i == 1 && j == 0) || (i == 1 && j == 1) || (i == 2 && j == 1) || (i == 2 && j == 2) || (i == 3 && j == 2))
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


	cout << "new shiiit~\n|------------------------------------|" << endl;
	for (int i = 0; i < HORZ_M; i++) {
		for (int j = 0; j < VERT_M; j++) {
			if (isnan(CELLS_TABLE[i][j].Value))
				cout << "| NN | " << CELLS_TABLE[i][j].PT << " |";
			else
				cout << "| " << CELLS_TABLE[i][j].Value << " | " << CELLS_TABLE[i][j].PT << " |";
			if (j + 1 >= VERT_M)
				cout << "| " << U[i] << " |";
		}
		cout << endl;
	}
	cout << "|------------------------------------|" << endl;
	for (int j = 0; j < VERT_M; j++) {
		cout << "| " << V[j] << " |";
	}
	cout << endl << "|------------------------------------|" << endl;

	_getch();
	return 0;
}