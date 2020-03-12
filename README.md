# Projet-Toupie

Pour compiler le programme:
1. S'assurer que toutes les sources et headers necessaires sont inclus dans le fichier `project.pro`
2. Generer le Makefile pour la compilation (choisir *une* des options suivantes):
  - Pour la version graphique: `qmake project_qt.pro`
  - Pour la version texte: `qmake project_txt.pro`
  - Pour les tests unitaires: `qmake project_test.pro`
3. Executer `make` dans le repertoire de base du projet.

Le ficher executable serait cree dans le repertoire `bin/`. Tout autre fichier temporaire serait cree dans le repertoire `build/`.

Pour tout compiler a la fois, vous pouvez utiliser le script `build_all.sh`
