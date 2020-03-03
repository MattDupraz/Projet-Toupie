# CONCEPTION DU PROJET

## HIEROGRAPHIE

* /: repertoire de base avec le fichier de compilation
* /src/: sources C++
	- main.cpp: Lancement du programme
	- vect.h: Headers pour la classe Vector
	- vect.cpp: Implementation de la classe Vector
	- gl\_widget.h: Headers pour le main loop d'OpenGL
	- gl\_widget.cpp: Implementation du main loop d'OpenGL
	- vertex\_shader.h: Indices d'attributs utilises par le vertex shader.
* /res/: resources accedees par le programme (prefix :/)
	- vertex\_shader.glsl
	- fragment\_shader.glsl
	- resources.qrc: fichier qui indexe les resources

## CLASSES

* Vector
	- on a choisi de prendre une approche qui raproche la manipulation des vecteurs a celle de la manipulation d'un type de base, c.-a-d. par des operateurs de base (+, -, ^, \*)
	- la taille du vecteur est dynamique, ce qui mene a un probleme quand on fait des operations sur des vecteurs de tailles differentes (a resoudre)


