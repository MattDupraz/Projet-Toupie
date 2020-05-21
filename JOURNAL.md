# Journal de bord

## Semaine 2 :

Nous avons lu les objectifs et commencé par implémenter les vecteurs.  On a
choisi d'implementer les opérations sur les vecteurs a l'aide des operator
overloads, car ca nous parait la solution la plus naturelle vu que c'est un type
algébrique. On a aussi décidé d'utiliser les exceptions dans les cas des
opérations sur des vecteurs de tailles différentes, au lieu de chercher a
établir une convention, car les opérations ne sont pas mathématiquement définies
et nous estimons que les opérations mathématiquement erronées n'ont pas de sens
dans la réalisation de notre projet.

Nous avons par ailleurs aussi décidé de commencer directement avec une structure
de projet adapté à la compilation séparée. Comme nous avons aussi commencé à
explorer la libraire graphique de Qt et OpenGL, nous avons décidé d'utiliser
qmake pour gérer la compilation. Nous avons créé des répertoires séparés pour le
code source, les fichiers temporaires générés lors de la compilation, et la
sortie de la compilation, pour maintenir un ordre dans les fichier du projet.

--------------------------------------------------
## Semaine 3 :

Prise en main de d'OpenGL avec le tutoriel. Modularisation du projet suivant les
exercices sur OpenGL. Nous avons décidé de suivre l'exemple et de séparer la
compilation de la version graphique et textuelle du programme.  Nous nous sommes
familiarisés avec `qmake` pour la compilation séparée.  Nous avons finalisé la
classe Vector et commencé a implémenter les matrices 3x3.

--------------------------------------------------
## Semaine 4 :

Nous avons terminé de défninir les principaux opérateurs de la classe
"Matrix3x3" et on a créé les tests unitaires pour les classes Vector et
Matrix3x3.  Prise en main des animations OpenGL et simulation en temps réel.
Défini la classe Top (toupie) pour compléter la structure du projet, sans ayant
commencé a implémenter ses méthodes. Nous commençons a étudier le complément
mathématico-physique.

--------------------------------------------------
## Semaine 5 :

Nous avons défini la classe abstraite Integrator et la classe
EulerCromerIntegrator ainsi que les méthodes associées. Nous avons aussi défini
la classe SimpleCone et remanié la classe Matrix3x3 pour le calcul de l'inverse.
La manière dont le classes Top et Integrator dépendent une de l'autre nous
paraît pas très claire pour l'instant.

--------------------------------------------------
## Semaine 6 :

Nous avons trouvé un moyen de mettre la classe Top et Integrator en relation et
implémenté les trois intégrateurs proposés dans le complément mathématique.
Nous avons créé la classe abstraite Gyroscope qui correspond à une toupie sans
déplacement et t.q. son point de contact est contenu dans son axe de symétrie.
On a écrit les équations de mouvement pour cette classe et créé une sous-classe
SimpleCone.  On a implémenté l'affichage 3D pour le cône, ainsi que des
fonctionalités interactives pour l'affichage OpenGL - déplacement, rotation du
point de vue, affichage du sol.

--------------------------------------------------
## Semaine 7 :

On a implémenté la classe système et finalisé la simulation mode textuelle.
Nous avons ajouté le contrôle de la simulation graphique par souris, on a
implémenté la classe `Gyroscope` à la place de celle d'avant, qu'on à renomé à
`NonRollingTop`. Cette fois-ci le `Gyroscope` représente vraiment un gyroscope -
disque en rotation. On a ajouté les trajectoires de toupes au graphisme.

--------------------------------------------------
## Semaine 8 :

On implémente les tests pour les intégrateurs, les résultats seront stockés dans
un fichier. On avait un problème avec la simulation en temps réel - sur la
machine de l'EPFL une toupie n'apparaissait pas du tout, on a trouvé qu'il
s'agissait d'un problème d'intervalle de temps irrégulier, on a alors implémenté
un limite à la periode de temps simulée pour éviter des problèmes si le
programme il ralenti. On a limité la longueur des trajectoires et la fréquence à
la quelle on ajoute des points à la trajectoire (ceci dépend de la vitesse de la
toupie)

--------------------------------------------------
## Semaine 9 :

Nous avons élargi les tests aux différents intégrateurs. Nous avons implémenté
la toupie roulante et on a implémenté des VAOs et VBOs ainsi que des classes
utilitaires pour l'affichage 3D. On s'est assuré que notre code est bien
commenté.

--------------------------------------------------
## Semaine 10 :

Nous commençons l'implétentation des toupies générales. On a amelioré certains
aspets graphiques, à présent la caméra peut suivre les toupies. La toupie
chinoise est affichée correctement à présent. On a netoyé un peu notre code
ainsi que éliminé de noumbreux beugs.

--------------------------------------------------
## Semaine 11 :

Nous avons terminés les toupies générales, ainsi que leur affichage graphique.
Nous avons implémentés les indicateurs, mais pour l'instant nous avons toujours
quelques soucis. Nous avons réorganisés notre code en séparant bien chanque
classe dans un fichier séparé (le nombre de toupie devennait assez grand et on
se perdait dans le fichier qui les contennait). Nous avons reévalué quelques
aspets de conception pour les toupies, à présent la classe de base a plus de
fonctionalités communes à toutes les toupies.

--------------------------------------------------
## Semaine 12 :

On a refactoré la partie graphique, et implémenté la caméra fixé dans le
référentiel de la toupie. Nous se sommes assurés que les indicateurs marchent
bien avec chaque intégrateur, en comparant avec les résultats sur ProgMaPh. Nous
avons travaillé sur les fichiers de documentation. On a bien relu les consignes
du projet.

--------------------------------------------------
## Semaine 13 :

