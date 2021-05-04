using namespace std;

struct Cell {
	double Value = NULL; //значение внутри €чейки
	double PT = NULL; //потанцевал
	bool isCheckedAlready = false; //флаг проверки €чейки
	bool isUsedOnCycle = false; //флаг вершины в цикле перестановки
	bool isMinus_PT = true; //флаг отрицательной метки
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
	int i = NULL; //координата строки
	int j = NULL; //координата столбца
	WayCell()
	{}

	WayCell(int aa, int bb)
	{
		i = aa;
		j = bb;

	}
};

int VERT_M = 3; //кол-во €чеек по вертикали
int HORZ_M = 4; //кол-во €чеек по горизонтали
int min = INT_MIN;
int A_BASIC_i, A_BASIC_j; //координаты исходной точки поиска

Cell **CELLS_TABLE; //массив €чеек
vector <WayCell> WAY; //вектор пам€ти пути робота

WayCell *SAVETHEWAY;

int *U;
int *V;