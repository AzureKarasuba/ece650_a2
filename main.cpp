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

std::string BFS(std::vector<Vertex> graph, int sourceNum, int destinationNum){
    std::queue<Vertex> q;
    q.push(graph.at((sourceNum)));
}

int main(){
    try{
        while(true){
            // variable to store a line
            std::string line;
            std::vector<std::string> lines;

            while(std::getline(std::cin,line)){
                lines.push_back(line);
            }

            // command is the first character
            char command = lines[0].at(0);

            switch(command){
                case 'V':{
                    //initiate a graph. We store the graph in a vector ds holding pointers to Vertex object.
                    std::vector<Vertex> graph = std::vector<Vertex>();

                    std::istringstream stream(lines[0]);
                    char c;
                    int numOfV;

                    stream >> c;
                    stream >> c;

                    stream >> numOfV;

                    // initiate vertices and push back to the graph
                    for (int i = 0; i < numOfV ; i++){
                        Vertex v = Vertex(i);
                        graph.push_back(v);
                    }

                    std::regex reg("\\<(.*?)\\>");
                    std::smatch match;
                    if(std::regex_match(lines[1],match,reg)){
                        //traverse through the input of edges
                        for (int i = 0; i < match.size(); i++){
                            std::string s = match[i];

                            int node1_int = -1;
                            int node2_int = -1;

                            //extract id's of the nodes
                            if(char node1 = s.at(0)){
                                node1_int = node1;
                            }else{
                                throw std::invalid_argument("Error: vertex out of bound.");
                            }

                            if(char node2 = s.at(0)){
                                node2_int = node2;
                            }else{
                                throw std::invalid_argument("Error: vertex out of bound.");
                            }

                            if(node1_int > 0 && node2_int > 0){
                                graph.at(node1_int).addV(graph.at(node2_int));
                                graph.at(node2_int).addV(graph.at(node1_int));
                            }
                        }//end for
                    }//end if
                }
                case 's':{
                    std::istringstream stream(lines[0]);
                    char c;
                    int source;
                    int destination;

                    stream >> c;
                    stream >> c;
                    stream >> source;
                    stream >> c;
                    stream >> destination;

                }
                default:{
                    //throw Exception: invalid input
                }
            }


        }
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }


    return 0;
}
