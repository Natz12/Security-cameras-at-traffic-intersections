// #pragma once

#include <climits>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>


#include "a2ece650.hpp"

bool verbose2 = false;

Graph::Graph() : m_num_vertices(0) {}
void Graph::set_num_vertices(int t_num_vertices) { m_num_vertices = t_num_vertices;}
int Graph::get_num_vertices() { return m_num_vertices; }

bool Graph::ini_adjacency_matrix() {
    std::vector<int> tem(m_num_vertices, m_num_vertices*m_num_vertices);
    m_adj_mat.assign(m_num_vertices, tem);
    if (verbose2){
        std::cout << "Your initialized adjacency matrix: \n";
        for (std::vector<int> &i : m_adj_mat) {
            std::vector<int> vec = i;
            for (int j : vec) {
                std::cout << j << " ";
            }
        std::cout << std::endl;
        }
    }
    return true;
}

void Graph::set_edges(std::list<unsigned> &t_edges) { m_edges = t_edges;}

bool Graph::adjacency_matrix(std::string &err_msg) {
    int num1;
    int num2;
    std::list<unsigned> nums = m_edges;
    int V = m_num_vertices;
    ini_adjacency_matrix();
    if (nums.size() % 2 == 0){
        int nums_size = nums.size();
        for (int i = 0; i != (nums_size/2); i++){

            num1 = nums.front();
            nums.pop_front();
        

            num2 = nums.front();
            nums.pop_front();

            if (verbose2){
                std::cout << "num1: " << num1 << "num2: " << num2 << std::endl;
            }

            if (num1 < V && num2 < V){
                m_adj_mat[num1][num2] = 1;
                m_adj_mat[num2][num1] = 1;
            } else {
                err_msg = "Vertices out of bounds";
                return false;
            } 
        }  
        if (verbose2) {

            std::cout << "Your populated adjacency matrix: \n";
            for (std::vector<int> &i : m_adj_mat) {
                std::vector<int> vec = i;
                for (int j : vec) {
                    std::cout << j << " ";
                }
            std::cout << std::endl;
            }
        } 
          
        return true;
        
    } 
    err_msg = "Missing argument for vertices";
    return false;
}

bool shortest_path (std::vector<int> prev, int source, int target, std::list<unsigned> &short_path, std::string &err_msg){
    int u = target;

    if (verbose2) {
        std::cout << "Entered shortest_path" << std::endl;
    }
    
    if (prev[u] != -1 || u == source){
        while (u != -1){
            short_path.push_front(u);
            u = prev[u];
        }
        if (verbose2) {
            std::cout << "Short Path:" << std::endl;
            for (int i : short_path) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        return true;
    } 
    err_msg = "Unreachable vertex";
    return false;
    
}

bool Graph::dijkstra( std::list<unsigned> coordinates, std::list<unsigned> &short_path, std::string &err_msg){

    if (coordinates.size() == 2) { 

        int source  = coordinates.front();
        coordinates.pop_front();


        int target = coordinates.front();
        coordinates.pop_front();

        std::list<unsigned> nums = m_edges;
        int V = get_num_vertices();
        if (source > V || target > V) {
            err_msg = "error: vertices out of bounds";
            return false;
        }

        std::list<unsigned> q;
        std::vector<int> dist(V, V*V);
        std::vector<int> prev(V, -1);

        if (verbose2) {
            std::cout << "nums.begin(): " << *nums.begin() << " nums.end(): " << *nums.end() << std::endl;
        }

        // for (auto i = nums.begin(); i != nums.end(); ++i){

        //     dist[*i] = INT_MAX;
        //     prev[*i] = -1;
        //     q.push_back(*i);
        
        //     if (verbose2) {
        //         std::cout << "dijkstra" << std::endl;
        //         std::cout << "i: "<< *i << std::endl;
        //     }
        // }

        for ( int i = 0; i < V; i++){
            q.push_back(i);
        }

        // q.push_back(source);

        dist.at(source) = 0;

        if (verbose2) {
            std::cout << "dist with source " << source <<  " = 0 \n" << std::endl;
        }

        int u = 0;
        while (!q.empty()) {
            int distance = INT_MAX;
            

            for (int i : q){
                if (dist[i] < distance) {
                    distance = dist[i];
                    u = i;
                }
            }

            if (verbose2) {
                std::cout << "assigned u = " << u << " as the one with the shortest distance to source: " << u << std::endl;
            }

            if (u == target){

                break;
            }

            q.remove(u);

            if (verbose2) {
                std::cout << "removed u = " << u << "from q" << std::endl;
            }

            int alt;
            if (verbose2) {
                std::cout << "nums.begin(): " << *nums.begin() << " nums.edn(): " << *nums.end() << " u: " << u << std::endl;
            }

            for (int i : q){
                alt = dist[u] + m_adj_mat[u][i];
                if (alt < dist[i]){
                    dist.at(i) = alt;
                    prev.at(i) = u;
                }

            }
            if (verbose2) {
                std::cout << "New q using u: " << u << " are " << std::endl;
                for (int i : q){
                    std::cout << i << " ";
                }
                std::cout << std::endl;

                 std::cout << "New dist using u: " << u << " are " << std::endl;
                for (int i : dist){
                    std::cout << i << " ";
                }
                std::cout << std::endl;               


                std::cout << "New prev using u: " << u << " are " << std::endl;
                for (int i : prev){
                    std::cout << i << " ";
                }
                std::cout << std::endl;
            }
        }

        if (verbose2) {
            std::cout << "Ended calculating dist and prev" << std::endl;
        }
        
        if (verbose2) {
            std::cout << "Output prev " << std::endl;
            for (int i : prev) {
                std::cout << i << " ";
            }
        }
        return (shortest_path(prev, source, target, short_path, err_msg));
    }
    err_msg = "Missing or Bad argument for s";
    return false;
}


