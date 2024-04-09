#ifndef INCLUDE_TYPE_NAME_HPP
#define INCLUDE_TYPE_NAME_HPP

#include <string>

#ifdef _MSC_VER
// MSVC does not need demangling, just convert to C++ string:
inline std::string demangle(const char* name) { return name; }
#else /* GCC, Clang and others use mangled type names */

#include <cxxabi.h>	 // started as GNU extension, but it's more popular now
inline std::string demangle(const char* name)
{
	auto res = std::string{};
	int	  status	= 0;
	char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
	if (status == 0) {
		res = demangled;
		free(demangled);  // C-API: malloc'ed memory has to be free'd
	} else
		res = name;
	return res;
}
#endif

template <typename T>
std::string type_name()
{
	// is_const and is_volatile does not work on references, hence remove it:
	using TR = std::remove_reference_t<T>; // C++14
    // using TR = typename std::remove_reference<T>::type;	 // C++11

	auto res = demangle(typeid(T).name());
	if (std::is_function_v<std::remove_pointer_t<TR>>) {
		if (std::is_const_v<TR>)
			res.insert(res.find(')'), " const");
		if (std::is_volatile_v<TR>)
			res.insert(res.find(')'), " volatile");
		if (std::is_lvalue_reference_v<T>) {
			if (auto p = res.find("()"); p != res.npos) {
				if (p + 3 != res.size())
					res += "()";
			}
			res.insert(res.find(')'), "&");
		} else if (std::is_rvalue_reference_v<T>) {
			if (auto p = res.find("()"); p != res.npos) {
				if (p + 3 != res.size())
					res += "()";
			}
			res.insert(res.find(')'), "&&");
		}
	} else if (std::is_array_v<std::remove_pointer_t<TR>>) {
		if (std::is_const_v<TR>)
			res.insert(res.find('['), "const ");
		if (std::is_volatile_v<TR>)
			res.insert(res.find('['), "volatile ");
		if (std::is_lvalue_reference_v<T>)
			res.insert(res.find('['), "(&) ");
		else if (std::is_rvalue_reference_v<T>)
			res.insert(res.find('['), "(&&) ");
	} else {
		if (std::is_const_v<TR>)
			res += " const";
		if (std::is_volatile_v<TR>)
			res += " volatile";
		if (std::is_lvalue_reference_v<T>)
			res += "&";
		else if (std::is_rvalue_reference_v<T>)
			res += "&&";
	}
	return res;
}

#endif /* INCLUDE_TYPE_NAME_HPP */
