#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

enum VectorException { INDEX_OUT_OF_BOUND, INCOMPATIBLE_VECTOR_SIZE };

class Vector {
	public:
	  	Vector() {}
		Vector(std::initializer_list<double> l)
			: coords_(l)
		{}
		Vector(std::size_t s)
			: coords_(s, 0.0)
		{}
	
		Vector& augment(double val);
		double norm() const;
		double norm2() const;

		std::size_t size() const { return coords_.size(); }
		double operator[](std::size_t i) const {
			if (i >= size()) throw INDEX_OUT_OF_BOUND;
			return coords_[i];
		}
		double& operator[](std::size_t i) {
			if (i >= size()) throw INDEX_OUT_OF_BOUND;
			return coords_[i];
		}

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

Vector& operator*=(Vector& u, double d);
Vector& operator+=(Vector& u, Vector const& v);
Vector& operator-=(Vector& u, Vector const& v);
