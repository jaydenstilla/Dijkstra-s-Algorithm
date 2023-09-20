/*	Name:		Kevin Mezger
 *	Project:	PP4	
 *  Partner:	Viraj Amarasinghe
				Piyush Manjhi
				Jayden Stilla
*/

#include "Graph.hpp"

//Breaks down the graph
Graph::~Graph()
{
	for(auto& x : vertex_list) { delete x; }
	for(auto& x : edge_list) { delete x; }
    vertex_list.clear();
	edge_list.clear();
}
/*Thow if single string input is null*/
void Graph::check_string(std::string stringInput) {
	if (stringInput.empty()) {
		throw stringInput;
	}
}
/*Thow if both string input are null*/
void Graph::string_with_two(std::string stringInput1, std::string stringInput2) {
	if (stringInput1.empty()) {
		throw stringInput1;
	}
	else if (stringInput2.empty()) {
		throw stringInput2;
	}
	else if (stringInput1.empty() && stringInput2.empty()) {
		throw ("The arguments of both strings are empty\n");
	}
}
//Makes and adds a vertex
void Graph::addVertex(std::string label)
{
	check_string(label);
	Vertex *new_vertex = new Vertex;
	new_vertex->vertex = label;
	new_vertex->distance_min = std::numeric_limits<unsigned long>::max();
	new_vertex->sh_path = { "" };
	new_vertex->block = false;

	vertex_list.push_back(new_vertex); 
}
//Removes the vertex and the edges between the vertex
void Graph::removeVertex(std::string label)
{
	check_string(label);

	//Removes vertex
	for (std::deque<Vertex*>::iterator iteration = vertex_list.begin(); iteration != vertex_list.end();) {
		if ((*iteration)->vertex == label) {
			vertex_list.erase(iteration);
		}
		else {}
		++iteration;
	}
	//Removes edges
	for (std::deque<Edge*>::iterator edgeIterator = edge_list.begin(); edgeIterator != edge_list.end();) {
		if (((*edgeIterator)->curr_edge == label) || ((*edgeIterator)->adj_edge == label)) {
			edge_list.erase(edgeIterator);
		}
		else{}
		++edgeIterator;
	}
}
//adds edge of weighted value between label 1 and 2
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
	string_with_two(label1, label2);
	Edge *newEdge1 = new Edge(label1, label2, weight);
	Edge* newEdge2 = new Edge(label2, label1, weight);

	edge_list.push_back(newEdge1);
	edge_list.push_back(newEdge2);
}
//Removes the edge
void Graph::removeEdge(std::string label1, std::string label2)
{
	string_with_two(label1, label2);
	
	for (std::deque<Edge*>::iterator edgeIterator = edge_list.begin(); edgeIterator != edge_list.end();) {
		if (((*edgeIterator)->curr_edge == label1) && ((*edgeIterator)->adj_edge == label2)) {
			edge_list.erase(edgeIterator);
		}
		else{}
		++edgeIterator;
	}
}
//Compututes shortest path between the startLabel and endLabel vertexes
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path)
{
	string_with_two(startLabel, endLabel);
	st_path(startLabel); 
	//Makes list in ascending order
	make_path(startLabel);
	//Uses priority queue to find shortest path
	build_path(endLabel, path); 
	rst_path(); //resets

	return distance;
}
// Starts the path, initializes the distance to zero, and pshes to the shortes
void Graph::st_path(std::string startLabel){	
	
	for (std::deque<Vertex*>::iterator iteration = vertex_list.begin(); iteration != vertex_list.end();) {
		if ((*iteration)->vertex == startLabel) {
			(*iteration)->distance_min = 0;
			(*iteration)->sh_path.clear();
			(*iteration)->sh_path.push_back(startLabel);
		}
		else{}
		 ++iteration;
	}
	pathList.push(std::make_pair(0, startLabel));
}
//Gets the position of the minimum vertex
void Graph::index_min_vert(std::string& ele_min){
	int ver_idx = 0;
	for (std::deque<Vertex*>::iterator iteration = vertex_list.begin(); iteration != vertex_list.end();) {
		if ((*iteration)->vertex == ele_min) {
			vertex_min_ind = ver_idx;
		}
		else{ ++ver_idx;}
		 ++iteration;
	}
}

void Graph::put_min_dist(std::string startLabel){
	
	for (std::deque<Edge*>::iterator edgeIterator = edge_list.begin(); edgeIterator != edge_list.end();) {

		if ((*edgeIterator)->curr_edge == ele_min) { 

			
			for (std::deque<Vertex*>::iterator iteration = vertex_list.begin(); iteration != vertex_list.end();) {
				
				if (((*edgeIterator)->adj_edge == (*iteration)->vertex) &&
					((vertex_list.at(vertex_min_ind)->distance_min + (*edgeIterator)->weight) < (*iteration)->distance_min) &&
					((*iteration)->block == false))
				{
					(*iteration)->distance_min = vertex_list.at(vertex_min_ind)->distance_min + (*edgeIterator)->weight;

					if (ele_min == startLabel) {
						(*iteration)->sh_path.clear(); 
						(*iteration)->sh_path.push_back(startLabel);
					}
					else if (ele_min != startLabel) { 
						(*iteration)->sh_path.clear();
						(*iteration)->sh_path = vertex_list.at(vertex_min_ind)->sh_path;
						(*iteration)->sh_path.push_back(vertex_list.at(vertex_min_ind)->vertex);
					}
					
					pathList.push(std::make_pair((*iteration)->distance_min, (*iteration)->vertex));
				}
				else{}
				++iteration;
			}
		}
		else{}
		++edgeIterator;
	}
}
//check all possible paths
void Graph::make_path(std::string startLabel){
	for (;!pathList.empty();) {

		ele_min = pathList.top().second; 

		pathList.pop();
		//Index with min value
		index_min_vert(ele_min); 
		//finds the weight
		put_min_dist(startLabel); 

		vertex_list.at(vertex_min_ind)->block = true;
	}
}
//Buils the shortest path
void Graph::build_path(std::string endLabel, std::vector<std::string>& path){

	for (std::deque<Vertex*>::iterator iteration = vertex_list.begin(); iteration != vertex_list.end();) {
		//loops until endLabel
		if (endLabel == (*iteration)->vertex) { 
			//Stores and obtains the min distance
			distance = (*iteration)->distance_min; 
			(*iteration)->sh_path.push_back(endLabel); 
			path = (*iteration)->sh_path; 
			
		}
		else{}
		++iteration;
	}

}

void Graph::rst_path(){
	//Sets distance to infinite
	for (std::deque<Vertex*>::iterator iteration = vertex_list.begin(); iteration != vertex_list.end();) {
		(*iteration)->distance_min = std::numeric_limits<unsigned long>::max();;
		(*iteration)->sh_path = { "" };
		(*iteration)->block = false;
		++iteration;
	}
}