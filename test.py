## A simple unit test example. Replace by your own tests
# https://docs.python.org/2/library/unittest.html


import sys
import unittest

from Assignment1 import *
# import a1ece650


def parseLine(line_to_parse):
    """
    :param line_to_parse: string that will be sent to the parse function.
    :return: Nothing
    """

    try:
        test = line_to_parse
        if test is None:
            line = sys.stdin.readline()
        else:
            line = test

        if line == '':
            if verbose is True:
                print("exiting")

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
            print_graph(graph_built)

    except Exception as ex:
        sys.stderr.write('Error: ' + str(ex) + '\n')


parseLine('a "street with the same coordinates twice" (2,1)(2,1)(3,2)')

class MyTest(unittest.TestCase):

    # def test_street_check(self):
    #     # Check if it is correctly returning the street name
    #     parsedLine = 'a "Weber Street" (0,1)(0,2)'
    #     self.assertEqual(streetCheckName(parsedLine)[0], "Weber Street")
    #
    #     # Check if it is correctly returning the street name
    #     parsedLine = 'a       "new not created Street" (0,1)(0,2)'
    #     self.assertEqual(streetCheckName(parsedLine)[0], "new not created Street")
    #
    #     # Check if it is correctly returning the coordinates
    #     parsedLine = 'a       "new not created Street" (0,1)(0,2)'
    #     self.assertEqual(streetCheckName(parsedLine)[1], ['(0,1)', '(0,2)'])
    #
    #     # Check if it is correctly returning the coordinates
    #     parsedLine = 'a       "new not created Street" (0,1)(0,2) (0,3)  (0,4)   (5,5)    (-1,9)(20,20)'
    #     self.assertEqual(streetCheckName(parsedLine)[1], ['(0,1)', '(0,2)', '(0,3)', '(0,4)', '(5,5)', '(-1,9)', '(20,20)'])

    # def test_parser(self):
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Repeated coordinates
    #         parseLine('a "street with the same coordinates twice" (2,1)(2,1)(3,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Changing a street that does not exist
    #         parseLine('a "just created street" (2,1)(5,8)')
    #         parseLine('c "not created street" (5,1)(8,5)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Missing apostrophes
    #         parseLine('a "street street (0,1) (0,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Extra apostrophes on both sides
    #         parseLine('a ""street street"" (0,1) (0,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Extra street name
    #         parseLine('a "street street" "street" (0,1) (0,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Extra apostrophes on one side
    #         parseLine('a "street street"" (0,1) (0,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Missing a comma in a coordinate
    #         parseLine('a "street street two" (01) (0,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Empty street name
    #         parseLine('a "" (0,1) (0,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # No space after the command
    #         parseLine('a"street street three" (0,1)(0,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # No space after the street name
    #         parseLine('a "street street four"(0,1)(0,3)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # No spaces whatsoever
    #         parseLine('a""(0,1)(0,1)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Two commas in the coordinates
    #         parseLine('a "street street five" (0,,1)(0,3)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Missing parenthesis in coordinates
    #         parseLine('a "incomplete street one" (0,1)(0,3')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Different command
    #         parseLine('h')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Repeated street name
    #         parseLine('a "a very unique street" (0,1)(0,2)')
    #         parseLine('a "a very unique street" (0,1)(0,2)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Number in street name
    #         parseLine('a "street street 1" (0,1)(0,5)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Wrong command
    #         parseLine('h "street street one" (0,1)(0,5)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Extra parenthesis
    #         parseLine('a "street street two" (0,1)(0,5))')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Extra parentheses
    #         parseLine('a "street street three" ((0,1)(0,5))')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Extra minus signs
    #         parseLine('a "street street four" (--1,1)(0,5)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Comma between coordinates
    #         parseLine('a "street street five" (-1,1),(0,5)')
    #
    #     with self.assertRaisesRegexp(Exception, r'^Error:[A-Za-z ,.:]+'):  # Comma between coordinates
    #         parseLine('a "street street six" (-1,1),(0,5) (2,6)')

    def test_parser(self):
        with self.assertRaises(Exception):  # Repeated coordinates
            parseLine('a "street with the same coordinates twice" (2,1)(2,1)(3,2)')

        with self.assertRaises(Exception):  # Changing a street that does not exist
            parseLine('a "just created street" (2,1)(5,8)')
            parseLine('c "not created street" (5,1)(8,5)')

        with self.assertRaises(Exception):  # Missing apostrophes
            parseLine('a "street street (0,1) (0,2)')

        with self.assertRaises(Exception):  # Extra apostrophes on both sides
            parseLine('a ""street street"" (0,1) (0,2)')

        with self.assertRaises(Exception):  # Extra street name
            parseLine('a "street street" "street" (0,1) (0,2)')

        with self.assertRaises(Exception):  # Extra apostrophes on one side
            parseLine('a "street street"" (0,1) (0,2)')

        with self.assertRaises(Exception):  # Missing a comma in a coordinate
            parseLine('a "street street two" (01) (0,2)')

        with self.assertRaises(Exception):  # Empty street name
            parseLine('a "" (0,1) (0,2)')

        with self.assertRaises(Exception):  # No space after the command
            parseLine('a"street street three" (0,1)(0,2)')

        with self.assertRaises(Exception):  # No space after the street name
            parseLine('a "street street four"(0,1)(0,3)')

        with self.assertRaises(Exception):  # No spaces whatsoever
            parseLine('a""(0,1)(0,1)')

        with self.assertRaises(Exception):  # Two commas in the coordinates
            parseLine('a "street street five" (0,,1)(0,3)')

        with self.assertRaises(Exception):  # Missing parenthesis in coordinates
            parseLine('a "incomplete street one" (0,1)(0,3')

        with self.assertRaises(Exception):  # Different command
            parseLine('h')

        with self.assertRaises(Exception):  # Repeated street name
            parseLine('a "a very unique street" (0,1)(0,2)')
            parseLine('a "a very unique street" (0,1)(0,2)')

        with self.assertRaises(Exception):  # Number in street name
            parseLine('a "street street 1" (0,1)(0,5)')

        ### This test should fail
        # with self.assertRaises(Exception):  # Valid input
        #     parseLine('a "street street" (0,1)(0,5)')

        with self.assertRaises(Exception):  # Wrong command
            parseLine('h "street street one" (0,1)(0,5)')

        with self.assertRaises(Exception):  # Extra parenthesis
            parseLine('a "street street two" (0,1)(0,5))')

        with self.assertRaises(Exception):  # Extra parentheses
            parseLine('a "street street three" ((0,1)(0,5))')

        with self.assertRaises(Exception):  # Extra minus signs
            parseLine('a "street street four" (--1,1)(0,5)')

        with self.assertRaises(Exception):  # Comma between coordinates
            parseLine('a "street street five" (-1,1),(0,5)')

        with self.assertRaises(Exception):  # Comma between coordinates
            parseLine('a "street street six" (-1,1),(0,5) (2,6)')

        self.assertEqual('foo'.upper(), 'FOO')

    # def test_upper(self):
    #     """Test the upper() function of class string"""
    #     self.assertEqual('foo'.upper(), 'FOO')
    #
    # def test_isupper(self):
    #     """Test isupper() function of class string"""
    #     self.assertTrue('FOO'.isupper())
    #     self.assertFalse('foo'.isupper())
    #     self.assertFalse('foo'.isupper())
    #     self.assertFalse('Foo'.isupper())


if __name__ == '__main__':
    unittest.main()
