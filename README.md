# C (dans la poche !)

> Ce dépôt, comme beaucoup parmi tous les miens, me sert à ranger des bricoles.

En l'occurence, mes programmes et ébauches de programmes en C,
parce que j'ai envie d'apprendre le C.

(Java étant un langage pour les *noobs*.)

Tous mes programmes sont rangés dans des sous-dossiers, chacun correspondant à un programme ou
projet indépendant.


## dossier liste

Ce dossier est une implémentation d'une liste d'entiers sous forme d'un `struct`,
ça ressemble beaucoup à de l'orienté objet, mais avec de la gestion de mémoire dynamique en plus,
et des pointeurs : beaucoup plus fun.


## dossier C-CGI

Ce dossier contient une ébauche de programme *CGI* écrit en C.
Il possède une interface simpliste, et permet d'afficher un texte rentré par l'utilisateur :
support des méthodes *GET* et *POST*.

Pour utiliser ce programme dans un terminal, exécutez :

    $ export REQUEST_METHOD=GET

pour accéder à la page en méthode *GET* (formulaire simple, demande d'entrée d'un champ), ou :

    $ export REQUEST_METHOD=POST
    $ export CONTENT_LENGTH=<N>
    $ ./a.out << EOF
    data=<j'aime le C>
    EOF

ou

    $ montexte="data=du texte"
    $ ./a.out <<< $montexte

pour émuler un envoi de formulaire. Adaptez les valeurs de *CONTENT_LENGTH* pour qu'elle corrseponde
(au minimum) à la valeur donnée en entrée du programme.


## dossier JSON-parser

Un simple parseur JSON.
Ne fonctionne pas encore (`SEGFAULT` \o/)


## dossier Deadfish

Un interpréteur [Deadfish <sup>(en)</sup>](https://esolangs.org/wiki/Deadfish),
un *langage ésotérique* des plus particuliers, mais aussi des plus simples à programmer :

Il y a une valeur en mémoire, de valeur comprise entre 0 et 256, et quatre caractères-commandes :
- `i`, qui incrémente la valeur,
- `d`, qui décrémente la valeur,
- `s`, qui porte la valeur au carré, et
- `o`, qui affiche la valeur numérique de la valeur à l'écran.

***C'EST TOUT***

L'interpréteur peut lire un programme depuis la ligne de commande, ou s'il est lancé sans arguments,
affiche un interpréteur interctif, avec comme *prompt*, `>> `.

