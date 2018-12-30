#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
 


// ��������� ������� ��������� �����
int** generator(int size, int eps)
{
	// ������������ ���������� ����� ��������� ���������� ������
	// ������������� ��� ����������� ��� ������


	// �������� ��� ����������� ���������� ������������� �����
	int min = eps/4;

	// ������� ������
	int** mtr = new int*[size]; 

	// ��������� ������� ������. �� ��������� - ����, ������������� ����� - INT_MAX
	for (int i = 0; i < size; i++) 
	{
		mtr[i] = new int[size]; 
		for (int j = 0; j < size; j++)
		{
			mtr[i][j] = rand() % eps;

			// ����������� ���������� ������������� �����
			if (mtr[i][j] < min)
				mtr[i][j] = INT_MAX;
			else
				// ����� ���� ��� ����� �����, ������� 10
				mtr[i][j] *= 10;
		}
		mtr[i][i] = 0;
	}

	return mtr;
}




// �������� ��������
int* dijkstra(int** mtr, int size, int start) 
{ 
	// ����������� ����������
	int* minDist = new int[size];  

	// ���������� �������
	bool* isDone = new bool[size]; 
   
	// ��������� ������� ���������� � ���������� ������
	for (int i = 0; i < size; i++) 
	{
		minDist[i] = INT_MAX;
		isDone[i] = false; 
	}

	// ���������� �� ��������� ������� �� ����� ���� ����� ����
	minDist[start] = 0; 

	int min;

	// ������� ���������� ���������� ������
	int count = 0;

	int curr = start;

	// ��� ���������
	while (count < size-1)
	{
		min = INT_MAX;

		for (int i = 0; i<size; i++)
		{ 
			// ���� ������� ��� �� ������ � ���� �� ��� ������ ����������
			if ((isDone[i] == false) && (minDist[curr] + mtr[curr][i] < minDist[i]) && (mtr[curr][i] != INT_MAX))
				minDist[i] = minDist[curr] + mtr[curr][i];
		}

		// �������� ������� ������� ��� ����������
		isDone[curr] = true;
		count++;

		for (int i = 0; i<size; i++)
		{ 
			// ���� ������� ��� �� ������ � ���� �� ��� ������ ����������
			if ((isDone[i] == false) && (minDist[i] < min))
			{
				curr = i;
				min = minDist[i];
			}

		}

	}
     
     return(minDist); 
} 


// ����� ������� ������
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

// ����� ����������� ����������
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

	// ������ ������������ � ����������� ������ �����
	int eps = 10;
	int min = 4;
	int z = 0;
	while (z <= 15)
	{
		// ���������� ������ ����� � ������ ��������� �������
		//int size = (rand() % eps) + min;
		int size = 6000 + z*1000;
		int start = rand() % size;

		// ���������� ������� ���������
		int** mtr = generator(size, eps);

		//mtrOut(mtr, size, start);

		double start_time =  clock(); // ��������� �����

		int* ans = dijkstra(mtr, size, start); 

		double end_time = clock(); // �������� �����
		double search_time = (end_time - start_time)/1000.0; // ������� �����

		// ������� ���������
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