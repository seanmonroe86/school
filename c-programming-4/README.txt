Compile the source code files `main.c`, `cards.c` and `poker.c` with gcc.

Execute `dealer` with `./` with valid arguments A B, where

1 <= A <= 13

1 <= B <= 13

A * B <= 52

and are integers.

###Example:

    gcc main.c cards.c poker.c -o dealer
    ./dealer 5 5
