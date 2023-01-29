# NCPP Naming Convention #
## Sufixes: ##
+ It is more helpful in `distinguishing` and `identifying` the type of items.
+ `Syntax highlight` is good at distinguishing the type of items but its not good at identifying them because `the syntax high color` is different among `IDEs`, `Text Editors`, and `Themes`.
+ List of Sufixes:
    + Interface, Enum:
        + **_i** : `Interface` (allow multiple inheritable but not allow public constructor)
        + **_e** : `Enum`
    + Variable, Constant:
        + **_** : `Member Variable` (use for private or protected member only)
        + **_s** : `Static Variable`
        + **_g** : `Global Variable`
        + **_p** : `Pointer`
        + **_pp** : `2nd Level Pointer`
        + **_ppp...** (there are n "p") : `Nth Level Pointer`
        + **_l** : `LValue Reference`
        + **_r** : `RValue Reference`
        + **_u** : `Universal Reference`
    + Template:
        + **_t** : `Template`
    + Multiple Prefixes:
        + Non-template:
            + Member:
                + **\__p\__** : `Member Pointer`
                + **\__l\__** : `Member LValue Reference`
                + **\__r\__** : `Member RValue Reference`
                + **\__u\__** : `Member Universal Reference`
            + Static:
                + **_ps** : `Static Pointer`
                + **_ls** : `Static LValue Reference`
                + **_rs** : `Static RValue Reference`
                + **_us** : `Static Universal Reference`
            + Global:
                + **_pg** : `Global Pointer`
                + **_lg** : `Global LValue Reference`
                + **_rg** : `Global RValue Reference`
                + **_ug** : `Global Universal Reference`
        + Template:
            + Ordinary:
                + **_pt** : `Pointer Template`
                + **_lt** : `LValue Reference Template`
                + **_rt** : `RValue Reference Template`
                + **_ut** : `Universal Reference Template`
            + Member:
                + **\__pt\__** : `Member Pointer Template`
                + **\__lt\__** : `Member LValue Reference Template`
                + **\__rt\__** : `Member RValue Reference Template`
                + **\__ut\__** : `Member Universal Reference Template`
            + Static:
                + **_pst** : `Static Pointer Template`
                + **_lst** : `Static LValue Reference Template`
                + **_rst** : `Static RValue Reference Template`
                + **_ust** : `Static Universal Reference Template`
            + Global:
                + **_pgt** : `Global Pointer Template`
                + **_lgt** : `Global LValue Reference Template`
                + **_rgt** : `Global RValue Reference Template`
                + **_ugt** : `Global Universal Reference Template`

## Casings: ##
- Camel Case:
    + **Variable** (lower case)
    + **Struct** (lower case)
    + **Class** (lower case)
    + **Enum** (lower case)
    + **Union** (lower case)
    + **Function** (lower case)
    + **Template** (lower case)
    + **Namespace** (lower case)
- Snake Case:
    + **Macro** (upper case)
    + **Constant** (upper case)