# Security-cameras-at-traffic-intersections

Project for ECE 650 Methods and Tools of Software Engineering with prof Arie Gurfinkel


## `1-Input-GraphCreation.py`
python script that creates graphs based on the intersections between the input streets.

Input:

- `a "Street Name" (x1, y1) (x2, y2) . . . (xn, yn)` where Street Name is the name of the street and xi & yi coordinates on the plane. It is used to add a street. The coordinates are itnerpreted as a poly-line segment with a line segment from (xi, yi) to (xi+1, yi+1). Each xi and yi is an integer.

- `c "Street Name" (x1, y1) (x2, y2) . . . (xn, yn)` is used to change the coordinates of a street that was specified before. 

- `r "Street Name"` is used to remove a street.

- `g` causes the program to output the corresponding graph.

Output:

Vertices with their corresponding id and edges between vertices

`V = {`

`id1: (x1,y1)`

`id2: (x2,y2)`

`id3: (x3,y3)`

`}`

`E = {`

`<id1,id2>,`

`<id2,id3>`

`}`
