# Projet-Toupie

Pour compiler le programme (sous Linux):
  - Pour la version graphique: `qmake project_qt.pro && make`
  - Pour la version texte: `qmake project_txt.pro && make`
  - Pour les tests unitaires: `qmake project_test.pro && make`
  - Pour compiler tout a la fois: `./build_all.sh`

Les fichers executables seraient crees dans le repertoire `bin/`. Tout autre fichier temporaire serait cree dans le repertoire `build/`.
