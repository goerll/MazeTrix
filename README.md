# MazeTrix


# Logic behind the implementation
Cells are objects that have booleans to describe their individual state: which walls are supposed to be displayed, if it's supposed to be highlighted and if it is currently active. The class has a member function that draws the cell considering it's state.

The size of the cells, number of them and their color can all be changed with the global variables.

Mazes have a matrix, that is an array, of arrays, of Cells, where the outmost array contains the lines, and the subarrays contain the elements of each line (which are Cells). The Maze class has various member functions that are important for the implementation of the maze generating algorithms. The functions that generate the mazes also display them on screen (providing interesting visualizations of how each algorithm works).

# What currently works
- Drawing a matrix with any number of lines, on any screen size
- Binary tree maze generation algorithm
- Depth-first search maze generation algorithm

# Keybinds
- A - activate cell at mouse position
- S - deactivate cell at mouse position
- D - use depth-first search algorithm (starts at the cell at mouse position)
- B - use binary tree algorithm
- R - clear maze;
- H - highlight cell at mouse position (currently broken)
