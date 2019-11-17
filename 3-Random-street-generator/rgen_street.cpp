// #pragma once

#include <climits>
#include <iostream>
#include <list>
#include <sstream>
#include <tuple>
#include <vector>


#include "rgen.hpp"

bool verbose2 = false;

// Auxiliary function to find intersections in consecutive line segments
bool find_inter_consecutive(std::tuple<int,int> src1, std::tuple<int,int> dst1, std::tuple<int,int> src2, std::tuple<int,int> dst2){
    int x1 = std::get<0>(src1);
    int y1 = std::get<1>(src1);
    int x2 = std::get<0>(dst1);
    int y2 = std::get<1>(dst1);

    float mden1 = x2-x1; 

    int x3 = std::get<0>(src2);
    int y3 = std::get<1>(src2);
    int x4 = std::get<0>(dst2);
    int y4 = std::get<1>(dst2);

    float mden2 = x4-x3;

    if (mden1 == mden2){
        return 1;
        if (verbose2){
            std::cout << "mden1: " << mden1 << "\tmden2: " << mden2 << std::endl;
        }
    }

    if (mden1 != 0){
        float m1 = (y2-y1)/mden1;
        float m2 = (y3-y4)/mden2;

        if (m1 == m2) {
            if (verbose2){
                std::cout << "m1: " << m1 << "\tm2: " << m2 << std::endl;
            }
            return 1;
        }
    }

    return 0;
}


// Auxiliary function to find intersections in non consecutive line segments
bool find_inter_non_consecutive(std::tuple<int,int> src1, std::tuple<int,int> dst1, std::tuple<int,int> src2, std::tuple<int,int> dst2){
    int x1 = std::get<0>(src1);
    int y1 = std::get<1>(src1);
    int x2 = std::get<0>(dst1);
    int y2 = std::get<1>(dst1);

    int x3 = std::get<0>(src2);
    int y3 = std::get<1>(src2);
    int x4 = std::get<0>(dst2);
    int y4 = std::get<1>(dst2);

    if (verbose2) {
        std::cout << "x1: " << x1 << "\ty1: " << y1 << "x2: " << x2 << "\ty2: " << y2 << "\tx3: " << x3 << "\ty3: " << y3 << "x4: " << x4 << "\ty4: " << y4 << std::endl;
    }

    bool inters = false;

    float t_num = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
    float t_den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    // if t_den != 0 then the lines are not parallel
    if (t_den != 0){
        float t = t_num / t_den;

        float u_num = (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3);
        // u_den = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4)
        float u = -u_num / t_den;

        if (0 <= t && t <= 1 && 0 <= u && u <= 1){
            if (verbose2) {
                std::cout << "t: " << t << "\tu: " << u << std::endl;
            }
            inters = true;
            return inters;
        }
    }
    else{
        // This lines are parallel
        // Checking for collinear lines
        int m_num = (y2 - y1);
        int m_den = (x2 - x1);
        // This lines are not vertical
        if (m_den != 0){

            float m = m_num / m_den;
            // float b = y2 - m * x2;
            float m2;

            // This lines are collinear
            // Since we know that this are not vertical lines, one of the two following has to be fulfilled
            if (x2 - x3 != 0){
                m2 = (y2 - y3) / (x2 - x3);
            }
            else if (x1 - x4 != 0){
                m2 = (y1 - y4) / (x1 - x4);
            }

            // these lines are parallel, not vertical, and with one of them I can reproduce the other
            if (m == m2){
                inters = true;
                return inters;
            }
        }    
        // This lines are vertical
        else{
            // This lines are vertical and collinear
            if (x2 == x3){
                inters = true;
                return inters;
            }
        }
    }
    return inters;
}

