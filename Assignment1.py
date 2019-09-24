# https://notebooks.azure.com/arie-gurfinkel/projects/ece650-py


# ---LIBRARIES---

from __future__ import print_function
from __future__ import division
import re
import sys

####################################3
verbose = True
trial_run = True

# # Street
# class Street(object):
#     def __init__(self, street_name, coord):
#         self.street_name = street_name
#         self.coord = coord
#
#     def __repr__(self):
#         return '({})'.format(self.street_name)
#
#     def __str__(self):
#         return repr(self)

# ---PARSING (in: String, Out: 1-4)
def parse_line(inline):
    sp = inline.strip().lower()
    # Extracting command
    command = sp[0]

    # Checking command
    if command not in "acrga":
        raise Exception("Unknown command: The command should only be one of the following options: "
                        "'c', 'a', 'r', or 'g '")

    # Parsing Street Name

    if command != 'g':
        street_name = re.findall(r'["][a-zA-Z0-9 ]+["]', sp)
        if len(street_name) != 1:
            raise Exception('Invalid Input: Remember to add exactly one "Street Name" within quotation '
                            'marks and without special characters')
        street_name = street_name[0][1:-1]
    else:
        if sp != 'g':
            raise Exception("Invalid Input")
        else:
            return command, None, None

    # Checking for space after the command
    if sp[1] != " ":
        raise Exception('Invalid Input: Remember to have exactly one space after the Command')

    # initializing coordinates
    coordinates = None

    if command == 'a' or command == 'c':
        # Checking completeness
        if len(sp) < 16:
            raise Exception("Invalid Input: There is something missing, input is too short")
        # Checking for space after the street
        if sp[sp.rfind('"') + 1] != " ":
            raise Exception('Invalid Input: Remember to have exactly one space after the "Street Name"')
        # Checking that at least 2 coordinates were entered
        coordinates_found = re.findall(r'[(][ ]*[-]?[ ]*[0-9]+[ ]*[,][ ]*[-]?[ ]*[0-9]+[ ]*[)]', sp)
        if len(coordinates_found) < 2:
            raise Exception('Invalid Input: at least 2 coordinates must be entered')

        # checking that the # of opening parentheses = # of closing parentheses = # of coordinates found
        opening = sp.count('(')
        closing = sp.count(')')
        if len(coordinates_found) != opening:
            raise Exception("Invalid Input: remember to add valid coordinates between an opening "
                            "and a closing parentheses")
        if len(coordinates_found) != closing:
            raise Exception("Invalid Input: remember to add valid coordinates between an opening "
                            "and a closing parentheses")

        # Formatting coordinates_found
        coordinates_found_array = []
        for i in range(len(coordinates_found)):
            c = (int(re.search(r'[-]?[ ]*[0-9]+', coordinates_found[i]).group().replace(" ", "")),
                 int((re.search(r'[,][ ]*[-]?[ ]*[0-9]*', coordinates_found[i]).group()[1:]).replace(" ", "")))
            coordinates_found_array.append(c)

        coordinates = coordinates_found_array
        # Checking if all coordinates are unique
        if len(coordinates) != len(list(set(coordinates))):
            if verbose is True:
                print("coordinates: " + str(coordinates) + "\nset:\t" + str(list(set(coordinates))))
            raise Exception("Invalid coordinate points. Please enter unique coordinate points")

    # Returns command as a string, street_name as an array and coordinates as an array
    return command, street_name, coordinates


# ---STREET DB---
class StreetDb(object):
    def __init__(self, db):
        self.db = db

    def __repr__(self):
        return '({})'.format(self.db)

    def __str__(self):
        return repr(self)

    # check existence of the street in the db
    def check_existence(self, stt_name):
        if verbose is True:
            print("Called Check_existence ")
            print(stt_name)
        if stt_name in self.db:
            return True
        else:
            return False

    # Add new street to the db
    def db_add(self, stt_name, coord):
        if not self.check_existence(stt_name):
            if verbose is True:
                print("Check_existence successful")
            self.db[stt_name] = coord
            if verbose is True:
                print("existing db: " + str(self.db))
        else:
            raise Exception("the street you are trying to add already exists in the database")

    # Remove street from the db
    def db_remove(self, stt_name):
        if self.check_existence(stt_name):
            self.db.pop(stt_name, None)
            if verbose is True:
                print("new db: " + str(self.db))
        else:
            raise Exception("the street you are trying to remove does not exist in the database")

    # Change street in the db
    def db_change(self, stt_name, coord):
        if self.check_existence(stt_name):
            self.db[stt_name] = coord
            if verbose is True:
                print("new db: " + str(self.db))
        else:
            raise Exception("the street you are trying to change does not exist in the database")


