#include <iostream>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <cmath>

using namespace std;

// height, width	- количество строк и количество столбцов матрицы,
// sum				- переменная, используемая для подсёта нулей,
// step				- переменная, отсчитывающая шаг от заглавной строки в цикле преобразований по методу Гаусса,
// sort1, sort2		- переменные, используемые для переноса нулей в низ матрицы,
// rank				- ранг матрицы,
// i, j, k, p		- переменные, необходимые для работы с двумерным вектором (матрицей),
// tempmath			- изменяемый множитель, используемый в преобразованиях,
// eps				- точность вычислений,
// matrix			- двумерный вектор (матрица).

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int height, width, sum = 0, step = 0, sort1, sort2, rank; 
	int i, j, k, p, e;
	double tempmath, eps = 0.00001;
	cout << "Введите количество строк и количество столбцов матрицы: ";
	cin >> height >> width;
	if (height <= 0 || width <= 0)
	{
		cout << "Ошибка. Неверные параметры матрицы." << endl;
		return 0;
	}
	rank = height;
	vector <vector <double>> matrix;

	// ввод матрицы

	cout << "Введите " << width * height << " элементов матрцицы: ";
	for (i = 0; i < height; i++)
	{
		vector <double> temp;
		for (j = 0; j < width; j++)
		{
			cin >> e;
			temp.push_back(e);
		}
		matrix.push_back(temp);
	}
	cout << "\n";

	// вывод первоначальной матрицы

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	
	// приведение матрицы к ступенчатому виду по методу Гаусса
	// проверка условия для диагонали ступеней

	if (width > height - 1)
	{
		for (k = 0; k < height - 1; k++)
		{

			// перенос нулей столбца в низ матрицы путём перемены строк (сортировка методом пузырька)

			j = k;
			for (sort1 = k; sort1 < height; sort1++) {
				for (sort2 = k; sort2 < height - 1; sort2++) {
					if (abs(matrix[sort2][j]) < abs(matrix[sort2 + 1][j]))
					{
						for (j = 0; j < width; j++) swap(matrix[sort2][j], matrix[sort2 + 1][j]);
					}
					j = k;
				}
			}

			// преобразования к ступенчатому виду

			for (i = k + 1; i < height; i++)
			{
				j = k;
				tempmath = matrix[i][j] / matrix[i - 1 - step][j];
				if (matrix[i][j] == 0)
				{
					step++;
					continue;
				}
				else
				{
					for (j = k; j < width; j++)
					{
						matrix[i - step - 1][j] = matrix[i - step - 1][j] * tempmath;
						matrix[i][j] = matrix[i][j] - matrix[i - step - 1][j];
					}
					step++;
				}
			}
			step = 0;

			// перенос нулевых строк в самый низ и подсчёт ранга матрицы

			for (p = 0; p < width; p++)
				if (matrix[k + 1][p] == 0) sum++;
			if (sum == width)
			{
				for (p = 0; p < width; p++)
				{
					swap(matrix[height - 1][p], matrix[k + 1][p]);
				}
			}
			sum = 0;
		}
	}
	
	else
	{
		for (k = 0; k < width; k++)
		{

			// перенос нулей столбца в низ матрицы путём перемены строк (сортировка методом пузырька)

			j = k;
			for (sort1 = k; sort1 < height; sort1++) {
				for (sort2 = k; sort2 < height - 1; sort2++) {
					if (matrix[sort2][j] < matrix[sort2 + 1][j])
					{
						for (j = 0; j < width; j++) swap(matrix[sort2][j], matrix[sort2 + 1][j]);
					}
					j = k;
				}
			}

			// преобразования к ступенчатому виду

			for (i = k + 1; i < height; i++)
			{
				j = k;
				tempmath = matrix[i][j] / matrix[i - 1 - step][j];
				if (matrix[i][j] == 0)
				{
					step++;
					continue;
				}
				else
				{
					for (j = k; j < width; j++)
					{
						matrix[i - step - 1][j] = matrix[i - step - 1][j] * tempmath;
						matrix[i][j] = matrix[i][j] - matrix[i - step - 1][j];
					}
					step++;
				}
			}
			step = 0;

			// перенос нулевых строк в самый низ матрицы

			for (p = 0; p < width; p++)
				if (matrix[k + 1][p] == 0) sum++;
			if (sum == width)
			{
				for (p = 0; p < width; p++)
				{
					swap(matrix[height - 1][p], matrix[k + 1][p]);
				}
			}
			sum = 0;
		}
	}

	// округление чисел близких к нулю

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (abs(matrix[i][j]) < eps) matrix[i][j] = 0;
		}
	}

	// вывод приведенной матрицы

	cout << "\nПриведенная матрица:" << endl;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

	// получение ранга матрицы и его последующий вывод

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (matrix[i][j] == 0) sum++;
		}
		if (sum == width) rank--;
		sum = 0;
	}

	cout << "\nРанг матрицы: " << rank;

	return 0;
}	