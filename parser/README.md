# Bon a savoir
- pas besoin d'interpreter les ';', les (d)quotes non fermee, et les \   
    - Est-ce qu'on affiche juste rien ?

- Gérer ’ (single quote) qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets.
- Gérer " (double quote) qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets sauf le $ (signe dollar).
    - Ca veut dire qu'on ne doit pas interpreter les \" et autre truc louche ??


# Priorite en bash
- avec && et || -> ltr (left to right)
    - `ls && bc dontexist || echo oui`   =   `(ls && bc dontexist) || echo oui`

- avec les pipes et les redirection : je crois que les pipes sont prioritaire
    - https://unix.stackexchange.com/questions/163479/pipes-redirection-binding-precedence-with-disjuncts-conjuncts-etc
	- `< >`   >   `|`   >   `&& ||`
    - `ls || ls | cat -e`  =  `ls || (ls | cat -e)`
    - `ls | cat -e > file` =  `(ls | cat -e) > file` ( pas sure ... )