# ---GRAPH BUILDER---

# Point
class Point(object):
    # initialization
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    # how to be printed for developers
    def __repr__(self):
        return '({0:.2f}, {1:.2f})'.format(self.x, self.y)

    # how to be printed for everyone else

    def __str__(self):
        return repr(self)


# Line
# how to initialize mutable parameters with a default https://stackoverflow.com/a/2681507
class Line(object):
    def __init__(self, p1, p2, intersec=None):
        self.src = p1
        self.dst = p2
        if intersec is None:
            intersec = []
        self.intersec = intersec

    def __repr__(self):
        return repr(self.src) + '-->' + repr(self.dst)


# Compute intersection
# Wikipedia: https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
# When lines are parallel there might be a division by 0
def intersect(l1, l2):
    x1, y1 = l1.src.x, l1.src.y
    x2, y2 = l1.dst.x, l1.dst.y
    x3, y3 = l2.src.x, l2.src.y
    x4, y4 = l2.dst.x, l2.dst.y

    inters = []

    t_num = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)
    t_den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)

    if t_den != 0:
        t = t_num / t_den

        u_num = (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)
        # u_den = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4)
        u = -u_num / t_den

        if 0 <= t <= 1 and 0 <= u <= 1:
            x_coor = round(x1 + t * (x2 - x1), 2)
            # print("x_coor: ",x_coor)
            y_coor = round(y1 + t * (y2 - y1), 2)
            inters.append(Point(x_coor, y_coor))
    else:
        # This lines are parallel
        # Checking for collinear lines
        m_num = (y2 - y1)
        m_den = (x2 - x1)
        # This lines are not vertical
        if m_den != 0:

            m = m_num / m_den
            b = y2 - m * x2
            m2 = "a"

            # This lines are collinear
            # Since we know that this are not vertical lines, one of the two following has to be fulfilled
            if x2 - x3 != 0:
                m2 = (y2 - y3) / (x2 - x3)
            elif x1 - x4 != 0:
                m2 = (y1 - y4) / (x1 - x4)

            if m == m2:

                x_l1_max = max(x1, x2)
                x_l1_min = min(x1, x2)
                x_l2_max = max(x3, x4)
                x_l2_min = min(x3, x4)

                # Checking one is not the sub-segment of the other
                if x_l1_max > x_l2_max and x_l1_min > x_l2_min:
                    # Checking if 2 points are the same
                    if x_l2_max == x_l1_min:
                        inters.append(Point(x_l1_min, m * x_l1_min + b))
                    else:
                        inters.append(Point(x_l2_max, m * x_l2_max + b))
                        inters.append(Point(x_l1_min, m * x_l1_min + b))
                # Checking one is not the sub-segment of the other
                elif x_l2_max > x_l1_max and x_l2_min > x_l1_min:
                    # Checking if 2 points are the same
                    if x_l2_min == x_l1_max:
                        inters.append(Point(x_l1_max, m * x_l1_max + b))
                    else:
                        inters.append(Point(x_l1_max, m * x_l1_max + b))
                        inters.append(Point(x_l2_min, m * x_l2_min + b))
                else:
                ###### If sub-segments are accepted

                    l1_max = max([(x1, y1), (x2, y2)])
                    l1_min = min([(x1, y1), (x2, y2)])
                    l2_max = max([(x3, y3), (x4, y4)])
                    l2_min = min([(x3, y3), (x4, y4)])

                    sor = sorted([l1_max, l1_min, l2_max, l2_min], key=lambda element: (element[0], element[1]))
                    inters.append(Point(sor[1][0], sor[1][1]))
                    inters.append(Point(sor[2][0], sor[2][1]))
                    print("j")




        # This lines are vertical
        else:
            # This lines are vertical and collinear
            if x2 == x3:
                # m = m_num / m_den
                # b = y2 - m * x2
                l1_max = max([(x1, y1), (x2, y2)])
                l1_min = min([(x1, y1), (x2, y2)])
                l2_max = max([(x3, y3), (x4, y4)])
                l2_min = min([(x3, y3), (x4, y4)])
                # y_l1_min = min(y1, y2)
                # y_l2_max = max(y3, y4)
                # y_l2_min = min(y3, y4)

                # Checking one is not the sub-segment of the other
                if l1_max[1] > l2_max[1] and l1_min[1] > l2_min[1]:
                    # Checking if 2 points are the same
                    if l2_max[1] == l1_min[1]:
                        inters.append(Point(l1_min[0], l1_min[1]))
                    else:
                        inters.append(Point((l2_max[0]), l2_max[1]))
                        inters.append(Point((l1_min[0]), l1_min[1]))
                # Checking one is not the sub-segment of the other
                elif l2_max[1] > l1_max[1] and l2_min[1] > l1_min[1]:
                    # Checking if 2 points are the same
                    if l2_min[1] == l1_max[1]:
                        inters.append(Point(l1_max[0], l1_max[1]))
                    else:
                        inters.append(Point(l1_max[0], l1_max[1]))
                        inters.append(Point(l2_min[0], l2_min[1]))
    return inters


