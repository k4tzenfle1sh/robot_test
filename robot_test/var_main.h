using namespace std;

struct Cell {
	double Value = NULL; //�������� ������ ������
	double PT = NULL; //����������
	bool isCheckedAlready = false; //���� �������� ������
	bool isUsedOnCycle = false; //���� ������� � ����� ������������
	bool isMinus_PT = true; //���� ������������� �����
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

struct WayCell{
	int i = NULL; //���������� ������
	int j = NULL; //���������� �������
	int iteration; //�������� �������� �� �����
	WayCell()
	{}

	WayCell(int aa, int bb, int cc)
	{
		i = aa;
		j = bb;
		iteration = cc;

	}
};

int VERT_M = 3; //���-�� ����� �� ���������
int HORZ_M = 4; //���-�� ����� �� �����������
int min = INT_MIN;
int A_BASIC_i, A_BASIC_j; //���������� �������� ����� ������

Cell **CELLS_TABLE; //������ �����
vector <WayCell> WAY; //������ ������ ���� ������

WayCell *SAVETHEWAY;

int *U;
int *V;


