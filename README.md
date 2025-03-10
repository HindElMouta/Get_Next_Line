# 📝 get_next_line

## 📌 Description
`get_next_line` est une fonction qui permet de lire un fichier ligne par ligne, en conservant en mémoire les données restantes entre chaque appel. Elle est particulièrement utile pour traiter de gros fichiers sans tout charger en mémoire.

## 🚀 Fonctionnalités
- Lit un fichier **ligne par ligne**.
- Gère un **buffer dynamique** pour optimiser la lecture.
- Prend en charge les **fichiers standards** et l'entrée **stdin**.
- Supporte plusieurs **file descriptors** en simultané (bonus).
- Assure une **gestion mémoire sécurisée**.

## 🛠️ Compilation
Pour utiliser `get_next_line`, compile-le avec ton fichier principal :

```sh
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line


## Gestion de la mémoire (Heap vs Stack) :

    La mémoire stack est utilisée pour les variables locales dans les fonctions. Par exemple, dans le code, int i; dans les fonctions comme ft_next, ft_line, etc., est alloué sur la pile.
    La mémoire heap est utilisée pour allouer dynamiquement des blocs de mémoire avec malloc, calloc, etc. Par exemple, lorsque tu utilises malloc dans ft_strjoin, ft_calloc, et dans read_file pour allouer des espaces pour les buffers et les lignes, tu utilises la mémoire heap.
    Défends la manière dont tu utilises la mémoire heap pour gérer des chaînes de caractères et les buffers qui sont modifiés à chaque appel, en expliquant que cela permet de gérer des tailles de données dynamiques sans dépasser les limites de la pile.
    Tu peux expliquer que chaque fois que tu alloues de la mémoire avec malloc ou calloc, tu t'assures de bien libérer la mémoire à la fin, ce qui évite les fuites de mémoire.

Gestion des erreurs et retour des valeurs :

    Dans ton code, tu gères correctement les erreurs avec des vérifications comme if (!var_static) et if (byte_read == -1) pour t'assurer que tu ne continues pas d'opérer avec des valeurs invalides. C’est essentiel pour éviter des comportements indéterminés.
    Explique pourquoi tu retournes NULL dans des cas où il n'y a rien à lire ou en cas d’erreur, et que c’est la norme dans des fonctions comme get_next_line où l’on attend une valeur valide ou un indicateur d'erreur.

Optimisation de la lecture avec read :

    Tu utilises le read système pour lire les fichiers par blocs de taille définie par BUFFER_SIZE. Cela permet d’éviter de charger tout le fichier en mémoire, ce qui est crucial pour des fichiers volumineux.
    Défends ta solution en expliquant que get_next_line ne lit qu'une partie du fichier à chaque appel et s’arrête dès qu’elle trouve un caractère \n ou la fin du fichier. Cela garantit que le programme ne gaspille pas de mémoire ou de temps CPU en lisant inutilement des données déjà lues.

Utilisation de la variable statique :

    Tu utilises var_static, qui est une variable statique, pour conserver l'état entre les appels à get_next_line. C’est une solution clé pour la gestion d’un état persistant, puisqu'une variable statique conserve sa valeur entre les appels de fonction, contrairement à une variable locale qui serait réinitialisée à chaque appel.
    Défends cette approche en expliquant qu’elle permet de conserver la portion du fichier qui n'a pas encore été lue, évitant ainsi de tout relire à chaque appel à get_next_line.

Comportement de get_next_line :

    get_next_line lit une ligne à la fois et retourne cette ligne avec le caractère \n à la fin, sauf si c'est la dernière ligne d'un fichier sans saut de ligne. C'est un comportement attendu qui suit la spécification du projet.
    Tu as bien géré la fin de fichier en vérifiant que lorsque la ligne lue n’est pas suivie de \n, tu n'ajoutes pas un caractère \n à la fin de cette ligne.