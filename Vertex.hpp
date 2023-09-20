#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

class Vertex{
private:
	std::string vertex; 
	unsigned long distance_min; //Minimum distance
	std::vector<std::string> sh_path;// shortest path
	bool block; //Sees if a node is blocking
protected:
public:
	//Makes class Graph a friend
	friend class Graph;
	//Constructor and Destructor 
	Vertex() { vertex = ""; }
	~Vertex() {}
};
#endif