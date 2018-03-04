#include <iostream>
#include <chrono>

class Matrix {
    int n,m;
    int *coef;
    public:
    Matrix(int n_new, int m_new) {
        n = n_new;
        m = m_new;
        coef = new int[n*m];
    }
    ~Matrix() {
        delete[] coef;
    }
    void gen(int seed) {
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                coef[i * m + j] = (i *431 + j *271 + seed) % 513;
            }
        }
    }
    int sum () {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans += coef[ i * m + j];
            }
        }
        return ans;
    }
};

class Timer {
    public:
        Timer():start_(std::chrono::high_resolution_clock::now())
        {
        }
        int get() {
            const auto finish = std::chrono::high_resolution_clock::now();
            std::cout <<std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us for step"<<std::endl;
            return std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
        }
    private:
        const std::chrono::high_resolution_clock::time_point start_;
};

const int STEP = 1000;
const int N = 100;
int main()
{
    long double mid = 0;
    for (int i = 0; i < STEP; i++) {
        Timer t;
        Matrix a(N,N);
        a.gen(31 * i + 7 );
        a.sum();
        mid += t.get();
    }
    mid /= STEP;
    std:: cout << "average time is " << mid << " us\n";
    return 0;
}