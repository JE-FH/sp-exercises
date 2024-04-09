/**
 * Prints deduction tables for each combination of function template and argument type.
 */
#include "type_name.hpp"

#include <iostream>
#include <iomanip> // setw, left

using std::ostream;
using std::cout;
using std::left;
using std::setw;

void t_pt(const std::string& t, const std::string& pt) {
	cout << "T="  << setw(12) << t;
	cout << "pt=" << setw(12) << pt;
}

template <typename T>
void f_ref(T& p) {
	t_pt(type_name<T>(), type_name<decltype(p)>());
}


template <typename T>
void f_cref(const T& p) {
	t_pt(type_name<T>(), type_name<decltype(p)>());
}

template <typename T>
void f_p(T* p) {
	t_pt(type_name<T>(), type_name<decltype(p)>());
}

template <typename T>
void f_cp(const T* p) {
	t_pt(type_name<T>(), type_name<decltype(p)>());
}

template <typename T>
void f_uref(T&& p) {
	t_pt(type_name<T>(), type_name<decltype(p)>());
}

template <typename T>
void f_val(T p) {
	t_pt(type_name<T>(), type_name<decltype(p)>());
}

template <typename...Args>
ostream& head(ostream& os, Args&&... args) {
	return ((os << setw(29) << left << args), ...) << '\n';
}

void na(ostream& os){
	os << setw(29) << std::string(27,'-');
}

int main()
{
	int x = 42;
	int* px = &x;
	const int cx = 42;
	const int& cr = x;
	const int* cp = &x;

	cout << setw(13) << left << "<typename T>";
	head(cout, "int* px = &x;", "const int* cp = &x;");
	cout << setw(13) << "f(T*): ";
	f_p(&x);    f_p(cp);    cout << '\n';
	cout << setw(13) << "f(const T*): ";
	f_cp(&x);   f_cp(cp);   cout << '\n';

	cout << '\n';
	cout << setw(13) << "<typename T>";
	head(cout, "int x;", "const int cx = 42;", "const int& cr = x;", "42", "const int* cp = &x;");
	cout << setw(13) << "f(T&): ";
	f_ref(x); f_ref(cx);  f_ref(cr);  na(cout);  f_ref(cp); cout << '\n';
	cout << setw(13) << "f(const T&): ";
	f_cref(x);  f_cref(cx); f_cref(cr); f_cref(42); f_cref(cp); cout << '\n';
	cout << setw(13) << "f(T&&): ";
	f_uref(x);  f_uref(cx); f_uref(cr);	f_uref(42); f_uref(cp); cout << '\n';
	cout << setw(13) << "f(T): ";
	f_val(x);	f_val(cx);  f_val(cr);	f_val(42); f_val(cp);  cout << '\n';
}
