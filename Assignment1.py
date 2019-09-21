# https://notebooks.azure.com/arie-gurfinkel/projects/ece650-py

### LIBRARIES
import sys
from __future__ import print_function
import re
from __future__ import division

# Street
class Street(object):
    def __init__(self, street_name, coord):
        self.street_name = string(street_name)
        self.coord = coord
    def __repr__(self):
        return '({})'.format(self.street_name)
    def __str__(self):
        return repr()

# Point (Controlling how it prints) 
class Point(object):
    #inicialization
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)
    #how to be printed for developers
    def __repr__(self):
        return '({0:.2f}, {1:.2f})'.format(self.x, self.y)
    # how to be printed for everyone else
    def __str__(self):
        return repr(self)
# Line
class Line(object):
    def __init__(self, p1, p2):
        self.src = p1
        self.dst = p2
    def __repr__(self):
        return repr(self.src) + '-->' + repr(self.dst)

### PARSING (in: String, Out: 1-4)
def parse_line(inline):

    sp = inline
    # Extracting command
    cmd = sp[0]

    # Checking command
    if cmd not in "acrg":
        raise Exception("Unknown command: The command should only be one of the following options: 'c', 'a', 'r', or 'g '")

    
    # Parsing Street Name
    street_name = re.findall(r'["][a-zA-Z0-9 ]+["]',sp)

    if len(street_name) !=1:
        raise Exception('Invalid Input: Remember to add exactly one "Street Name" within quotation marks')

    # Checking for space after the command
    if sp[1] != " ":
        raise Exception('Invalid Input: Remember to have exactly one space bafter the Command')
    
    #initializing coordinates
    coordinates = None

    if cmd == 'a' or cmd == 'c':
        coordinates = re.findall(r'[\(][-]?[0-9]+[,][-]?[0-9][\)]',sp)
        opening = sp.count('(')
        closing = sp.count(')')
        if len(coord) != opening:
            raise Exception("Invalid Input: remember to add the coordinates between an opening and a closing parentheses")
        if len(coord) != closing:
            raise Exception("Invalid Input: remember to add the coordinates between an opening and a closing parentheses")
    if cmd == 'r':
        remove_street()

    elif cmd == 'g':
        graph_buider()
    else:
        raise Exception("Unknown command: The command should only be one of the following options: c, a, r, or g")
   
    

    # Command a or c Checking minimum lenght of input = 16
    # if len(sp) < 16:
    #     raise Exception('Your input is too short. It seems like you are forgetting something.')
    


    if inline[0] == 'c':
        if len(sp) > 1:
            raise Exception("Error: too many arguments for 'c' command")
    

    if len(sp) > 2:
        raise Exception('Error: too many arguments')
    if len(sp) == 0:
        raise Exception('Error: too few arguments')

    return (sp[0], num)


### STREET DB

### GRAPH BUILDER
# Compute intersection
#wikipedia
#When lines are parallel there might be a division by 0
def intersect (l1, l2):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.src.x, l1.src.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.src.x, l2.src.y
       
    
    tnum = (x1-x3)*(y3-y4)-(y1-y3)*(x3-x4)
    tden = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4)

    t = tnum/tden

    unum = (x1-x2)(y1-y3)-(y1-y2)(x1-x3)
    # uden = (x1-x2)(y3-y4)-(y1-y2)(x3-x4)
    u=unum/tden
    
    xcoor = x1+t*(x2-x1)
    ycoor = y1+t*(y2-y1)


    return Point(xcoor, ycoor)

# l1 = Line(Point(0, 0), Point(5, 5))
# l2 = Line(Point(5, 0), Point(0, 5))

# intersect(l1, l2)
    
### GRAPH


### GRAPH PRINTER


### MAIN()

def main():

    ### sample code to read from stdin.
    ### make sure to remove all spurious print statements as required
    ### by the assignment
    while True:
        line = sys.stdin.readline()
        if line == '':
            break
        
            
        try:

        except Exception as ex:
            sys.stderr.write('Error: ' + str(ex) + '\n')
    

    # return exit code 0 on successful termination
    sys.exit(0)

if __name__ == '__main__':
    main()