#pragma once

#include <QVector3D>

struct Vertex {
	QVector3D pos;
	QVector3D color;
	QVector3D normal;

	static int posOffset();
	static int colorOffset();
	static int normalOffset();
	static int stride();
};

inline int Vertex::posOffset() { return offsetof(Vertex, pos); }
inline int Vertex::colorOffset() { return offsetof(Vertex, color); }
inline int Vertex::normalOffset() { return offsetof(Vertex, normal); }
inline int Vertex::stride() { return sizeof(Vertex); }
