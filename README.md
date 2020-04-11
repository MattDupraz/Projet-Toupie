# Projet-Toupie

Pour compiler le programme (sous Linux):
  - Pour la version graphique: `qmake project_qt.pro && make`
  - Pour la version texte: `qmake project_txt.pro && make`
  - Pour les tests unitaires: `qmake project_test.pro && make`
  - Pour compiler tout a la fois: `./build_all.sh`

Les fichers executables seraient crees dans le repertoire `bin/`. Tout autre fichier temporaire serait cree dans le repertoire `build/`.

Contrôle:
  - Mouvement horizontal: `W`, `A`, `S`, `D`
  - Mouvement vertical: `Shift`, `Space`
  - Caméra: souris ou `←`, `↓`, `↑`, `→`
  - Afficher/cacher le sol: `F`
  - Afficher/cacher les trajectoires: `T`
  - Libérer la souris: `Esc`

Affichage des tests:
  - Les fichiers sont au format :    1           2               3               4
                                   temps - 1e composante - 2e composante - 3e composante
  1.ouvrir gnuplot
  2.taper : `plot "nom_fichier.txt" u 1:n linesp
  3.n est un entier entre 2 et 4