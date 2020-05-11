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
pensons pas qu'il soit nécessaire - la classe n'utilise pas de pointeurs 
donc le constructeur par copie par défaut est suffisant.

### QUESTION 4.2

a)  Ceci n'impliquerait rien de particulier au niveau des attributs de la
    classe, car l'interface et l'implémentation sont deux choses séparées.
b)  La difficulté majeure serait qu'il y aurait un conflit entre le constructeur
    qui construit un vecteur avec ses coordonnées cartésiennes et ce nouveau
    constructeur. Ainsi il faudrait trouver une solution altérnative
    (par exemple l'ajout d'un paramètre inutile, les forges) mais ceci mène à
    d'autre problèmes - nottament l'utilisation de telles manières
    d'initialisation n'est pas naturelle et pourait mener à confusion.


### QUESTION 4.3

En réalité, nous avons décidé lors de la conception de la première partie
(première semaine) d'implémenter directement des opérateurs qui sont en 
général semblables à des opérateurs mathématiques, la définition de ces 
opérateurs semblait tout à fait naturelle.

### QUESTION 6.1

Nous avons décidé d'implémenter une class `Gyroscope` qui hérite de `Top` pour
représenter les toupies qui ne roulent pas, et qui contient leur équation de
mouvement. `SimpleCone` est une sous-classe de `Gyroscope` avec des propriétés
spécifiques au cône. Ceci nous permet dans le futur d'implémenter d'autres
toupies sans roulement, sans avoir a réécrir les équations du mouvement.

### QUESTION 7.1

La classe `Integrator` est une classe abstraite sans attributs qui ne contient
qu'une méthode virtuelle `evolve` qui évolue la toupie pour un certain pas de
temps. Les intégrateurs Euler Cromer, Newmark et
Runge-Kutta héritent toutes de la classe Integrator car toutes ces classes ont
la même fonctionalité d'un point de vue externe, seulle l'implémentation change.
Ainsi ça vient naturellement que toutes ces classes devrait être du même type
commun - `Integrator`.

### QUESTION 7.2

La classe `EulerCromerIntegrator` hérite de la classe `Integrator` car l'intégrateur
d'Euler-Cromer est un intégrateur. La classe Integrator contient la déclaration
de la méthode `evolve` pour les intégrateurs en général et la classe
`EulerCromerIntegrator` l'implémente.

### QUESTION 8.1

Il sagit d'un single dispatch - une méthode qui a le même but, mais une
implémentation différente dépendant de l'instance sur la quelle elle opère.
Dans le cas de notre projet, `draw` sert à afficher des données, mais la
manière dont les données sont affichées peut varier dynamiquement (graphisme, texte).

### QUESTION 8.2

Une manière de faire est de considérer qu'un système est une collection hétérogène
de différentes toupies, et de même pour les intégrateurs, et ainsi créer une
interface commune à toute les toupies pour la fonction `f` et une interface
commune pour la méthode des intégrateurs qui fait évoluer une toupie. Ces
méthodes sont après implémentée d'une manière différente dépendant des cas spéficique,
mais ceci n'impacte plus l'utilisation des classes d'un point de vue externe.
Ainsi on peut faire évoluer une toupie à l'aide d'un intégrateur sans se soucier de
leur type.

### QUESTION 8.3

Il faut faire attention à la gestion des pointeurs et l'espace mémoire pointé.
Il faut donc penser à définir les constructeurs par copie, destructeurs et l'opérateur
d'affectation, pour éviter des memory leaks ou que les objets pointés soient
détruits à cause d'une coupie de surface (lors de la destruction de cette copie).

### QUESTION 11.1

Nous programmons les différents indicateurs dans les classes toupies correspondante
car que l'on décide de dessiner sur l'écran ou d'afficher des valeurs numériques
l'information reste la même, seule sa représentation change de plus ces informations
sont propres à la toupie en question.
