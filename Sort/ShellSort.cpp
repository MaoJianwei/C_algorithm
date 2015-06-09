
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

#define randomSize 20000
bool checkSort(int sorted[], int size);
void showArray(int Array[], int size);

void XiErBook(int random[], int size);
void XiErMy(int random[], int size);

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

	XiErMy(random, randomSize);
	//XiErBook(random, randomSize-1);

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

void XiErMy(int random[], int size)
{
	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
	cout << "Start..." << endl;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	//My - origin
	int temp = -1;
	for (int d = randomSize / 2; d > 0; d /= 2)//“增量”
	{
		for (int i = 0 + d; i < size; i ++)//“划组”，切记不是“i = i + d”！否则就会忽略除了第一分组以外的其他分组！几乎相当于只进行了d=1，即插入排序
		{
			if (random[i]<random[i - d])
			{
				temp = random[i];
				int j = i - d;
				for (; j >= 0 && temp < random[j];j-=d)
					random[j + d] = random[j];
				random[j + d] = temp;

				//for (int j = i - d; j >= -d; j -= d)//比上面多了一次比较
				//{
				//	if (-d == j || temp >= random[j])
				//	{
				//		random[j + d] = temp;
				//		break;
				//	}
				//	else
				//		random[j + d] = random[j];
				//}
			}
		}
	}

	QueryPerformanceCounter(&stop);



	cout << "Finish!  My Sort Time: " << double(stop.QuadPart - start.QuadPart) / double(freq.QuadPart) * 1000 << " ms" << endl;




	cout << "Checking..." << endl;

	if (true == checkSort(random, size))
		cout << endl << "GOOD!" << endl;
	else
		cout << endl << "Fail!" << endl;
}

void XiErBook(int random[],int size)
{
	LARGE_INTEGER freq;
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
	cout << "Start..." << endl;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	//BOOK
	for (int d = size / 2; d >= 1; d = d / 2)
	{
		for (int i = d + 1; i <= size; i++)
		{
			if (random[i] < random[i - d])
			{
				random[0] = random[i];
				int j = i - d;
				for (; j>0 && random[0] < random[j]; j = j - d)
					random[j + d] = random[j];
				random[j + d] = random[0];
			}
		}
	}

	QueryPerformanceCounter(&stop);

	//cout << "Result :" << endl;
	//showArray(random, randomSize);

	cout << "Finish!  My Sort Time: " << double(stop.QuadPart - start.QuadPart) / double(freq.QuadPart) * 1000 << " ms" << endl;




	cout << "Checking..." << endl;
	random[0] = -1;
	if (true == checkSort(random, size))
		cout << endl << "GOOD!" << endl;
	else
		cout << endl << "Fail!" << endl;
}