FAP08 Archive. 
R. Montemanni and D.H. Smith

The graphs of the archive have been used for the experiments reported in the manuscript "Heuristic manipulation, tabu search and frequency assignment".

The files containing the description of graphs have the sintax described in the reminder of this document. 

Nodes of the graph are identified by consecutive numbers starting from 0. E.g. if we have 6 nodes, we will have the following lables: 0, 1, 2, 3, 4, 5.

Each line of the file represents a constraint, and has the following format:

a	b	R	>	s	p

where: 

"a" and "b" are indexes of nodes. 

"R" and ">" are control characters. 

"s" is separation required between "a" and "b" minus 1 (e.g. we require "a" and "b" to be at least "s+1" frequencies apart. 

"p" is finally the penalty to be paid if the constraint is not respected.

Notice that the number of nodes of the graph can be inferred by analysing all the constraints.
