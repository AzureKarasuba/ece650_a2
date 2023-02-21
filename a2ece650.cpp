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
#include <limits>
#include <unordered_set>
#include <unordered_map>
#include <list>

#include "Vertex.h"

std::stack<int> searchForRoute(std::vector<int> path, int source, int destination){
    //std::cout << "Enter sFR!" <<std::endl;
    std::stack<int> stack;
    int current = destination;
    //std::cout << "current is " <<  current <<std::endl;
    //std::cout << "source is " <<  source <<std::endl;
    while(current != source){
        //std::cout << "push" << current<< std::endl;
        stack.push(current);
        current = path[current];
    }
    //stack push source node
    stack.push(current);

    return stack;

}


std::vector<int> BFS(std::unordered_map<int, Vertex*> &graph, int sourceNum, int destination){
    //queue to keep track of nodes
    //std::cout << "entered BFS" << std::endl;
    std::queue<Vertex*> q;

    //std::cout << "after q" << std::endl;

    // an array to store the visit state of nodes.
    std::vector<bool> visited(graph.size(),false);
    //std::cout << "after visited" << std::endl;
    // an array to store distance from source
    //std::vector<int> distance(graph.size(),-1);
    // an array to store previous node
    std::vector<int> previous(graph.size(),-1);
    //std::cout << "after previous" << std::endl;

    // visit the Source Node.
    visited[sourceNum] = true;
    //std::cout << "after sourceNum" << std::endl;
    q.push(graph.find(sourceNum)->second);
    //std::cout << "after graph at" << std::endl;

    if(sourceNum != destination){
        //std::cout << "before traverse" << std::endl;
        while(!q.empty()){
            //std::cout << "q is not empty" << std::endl;
            //remove the first entry
            Vertex* node = q.front();
            q.pop();

            //std::cout << "node is " << node->getID() << std::endl;
            // std::cout << "node adjacent list size is " << node->getList().size() << std::endl;
            // traverse through all adjacent nodes of the current node
            for(auto n:node->getList()){
                //std::cout << "in for" << std::endl;
                if(!visited[n]){
                    visited[n] = true;
                    //std::cout << "push: " << n << " into queue." << std::endl;
                    q.push(graph.find(n)->second);
                    //store the id of the previous node to the current node
                    previous[n] = node->getID();
                    //std::cout << "previous node of " << n << " is " << node->getID() << std::endl;
                }
                }
        }
    }
        return previous;
}

std::list<int> findBest(std::unordered_map<int, Vertex*> &graph, std::vector<std::vector<int>> lists,int source){
    //std::cout << "enter FindBest"<< std::endl;

    std::list<int> optimalPath(999,-1);

    for(unsigned i = 0;i < lists.size(); i++){
        //std::cout << "check list " << i << std::endl;
        // all adjacent lists
        for( auto v: graph.find(source)->second->getList()){
            //std::cout << "check src " << v << std::endl;
            for( auto v2: graph.find(source)->second->getList()){
                //std::cout << "check end " << v2 << std::endl;
                if(v != v2 && lists[i][v2] != -1 ){
                    std::list<int>  path;
                    //std::cout << "start to push to vector " << std::endl;
                    int current = v2;
                    //std::cout << "current is " << current << std::endl;
                    while(current != v){
                        //std::cout << "before push back in fb " << v2 << std::endl;
                        path.push_back(current);
                        //std::cout << "after push back in fb " << v2 << std::endl;
                        //std::cout << "current is " << current << std::endl;
                        current = lists[i][current];
                        //std::cout << "v2 is now " << v2 << std::endl;
                        //std::cout << "v1 is now " << v << std::endl;

                        if(current == -1){
                            path.clear();
                            break;
                        }
                    }

                    if(current == v){
                        path.push_back(v);
                    }

                    if(optimalPath.size() > path.size() && !path.empty()){
                        optimalPath = path;
                        //std::cout << "Optimal path size is " << optimalPath.size() << std::endl;
                    }
                }
            }
        }
    }

    optimalPath.push_front(source);
    optimalPath.push_back(source);

    return optimalPath;
}

std::list<int> BFStoItself(std::unordered_map<int, Vertex*> &graph, int node){

    //std::cout << "route to itself "<< std::endl;

    std::vector<std::vector<int>> lists;

    if(graph.find(node)->second->getList().size() <= 1){
        //only one node or no node connects to itself, which means no valid route.
        std::list<int> list = {};
        return list;
    }


    for (auto v:graph.find(node)->second->getList()){
        std::vector<bool> visited(graph.size(),false);
        std::vector<int> previous(graph.size(),-1);

        visited[node] = true;
        visited[v] = true;

        std::queue<Vertex*> q;
        //std::cout << "before q push: " << v << std::endl;
        q.push(graph.find(v)->second);

        //std::cout << "add to: " << v << std::endl;

        while(!q.empty()){
            //std::cout << "q is not empty" << std::endl;
            //remove the first entry
            Vertex* currentNode = q.front();
            q.pop();

            //std::cout << "node is " << currentNode->getID() << std::endl;
            // std::cout << "node adjacent list size is " << node->getList().size() << std::endl;
            // traverse through all adjacent nodes of the current node
            for(auto n:currentNode->getList()){
                //std::cout << "in for" << std::endl;
                if(!visited[n]){
                    visited[n] = true;
                    //std::cout << "push: " << n << " into queue." << std::endl;
                    q.push(graph.find(n)->second);
                    //store the id of the previous node to the current node
                    previous[n] = currentNode->getID();
                    //std::cout << "previous node of " << n << " is " << currentNode->getID() << std::endl;
                }
                //std::cout << "out for" << std::endl;
            }
        }
        //std::cout << "before push back" << std::endl;
        if(previous.empty()){
            //std::cout << "print empty" << std::endl;
        }
        lists.push_back(previous);
        //std::cout << "after push back" << std::endl;
    }


    return findBest(graph,lists,node);
}



