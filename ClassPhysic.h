#ifndef CLOTHES_CLASSPHYSIC_H
#define CLOTHES_CLASSPHYSIC_H

#include "ClassObject.h"

using namespace std;

class Physic{
public:
    vector<Object*> objects_list;

    void solving_constraints();

    Physic(vector<Object*> vec) {
        objects_list = vec;
    }
};

void Physic::solving_constraints() {
    return;
}

#endif //CLOTHES_CLASSPHYSIC_H
