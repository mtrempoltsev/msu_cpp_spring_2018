#include "numbers.dat"
#include <iostream>

bool isSimple(int number) {
	for (int i = 2; i*i <= number; i++) 
		if (number%i == 0)
			return false;
	return number > 1;
}
void eratosfen(bool *arr, int size) {
	arr[0] = false;
	arr[1] = false;
	for (int i = 2; i < size; i++)
		arr[i] = true;
	for (int i = 2; i*i < size; i++) {
		if (arr[i])
			for (int j = i*i; j < size; j += i) {
				if (arr[j])
					arr[j] = false;
			}
	}
}
int main(int argc, char* argv[]){
	if (argc % 2 == 0 || argc == 1)
		return -1;
	bool *simpleMask = new bool[Data[Size - 1]];
	eratosfen(simpleMask, Data[Size - 1]);
	for (int i = 1; i < argc; i+=2) {
		int simpleCount = 0;
		int leftNumber = std::atoi(argv[i]);
		int rightNumber = std::atoi(argv[i + 1]);
		if (leftNumber > rightNumber) {
			std::cout << simpleCount<<"\n";
			continue;
		}
		if (Data[Size - 1] < rightNumber){
			std::cout << simpleCount << "\n";
			continue;
		}
		bool enterRange = false;
		for (int i = 0; i < Size; i++) {
			if (Data[i] == leftNumber)
				enterRange = true;
			if (enterRange) {
				if (simpleMask[Data[i]])
					simpleCount++;
				if (Data[i] == rightNumber && Data[i + 1] != Data[i])
					break;
			}else if (Data[i] >= rightNumber) {
				simpleCount = 0;
				break;
			}
		}
		std::cout << simpleCount<<"\n";
	}
	delete[] simpleMask;
	return 0;

}