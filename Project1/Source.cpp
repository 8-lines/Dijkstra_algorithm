#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
 


// Генератор матрицы смежности графа
int** generator(int size, int eps)
{
	// Ограничивает расстояние между вершинами двузначным числом
	// Исключительно для наглядности при выводе


	// Параметр для регулировки количества отсутствующих ребер
	int min = eps/4;

	// Матрица связей
	int** mtr = new int*[size]; 

	// Заполняем матрицу связей. На диагонали - нули, отсутствующие ребра - INT_MAX
	for (int i = 0; i < size; i++) 
	{
		mtr[i] = new int[size]; 
		for (int j = 0; j < size; j++)
		{
			mtr[i][j] = rand() % eps;

			// Регулировка количества отсутствующих ребер
			if (mtr[i][j] < min)
				mtr[i][j] = INT_MAX;
			else
				// Длина пути как целое число, кратное 10
				mtr[i][j] *= 10;
		}
		mtr[i][i] = 0;
	}

	return mtr;
}




// Алгоритм Дейкстры
int* dijkstra(int** mtr, int size, int start) 
{ 
	// Минимальное расстояние
	int* minDist = new int[size];  

	// Посещенные вершины
	bool* isDone = new bool[size]; 
   
	// Заполняем массивы расстояний и пройденных вершин
	for (int i = 0; i < size; i++) 
	{
		minDist[i] = INT_MAX;
		isDone[i] = false; 
	}

	// Расстояние от начальной вершины до самой себя равно нулю
	minDist[start] = 0; 

	int min;

	// Счетчик количества пройденных вершин
	int count = 0;

	int curr = start;

	// Шаг алгоритма
	while (count < size-1)
	{
		min = INT_MAX;

		for (int i = 0; i<size; i++)
		{ 
			// Если вершину ещё не обошли и путь до нее меньше известного
			if ((isDone[i] == false) && (minDist[curr] + mtr[curr][i] < minDist[i]) && (mtr[curr][i] != INT_MAX))
				minDist[i] = minDist[curr] + mtr[curr][i];
		}

		// Помечаем текущую вершину как пройденную
		isDone[curr] = true;
		count++;

		for (int i = 0; i<size; i++)
		{ 
			// Если вершину ещё не обошли и путь до нее меньше известного
			if ((isDone[i] == false) && (minDist[i] < min))
			{
				curr = i;
				min = minDist[i];
			}

		}

	}
     
     return(minDist); 
} 


// Вывод матрицы связей
void mtrOut(int** mtr, int size, int start)
{	
	cout << "Size: " << size << endl;
	cout << "Start: " << start+1 << endl << endl;
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++)
		{
			switch (mtr[i][j])
			{
				case 0: 
					cout << " " << mtr[i][j] << " ";
					break;
				case INT_MAX: 
					cout  << "-- ";
					break;
				default:
					cout << mtr[i][j] << " ";
			}

		}
		cout << endl;
	}
	cout << endl;
}

// Вывод минимальных расстояний
void printSolution(int* minDist, int size)
{	
	for (int i = 0; i < size; i++) 
	{
		if (minDist[i] == INT_MAX)
			cout << "unreachable" << " ";
		else
			cout << minDist[i] << " ";
	}

	cout << endl;
}


int main() 
{ 
	srand((unsigned int)time(NULL));
	ofstream fout1, fout2;
	fout1.open("output1.txt");
	fout2.open("output2.txt");

	// Задаем максимальный и минимальный размер графа
	int eps = 10;
	int min = 4;
	int z = 0;
	while (z <= 15)
	{
		// Генерируем размер графа и индекс стартовой вершины
		//int size = (rand() % eps) + min;
		int size = 6000 + z*1000;
		int start = rand() % size;

		// Генерируем матрицу смежности
		int** mtr = generator(size, eps);

		//mtrOut(mtr, size, start);

		double start_time =  clock(); // начальное время

		int* ans = dijkstra(mtr, size, start); 

		double end_time = clock(); // конечное время
		double search_time = (end_time - start_time)/1000.0; // искомое время

		// Выводим результат
		//printSolution(ans, size);
		fout1 << size << ", ";
		fout2 << search_time << ", ";
		cout << size << " " << search_time << endl;
		z++;
		
		for (int i = 0; i < size; i++) 
			delete[] mtr[i];
		delete[] mtr;
		delete[] ans;
	}

	fout1.close();
	fout2.close();
	system("pause");
    return 0; 
} 