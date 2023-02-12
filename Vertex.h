//
// Created by Xinran on 2023/2/9.
//

#ifndef ECE650_A2_VERTEX_H
#define ECE650_A2_VERTEX_H

#include <vector>


class Vertex {
private:
    int id;
    std::vector<Vertex> list;
public:
    Vertex(int id);

    void setID(int id);
    int getID();

    void addV(Vertex v);
};


#endif //ECE650_A2_VERTEX_H
