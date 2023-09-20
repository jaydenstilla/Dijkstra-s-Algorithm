#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <deque>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <iterator>


class Graph : public GraphBase {
public:
	Graph() {} 
	~Graph(); //Breaks down the graph
	
	void addVertex(std::string label);
	void removeVertex(std::string label);
	void addEdge(std::string label1, std::string label2, unsigned long weight);
	void removeEdge(std::string label1, std::string label2);
	unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);

protected:
	void check_string(std::string input_str); 
	void string_with_two(std::string input_str1, std::string input_str2);
	void st_path(std::string startLabel); //starts path
	void make_path(std::string startLabel);//Uses priority queue to make path
	void index_min_vert(std::string& ele_min); //finds the vertex's mim index
	void put_min_dist(std::string startLabel); 
	void build_path(std::string endLabel, std::vector<std::string>& path); //builds a path from one to another
	void rst_path(); //resets the path

private:
	std::deque<Vertex*> vertex_list; //Vertex and distance list
	std::deque<Edge*> edge_list; //Edge and weight list
	unsigned long distance = 0; //Variable for the shortest distance
	int vertex_min_ind = 0; //Minimum node index
	std::string ele_min = ""; //Minimum element
	
	//Stores vertexes by distance via Priority queue
	std::priority_queue<std::pair<unsigned long, std::string>,std::vector<std::pair<unsigned long, std::string>>,
	std::greater<std::pair<unsigned long, std::string>>> pathList;




};
#endif