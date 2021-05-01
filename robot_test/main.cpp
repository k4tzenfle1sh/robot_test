/*������ ������ �� �����-������ ����� ��� ������������ ������ ����� �� � ���
������ 1.0.1.��.�����
���� �� ������� */

#include <iostream>
#include <conio.h>
#include <cmath>
#include <vector>
#include <ctime>
#include "var_main.h"

using namespace std;

bool checkCell(Cell **CELLS_TABLE, vector <WayCell> WAY, int *i, int *j, int iteration) {
	if (!CELLS_TABLE[*i][*j].isCheckedAlready || !CELLS_TABLE[*i][*j].isUsedOnCycle) { //���� ������ ����� ����� �� �������������
		if (!isnan(CELLS_TABLE[*i][*j].Value)) { //� ��� ����� � ���� ��������, ��
			iteration++; //���������� ��� ��������
			CELLS_TABLE[*i][*j].isCheckedAlready = true; //������ ���� �������� ������
			CELLS_TABLE[*i][*j].isUsedOnCycle = true; //������ ���� ������� �����
			WAY.push_back(WayCell(*i, *j, iteration)); //����������
			if (iteration % 2 == 0) //���� ������
				CELLS_TABLE[*i][*j].isMinus_PT = false; //�� ���� �� �����
			else
				CELLS_TABLE[*i][*j].isMinus_PT = true; //����� - �����
			return true;
		}
		else { //���� ����� ��������� ������, ��
			CELLS_TABLE[*i][*j].isCheckedAlready = true; //�� ������ ����� ���� �������� ����� ������������ ������
		}
	}
	else
		return false; //���� ��� ��������� ����� - ���� ������
}

bool findway(Cell **CELLS_TABLE, vector <WayCell> WAY, int VERT_M, int HORZ_M, int A_i, int A_j, int A_BASIC_i, int A_BASIC_j, int iteration, bool isCycleIsOver, bool isVerticalSearch) {
	int *i_ptr, int *j_ptr; //��������� �� i-e, j-e
	int *A_Find; //��������� �� ���������� �������� �����, ���� ������ �� i, ���� �� j
	int *LIMIT; //��������� �� ����������� ������� ������/�������
	int A; //��� ������
	int *A_state, *A_state_from; //��������� �� �������� �������� ������� i/j � ��������
	int *A_check_valid; //��������� �� �������� ���������� ������� � ��������
	bool ifCheckedisTrue = false; //

	if (isVerticalSearch) { //���� ���� �� ���������, ��
		A_Find = &A_i; //���������� �������� ���� i-e
		LIMIT = &HORZ_M; // ������������ �� ��������� (��������, ��� ��������, �� ��� ���� ������� ��� ��-�� ����� �����

		i_ptr = &A; //��������� �� ����� ����� �� i-�� ���� ��������� ������
		j_ptr = &A_j; //����� ��������� �� j-� ���� ������� ������ j-��

		A_check_valid = &A_BASIC_i; //��������� �� i-�� ������

		A_state = &A_j; //� ��������� �������� �� j-��, ��� �� ������ �� ������
		A_state_from = &A_BASIC_j;

	}
	//�� j-�� ��� ����� ��������, ������ ��������, ���� ������ ��� ������
	else {
		A_Find = &A_j;
		LIMIT = &VERT_M;

		i_ptr = &A_i;
		j_ptr = &A;

		A_check_valid = &A_BASIC_j;

		A_state = &A_i;
		A_state_from = &A_BASIC_i;
	}


	for (A = *A_Find - 1;; A--) { //���� �� ������ ������-��������� ����, ���� � ����� [0;0]
		if (A == *A_check_valid && *A_state == *A_state_from) { //���� ���������� ������� ������ � ������� �������
			if (iteration > 0) { //� ���� �������� �� ������� ������
				isCycleIsOver = true; //�� ���� ��������, ���� �����
				return true;
			}
			else { //����� ����� ������� ������, ��� ����� ����� �� �����, ���
				isCycleIsOver = true;
				return false;
			}
		}
		else if (A == *A_Find) { //���� �� ��������� � ����� ������, �� �� �������
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
	int A_i, A_j; //���������� ���������� �����
	int iteration = 0; //���������� ������� ��������
	bool isCycleIsOver = false;
	bool isVerticalSearch;

	//������� �������� �����
	A_i = A_BASIC_i;
	A_j = A_BASIC_j;

	WAY.push_back(WayCell(A_i, A_j, iteration)); //������ � ���� ������ ���
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
	//cin >> VERT_M >> HORZ_M; ����� ����
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