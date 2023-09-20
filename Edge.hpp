#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>

class Edge{
public:
	friend class Graph;

	Edge(std::string a = "", std::string b = "", unsigned long w = 0) {
		curr_edge = a;
		adj_edge = b;
		weight = w;
	}
private:
	std::string curr_edge; 
	std::string adj_edge; 
	unsigned long weight; 
protected:
	
	~Edge() {}
};
#endif