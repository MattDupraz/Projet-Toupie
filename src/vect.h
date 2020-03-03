#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

class Vector {
	public:
	  	Vector() {}
		Vector(std::initializer_list<double> l)
			: coords_(l)
		{}
		Vector(std::size_t s)
			: coords_(s, 0.0)
		{}
		Vector(Vector const& other)
			: coords_(other.coords_)
		{}
	
		void augment(double val);
		double norm() const;
		double norm2() const;

		std::size_t size() const { return coords_.size(); }
		double operator[](std::size_t i) const { return coords_[i]; }
		double& operator[](std::size_t i) { return coords_[i]; }

	private:
		std::vector<double> coords_;

};

std::ostream &operator<<(std::ostream& os, Vector const& v);
Vector operator*(double d, Vector const& v);
Vector operator*(Vector const& v, double d);
Vector operator~(Vector const& v);
Vector operator-(Vector const& v);
Vector operator+(Vector const& u, Vector const& v);
Vector operator-(Vector const& u, Vector const& v);
Vector operator^(Vector const& u, Vector const& v);
double operator*(Vector const& u, Vector const& v);
bool operator==(Vector const& u, Vector const& v);
