# minishell
**Best collab ever**

*This is the first "real project", We are not alone anymore (with the amazing [Alexis](https://github.com/Cpt-Graby/))*
<br>
**The goal** : re-implement a simplified version of **bash** !
<br>
It is impossible to imagine doing it without unit testing (at least for the main functionality). It begins to be so big that a breaking change might be impossible to find if detected too late. We used gtest in order to avoid this.
<br>
Regarding the parsing and execution, there are two main ways:
1. Cover every case "by hand"
2. Create an AST
I order to do the bonuses, why decided to implement an AST which was fascinating.
