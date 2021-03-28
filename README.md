# Code_robots
Contains codes for implementation of optimal and heuristic algorithm 

AI_Assignment_code.cpp contains the implementation of breadth-first search algorithm for finding optimal solution for warehouse problem.

AI_Assignment_code_heuristics.cpp contains the implementation of A* algorithm for finding approximate solution for warehouse problem.

Input Definition

*INDEX VARIES FROM 0 TO N-1 AND 0 TO M-1 IN GRID*
First line contains two spaced integers - n and m - n for no. of rows and m for no. of rows for the grid.

Second line contains single integers - r - no. of robots

Next r lines contain 4 spaced integers

i th line contains x, y, final_x, final_y - x and y coordinates for initial and final locations of the i th robot respectively

Next line contains single integer - t - no. of tasks

Next t lines contain 4 spaced integers

i th line contains x, y, dest_x, dest_y - x and y coordinates for initial and final locations of the i th task respectively

Next line contains single integer - te - no. of temporary locations

Next te lines contain 2 spaced integers

i th line contains x, y - x and y coordinate for the i th temporary location

Next line contains single integer - obs - no. of obstacles

Next obs lines contain 2 spaced integers

i th line contains x, y - x and y coordinate for the i th obstacle location

Example Input

3 3
1
1 1 0 2
1
0 0 2 0
0
2
0 1 2 1



