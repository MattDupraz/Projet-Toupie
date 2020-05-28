# Conception du Projet

Le projet est divisé en 3 parties:

  1. Partie commune (la partie physique du projet)
  2. Partie affichage textuel 
  3. Partie affichage graphique

Ces trois parties sont séparées dans les répertoires `src/common`,
`src/txt`, `src/qt` respectivement 
 
De plus nous avons un petit module séparé où on effectue les tests unitaires,
situé dans le répertoire `src/test`

## Partie commune

La partie commune consiste des classes suivantes:

- Vector (vecteurs de `double` à taille variable)
- Matrix3x3 (matrices de `double` de dimension 3x3)
- View (interface d'affichage des objets dessibables)
- Drawable (objet dessinable)
  - System (monde "physique")
  - Top (toupie abstraite)
    - NonRollingTop (classe abstraite qui généralise la notion de toupie qui ne
roule pas)
      - SimpleCone (toupie conique simple)
      - Gyroscope (gyroscope simple)
    - GeneralTop (toupie générale constituée de plusieurs disques)
    - ChineseTop (toupie de la forme d'une sphére tronquée, roulante)
- Integrator (intégrateur, fait évoluer les toupies dans le temps)
  - EulerCromerIntegrator
  - NewmarkIntegrator
  - RungeKuttaIntegrator

Cette hierarchie nous a permi de bien prendre avantage du polymorphisme et de
éviter la réutilisation du code autant que possible.

Nous avons aussi dans cette partie 2 fichiers contenant des fonctions/variables
utilitaires
- `math_utils.h`/`math_utils.cpp` (contient des fonctions mathématiques
utilitaires, dans un namespace dédié)
- `constants.h`/`constants.cpp` (contient la constante g, dans un namespace dédié)

La classe Top ne contient pas d'information sur la toupie, apart des degrés de
liberté, à la place elle fourni des accesseurs virtuels qui sont implémentées
par les sous-classes. Cette manière de faire à étée choisie en particulier car
chaque toupie contient des variables différentes dans les vecteurs P et DP, et
gèrent la position de la toupie d'une manière distincte - par exemple
NonRollingTop contient la position de la toupie dans une variable `A` qui ne
change pas, quand à GeneralTop, elle contient la position de la toupie comme un
des éléments de `DP`, ainsi les deux classes implémentent la méthode `x()`
différemment.

La classe Top contient des méthodes qui calculent des variables qui sont
communes à toutes les toupies (par exemple sa matrice d'inertie par rapport à
un certain point).

On a choisi de faire hériter SimpleCone et Gyroscope de NonRollingTop, car elles
marchent d'une manière similaire - les variables sont traités de la même
manière, et les équations du mouvement sont les mêmes. Conceptuellement les deux
sont des toupies qui ne roulent pas, donc cette hierarchie fait sens.

## Partie affichage textuelle

Cette partie consiste uniquement des classes ViewText et ViewFile, qui héritent
les deux de View. ViewText s'occupe de l'écriture à la ligne de commande,
ViewFile s'occupe de l'écriture dans des fichiers. Le choix entre les deux est
fait lors de l'éxecution - l'argument de ligne de commande `-f` permet de
choisir la vue ViewFile à la place de ViewText.

On a choisi de ne pas séparer ces deux versions, car elles ne nécessitent pas de
libraires en plus, contrairement au cas de l'affichage graphique.

## Partie affichage graphique

Cette partie consiste des classes suivantes:

- ViewOpenGL (classe qui s'occupe de l'affichage graphique)
- GLWidget (classe qui représente la fenètre affichée par Qt)
- GLMesh (forme 3D, encapsule les VBOs et VAOs pour l'affichage des formes
  compliquées)
  - GLCone
  - GLCylinder
  - GLCircle
  - GLSphere
- GLUniform (interface pour accéder et modifier les valeurs uniformes passées au
  shaders)
- Vertex (structure de données identiques à celle passée au vertex shader)

De plus, dans le répertoire `res` se situent les codes sources des deux shaders
utilisés (vertex et fragment)

Nous avons aussie un fichier contenant un enum des attributs du vertex shader
(`vertex_shader.h`)

On a décidé de compiler la partie graphique séparément de la partie textuelle,
car ainsi on peut quand même compiler le code si il y a des problèmes avec la
partie graphique.

On a créé des classes séparés pour les objets déssinés, car ceci nous permet de
ne pas avoir à recalculer leur forme à chaque dession. Les formes sont de
dimensions fixés et doivent être transformées avec des matrices pour être
dessinés correctement. On a fixé les couleurs de ces formes.

GLUniform est une classe qui encapsule les valeurs des shaders, ceci nous permet
d'avoir une copie locale (sur le CPU) des variables, qu'on peut syncroniser à tout
temps.

GLWidget s'occupe de la boucle principale, de l'évolution du système et des
contrôles clavier. L'affichage est géré dans ViewOpenGL. Ceci permet bien de
séparer la partie logique de l'interface de la partie aéstétique.
