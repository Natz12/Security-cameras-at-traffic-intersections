#pragma once

/// Graph class. Keeps track
class Street
{
    /// the number of vertices
    int m_num_segments;
    std::vector<std::tuple<int,int>> m_coordinates;
    // std::list<unsigned> m_edges;

public:
    /// Constructor. Creates a street with no line segments
    Street();
    /// Sets the number of segments
    void set_num_segments(int &t_num_segments);
    /// Returns the number of segments
    int get_num_segments();
    /// Tests if line segment is non-zero
    bool test_non_zero(std::tuple<int,int> &t_coordinates);
    /// Tests if line segment does not generate a self-intersection
    bool test_self_inter(std::tuple<int,int> &t_coordinates);
    /// Sets coordinates to form new segment
    void set_coordinates(std::tuple<int,int> &t_coordinates);
    /// pops last entered coordinates
    void pop_last_coordinates();
    /// Returns the specified tuple of coordinates
    std::tuple<int,int> get_coordinates(int i);
    /// Returns the number of stored coordinates
    int get_num_stored_coordinates();
    // /// Initializes adjacency matrix
    // bool ini_adjacency_matrix();
    // /// Creates the adjacency matrix
    // bool adjacency_matrix(std::string &err_msg);
    // /// Calculates the shortest path
    // bool dijkstra( std::list<unsigned> coordinates, std::vector<unsigned> &short_path, std::string &err_msg);
};

class Graph
{
    /// the number of vertices
    int m_num_streets;
    std::vector<Street> m_streets;
    // std::list<unsigned> m_edges;

public:
    /// Constructor. Creates a street with no line segments
    Graph();
    /// Resets graph to default values
    bool reset_graph();
    /// Sets the number of streets
    void set_num_streets(int &t_num_streets);
    /// Returns the number of streets
    int get_num_streets();
    /// Get lenght of m_streets
    int lenght_m_streets();
    /// Sets streets
    void set_street(Street t_street);
    /// Returns the street
    Street get_street(int street_to_get);
    /// Tests that line segment does not overlap with line segments of other streets.
    std::tuple<bool,int> test_overlap(std::tuple<int,int> &t_previous_coordinates, std::tuple<int,int> &t_coordinates, int num_street);
    // /// Initializes adjacency matrix
    // bool ini_adjacency_matrix();
    // /// Creates the adjacency matrix
    // bool adjacency_matrix(std::string &err_msg);
    // /// Calculates the shortest path
    // bool dijkstra( std::list<unsigned> coordinates, std::vector<unsigned> &short_path, std::string &err_msg);
};