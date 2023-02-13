//
// Created by Xinran on 2023/2/11.
//
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <exception>
#include <queue>

#include "Vertex.h"

std::vector<int> BFS(std::vector<Vertex*> &graph, int sourceNum){
    //queue to keep track of nodes
    std::cout << "entered BFS" << std::endl;
    std::queue<Vertex*> q;

    std::cout << "after q" << std::endl;

    // an array to store the visit state of nodes.
    std::vector<bool> visited(graph.size(),false);
    std::cout << "after visited" << std::endl;
    // an array to store distance from source
    //std::vector<int> distance(graph.size(),-1);
    // an array to store previous node
    std::vector<int> previous(graph.size(),-1);
    std::cout << "after previous" << std::endl;

    // visit the Source Node.
    visited[sourceNum] = true;
    std::cout << "after sourceNum" << std::endl;
    q.push(graph.at((sourceNum)));
    std::cout << "after graph at" << std::endl;

    std::cout << "before traverse" << std::endl;
    while(!q.empty()){
        std::cout << "q is not empty" << std::endl;
        //remove the first entry
        Vertex* node = q.front();
        q.pop();

        std::cout << "node is " << node->getID() << std::endl;
        std::cout << "node adjacent list size is " << node->getList().size() << std::endl;
        //traverse through all adjacent nodes of the current node
        for(auto n:node->getList()){
            std::cout << "in for" << std::endl;
            if(!visited[n]){
                visited[n] = true;
                std::cout << "push: " <<n << " into queue." << std::endl;
                q.push(graph.at(n));
                //store the id of the previous node to the current node
                previous[n] = node->getID();
                std::cout << "previous node of " <<n << " is " << node->getID() << std::endl;
            }
        }
    }

    std::cout << "end of BFS in function" << std::endl;

    return previous;
}

std::vector<std::string> parseEdges(std::string &line){
    std::vector<std::string> edges;
    while(line != "}"){
        int pos_start = line.find("<");
        int pos_end = line.find(">");

        std::string s = line.substr(pos_start,pos_end - pos_start + 1);
        edges.push_back(s);

        std::cout << s << std::endl;

        line = line.substr(pos_end + 1);
        std::cout << line << std::endl;
    }

    return edges;
}

int main(){
    try{
        std::vector<Vertex*> graph = std::vector<Vertex*>();
        while(!std::cin.eof()){
            std::cout << "enter while true!" << std::endl;
            // variable to store a line
            std::string line;
            std::getline(std::cin,line);
            //std::vector<std::string> lines;


            std::cout << "after getline" << std::endl;

            // command is the first character
            char command = line.at(0);
            std::cout << "command is" << std::endl;

            switch(command){
                case 'V':{
                    std::cout << "enter V!" << std::endl;
                    //initiate a graph. We store the graph in a vector ds holding pointers to Vertex object.
                    graph.clear();
                    std::istringstream stream(line);
                    char c;
                    int numOfV;

                    stream >> c;

                    stream >> numOfV;

                    std::cout << "num of V is: " << numOfV << std::endl;

                    // initiate vertices and push back to the graph
                    for (int i = 0; i < numOfV ; i++){
                        Vertex* v = new Vertex(i);
                        graph.push_back(v);
                    }
                    break;
                }
                case 'E':{
                    std::cout << "enter E!" << std::endl;
                    std::vector<std::string> edges = parseEdges(line);
                    if(!edges.empty()){
                        std::cout << "There are matches!" << std::endl;
                        //traverse through the input of edges
                        for (auto e: edges){
                            std::cout << "Loop through match" << std::endl;
                            std::cout << "edge is : " << e << std::endl;

                            int node1_int = -1;
                            int node2_int = -1;

                            std::string n1pos = e.substr(e.find("<")+1,e.find(",")-e.find("<")-1);
                            std::string n2pos = e.substr(e.find(",")+1,e.find(">")-e.find(",")-1);

                            node1_int = std::atoi(n1pos.c_str());
                            node2_int = std::atoi(n2pos.c_str());

                            std::cout << "node 1 is " << n1pos << " and node 2 is " << n2pos << std::endl;
                            std::cout << "graph size is " << graph.size() << std::endl;

                            if (node1_int < 0 || node2_int < 0 || node1_int >= graph.size() || node2_int >= graph.size()){
                                throw std::invalid_argument("Error: index out of bound.");
                            }

                            if(node1_int >= 0 && node2_int >= 0){
                                std::cout << "add nodes " << std::endl;
                                graph.at(node1_int)->addV(node2_int);
                                graph.at(node2_int)->addV(node1_int);
                            }
                        }//end for
                    }//end if
                    break;
                }
                case 's':{
                    std::cout << "enter s!" << std::endl;
                    std::istringstream stream(line);
                    char c;
                    int source;
                    int destination;

                    stream >> c;
                    stream >> source;
                    stream >> destination;

                    std::cout << "source is: " << source << ", and dest is: " << destination << std::endl;

                    std::cout << "BFS" << std::endl;

                    std::vector<int> path = BFS(graph,source);
                    if(path[destination] == -1){
                        std::cout << "no path found, throw error" << std::endl;
                        throw std::invalid_argument("Error: No valid path found.");
                    }else{
                        std::cout << "initiate stack" << std::endl;
                        std::stack<int> stack;
                        std::cout << "after initiating stack" << std::endl;
                        int current = destination;
                        while(current != source){
                            std::cout << "push" << current<< std::endl;
                            stack.push(current);
                            current = path[current];
                        }
                        //stack push source node
                        stack.push(current);

                        //print the source node
                        std::cout << "top" << std::endl;
                        std::cout << stack.top();
                        stack.pop();
                        while(!stack.empty()){
                            std::cout << "-" << stack.top();
                            stack.pop();
                        }
                    }
                    break;
                }
                default:{
                    throw std::invalid_argument("Error: Invalid Input.");
                }
            }


        }
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}
