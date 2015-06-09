
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

void ChooseMy(int random[], int size);

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



void MergeMy(int random[], int size)
{
	//My - origin

}

void MergeBook(int random[], int size)
{
	
}