std::vector<std::string> parseEdges(std::string &line){
    std::vector<std::string> edges;
    while(line != "}"){
        int pos_start = line.find("<");
        int pos_end = line.find(">");

        std::string s = line.substr(pos_start,pos_end - pos_start + 1);
        edges.push_back(s);

        //std::cout << s << std::endl;

        line = line.substr(pos_end + 1);
        //std::cout << line << std::endl;
    }

    return edges;
}



int main(){
    try{
        std::unordered_map<int, Vertex*> graph;
        while(!std::cin.eof()){
            //std::cout << "enter while true!" << std::endl;
            // variable to store a line
            std::string line;
            std::getline(std::cin,line);
            //std::vector<std::string> lines;


            //std::cout << "after getline" << std::endl;

            if(line.empty()){
                break;
            }

            // command is the first character
            char command = line.at(0);
            //std::cout << "command is" << std::endl;

            switch(command){
                case 'V':{
                    //std::cout << "enter V!" << std::endl;
                    //initiate a graph. We store the graph in a vector ds holding pointers to Vertex object.
                    if(!graph.empty()){
                        for (auto p: graph){
                            // delete pointer
                            delete p.second;
                        }
                    }
                    graph.clear();
                    std::istringstream stream(line);
                    char c;
                    int numOfV;

                    stream >> c;

                    stream >> numOfV;

                    //std::cout << "num of V is: " << numOfV << std::endl;

                    // initiate vertices and push back to the graph
                    for (int i = 0; i < numOfV ; i++){
                        Vertex* v = new Vertex(i);
                        graph.insert({i,v});
                    }
                    //std::cout << graph.size()<<std::endl;
                    break;
                }
                case 'E':{
                    //std::cout << "enter E!" << std::endl;
                    std::vector<std::string> edges = parseEdges(line);
                    if(!edges.empty()){
                        //std::cout << "There are matches!" << std::endl;
                        //traverse through the input of edges
                        for (auto e: edges){
                            //std::cout << "Loop through match" << std::endl;
                            //std::cout << "edge is : " << e << std::endl;

                            int node1_int = -1;
                            int node2_int = -1;

                            std::string n1pos = e.substr(e.find("<")+1,e.find(",")-e.find("<")-1);
                            std::string n2pos = e.substr(e.find(",")+1,e.find(">")-e.find(",")-1);

                            node1_int = std::atoi(n1pos.c_str());
                            node2_int = std::atoi(n2pos.c_str());

                            //std::cout << "node 1 is " << n1pos << " and node 2 is " << n2pos << std::endl;
                            //std::cout << "graph size is " << graph.size() << std::endl;

                            try{
                                if (node1_int < 0 || node2_int < 0 || (unsigned)node1_int >= graph.size() || (unsigned)node2_int >= graph.size()){
                                    throw std::invalid_argument("Error: index out of bound.");
                                }

                                //std::cout << "add nodes " << std::endl;
                                graph.find(node1_int)->second->addV(node2_int);
                                graph.find(node2_int)->second->addV(node1_int);

                            }catch(std::exception &e){
                                std::cout << e.what() << std::endl;
                            }

                        }//end for
                    }//end if
                    break;
                }
                case 's':{
                    //std::cout << "enter s!" << std::endl;
                    std::istringstream stream(line);
                    char c;
                    int source;
                    int destination;

                    stream >> c;
                    stream >> source;
                    stream >> destination;

                    //std::cout << "source is: " << source << ", and dest is: " << destination << std::endl;

                    //std::cout << "BFS" << std::endl;


                    try{
                        if(source < 0 || (unsigned)source >= graph.size() || destination < 0 || (unsigned)destination >= graph.size()){
                            throw std::invalid_argument("Error: Index out of bound.");
                        }
                        std::vector<int> path;
                        std::stack<int> selfStack;
                        if(source != destination){
                            path = BFS(graph,source,destination);
                            if(path[destination] == -1){
                                throw std::invalid_argument("Error: No valid path found.");
                            }else{
                                std::stack<int> stack = searchForRoute(path,source,destination);
                                // std::cout << "after initiating stack" << std::endl;

                                //print the source node
                                //std::cout << "top" << std::endl;
                                std::cout << stack.top();
                                stack.pop();
                                while(!stack.empty()){
                                    std::cout << "-" << stack.top();
                                    stack.pop();
                                }
                                std::cout << std::endl;
                            }
                        }else{
                            std::list<int> p = BFStoItself(graph,source);
                            if(p.empty()){
                                throw std::invalid_argument("Error: No valid path found.");
                            }else {
                                std::cout << p.back();
                                p.pop_back();
                                while(!p.empty()){
                                    std::cout << "-" << p.back();
                                    p.pop_back();
                                }
                                std::cout << std::endl;
                            }
                        }

                    }catch(std::exception &e){
                        std::cout << e.what() << std::endl;
                    }

                    break;
                }

            }


        }
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }



    return 0;
}
