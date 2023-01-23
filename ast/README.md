
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
    - ls && bc dontexist || echo oui     = meme chose que = (ls && bc dontexist) || echo oui
