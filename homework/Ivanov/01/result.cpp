#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    fstream fin1("sum_by_rows_results", ios_base::in);
    fstream fin2("sum_by_columns_results", ios_base::in);
    if(!fin1.is_open()) {
        return 0;
    }
    int buf, count = 0;
    string str;
    long double sum1 = 0, sum2 = 0;
    while(fin1 >> buf >> str) {
        sum1 += buf;
        count++;
    }
    sum1 /= count;
    count = 0;
    while(fin2 >> buf >> str) {
        sum2 += buf;
        count++;
    }
    sum2 /= count;
    cout << setprecision(10) << sum1 << endl;
    cout << setprecision(10) << sum2 << endl;
    fin1.close();
    fin2.close();
    return 0;
}
