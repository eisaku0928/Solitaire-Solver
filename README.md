# Solitaire-Solver
A peg solitaire solving AI, a DFS (depth-first search) algorithm implemented in the C programming language.
The significance of this project comes from this entire project being implemented in the C programming language. At a fundamental level I implemented performing a DFS for the AI to find a solution, as well as freeing all allocated memory on the RAM. 

# What is peg solitaire?

# Usage
Compile all files using the makefile.
```
$ make pegsol
```

You can play the game with the keyboard by executing the following. There are 9 levels in total, with the first starting at level 0.

```
$ ./pegsol <level>
```
Alternatively, you can let the AI solve the level for you (my part of the implementation), by running the following command.\<budget\> is an integer indicating the budget of your search, i.e. the maximum number of expanded nodes the AI will search. 

```
./pegsol <level> AI <budget> play_solution
```

For example:
```
./pegsol 6 AI 2000000 play_solution
```
Will run the 7th level expanding 2 million nodes at maximum, and will play the solution found, on the command line. 

# Big O analysis and results summary

