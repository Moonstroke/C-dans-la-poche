# C (dans la poche !)

> Ce dépôt, comme beaucoup parmi tous les miens, me sert à ranger des bricoles.

En l'occurence, mes programmes et ébauches de programmes en C,
parce que j'ai envie d'apprendre le C.

(Java étant un langage pour les *noobs*.)

Tous mes programmes sont rangés dans des sous-dossiers, chacun correspondant à un programme ou
projet indépendant.


## dossier liste

Ce dossier est une implémentation d'une liste d'entiers sous forme d'un `struct`,
ça ressemeble beaucoup à de l'orienté objet, mais avec de la gestion de mémoir dynamique en plus,
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
Ne fonctionne pas encore (`segfault` \o/)


