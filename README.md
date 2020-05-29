# Projet-Toupie

Dans notre projet, nous avons implémenté toutes les parties du barème et
quelques extensions, en particulier:
  - Toupie additionnelle (gyroscope simple)
  - Toupie générale (solide de révolution)
  - Modèles graphiques qui correspondent vraiment aux formes des toupies (y
compris la toupie générale)
  - Traces (en version graphique) et indicateurs (en version texte)
  - Suivi des toupies avec la caméra

Pour le graphisme, nous avons utilisés Qt ver. 5.14.2 avec OpenGL 1.4.0 (en
particulier pour profiter de la fonctionalité gl_ClipDistance, en gardant la
possibilité d'utiliser glBegin() et glEnd())

Nous estimons, que nous avons chacun passé environs 4h de travail sur le projet par
semaine en moyenne.

## Configuration

Tous les paramètres utilisés peuvent être facilement modifiés dans le fichier
`src/main.cpp`. Pour la construction des toupies, c.f. les headers des toupies
dans le répertoire `src/common`, le fichier `src/main.cpp` contient un exemple
de chaque toupie. Plus d'éxplications dans le fichier `src/main.cpp` lui-même.

## Compilation

Pour compiler le programme (sous Linux):
  - Pour la version graphique: `qmake project_qt.pro && make`
  - Pour la version texte: `qmake project_txt.pro && make`
  - Pour les tests unitaires: `qmake project_test.pro && make`
  - Pour compiler tout à la fois: `./build_all.sh`

En cas d'erreurs de compilation, essayer `make clean` et recompiler.

Les fichers executables seraient créés dans le repertoire `bin/`.
Tout autre fichier temporaire serait cree dans le repertoire `build/`.


## Utilisation

### Interface graphique

Pour affichage graphique, ouvrir le fichier exécutable `project_qt` (situé dans
le répertoire `bin/` après compilation)

Contrôle (partie graphique):
  - Mouvement horizontal: `W`, `A`, `S`, `D`
  - Mouvement vertical: `Shift`, `Space`
  - Caméra: `←`, `↓`, `↑`, `→`
  - Afficher/cacher le sol: `F`
  - Afficher/cacher les traces: `T`
  - Afficher/cacher la base du système de coordonnées: `Z`
  - Suivre une toupie: `C` (mouvement directionnel pour se libérer)
  - Se mettre dans le réfèrentiel d'une toupie: `R`
  - Pause: `P`
  - Un pas de temps physique en avant/arrière: `N`/`B` (il est possible de tenir
la touche)

### Mode texte

Pour affichage normal (dans la ligne de commande), simplement ouvrir le fichier
exécutable `project_txt` (situé dans le répértoire `bin/` après compilation).

Pour écrire les données dans des fichiers séparés pour analyse avec `gnuplot`
par exemple, ouvrir l'éxecutable `project_txt` avec l'option `-f` (taper
`./bin/project_txt -f` dans un terminal qui est ouvert dans le répertoire
principal du projet). Les fichiers seront créés dans un nouveau répertoire `out/`
qui sera situé dans le répertoire ouvert de la ligne de commande.

Pour afficher les données avec `gnuplot`:
  1. Ouvrir `gnuplot`
  2. Taper: `plot "nom_fichier.txt" using 1:N w linesp` où N est le numéro de la
	  colonne de la donnée spécifiée (voir en haut des fichiers pour une légende,
     attention les vecteurs P et DP contiennent un nombre variable de valeurs
     selon la toupie)

