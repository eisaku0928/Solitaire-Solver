# Solitaire-Solver
An AI algorithm to solve Peg Solitaire (also known as Brainvita in India), implemented in the C programming language. This project increased my dexterity with dynamic memory allocation, data structures, and a graph traversal algorithm. Rules of the game are discussed in "The Game" subsection. 

Solving Peg Solitaire belongs to a class of problems known as _NP-Complete_, famously including the _Travelling Salesman Problem_ as an example. NP-completeness of Peg Solitaire is discussed in [this paper](https://dspace.jaist.ac.jp/dspace/bitstream/10119/4709/1/3951.pdf) These are problems that run in exponential time as a function of the size of the problem, even with the best algorithms. 

\<gif\>

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

```
./pegsol <level> AI <budget> play_solution
```

For example:
```
./pegsol 6 AI 2000000 play_solution
```
Will run the 7th level expanding 2 million nodes at maximum, and will play the solution found, on the command line. 

## The Game
Peg Solitaire was invented in the 17th century in Madagascar, and rules appear in a french cultural magazine in 1687. As a classic board game puzzle, several boards exist, differing in shape and size. The game is available for playing by compiling the code in this repository and using the keyboard, or using [a web version of the game](https://www.pegsolitaire.org/). 

As explained in this [wikipedia page](https://en.wikipedia.org/wiki/Peg_solitaire#Play), this is a single player game of moving a "peg" over another adjacent peg, if there is a free cell to land across it. Four jumps are available: left, right, up, and down. The objective is to clean the board until there is only 1 peg left. 

Though the code was adapted from the open-source terminal version made available by [Maurits van der Schee](https://github.com/mevdschee/peg-solitaire.c), I have implemented the AI solver, and all files are included in the src file. 

## Big-O Analysis

