#pragma once
#include <memory>
#include <vector>
#include <ostream>
#include "Point.hpp"

class PolyLine {
	std::shared_ptr<std::vector<Point>> _points;

public:
	PolyLine() {
		_points = std::make_shared<std::vector<Point>>();
	}

	PolyLine(const PolyLine& other) {
		_points = other._points;
	}

	PolyLine(PolyLine&& other) noexcept {
		_points = std::move(other._points);
	}

	PolyLine& operator=(const PolyLine& other) {
		_points = other._points;
		return *this;
	}

	PolyLine& operator=(PolyLine&& other) noexcept {
		_points = std::move(other._points);
		return *this;
	}

	friend PolyLine& operator+=(PolyLine& lhs, Point rhs) {
		if (!lhs._points.unique()) {
			lhs._points = std::make_shared<std::vector<Point>>(*lhs._points);
		}
		lhs._points->push_back(std::move(rhs));
		return lhs;
	}

	operator bool() const {
		return !_points->empty();
	}

	friend std::ostream& operator<<(std::ostream& out, const PolyLine& polyLine) {
		out << "PolyLine {";
		for (const Point& point : *polyLine._points) {
			out << " (" << point.x << ", " << point.y << ")";
		}
		out << " }";
		return out;
	}
};