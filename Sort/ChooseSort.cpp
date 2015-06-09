
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <process.h>
#include <windows.h>
//#include <assert.h>
using namespace std;

#define randomSize 10000
bool checkSort(int sorted[], int size);
void showArray(int Array[], int size);

void ChooseMy(int random[],int size);

int main()
{
	srand(time(NULL));
	rand();
	int* random = new int[randomSize];
	//int* RANDOM = new int[randomSize];

	for (int i = 0; i < randomSize; i++)
		random[i] = rand();
	//memcpy(RANDOM, random, randomSize*sizeof(int));

	//for (int i = 0; i < randomSize; i++)
	//{
	//	if (random[i] != RANDOM[i])return 800;
	//}

	//cout << "Source :" << endl;
	//showArray(random, randomSize);


	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER stop;


	cout << "Start..." << endl;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	ChooseMy(random, randomSize);
	//XiErBook(random, randomSize-1);

	QueryPerformanceCounter(&stop);

	cout << "Finish!  My Sort Time: " << double(stop.QuadPart - start.QuadPart) / double(freq.QuadPart) * 1000 << " ms" << endl;


	cout << "Checking..." << endl;

	if (true == checkSort(random, randomSize))
		cout << endl << "GOOD!" << endl;
	else
		cout << endl << "Fail!" << endl;


	//cout << "Result :" << endl;
	//showArray(random, randomSize);

	system("pause");
	return 0;


	//cout << "time "<<i<<" :" << endl;
	//showArray(random, randomSize);
}

bool checkSort(int sorted[], int size)
{
	for (int i = 1; i < size; i++)
	{
		if (sorted[i - 1] > sorted[i])
			return false;
	}
	return true;
}

void showArray(int Array[], int size)
{
	for (int i = 0; i < size; i++)
		cout << Array[i] << '\t';
}



void ChooseMy(int random[], int size)
{
	//My - origin
	//int minI = -1;
	//int temp = 0;
	//for (int i = 0; i < size; i++)
	//{
	//	minI = i;
	//	for (int j = i + 1; j < size; j++)
	//		minI = random[j] < random[minI] ? j : minI;//random[minI]可以考虑提出来

	//	temp = random[i];
	//	random[i] = random[minI];
	//	random[minI] = temp;
	//}

	//My - Advanced - with BOOK
	int minI = -1;
	int temp = 0;
	for (int i = 0; i < size - 1; i++)
	{
		minI = i;
		for (int j = i + 1; j < size; j++)
		if (random[j] < random[minI])	//太慢：minI = random[j] < random[minI] ? j : minI;可能是多次不必要的写入minI //random[minI]没必要提出来到temp里
			minI = j;

		if (i != minI)
		{
			temp = random[i];
			random[i] = random[minI];
			random[minI] = temp;
		}
	}
}

void ChooseBook(int random[], int size)
{
	//My - origin
	int minI = -1;
	int temp = 0;
	for (int i = 0; i < size - 1; i++)
	{
		minI = i;
		for (int j = i + 1; j < size; j++)
		if (random[j] < random[minI])
			minI = j;
		//minI = random[j] < random[minI] ? j : minI;//random[minI]可以考虑提出来

		if (i != minI)
		{
			temp = random[i];
			random[i] = random[minI];
			random[minI] = temp;
		}
	}
}