// Auxiliary function to check if two line segments overlap and if they have an interception
std::tuple<bool,int> overlap_segment(std::tuple<int,int> src1, std::tuple<int,int> dst1, std::tuple<int,int> src2, std::tuple<int,int> dst2){
    int x1 = std::get<0>(src1);
    int y1 = std::get<1>(src1);
    int x2 = std::get<0>(dst1);
    int y2 = std::get<1>(dst1);

    // float mden1 = x2-x1; 

    int x3 = std::get<0>(src2);
    int y3 = std::get<1>(src2);
    int x4 = std::get<0>(dst2);
    int y4 = std::get<1>(dst2);

    // float mden2 = x4-x3;

    // if (mden1 != 0){

    // }       

    if (verbose2) {
        std::cout << "Overlap Segment\n[1] x1: " << x1 << " y1: " << y1 << " [2] x2: " << x2 << " y2: " << y2 
                  << " [3] x3: " << x3 << " y3: " << y3 << " [4] x4: " << x4 << " y4: " << y4 << std::endl;
    }

    int inters = 0;
    bool overlap = false;
    std::tuple<bool,bool> o;

    float t_num = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
    float t_den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    // if t_den != 0 then the lines are not parallel
    if (t_den != 0){
        overlap = false;
        float t = t_num / t_den;

        float u_num = (x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3);
        // u_den = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4)
        float u = -u_num / t_den;

        // test if lines have an interception
        if (0 <= t && t <= 1 && 0 <= u && u <= 1){
            if (verbose2) {
                std::cout << "t: " << t << "\tu: " << u << std::endl;
            }
            inters = inters+1;
        }

        if (verbose2) { 
            std::cout << "inters of overlap_segment: " << inters << std::endl;
        }        
        o = std::make_tuple(overlap, inters);
        return o;
    }
    else{
        // This lines are parallel
        // Checking for collinear lines
        int m_num = (y2 - y1);
        int m_den = (x2 - x1);
        // This lines are not vertical
        if (m_den != 0){

            float m = m_num / m_den;
            // float b = y2 - m * x2;
            float m2;

            // This lines are collinear
            // Since we know that this are not vertical lines, one of the two following has to be fulfilled
            if (x2 - x3 != 0){
                m2 = (y2 - y3) / (x2 - x3);
            }
            else if (x1 - x4 != 0){
                m2 = (y1 - y4) / (x1 - x4);
            }
            else{
                // this lines are completely overlaped
                inters = inters+1;
                overlap = true;
                o = std::make_tuple(overlap, inters);

                if (verbose2) { 
                    std::cout << "inters of overlap_segment: " << inters << std::endl;
                }
                return o;
            }

            if (m == m2){
                // these lines are parallel, not vertical, and with one of them I can reproduce the other. This line will not be further tested as creating a new coordinate is cheaper.
                inters = inters+1;
                // int x_l1_max = std::max(x1, x2);
                // int x_l1_min = std::min(x1, x2);
                // int x_l2_max = std::max(x3, x4);
                // int x_l2_min = std::min(x3, x4);
                overlap = true;
                o = std::make_tuple(overlap, inters);
                if (verbose2) { 
                    std::cout << "inters of overlap_segment: " << inters << std::endl;
                }
                return o;
            }
        }    
        // This lines are vertical
        else{
            // This lines are vertical and collinear
            if (x2 == x3){
                inters = inters+1;
                overlap = true;
                o = std::make_tuple(overlap, inters);
                if (verbose2) { 
                    std::cout << "inters of overlap_segment: " << inters << std::endl;
                }
                return o;
            }
        }
    }
    
    o = std::make_tuple(overlap, inters);
    if (verbose2) { 
        std::cout << "inters of overlap_segment: " << inters << std::endl;
    }    

    return o;
}
/// Constructor. Creates a street with no line segments
Street::Street() : m_num_segments(0) {}

/// Sets the number of segments
void Street::set_num_segments(int &t_num_segments){
    m_num_segments = t_num_segments;
};

/// Returns the number of segments
int Street::get_num_segments(){
    return m_num_segments;
};

/// Tests if line segment is non-zero
bool Street::test_non_zero(std::tuple<int,int> &t_coordinates){
    int n = m_coordinates.size(); 
    std::tuple<int,int> last_coor = m_coordinates.at(n - 1);
    if (verbose2){
        std::cout << "Testing non zero:\tLast coor: " << std::get<0>(last_coor) << "," << std::get<1>(last_coor) 
            << "\tCurrent_coor: " << std::get<0>(t_coordinates) << "," << std::get<1>(t_coordinates) 
            << "\tResult:" << (std::get<0>(last_coor)!= std::get<0>(t_coordinates) || std::get<1>(last_coor)!= std::get<1>(t_coordinates)) << std::endl;
    }
    return (std::get<0>(last_coor)!= std::get<0>(t_coordinates) || std::get<1>(last_coor)!= std::get<1>(t_coordinates));
};

