
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <process.h>
#include <windows.h>
using namespace std;

#define randomSize 20000
bool checkSort(int sorted[], int size);
void showArray(int Array[], int size);
unsigned int WINAPI insertSortMy(PVOID Array);
unsigned int WINAPI insertSortBook(PVOID Array);

int main()
{
	srand(time(NULL));
	rand();
	int* random = new int [randomSize];
	int* RANDOM = new int[randomSize];
	
	for (int i = 0; i < randomSize; i++)
		random[i] = rand();
	memcpy(RANDOM, random, randomSize*sizeof(int));
	
	for (int i = 0; i < randomSize; i++)
	{
		if (random[i] != RANDOM[i])return 800;
	}


	//HANDLE a = (HANDLE)_beginthreadex(NULL, 0, insertSortMy, random, 0, NULL);
	//HANDLE b = (HANDLE)_beginthreadex(NULL, 0, insertSortBook, RANDOM, 0, NULL);



	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
	cout << "Start..." << endl;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	//My - origin
	int temp = 0;
	for (int i = 1 + 1; i < randomSize; i++)
	{
		temp = random[i];
		for (int j = i - 1; j >= -1; j--)
		{
			if (-1 == j || temp >= random[j])
			{
				random[j + 1] = temp;
				break;
			}
			else
				random[j + 1] = random[j];
		}
	}
	QueryPerformanceCounter(&stop);

	cout << "Finish!  My Sort Time: " << double(stop.QuadPart - start.QuadPart) / double(freq.QuadPart) << " s" << endl;




	//LARGE_INTEGER freq2;
	//LARGE_INTEGER start2;
	//LARGE_INTEGER stop2;
	//cout << "Start..." << endl;

	//QueryPerformanceFrequency(&freq2);
	//QueryPerformanceCounter(&start2);

	//for (int i = 2; i <= randomSize; i++)
	//{
	//	if (RANDOM[i] < RANDOM[i - 1])
	//	{
	//		RANDOM[0] = RANDOM[i];
	//		int j = i - 1;
	//		for (; RANDOM[0] < RANDOM[j]; j--)
	//			RANDOM[j + 1] = RANDOM[j];
	//		RANDOM[j + 1] = RANDOM[0];
	//	}
	//}

	//QueryPerformanceCounter(&stop2);

	//cout << "Finish!  Book Sort Time: " << double(stop2.QuadPart - start2.QuadPart) / double(freq2.QuadPart) << " s" << endl;














	
	//cout << "Source :" << endl;
	//showArray(random, randomSize);

	cout << "Checking..." << endl;

	random[0] = 0;
	if (true == checkSort(random, randomSize))
		cout << endl << "GOOD!" << endl;
	else
		cout << endl << "Fail!" << endl;
	

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

unsigned int WINAPI insertSortMy(PVOID Array)
{
	int * random = (int *)Array;


	return 0;
}

unsigned int WINAPI insertSortBook(PVOID Array)
{
	int * RANDOM = (int *)Array;


	return 0;
}