using namespace std;

struct Cell {
	double Value = NULL; //�������� ������ ������
	double PT = NULL; //����������
	bool isCheckedAlready = false; //���� �������� ������
	bool isUsedOnCycle = false; //���� ������� � ����� ������������
	bool isMinus_PT = false; //���� ������������� �����
	Cell()
	{}

	Cell(double aa, double bb, bool cc, bool dd)
	{
		Value = aa;
		PT = bb;
		isCheckedAlready = cc;
		isUsedOnCycle = dd;
	}
};

int VERT_M = 3; //���-�� ����� �� ���������
int HORZ_M = 4; //���-�� ����� �� �����������

Cell **CELLS_TABLE; //������ �����
int *U;
int *V;

