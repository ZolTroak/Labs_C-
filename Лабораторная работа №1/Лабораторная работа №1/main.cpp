#include <cstdio>
#include <locale.h>

const int nmax = 100;

int ArrayInput(int* n, double x[], char* fname);
void ArrayPrint(const char* name, double x[], int n);
double ArithmeticMean(double x[], int n, double p);

int main(int argc, char* argv[])
{
	double a[nmax], b[nmax], c[nmax];
	double AMa, AMb, AMc, param, max;
	int na, nb, nc;

	setlocale(LC_ALL, "Russian");

	if (argc < 4) {
		printf_s("Недостаточно параметров! Укажите 3 файла в аргументах.\n");
		return 1;
	}

	if (!ArrayInput(&na, a, argv[1]))
		return 1;
	if (!ArrayInput(&nb, b, argv[2]))
		return 1;
	if (!ArrayInput(&nc, c, argv[3]))
		return 1;

	printf_s("\nСчитанные массивы:\n");
	ArrayPrint("Массив A (файл 1)", a, na);
	ArrayPrint("Массив B (файл 2)", b, nb);
	ArrayPrint("Массив C (файл 3)", c, nc);
	printf_s("\n");

	printf_s("Введите заданное число: ");
	if (scanf_s("%lf", &param) < 1) {
		printf_s("Ошибка ввода числа!\n");
		return 1;
	}

	AMa = ArithmeticMean(a, na, param);
	AMb = ArithmeticMean(b, nb, param);
	AMc = ArithmeticMean(c, nc, param);

	max = AMa;
	if (AMb > max) max = AMb;
	if (AMc > max) max = AMc;

	if (max == AMa)
		printf_s("Наибольшее среднее арифметическое %lf в первом массиве.\n", AMa);
	else if (max == AMb)
		printf_s("Наибольшее среднее арифметическое %lf во втором массиве.\n", AMb);
	else
		printf_s("Наибольшее среднее арифметическое %lf в третьем массиве.\n", AMc);

	if (AMa == AMb && AMb == AMc)
		printf_s("Среднее арифметическое значение во всех трёх массивах совпадает.\n");
	else if (AMa == AMb)
		printf_s("Среднее арифметическое первого и второго массивов совпадает.\n");
	else if (AMa == AMc)
		printf_s("Среднее арифметическое первого и третьего массивов совпадает.\n");
	else if (AMb == AMc)
		printf_s("Среднее арифметическое второго и третьего массивов совпадает.\n");
	else
		printf_s("Среднее арифметическое всех массивов различно.\n");

	return 0;
}

void ArrayPrint(const char* name, double x[], int n)
{
	printf_s("%s (элементов: %d):\n", name, n);
	for (int i = 0; i < n; ++i)
	{
		printf_s("%.2lf ", x[i]);
	}
	printf_s("\n");
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
	//if (count == 0)
	//	return 0;
	return (count == 0) ? 0 : sum / count;
	//else
	//	return sum / count;
}

int ArrayInput(int* n, double x[], char* fname)
{
	FILE* file = nullptr;

	if (fopen_s(&file, fname, "r") != 0 || file == nullptr) {
		printf_s("Невозможно открыть файл '%s'\n", fname);
		return 0;
	}

	if (fscanf_s(file, "%d", n) < 1) {
		printf_s("Ошибка чтения размера из файла '%s'\n", fname);
		fclose(file);
		return 0;
	}

	if (*n < 0 || *n > nmax) {
		printf_s("Кол-во элементов массива должно быть от 0 до %d! (файл '%s')\n", nmax, fname);
		fclose(file);
		return 0;
	}

	for (int i = 0; i < *n; ++i) {
		if (fscanf_s(file, "%lf", &x[i]) < 1) {
			printf_s("Ошибка чтения элемента %d из файла '%s'\n", i + 1, fname);
			fclose(file);
			return 0;
		}
	}

	fclose(file);
	return 1;
}