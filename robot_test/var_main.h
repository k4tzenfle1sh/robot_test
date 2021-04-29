using namespace std;

struct Cell {
	double Value = NULL; //значение внутри €чейки
	double PT = NULL; //потанцевал
	bool isCheckedAlready = false; //флаг проверки €чейки
	bool isUsedOnCycle = false; //флаг вершины в цикле перестановки
	bool isMinus_PT = false; //флаг отрицательной метки
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

int VERT_M = 3; //кол-во €чеек по вертикали
int HORZ_M = 4; //кол-во €чеек по горизонтали

Cell **CELLS_TABLE; //массив €чеек
int *U;
int *V;

