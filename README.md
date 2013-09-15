google
======

This is code I'm working on while I study for the google interview

I'm using it to demo:
hash tables
stacks
linked list
anything else as I work on the project.

The concept is simple.  I'm pulling a large (26MB) dictionary file fromm 
the gutenburg project.  It has words in all caps on a line by themselves and definition text afterwards using the first line of the defintion keyword DEFN:.

I intend to use gnu regex api to find the word, put it on the stack and then find the corresponding definition text afterwards and put each line on the stack as I parse them.

When i have the word and defintion lines complete, I'll pop them and build an entry for the hash table.  The key will be the word and the value for the table will be the definition text.  The hash table index based on the key will be a simple xor16 and I will store collisions with linked lists.

Afterwards I hope to do definition lookup from the hash table.

I'm hoping this will demo my abiltiy to implement the elementary data structures, ability to implement a working project, unit tests and ability to use git.

