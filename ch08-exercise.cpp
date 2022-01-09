#include <iostream>
#include <string>
#include <vector>
#include "ch07.h"

#define Semiring typename
#define M_SIZE 7
#define INF 100

using namespace std;

bool semiring_plus(bool a, bool b) {
	return a || b;
}

bool semiring_multiplies(bool a, bool b) {
	return a && b;
}

bool identity_element_semiring_plus(bool a) {
	return bool(0);
}


template <Semiring T>
struct matrix_multiplication {
	vector<vector<T>> operator()(vector<vector<T>> x, vector<vector<T>> y) const {
		vector<vector<T>> ret(M_SIZE, vector<T>(M_SIZE, identity_element_semiring_plus(T())));
		for (int i = 0; i < M_SIZE; i++)
			for (int j = 0; j < M_SIZE; j++)
				for (int k = 0; k < M_SIZE; k++)
					ret[i][j] = semiring_plus(ret[i][j], semiring_multiplies(x[i][k], y[k][j]));
		return ret;
	}
};


template <Semiring T>
void print_matrix(vector<vector<T>> m) {
	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}


class Tropical {
public:
	int val;
	Tropical() { val = 0; }
	Tropical(int v) {
		val = v;
	}

	friend std::ostream& operator << (std::ostream &out, const Tropical &tropical)
	{
		out.width(3);
		if (tropical.val == INF) out << "INF";
		else out << tropical.val;
		return out;
	}
};

Tropical semiring_plus(Tropical a, Tropical b) {
	if (a.val > b.val) return b;
	else return a;
}

Tropical semiring_multiplies(Tropical a, Tropical b) {
	if (a.val == INF || b.val == INF) return Tropical(INF);
	else return Tropical(a.val + b.val);
}

Tropical identity_element_semiring_plus(Tropical a) {
	return Tropical(INF);
}


class Tropical_Trace {
public:
	Tropical trop;
	string trace;
	Tropical_Trace() {
		trop.val = 0;
		trace = "";
	}
	Tropical_Trace(int v, string s) {
		trop.val = v;
		trace = s;
	}

	friend std::ostream& operator << (std::ostream &out, const Tropical_Trace &tropical_trace)
	{
		out.width(2);
		out << "[ " << tropical_trace.trop.val << ", ";
		if (tropical_trace.trace == "") out << "X ";
		else out << tropical_trace.trace;
		out << "]";
		return out;
	}
};

Tropical_Trace semiring_plus(Tropical_Trace a, Tropical_Trace b) {
	if (a.trop.val > b.trop.val) return b;
	else return a;
}

Tropical_Trace semiring_multiplies(Tropical_Trace a, Tropical_Trace b) {
	if (a.trop.val == INF || b.trop.val == INF) return Tropical_Trace(INF, "X");
	else return Tropical_Trace(a.trop.val + b.trop.val, a.trace + b.trace);
}

Tropical_Trace identity_element_semiring_plus(Tropical_Trace a) {
	return Tropical_Trace(INF, "");
}


int main(void) {
	// exercise 8.7
	vector<vector<bool>> adj{
		{1, 1, 0, 1, 0, 0, 0},
		{1, 1, 0, 0, 0, 1, 0},
		{0, 0, 1, 1, 0, 0, 0},
		{1, 0, 1, 1, 0, 1, 0},
		{0, 0, 0, 0, 1, 0, 1},
		{0, 1, 0, 1, 0, 1, 0},
		{0, 0, 0, 0, 1, 0, 1}
	};
	matrix_multiplication<bool> mat_mul_bool;
	adj = power_semigroup(adj, M_SIZE, mat_mul_bool);
	print_matrix(adj);
	cout << endl;

	// exercise 8.8
	vector<vector<Tropical>> dist{
		{  0,   6, INF,   3, INF, INF, INF},
		{INF,   0, INF, INF,   2,  10, INF},
		{  7, INF,   0, INF, INF, INF, INF},
		{INF, INF,   5,   0, INF,   4, INF},
		{INF, INF, INF, INF,   0, INF,   3},
		{INF, INF,   6, INF,   7,   0,   8},
		{INF,   9, INF, INF, INF, INF,   0}
	};
	matrix_multiplication<Tropical> mat_mul_Tropical;
	dist = power_semigroup(dist, M_SIZE, mat_mul_Tropical);
	print_matrix(dist);
	cout << endl;

	// exercise 8.9
	vector<vector<Tropical_Trace>> dist_trace {
		{{ 0,  ""},   {6, "AB "},  {INF, ""},   { 3, "AD "}, {INF, ""},    {INF, ""},    {INF, ""}  },
		{{INF, ""},   {0, ""},     {INF, ""},   {INF, ""},   { 2, "BE "},  {10, "BF "},  {INF, ""}  },
		{{ 7, "CA "}, {INF, ""},   { 0, ""},    {INF, ""},   {INF, ""},    {INF, ""},    {INF, ""}  },
		{{INF, ""},   {INF, ""},   { 5, "DC "}, { 0, ""},    {INF, ""},    { 4, "DF "},  {INF, ""}  },
		{{INF, ""},   {INF, ""},   {INF, ""},   {INF, ""},   { 0, ""},     {INF, ""},    { 3, "EG "}},
		{{INF, ""},   {INF, ""},   { 6, "FC "}, {INF, ""},   { 7, "FE "},  { 0, ""},     { 8, "FG "}},
		{{INF, ""},   { 9, "GB "}, {INF, ""},   {INF, ""},   {INF, ""},    {INF, ""},    { 0, ""}   }
	};
	matrix_multiplication<Tropical_Trace> mat_mul_Tropical_Trace;
	dist_trace = power_semigroup(dist_trace, M_SIZE, mat_mul_Tropical_Trace);
	print_matrix(dist_trace);
	cout << endl;
}
