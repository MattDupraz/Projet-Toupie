# REPONSES AUX QUESTION

## SEMAINE 2

### QUESTION 1.1

Nous avons choisi de représenter des vecteurs par des objets 
du type `vector` (des tableaux de taille variable) car le 
programme doit pouvoir augmenter un vecteur d'une coordonnée 
par le biais de la méthode `augmente()`.

Nous avons défini comme attribut privé un objet du type `vector` 
qui contient les coordonnées du vecteur. Celles-ci sont accessibles 
et modifiable de l'extérieur a l'aide de l'opérateur `[]`. Toutes 
les méthodes qu'on a implementées sont publiques. Nous avons choisi 
d'implémenter les opérations sur les vecteurs à l'aide de la surcharge 
d'opérateurs, qu'on a placé à l'extérieur de la classe.

### QUESTION 1.2

On a décidé d'utiliser les exceptions dans les cas des opérations sur 
des vecteurs de tailles différentes, au lieu de chercher a établir une 
convention, car les opérations ne sont pas mathématiquement définies et 
nous estimons que les opérations mathématiquement erronées n'ont pas de sens
dans la réalisation de notre projet.

### QUESTION 4.1

Un `Vector` est constructible a l'aide d'un `initializer_list<double>`
pour créer le vecteur avec des valeurs spécifiques, ou d'un
`size_t` pour créer un vecteur nulle de la dimension spécifié.
Nous n'avons pas implementé de constructeur par copie, car nous ne
pensons pas qu'il soit nécessaire, le constructeur par copie 
par défaut est suffisant.

### QUESTION 4.2

a)  Cela impliquerait de définir de nouveaux attributs ainsi que de 
    nouveaux getters et setters et des méthodes privées qui puissent
    "faire la mise à jour" entre les attributs en représentation 
    cartésiennes et sphériques

b)  La difficulté majeure serait l'initialisation car la surcharge 
    des constructeurs serait ambiguë même si cela peut se contourner.


### QUESTION 4.3

En réalité, nous avons décider lors de la conception de la première partie
(première semaine) d'implémenter directement des opérateurs qui sont en 
général semblables à des opérateurs mathématiques, la définition de ces 
opérateurs semblaient tout à fait naturelle.

### QUESTION 6.1

La classe ConeSimple hérite tout naturellement de la classe Toupie car 
un cone simple est une toupie.

### QUESTION 7.1

La classe Integrator est une classe abstraite sans attributs qui ne contient
qu'une méthode vituelle integ. Les classes EulerCromerIntegrator, Newmark et
Runge_Kutta hérite toutes de la classe Integrator car toutes ces classes sont
des intégrateurs de plus l'utilisation du polymorphisme est toute trouvée car
nous voulons appliquer un traitement similaire à des objets différents
(les intégrateurs en l'occurence).

### QUESTION 7.2

La classe EulerCromerIntegrator hérite de la classe Integrator car l'intégrateur
d'Euler-Cromer est un intégrateur.













