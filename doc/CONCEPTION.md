# CONCEPTION DU PROJET

## HIERARCHIE

* /: repertoire de base avec le fichier de compilation
* /src/: sources C++
	- main.cpp: Lancement du programme
	- vect: Vecteurs de taille variable
	- matrix3x3: Matrices de doubles 3x3
	- gl\_widget: Le main loop d'OpenGL
	- vertex\_shader.h: Indices d'attributs utilises par le vertex shader.
* /res/: resources accedees par le programme (prefix :/)
	- vertex\_shader.glsl
	- fragment\_shader.glsl
	- resources.qrc: fichier qui indexe les resources

## CLASSES

* Vector
	- on a choisi de prendre une approche qui raproche la manipulation des vecteurs a celle de la manipulation d'un type de base, c.-a-d. par des operateurs de base (+, -, ^, \*)
	- on a choisi de lancer des exeptions lors d'un mauvais traitement des vecteurs, car on considere qu'une operation entre deux vecteurs de tailles differentes n'a pas de sens et donc ne devrait pas etre permise.
		- L'exeption lance est definie dans le header file vect.h avec l'enum VectorException
* Matrix3x3
	- de meme, pour les matrices, on a choisi de utiliser les operator overloads, car c'est assez naturel pour les types algebriques.


