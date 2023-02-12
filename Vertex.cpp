//
// Created by Xinran on 2023/2/9.
//

#include "Vertex.h"

void Vertex::setID(int id) {
    this->id = id;
}

int Vertex::getID() {
    return this->id;
}

void Vertex::addV(Vertex v) {
    list.push_back(v);
}

Vertex::Vertex(int id) {
    this->id = id;
    this->list = std::vector<Vertex>();
}

