//
// Created by Xinran on 2023/2/9.
//

#ifndef ECE650_A2_VERTEX_H
#define ECE650_A2_VERTEX_H

#include <vector>


class Vertex {
private:
    int id;
    std::vector<int> list;
public:
    Vertex(int id);

    void setID(int id);
    int getID();

    std::vector<int> getList();

    void addV(int v);
};


#endif //ECE650_A2_VERTEX_H
