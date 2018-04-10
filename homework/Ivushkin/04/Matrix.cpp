// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// PVS-settings
// PVS-settings end

#include <iostream>
#include <vector>
#include <memory>
#include <string>

template <typename T = int>
class TMatrix
{
public:
	class Row
	{
	private:
		T * d;
		size_t max;

	public:
		Row(T * data = nullptr, size_t m = 0) : d(data), max(m) {};
		
		T & operator [] (size_t position)
		{
			if (position < max)
				return d[position];
			throw std::out_of_range("");
		}

        friend std::ostream & operator << (std::ostream & out, const Row & r)
        {
            for (size_t i = 0; i < r.max - 1; ++i)
            {
                out << r.d[i] << ' ';
            }
            out << r.d[r.max - 1];
            return out;
        }
        
        std::string to_string ()
        {
            return (std::stringstream () << *this).str ();
        }
	};

private:
	size_t rlen, clen; //rows, cols len
	std::unique_ptr<T[]> d; //data

public:
	TMatrix(size_t collen = 0, size_t rowlen = 0, T * data = nullptr) :
		rlen(rowlen), clen(collen)
	{
		d = std::make_unique<T[]>(rlen * clen);
		if (data)
			std::copy(data, data + (rlen * clen), &d[0]);
	}

	TMatrix(const TMatrix & other) : TMatrix(other.rlen, other.clen, other.d) {}

	TMatrix(TMatrix && other) : clen(other.clen), rlen(other.rlen), d(other.d)
	{
		other.clen = 0;
		other.rlen = 0;
        other.d = nullptr;
	}

	TMatrix & operator = (const TMatrix & other)
	{
		clen = other.clen;
		rlen = other.rlen;
		d = std::make_unique<T[]>(rlen * clen);
		std::copy(other.d, other.d + (rlen * clen), &d[0]);
        return *this;
	}

	TMatrix & operator = (TMatrix && other)
	{
		clen = other.clen;
		rlen = other.rlen;
		d = other.d;
        return *this;
	}

	Row operator [] (size_t position) const
	{
		if (position < clen)
			return Row(&(d[position * rlen]), rlen);
		throw std::out_of_range("");
	}

	TMatrix & operator *= (T number)
	{
        for (size_t i = 0; i < rlen * clen; ++i)
        {
            d[i] *= number;
        }
        return *this;
	}

    bool operator == (const TMatrix & other)
    {
        if (rlen != other.rlen || clen != other.clen)
            return false;
        for (size_t i = 0; i < rlen * clen; ++i)
        {
            if (d[i] != other.d[i])
                return false;
        }
        return true;
    }

    bool operator != (const TMatrix & other)
    {
        return !operator == (other);
    }

    friend std::ostream & operator << (std::ostream & out, const TMatrix & other)
    {
        for (size_t i = 0; i < other.clen; ++i)
        {
            out << other[i] << std::endl;
        }
        return out;
    }

    std::string to_string ()
    {
        return (std::stringstream () << *this).str ();
    }

    size_t getclen () { return clen; }
    size_t getrlen () { return rlen; }
    size_t getRows () { return rlen; }
    size_t getColumns () { return clen; }
};

using Matrix = TMatrix<int>;

#define check(cond) do { if (!(cond)) std::cout << "line " << __LINE__ << ": " << #cond << '\n'; } while(0)
#define check_throw(expr, err) do { try { expr; } catch (const err&) { break ; } catch (...) { } std::cout << "line " << __LINE__ << '\n'; } while(0)

int main ()
{
    int n = 0;

    
    Matrix m1 (3, 2);

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            m1[j][i] = ++n;
        }
    }

    std::cout << m1 << std::endl;

    check (m1[0][0] == 1);
    check (m1[1][0] == 2);
    check (m1[2][0] == 3);
    check (m1[0][1] == 4);
    check (m1[1][1] == 5);
    check (m1[2][1] == 6);

    check (m1.getColumns () == 3);
    check (m1.getRows () == 2);

    check_throw (m1[3][0], std::out_of_range);
    check_throw (m1[0][2], std::out_of_range);

    m1 *= 2;

    check (m1[0][0] == 1 * 2);
    check (m1[1][0] == 2 * 2);
    check (m1[2][0] == 3 * 2);
    check (m1[0][1] == 4 * 2);
    check (m1[1][1] == 5 * 2);
    check (m1[2][1] == 6 * 2);

    Matrix m2 (0, 0);
    check_throw (m2[0][0], std::out_of_range);

    const Matrix& m3 = m1;

    Matrix m4 (3, 2);

    check (m1 == m1);
    check (m1 != m2);
    check (m1 == m3);
    check (m1 != m4);

    std::cout << "done\n";
    
    return 0;
}