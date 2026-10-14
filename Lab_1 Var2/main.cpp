#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>

const int nmax = 100;

int ArrayInput(int* n, double x[], const char* fname);
void ArrayPrint(const char* name, double x[], int n);
double ArithmeticMean(double x[], int n, double p);

void ArrayPrint(const char* name, double x[], int n)
{
	std::cout << name << "(элементов) " << n << "\n";
	for (int i = 0; i < n; ++i)
		std::cout << " " << x[i] << " ";
	std::cout << "\n";
}

double ArithmeticMean(double x[], int n, double p)
{
	int count = 0;
	double sum = 0;

	for (int i = 0; i < n; ++i)
	{
		if (x[i] > p)
		{
			++count;
			sum += x[i];
		}
	}
	if (count == 0)
		return 0;
	else
		return sum / count;
}

int ArrayInput(int* n, double x[], const char* fname)
{
	std::ifstream inputFile(fname);
	if (!inputFile.is_open())
	{
		std::cout << "Невозможно открыть файл " << fname << std::endl;
		return 0;
	}

	if (!(inputFile >> *n)) {
		std::cout << "Ошибка чтения размера из файла '" << fname << "'\n";
		return 0;
	}

	if (*n < 0 || *n > nmax) {
		std::cout << "Кол-во элементов массива должно быть от 0 до " << nmax
			<< "! (файл '" << fname << "')\n";
		return 0;
	}

	for (int i = 0; i < *n; ++i) {
		if (!(inputFile >> x[i])) {
			std::cout << "Ошибка чтения элемента " << i + 1
				<< " из файла '" << fname << "'\n";
			return 0;
		}
	}

	return 1;
}

int main(int argc, char* argv[])
{
	double a[nmax], b[nmax], c[nmax];
	double AMa, AMb, AMc, param, max;
	int na, nb, nc;

	std::setlocale(LC_ALL, "Russian");

	if (argc < 4) {
		std::cout << "Недостаточно параметров! Укажите 3 файла в аргументах.\n";
		return 1;
	}

	if (!ArrayInput(&na, a, argv[1]))
		return 1;
	if (!ArrayInput(&nb, b, argv[2]))
		return 1;
	if (!ArrayInput(&nc, c, argv[3]))
		return 1;

	std::cout << std::fixed << std::setprecision(1);

	std::cout << "\nСчитанные массивы:\n";
	ArrayPrint("Массив A (файл 1)", a, na);
	ArrayPrint("Массив B (файл 2)", b, nb);
	ArrayPrint("Массив C (файл 3)", c, nc);
	std::cout << "\n";

	std::cout << "Введите заданное число: ";
	std::cin >> param;

	AMa = ArithmeticMean(a, na, param);
	AMb = ArithmeticMean(b, nb, param);
	AMc = ArithmeticMean(c, nc, param);

	max = AMa;
	if (AMb > max) max = AMb;
	if (AMc > max) max = AMc;

	if (max == AMa)
		std::cout << "Наибольшее среднее арифметическое " << AMa << " в первом массиве.\n";
	else if (max == AMb)
		std::cout << "Наибольшее среднее арифметическое " << AMb << " во втором массиве.\n";
	else
		std::cout << "Наибольшее среднее арифметическое " << AMc << " в третьем массиве.\n";

	if (AMa == AMb && AMb == AMc)
		std::cout << "Среднее арифметическое значение во всех трёх массивах совпадает.\n";
	else if (AMa == AMb)
		std::cout << "Среднее арифметическое первого и второго массивов совпадает.\n";
	else if (AMa == AMc)
		std::cout << "Среднее арифметическое первого и третьего массивов совпадает.\n";
	else if (AMb == AMc)
		std::cout << "Среднее арифметическое второго и третьего массивов совпадает.\n";
	else
		std::cout << "Среднее арифметическое всех массивов различно.\n";

	return 0;
}