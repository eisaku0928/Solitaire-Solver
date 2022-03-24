# Solitaire-Solver
An AI algorithm to solve Peg Solitaire (also known as Brainvita in India), implemented in the C programming language. This project increased my dexterity with dynamic memory allocation, data structures, and a graph traversal algorithm. When the AI solver is called,  Usage of the AI and the program is indicated at the bottom of this page.

Solving Peg Solitaire belongs to a class of problems known as _NP-Complete_, famously including the _Travelling Salesman Problem_ as an example. NP-completeness of Peg Solitaire is discussed in [this paper](https://dspace.jaist.ac.jp/dspace/bitstream/10119/4709/1/3951.pdf) These are problems that run in exponential time as a function of the size of the problem, even with the best algorithms. 

\<gif\>

## The Game
Peg Solitaire was invented in the 17th century in Madagascar, and rules appear in a french cultural magazine in 1687. As a classic board game puzzle, several boards exist, differing in shape and size. The game is available for playing by compiling the code in this repository and using the keyboard, or using [a web version of the game](https://www.pegsolitaire.org/). 

As explained in this [wikipedia page](https://en.wikipedia.org/wiki/Peg_solitaire#Play), this is a single player game of moving a "peg" over another adjacent peg, if there is a free cell to land across it. Four jumps are available: left, right, up, and down. The objective is to clean the board until there is only 1 peg left. 

The code was adapted from the open-source terminal version made available by [Maurits van der Schee](https://github.com/mevdschee/peg-solitaire.c). I implemented the AI solver function, and all files are included in the src file. 

## The AI algorithm
The possible configurations of the game is a tuple made of an _m x m_ grid board, called a _state_. The graph for the algorithm to search the solution _G = <V, E>_ is implicitly defined, where _V_ is all possible configurations (the state space), and edges _E_ are the legal jump actions that connect two vertices. Each node of the graph contains information about the state of the board (among others like pointers to parent nodes, the depth of the node, the action taken to create the node, etc.). Solution is found using DFS (depth-first search), and the maximum number of expanded nodes (called the "budget") are set by the user. Duplicates states have been checked and avoided during search. The algorithm returns the best solution found, i.e. the path leading to the least number of remaining pegs. The game engine will execute this solution live on the console. 

## Usage
Compile all files using the makefile.
```
$ make pegsol
```

You can play the game with the keyboard by executing the following. There are 9 levels in total, with the first starting at level 0.

```
$ ./pegsol <level>
```
Alternatively, you can let the AI solve the level for you (my part of the implementation), by running the following command.\<budget\> is an integer indicating the budget of your search, i.e. the maximum number of expanded nodes the AI will search. 

Use the enter/return key to select and deselect a peg, and use arrow keys to indicate which direction to move the peg in. A peg can move only if it can jump over an adjacent peg and land on empty space. Quit, restart, and undo keys are: "q", "r", and "u". 

```
./pegsol <level> AI <budget> play_solution
```

For example:
```
./pegsol 6 AI 2000000 play_solution
```
Will run the 7th level expanding 2 million nodes at maximum, and will play the solution found, on the command line. 


