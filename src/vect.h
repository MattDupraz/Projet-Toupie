#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <initializer_list>

class Vector {
	public:
	  	Vector() {}
		Vector(std::initializer_list<double> l)
			: coords_(l)
		{}
		Vector(Vector const& other)
			: coords_(other.coords_)
		{}
	
		void print() const;
		void augment(double val);
		double norm() const;
		double norm2() const;
		Vector unitVector() const;
		
		std::size_t size() const { return coords_.size(); }

		double get(std::size_t i) const { return coords_[i]; }
		void set(std::size_t i, double val) { coords_[i] = val; }

		double operator[](std::size_t i) const { return coords_[i]; }
		double& operator[](std::size_t i) { return coords_[i]; }

		Vector operator-() const;
		Vector operator+(Vector const& other) const;
		Vector operator^(Vector const& other) const;
		double operator*(Vector const& other) const;
		Vector operator*(double scalar) const;
		Vector operator-(Vector const& other) const;
		bool operator==(Vector const& other) const;


	private:
		std::vector<double> coords_;

};

Vector operator*(double d, Vector const& v);

#endif
