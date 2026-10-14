#include <iostream>
#include <clocale>
#include <fstream>
#include <iomanip>

const int nmax = 100;

bool ArrayNegative(double x[], int n);
int MatrixCountZero(double x[][nmax], int n, int m);
int MatrixInput(int& n, int& m, double x[][nmax], const char* fname);
void MatrixPrint(const char* name, double x[][nmax], int n, int m);

bool ArrayNegative(double x[], int n) {
	for (int i = 0; i < n; ++i)
		if (x[i] < 0) return true;
	return false;
}

int MatrixCountZero(double x[][nmax], int n, int m) {
	int count = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (x[i][j] == 0.0) ++count;

	return count;
}

int MatrixInput(int& n, int& m, double x[][nmax], const char* fname)
{
	std::ifstream inputFile(fname);
	if (!inputFile.is_open())
	{
		std::cout << "Невозможно открыть файл " << fname << '\n';
		return 0;
	}

	if (!(inputFile >> n)) {
		std::cout << "Ошибка чтения размера из файла " << fname << '\n';
		return 0;
	}

	if (!(inputFile >> m)) {
		std::cout << "Ошибка чтения размера из файла " << fname << '\n';
		return 0;
	}

	if (n < 0 || n > nmax) {
		std::cout << "Кол-во строк матрицы должно быть от 0 до " << nmax
			<< "! (файл '" << fname << "')\n";
		return 0;
	}

	if (m < 0 || m > nmax) {
		std::cout << "Кол-во столбцов матрицы должно быть от 0 до " << nmax
			<< "! (файл '" << fname << "')\n";
		return 0;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!(inputFile >> x[i][j])) {
				std::cout << "Ошибка чтения элемента " << i + 1
					<< " из файла " << fname << '\n';
				return 0;
			}
		}
	}

	return 1;
}

void MatrixPrint(const char* name, double x[][nmax], int n, int m)
{
	std::cout << name << ":\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cout << std::setw(8) << x[i][j] << " ";
		}
		std::cout << "\n";
	}
}

int main(int argc, char* argv[]) {
	double a[nmax][nmax];
	double b[nmax][nmax];
	int na = 0;
	int ma = 0;
	int nb = 0;
	int mb = 0;
	int countA = 0;
	int countB = 0;

	std::setlocale(LC_ALL, "rus");

	if (argc < 3) {
		std::cout << "Недостаточно параметров! Укажите 2 файла в аргументах.\n";
		return 1;
	}

	if (!MatrixInput(na, ma, a, argv[1]))
		return 2;
	if (!MatrixInput(nb, mb, b, argv[2]))
		return 3;

	std::cout << "\nСчитанные матрицы:\n";
	MatrixPrint("Матрица A", a, na, ma);
	MatrixPrint("Матрица B", b, nb, mb);
	std::cout << "\n";

	countA = MatrixCountZero(a, na, ma);
	countB = MatrixCountZero(b, nb, mb);

	std::cout << "Нулей в A: " << countA << ", нулей в B: " << countB << "\n\n";

	if (countA < countB) {
		for (int i = 0; i < na; ++i) {
			if (ArrayNegative(a[i], ma))
				std::cout << "В " << i + 1 << "-й строке матрицы A есть отрицательные элементы\n";
		}
	}
	else {
		for (int i = 0; i < nb; ++i) {
			if (ArrayNegative(b[i], mb))
				std::cout << "В " << i + 1 << "-й строке матрицы B есть отрицательные элементы\n";
		}
	}

	return 0;
}
