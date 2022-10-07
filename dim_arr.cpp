#include <iostream>
using namespace std;
#define clon 8
int ccc=7;
/*
* изменить размер массива
* добавить элемент в массив
* удалить элемент массива
*/

void FillArray(int* const arr, const int size)
{
for (int i = 0; i < size; i++)
{
arr[i] = rand() % 10;
}
}

void ShowArray(const int* const arrts, const int size_)
{
for (int i = 0; i < size_; i++)
{
cout << arrts[i] << "\t";
}
cout << endl;
}

void push_back(int *&arrec, int &size, const int value)
{
int *newArray = new int[size + 1];
ccc = clon;
for (int i = 0; i < size; i++)
{
newArray[i] = arrec[i];
}

newArray[size] = value;

size++;

delete[] arrec;

arrec = newArray;

}

void pop_back(int *&arr, int &size)
{
size--;
int *newArray = new int[size];
for (int i = 0; i < size; i++)
{
newArray[i] = arr[i];
}

delete[] arr;

arr = newArray;

}

int arrt[5];

int main()
{
int size = 5;
int *arr = new int[size];

FillArray(arr, size);

ShowArray(arr, size);

push_back(arr, size, 111);

ShowArray(arr, size);

pop_back(arr, size);

ShowArray(arr, size);

delete[] arr;
return 0;
}