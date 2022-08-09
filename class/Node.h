#ifndef NODE_H
#define NODE_H

#include "Point.h"
#include "Flag.h"

#include <cmath>

class Node;
class List;

class List {
public:
    List *next;
    Node *key;
    List(List *next, Node *key);
    ~List();
};

List::List(List *next, Node *key) {
    this->next = next;
    this->key = key;
}

List::~List() {
    List *p, *q;
    if (next != nullptr) return;
    for (p = this, q = this->next; q;) {
        p->next = nullptr;
        delete p;
        p = q;
        q = q->next;
    }
}

class Node {
public:
    Flag flag;
    unsigned int currentOperationNb;
    Point *vertices[3];
    Node *neighbors[3];
    List *sons;

    Node();
    Node(Node *root, unsigned int i);
    Node(Node *f, Point *c, unsigned int i);
    unsigned int conflict(Point *p);
    Node *find_conflict(Point *p);
    void output();
    unsigned int point_neighbor_index(Point *p);
    unsigned int neighbor_index(Node *n);
};

Node::Node() {
    vertices[0] = new Point(10, 0);
    vertices[1] = new Point(-5, 8);
    vertices[2] = new Point(-5, -8);
    flag.infinite(3);
    currentOperationNb = 0;
    sons = nullptr;
}

Node::Node(Node *root, unsigned int i) {
    vertices[0] = root->vertices[0];
    vertices[1] = root->vertices[1];
    vertices[2] = root->vertices[2];
    flag.infinite(4);
    currentOperationNb = 0;
    sons = nullptr;
    neighbors[i] = root;
    root->neighbors[i] = this;
}

Node::Node(Node *f, Point *c, unsigned int i) {
    switch (f->flag.is_infinite()) {
        case 0:
            flag.infinite(0);
            break;
        case 1:
            if (f->flag.is_last_finite())
                flag.infinite((i == 1) ? 0 : 1);
            else
                flag.infinite((i == 2) ? 0 : 1);
            if (flag.is_infinite()) {
                if (f->flag.is_last_finite()) {
                    if (i == 0)
                        flag.last_finite();
                }
                else {
                    if (i == 1)
                        flag.last_finite();
                }
            }
            break;
        case 2:
            flag.infinite((i == 0) ? 2 : 1);
            if (i == 1)
                flag.last_finite();
            break;
        case 3:
            flag.infinite(2);
            break;
    }
    currentOperationNb = 0;
    sons = nullptr;
    f->sons = new List(f->sons, this);
    f->neighbors[i]->sons = new List(f->neighbors[i]->sons, this);
    f->neighbors[i]->neighbors[f->neighbors[i]->neighbor_index(f)] = this;
    vertices[0] = c;
    neighbors[0] = f->neighbors[i];
    
    switch (i) {
        case 0:
            vertices[1] = f->vertices[1];
            vertices[2] = f->vertices[2];
            break;
        case 1:
            vertices[1] = f->vertices[2];
            vertices[2] = f->vertices[0];
            break;
        case 2:
            vertices[1] = f->vertices[0];
            vertices[2] = f->vertices[1];
            break;
    }
}

unsigned int Node::point_neighbor_index(Point *p) {
    return ((p == vertices[0]) ? 2 : ((p == vertices[1]) ? 0 : 1));
}
unsigned int Node::neighbor_index(Node *n) {
    return ((neighbors[0] == n) ? 0 : ((neighbors[1] == n) ? 1 : 2));
}

unsigned int Node::conflict(Point *p) {
    switch (flag.is_infinite()) {
        case 4:
            return 0;
        case 3:
            return 1;
        case 2:
            return ((*p - *vertices[0]) * (*vertices[1] + *vertices[2]) >= 0);
        case 1:
            return ((flag.is_last_finite())
                        ? (((*p - *vertices[2]) ^ (*vertices[2] - *vertices[0])) >= 0)
                        : (((*p - *vertices[0]) ^ (*vertices[0] - *vertices[1])) >= 0));
        case 0:
            double x, y;
            double x0, y0;
            double x1, y1;
            double x2, y2;
            double z1, z2;
            double alpha, beta, gamma;
            x = p->getX();
            y = p->getY();
            x0 = vertices[0]->getX();
            y0 = vertices[0]->getY();
            x1 = vertices[1]->getX();
            y1 = vertices[1]->getY();
            x2 = vertices[2]->getX();
            y2 = vertices[2]->getY();
            x1 -= x0;
            y1 -= y0;
            x2 -= x0;
            y2 -= y0;
            x -= x0;
            y -= y0;
            z1 = (x1 * x1) + (y1 * y1);
            z2 = (x2 * x2) + (y2 * y2);
            alpha = (y1 * z2) - (z1 * y2);
            beta = (x2 * z1) - (x1 * z2);
            gamma = (x1 * y2) - (y1 * x2);
            return ((alpha * x) + (beta * y) + gamma * ((x * x) + (y * y)) <= 0);
    }
    return 0;
}


Node *Node::find_conflict(Point *p) {
    List *l;
    Node *n;

    if (!conflict(p)) {
        return nullptr;
    }

    if (!flag.is_dead()) {
        return this;
    }

    for (l = sons; l; l = l->next) {
        if (l->key->currentOperationNb != currentOperationNb) {
            l->key->currentOperationNb = currentOperationNb;
            n = l->key->find_conflict(p);
            if (n) {
                return n;
            }
        }
    }
    return nullptr;
}

void Node::output() {
    List *l;
    if (flag.is_dead()) {
        for (l = sons; l; l = l->next)
            if (l->key->currentOperationNb != currentOperationNb) {
                l->key->currentOperationNb = currentOperationNb;
                l->key->output();
            }
        return;
    }

    if (neighbors[0]->currentOperationNb != currentOperationNb)
        if (!flag.is_infinite())
            vertices[1]->lineSegment(vertices[2]);

    if (neighbors[1]->currentOperationNb != currentOperationNb) {
        if (!flag.is_infinite())
            vertices[2]->lineSegment(vertices[0]);
        else if ((flag.is_infinite() == 1) && (flag.is_last_finite()))
            vertices[2]->lineSegment(vertices[0]);
    }

    if (neighbors[2]->currentOperationNb != currentOperationNb) {
        if (!flag.is_infinite())
            vertices[0]->lineSegment(vertices[1]);
        else if ((flag.is_infinite() == 1) && (!flag.is_last_finite()))
            vertices[0]->lineSegment(vertices[1]);
    }
}

#endif