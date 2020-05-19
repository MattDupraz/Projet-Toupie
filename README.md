# Projet-Toupie

Dans notre projet, nous avons implémenté toutes les parties du barème et
quelques extensions, en particulier:
  - Toupie additionnelle (gyroscope simple)
  - Modèles graphiques qui correspondent vraiment aux formes des toupies (y
compris la toupie générale)
  - Traces (en version graphique) et indicateurs (en version texte)
  - Suivi des toupies avec la caméra

Pour le graphisme, nous avons utilisés Qt ver. 5.14.2 avec OpenGL 1.4.0 (en
particulier pour profiter de la fonctionalité gl_ClipDistance, en gardant la
possibilité d'utiliser glBegin() et glEnd())

Nous estimons, que avons chacun passé environs 4h de travail sur le projet par
semaine en moyenne.

## Compilation

Pour compiler le programme (sous Linux):
  - Pour la version graphique: `qmake project_qt.pro && make`
  - Pour la version texte: `qmake project_txt.pro && make`
  - Pour les tests unitaires: `qmake project_test.pro && make`
  - Pour compiler tout à la fois: `./build_all.sh`

Les fichers executables seraient créés dans le repertoire `bin/`. Tout autre fichier temporaire serait cree dans le repertoire `build/`.

## Utilisation

Contrôle (partie graphique):
  - Mouvement horizontal: `W`, `A`, `S`, `D`
  - Mouvement vertical: `Shift`, `Space`
  - Caméra: souris ou `←`, `↓`, `↑`, `→`
  - Afficher/cacher le sol: `F`
  - Afficher/cacher les traces: `T`
  - Suivre une toupie: `C` (mouvement directionnel pour se libérer)

Affichage des tests:
  - Les fichiers sont au format : temps    vecteur degré liberté
  1.ouvrir gnuplot
  2.taper : `plot "nom_fichier.txt" w linesp`
