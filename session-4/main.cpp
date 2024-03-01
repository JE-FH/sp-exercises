
#include <iostream>
#include "PolyLine.hpp"
#include <sstream>
#include <cassert>


int main() {
	PolyLine line;
	line += Point { 1, 3 };
	line += Point { 4, 5 };
	PolyLine line2 = line;
	PolyLine line3 = line;

	line += Point { 6, 7 };
	
	std::ostringstream lineOut;
	std::ostringstream line2Out;
	std::ostringstream line3Out;

	lineOut << line;
	line2Out << line2;
	line3Out << line3;

	assert(lineOut.str() == "PolyLine { (1, 3) (4, 5) (6, 7) }");
	assert(line2Out.str() == "PolyLine { (1, 3) (4, 5) }");
	assert(line3Out.str() == "PolyLine { (1, 3) (4, 5) }");
}

