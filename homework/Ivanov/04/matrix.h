#pragma once
#include <vector>

using std::size_t;
using std::vector;

class Proxy
{
	vector<double> vec;
public:
	Proxy(size_t);
	size_t getsize() const;
	double& operator[] (size_t);
	Proxy& multconst(double);
	Proxy& multvect(const vector<double>&);
	bool operator== (const Proxy&) const;
	~Proxy();
};

class Matrix
{
	vector<Proxy> vec;
public:
	Matrix(size_t, size_t);
    size_t getcols() const;
    size_t getrows() const;
	Proxy& operator[] (size_t);
	Matrix& operator*= (double);
	Matrix& operator*= (const vector<double>&);
    bool operator== (Matrix &);
    bool operator!= (Matrix &);
	~Matrix();
};