/// Tests if line segment does not generate a self-intersection
bool Street::test_self_inter(std::tuple<int,int> &t_coordinates){
    int n = m_coordinates.size();


    if (n > 0){
        if (verbose2) {
            std::cout << "Testing no self-intersection:\t"<< std::endl;
        }
        if (n>1){
            bool find1 = find_inter_consecutive(m_coordinates.at(n-2), m_coordinates.at(n-1), m_coordinates.at(n-1), t_coordinates);
            if(find1){
                if (verbose2){
                    std::cout << "Found an INTERSECTION in consecutive line segments" << std::endl;
                }
                return 0;
            }
        }
        for (int i = 0; i < n-2; i++){
            if (verbose2) {
                std::cout << "n: " << n << "\ti: " << i << std::endl;
            }
            bool find2 = find_inter_non_consecutive(m_coordinates.at(i), m_coordinates.at(i+1), m_coordinates.at(n-1), t_coordinates);

            if (verbose2) {
                std::cout << "Found self intersection: " << find2 << " with m_coordinates: " << n << std::endl;
            } 
            if (find2) {
                if (verbose2){
                    std::cout << "Found an iNTERSECTION in NON consecutive line segments" << std::endl;
                }
                return 0;
            }       
        }
    }
    return 1;
};



/// Sets coordinates to form new segment
void Street::set_coordinates(std::tuple<int,int> &t_coordinates){
    m_coordinates.push_back(t_coordinates);
};

/// pops last entered coordinates
void Street::pop_last_coordinates(){
    m_coordinates.pop_back();
};

/// Returns the specified tuple of coordinates
std::tuple<int,int> Street::get_coordinates(int i){
    return m_coordinates.at(i);
};

/// Returns the number of stored coordinates
int Street::get_num_stored_coordinates(){
    return m_coordinates.size();
};




/* Class Graph*/
/// Constructor. Creates a Graph with no streets
Graph::Graph() : m_num_streets(0){}

/// Resets graph to default values
bool Graph::reset_graph(){
    m_num_streets = 0;
    m_streets.clear();
    return 1;
};

/// Sets the number of streets
void Graph::set_num_streets(int &t_num_streets){
    m_num_streets = t_num_streets;
};

/// Returns the number of streets
int Graph::get_num_streets(){
    return m_num_streets;
};

///  Get lenght of m_streets
int Graph::lenght_m_streets(){
    return m_streets.size();
};

/// Sets streets
void Graph::set_street(Street t_street){
    m_streets.push_back(t_street);    
};

/// Returns the street
Street Graph::get_street(int street_to_get){
    return m_streets.at(street_to_get);
};

/// Tests that line segment does not overlap with line segments of other streets.
std::tuple<bool,int> Graph::test_overlap(std::tuple<int,int> &t_previous_coordinates, std::tuple<int,int> &t_coordinates, int num_street){
    // int m = graph.lenght_m_streets();
    std::tuple<bool,bool> o;

    bool no_overlap = true;
    int inters= 0;
    for (int i = 0; i < num_street; i++){
        Street previous_street = m_streets.at(i);
        int n = previous_street.get_num_segments();
        std::tuple<bool,bool> over_seg;

        if (verbose2) {
            std::cout << "Inside test_overlap\nnum_street: " << num_street << "\ti: " << i << "\tn: " << n << std::endl;
        }

        for (int j = 0; j < n; j++) {
            over_seg = overlap_segment(previous_street.get_coordinates(j), previous_street.get_coordinates(j+1), t_previous_coordinates, t_coordinates);
            no_overlap = (no_overlap || !std::get<0>(over_seg)); 
            inters = inters + std::get<1>(over_seg);

            // bool trying = true;
            // if (trying) {
            //     std::cout << "Street " << i << "\tcoordinates: " << j << "j" << std::endl;
            // }
        }
    }
    if (no_overlap){
        o = std::make_tuple(no_overlap, inters);
        if (verbose2) { 
            std::cout << "inters of test_overlap1: " << inters << std::endl;
        }
        return o;  
    }
    else {
        if (verbose2) {
            std::cout << "Found an OVERLAP between streets" << std::endl;
        }
    }
    if (verbose2) { 
        std::cout << "inters of test_overlap2: " << inters << std::endl;
    }
    o = std::make_tuple(no_overlap, inters);
    return o;
};



    