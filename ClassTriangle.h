#pragma once

using namespace std;

#include "ClassJoint.h"
#include "ClassParticle.h"

class Triangle {
public:
    vector<Joint*> list_joints;
    vector<Triangle*> list_nearest_triangles;
    float normal_vector;

    // Constructeur avec trois Joint en paramètre
    // Donner à chaque particle du Triangle son ptr vers le Triangle
    Triangle(Joint* ptr_J1, Joint* ptr_J2, Joint* ptr_J3) {
        list_joints.push_back(ptr_J1);
        list_joints.push_back(ptr_J2);
        list_joints.push_back(ptr_J3);
        // Add the ptr_triangle to each Particl concerned
        //cout << "here0" << endl;
        ptr_J1->particle1->list_triangles_friends.push_back(this);
        //cout << "here1" << endl;
        ptr_J1->particle2->list_triangles_friends.push_back(this);
        if (ptr_J2->particle1 != ptr_J1->particle1 && ptr_J2->particle1 != ptr_J1->particle2) {
            //cout << "har1" << endl;
            // cout << ""
            ptr_J2->particle1->list_triangles_friends.push_back(this);
        } else {
            ptr_J2->particle2->list_triangles_friends.push_back(this);
            //cout << "har2" << endl;
        }
        //cout << "Triangle created" << endl;
    }

    // Update the normal_vector to the triangle, a scalar in 2D and vector in 3D
    void update_normal() {
        sf::Vector2f v1 = list_joints[0]->particle1->pos - list_joints[0]->particle2->pos;
        sf::Vector2f v2;
        if (list_joints[1]->particle2 == list_joints[0]->particle2) {
            v2 = list_joints[1]->particle1->pos - list_joints[0]->particle2->pos;
        } if (list_joints[1]->particle1 == list_joints[0]->particle2) {
            v2 = list_joints[1]->particle2->pos - list_joints[0]->particle2->pos;
        } if (list_joints[2]->particle1 == list_joints[0]->particle2) {
            v2 = list_joints[2]->particle2->pos - list_joints[0]->particle2->pos;
        } else {
            v2 = list_joints[2]->particle1->pos - list_joints[0]->particle2->pos;
        }

        float v1_x_v2 = v1.x * v2.y - v1.y *v2.x;
        float distance_v1 = sqrt(v1.x * v1.x + v1.y * v1.y);
        float distance_v2 = sqrt(v2.x * v2.x + v2.y * v2.y);

        normal_vector = v1_x_v2 / (distance_v1*distance_v2);
    }
};