# l1 = Line(Point(0, 0), Point(5, 5))
# l2 = Line(Point(5, 0), Point(0, 5))
# intersect(l1, l2)
class Segment(object):
    def __init__(self, segment=None, inter=None):
        # if street_name is None:
        #     street_name = str()
        # self.id = street_name
        if segment is None:
            segment = {}
        if inter is None:
            inter = []

        self.segment = segment
        self.inter = inter

    def __repr__(self):
        return '({} {})'.format(self.segment, self.inter)

    def __str__(self):
        return repr(self)


class Graph(object):
    def __init__(self, db_segments=None):
        if db_segments is None:
            db_segments = {}
        self.db_segments = db_segments
        # if db_intersection is None:
        #     db_intersection = {}
        # self.db_intersection = db_intersection

    def calc_segments(self, db):

        # keys = db.keys()
        # for i in range(0, len(keys)):
        #     self.db_segments[keys[i]] = []
        #     for j in range(i + 1, len(keys)):
        for key, value in db.iteritems():
            self.db_segments[key] = [Segment()]
            for i in range(len(value) - 1):
                point1 = Point(value[i][0], value[i][1])
                point2 = Point(value[i + 1][0], value[i + 1][1])
                self.db_segments[key].append(Segment(segment=Line(point1, point2)))
                # if verbose is True:
                #     print("hello", self.db_segments)

    def calc_intersection(self):
        keys = self.db_segments.keys()
        # for i in keys:
        #     self.db_intersection[keys[i]].inter = []
        for i in range(0, len(keys)):
            if verbose is True:
                (print("Length of keys: ", len(keys), "\nSegment: ", self.db_segments[keys[i]][1].segment))
            # self.db_segments[keys[i]].inter = []
            for j in range(1, len(self.db_segments[keys[i]])):
                for k in range(i + 1, len(keys)):
                    for l in range(1, len(self.db_segments[keys[k]])):
                        seg1 = self.db_segments[keys[i]][j].segment
                        seg2 = self.db_segments[keys[k]][l].segment
                        if verbose is True:
                            print("seg1: ", seg1)
                            print("seg2: ", seg2)

                        intersection = intersect(seg1, seg2)

                        if intersection != []:
                            self.db_segments[keys[i]][j].inter.append(intersection)
                            self.db_segments[keys[k]][l].inter.append(intersection)

                        if verbose is True:
                            if intersection != []:
                                print("intersection: ", self.db_segments[keys[i]][j].inter, " and ", self.db_segments[keys[k]][l].inter)
                                if len(self.db_segments[keys[i]][j].inter) > 2:
                                    print("In db_segments I have a dictionaty of segments that contain lines and "
                                          "inter that has a list and inside another list with size 1 and inside a "
                                          "point of type", type(self.db_segments[keys[i]][j].inter[2][0].x))
                            else:
                                print("No intersection", self.db_segments[keys[i]][j].inter)
        print("j")


                        # despues de hallar la interseccion, aprovechar y tomar el nodo antes y el nodo despues para
                        # hacer la grafica

        # for key, value in self.db_segments:
        #     self.db_intersection[str(key)] = []
        #     for i in range(len(value)):
        #         self.db_segments[str(key)] = self.db_segments[str(key)].append(Line(value))

    def __repr__(self):
        return '({})'.format(self.db_segments)

    def __str__(self):
        return repr(self)


