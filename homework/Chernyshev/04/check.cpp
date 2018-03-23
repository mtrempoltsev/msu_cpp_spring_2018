#include <iostream>

#include "matrix.h"

#define check(cond) do { if (!(cond)) std::cout << "line " << __LINE__ << ": " << #cond << '\n'; } while(0)
#define check_throw(expr, err) do { try { expr; } catch (const err&) { break ; } catch (...) { } std::cout << "line " << __LINE__ << '\n'; } while(0)

int main()
{
    int n = 0;

    Matrix m1(3, 2);
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            m1[j][i] = ++n;
        }
    }

    check(m1[0][0] == 1);
    check(m1[1][0] == 2);
    check(m1[2][0] == 3);
    check(m1[0][1] == 4);
    check(m1[1][1] == 5);
    check(m1[2][1] == 6);

    check(m1.getColumns() == 3);
    check(m1.getRows() == 2);

    check_throw(m1[3][0], std::out_of_range);
    check_throw(m1[0][2], std::out_of_range);

    m1 *= 2;

    check(m1[0][0] == 1 * 2);
    check(m1[1][0] == 2 * 2);
    check(m1[2][0] == 3 * 2);
    check(m1[0][1] == 4 * 2);
    check(m1[1][1] == 5 * 2);
    check(m1[2][1] == 6 * 2);

    Matrix m2(0, 0);
    check_throw(m2[0][0], std::out_of_range);

    const Matrix& m3 = m1;

    Matrix m4(3, 2);

    check(m1 == m1);
    check(m1 != m2);
    check(m1 == m3);
    check(m1 != m4);

    std::cout << "done\n";

    return 0;
}
