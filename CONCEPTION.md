# Conception du Projet

Le projet est divisé en 3 parties:

  1. Partie commune (la partie physique du projet)
  2. Partie affichage textuel 
  3. Partie affichage graphique

Ces trois parties sont séparées dans les répertoires `/src/common`,
`/src/txt`, `/src/qt` respectivement 
 
De plus nous avons un petit module séparé où on effectue les tests unitaires,
situé dans le répartoire `/src/test`

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
      - GeneralTop (toupie constituée de plusieurs disques)
    - ChineseTop (toupie de la forme d'une sphére tronquée, roulante)
- Integrator (intégrateur, fait évoluer les toupies dans le temps)
  - EulerCromerIntegrator
  - NewmarkIntegrator
  - RungeKuttaIntegrator

Cette hierarchie nous a permi de bien prendre avantage du polymorphisme et de
éviter la réutilisation du code autant que possible.

Nous avons aussi dans cette partie 2 fichiers contenant des fonctions/variables
utilitaires
- `math_utils.h`/`math_utils.cpp`
- `constants.h`/`constants.cpp` (contient la constante g, dans un namespace dédié)

## Partie affichage textuelle

Cette partie consiste uniquement de la class ViewText qui contient les méthodes
d'affichage et le fichier `main_txt.cpp` contenant la boucle principale pour la
partie textuelle.

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

De plus, dans le répertoire `/res` se situent les codes sources des deux shaders
utilisés (vertex et fragment)

Nous avons aussie un fichier contenant un enum des attributs du vertex shader
(`vertex_shader.h`) ainsi que le fichier `main_qt.cpp` contenant la boucle
principale de la partie graphique.