# ---GRAPH---
class GraphBuilder(object):

    def __init__(self, graph=None, vertex=None, edge=None):
        if graph is None:
            graph = []
        self.graph = graph
        if vertex is None:
            vertex = {}
        if edge is None:
            edge = []

        self.vertex = vertex
        self.edge = edge

    def __repr__(self):
        return '({} {})'.format(self.vertex, self.edge)

    def __str__(self):
        return repr(self)

    def db_vertices(self):
        if verbose is True:
            print("entering db_vertices ", type(self.graph.db_segments))
            y = self.graph.db_segments
        key_dict = self.graph.db_segments.keys()
        edges = []
        for key in key_dict:
            value = self.graph.db_segments[key]
            # print("graph.db_segments", self.graph.db_segments)
            # print("graph.db_segments", self.graph.db_segments[key])
            # if verbose is True:
            #     print("key: ", key, " value: ", value, " len(value): ", len(value))

            for i in range(len(value)-1):
                j = i + 1
                if value[j] is not []:
                    if len(value[j].inter) > 0:
                        edges.append((round(value[j].segment.src.x, 2), round(value[j].segment.src.y, 2)))
                        edges.append((round(value[j].segment.dst.x, 2), round(value[j].segment.dst.y, 2)))

                        for k in range(len(value[j].inter[0])):
                            print(value[j].segment.src.x)
                            self.vertex[str(round(value[j].segment.src.x, 2)) + "," + str(round(value[j].segment.src.y, 2))] = value[j].segment.src
                            self.vertex[str(round(value[j].segment.dst.x, 2)) + "," + str(round(value[j].segment.dst.y, 2))] = value[j].segment.dst
                            self.vertex[str(round(value[j].inter[0][k].x, 2)) + "," + str(round(value[j].inter[0][k].y, 2))] = value[j].inter[0][k]
                            edges.append((round(value[j].inter[0][k].x, 2), round(value[j].inter[0][k].y, 2)))

        edges = sorted(list(set(edges)), key=lambda element:(element[0], element[1]))
        for ed in range(len(edges)-1):
            print(str(edges[ed][0])+str(edges[ed][1])+str(0)+str(edges[ed+1][0])+str(edges[ed+1][1]))
            self.edge.append(str(edges[ed][0])+str(edges[ed][1])+str(0)+str(edges[ed+1][0])+str(edges[ed+1][1]))
        print("j")




# ---GRAPH PRINTER---

# ---MAIN()---


def main():
    # sample code to read from stdin.
    # make sure to remove all spurious print statements as required
    # by the assignment
    street_db = StreetDb({})
    if trial_run is False:
        while True:
            line = sys.stdin.readline()
            if line == '':
                if verbose is True:
                    print("exiting")
                break

            try:
                if line == "\n":
                    raise Exception("Invalid entry: please try again")
                cmd, stt_name, coord = parse_line(line)

                if verbose is True:
                    print("Command: " + str(cmd) + "\nstreet name: " + str(stt_name) + '\ncoordinates: ' + str(coord))

                if cmd == 'a':
                    street_db.db_add(stt_name, coord)
                elif cmd == 'c':
                    street_db.db_change(stt_name, coord)
                elif cmd == 'r':
                    street_db.db_remove(stt_name)
                elif cmd == 'g':
                    # checking that at least 2 streets have been created
                    if verbose is True:
                        print(street_db.db)

                    g = Graph()
                    Graph.calc_segments(g, street_db.db)
                    Graph.calc_intersection(g)
                    graph_built = GraphBuilder(graph = g)
                    GraphBuilder.db_vertices(graph_built)
                else:
                    raise Exception("Unknown command: The command should be one of the following options: "
                                    "c, a, r, or g")

            except Exception as ex:
                sys.stderr.write('Error: ' + str(ex) + '\n')




    if trial_run is True:
        while True:
            line = sys.stdin.readline()
            if line == '':
                if verbose is True:
                    print("exiting")
                break

            if line == "\n":
                raise Exception("Invalid entry: please try again")
            cmd, stt_name, coord = parse_line(line)

            if verbose is True:
                print("Command: " + str(cmd) + "\nstreet name: " + str(stt_name) + '\ncoordinates: ' + str(coord))

            if cmd == 'a':
                street_db.db_add(stt_name, coord)
            elif cmd == 'c':
                street_db.db_change(stt_name, coord)
            elif cmd == 'r':
                street_db.db_remove(stt_name)
            elif cmd == 'g':
                # checking that at least 2 streets have been created
                if verbose is True:
                    print(street_db.db)

                g = Graph()
                Graph.calc_segments(g, street_db.db)
                Graph.calc_intersection(g)
                graph_built = GraphBuilder(graph=g)
                GraphBuilder.db_vertices(graph_built)
            else:
                raise Exception("Unknown command: The command should be one of the following options: "
                                "c, a, r, or g")





    # return exit code 0 on successful termination
    sys.exit(0)


if __name__ == '__main__':
    main()
# string to dictionary https://stackoverflow.com/a/988251
