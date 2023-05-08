## Convention ##

### Naming ###
+ **Sufixes**
    + It is more helpful in `distinguishing` and `identifying` the type of items.
    + `Syntax highlight` is good at distinguishing the type of items but its not good at identifying them because `the syntax high color` is different among `IDEs`, `Text Editors`, and `Themes`.
    + List of Sufixes:
        + Interface, Enum: 
            + `_i` : `Interface` (allow multiple inheritable but not allow public constructor)
        + Variable, Constant:
            + `_` : `Member Variable` (use for private or protected member only)
            + `_s` : `Static Variable`
            + `_g` : `Global Variable`
            + `_p` : `Pointer`
            + `_pp` : `2nd Level Pointer`
            + `_ppp...` (**there are n "p"**) : `n-th Level Pointer`
        + Template:
            + `_t` : `Template`
            + `__` : `Template Argument`
        + Multiple Prefixes:
            + Non-template:
                + `_p_` : `Member Pointer`
                + `_ps` : `Static Pointer`
                + `_pg` : `Global Pointer`
            + Template:
                + `_pt` : `Pointer Template`
                + `_pt_` : `Member Pointer Template`
                + `_pst` : `Static Pointer Template`
                + `_pgt` : `Global Pointer Template`
                + `_it` : `Interface Template`

+ **Casings**
    + Camel Case:
        + `Variable` (**lower case**)
    + Snake Case:
        + `Macro` (**upper case**)
        + `Constant` (**upper case**)
        + `Struct` (**lower case**)
        + `Class` (**lower case**)
        + `Enum` (**lower case**)
        + `Union` (**lower case**)
        + `Function` (**lower case**)
        + `Template` (**lower case**)
        + `Namespace` (**lower case**)