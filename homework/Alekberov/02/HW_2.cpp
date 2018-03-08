#include <iostream>
#include <cmath>


#include "numbers.dat"


bool* getSieve (const int sizeSieve) {
  bool* result = new bool[sizeSieve];
  std::fill_n (result, sizeSieve, true);

  result[0] = result[1] = false;
  for (int i = 2; i < int (ceil (sqrt (sizeSieve))); i++) {
    if (result[i]) {
      for (int j = i*i; j < sizeSieve; j += i)
        result[j] = false;
    }
  }

  return result;
}

int main (int argc, char* argv[]) {
  auto sieve = getSieve (100001);

  if ((argc == 1) || (argc % 2 == 0))
    return -1;

  const int countOfPairs = (argc - 1) / 2;

  for (int j = 0; j < countOfPairs; ++j) {
    int nmb_1 = std::atoi (argv[1 + 2 * j]);
    int nmb_2 = std::atoi (argv[2 * j + 2]);

    if (nmb_1 > nmb_2) {
      std::cout << 0 << '\n';
      return 0;
    }


    int nmb_nmb_1 = -1;
    int nmb_nmb_2 = -1;
    int count_of_prime = 0;


    for (int i = 0; i < Size; i++) {
      if (nmb_1 == Data[i]) {
        nmb_nmb_1 = i;
        break;
      }
    }




    for (int i = Size - 1; i >= 0; i--) {
      if (nmb_2 == Data[i]) {
        nmb_nmb_2 = i;
        break;
      }
    }


    if ((nmb_nmb_1 != -1) && (nmb_nmb_2 != -1)) {
      for (int i = nmb_nmb_1; i <= nmb_nmb_2; i++) {
        if (sieve[Data[i]])
          count_of_prime++;
      }
      std::cout << count_of_prime << '\n';
    }


    if ((nmb_nmb_1 == -1) || (nmb_nmb_2 == -1))
      std::cout << 0 << '\n';
  }

  delete[] sieve;

  return 0;
}