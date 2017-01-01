# Futoshiki Solver

This application uses backtracking to solve Futoshiki puzzles of varying sizes (from 4x4 to 9x9).

Clicking the larger squares will cycle through valid digits (from 1 to size). 
The sequence returns to a blank square (representing an unknown value) before restarting.

Clicking the smaller squares will cycle through possible inequality relationships between 
adjacent larger squares. The sequence is:
1. left/top < right/bottom 
2. left/top > right/bottom  
3. no relationship between left/top and right/bottom.

Use the dropdown to select the board size. Do note that changing the size will clear 
the currently inputted puzzle.

The application supports a loading functionality that allows the user to read in a puzzle
from a text file. The accepted format is as follows:
1. The first line contains an integer n such that 4 <= n <= 9
2. The next n lines contain 2n - 1 integers representing a row in the puzzle
3. If n % 2 == 0, then the odd-indexed integers represent intra-row inequality relationships,
and the even-indexed integers represent the numbers in the puzzle.
4. Otherwise, the even-indexed integers represent intra-column inequality relationships and the
odd-indexed integers have no meaning.

The user will be alerted if they attempt to load an improperly formatted file.