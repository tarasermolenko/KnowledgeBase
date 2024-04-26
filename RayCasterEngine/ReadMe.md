## Raycast Wolfenstein Style Render

main idea: calculating the intersections of rays with the grid (both horizontal and vertical grid lines)
based on the properties of the map grid and the angle of each ray.
stepping through the grid cell by cell (either horizontally or vertically) until a wall is encountered.
use trigonometric operations to find the next x or y coordinate where the ray intersects grid lines, 
updating incrementally in a loop until it hits a wall or reaches the depth of field limit.


!["demoimage"](raycastdemp.png)

To compile:
gcc -Wall -O2 raycaster.c -o raycaster -lGL -lGLU -lglut -lm

To run:
/raycaster



