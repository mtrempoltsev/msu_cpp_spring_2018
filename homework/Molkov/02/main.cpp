#include <iostream>
#include "numbers.dat"

int bin_search(const int *arr, int left, int right, int key)
{
	int mid;
	if (left > right)
		return -1;

	mid = (left + right) / 2;

	if (key < arr[mid])
		bin_search(arr, left, mid - 1, key);
	else if (key > arr[mid])
		bin_search(arr, mid + 1, right, key);
	else
		return mid;
}

//решето эратосфена
void eratosphen(bool *arr, int size) {
	for (int i = 0; i < size; i++)
		arr[i] = true;

	for (int i = 2; ((i*i) < size); i++) {
		if (arr[i])
			for (int j = (i*i); j < size; j += i) {
				if (arr[j])
					arr[j] = false;
			}
	}
	arr[0] = false;
	arr[1] = false;
}


int main(int argc, char* argv[])
{
	if (argc <= 1)
		return -1;
	if (argc % 2 == 0)
		return -1;

	bool *arr;
	arr = new bool[Data[Size - 1]];

	eratosphen(arr, Size - 1);

	int left, right;
	for (int i = 1; i < argc; i += 2) {
		int tmp1 = std::atoi(argv[i]);
		int tmp2 = std::atoi(argv[i + 1]);
		left = bin_search(Data, 0, Size, tmp1);
		right = bin_search(Data, 0, Size, tmp2);

		int count = 0;
		if (left == -1)
			std::cout << count << "\n";
		else {
			for (int i = left; i <= right; i++) {
				if (arr[Data[i]]) {
					count++;
				}
			}
		}

		std::cout << count << "\n";
	}
	delete [] arr;
	//system("pause");
	return 0;
}