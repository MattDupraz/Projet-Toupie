#pragma once

#include <QVector3D>

// Structure de donnée qui nous permet de travailler avec les données
// envoyées à la mémoire
// du GPU (pour communiquer les objets 3D au cache du shader) d'une
// manière native à C++
struct Vertex {
	// Attributs identiques à ceux définis dans le shader
	QVector3D pos;
	QVector3D color;
	QVector3D normal;

	// Donne les tailles en bit des différentes valeurs
	static int posOffset();
	static int colorOffset();
	static int normalOffset();
	// Taille de toute la structure de données
	static int stride();
};

inline int Vertex::posOffset() { return offsetof(Vertex, pos); }
inline int Vertex::colorOffset() { return offsetof(Vertex, color); }
inline int Vertex::normalOffset() { return offsetof(Vertex, normal); }
inline int Vertex::stride() { return sizeof(Vertex); }
