#ifndef DELAUNAY_TREE_H
#define DELAUNAY_TREE_H

#include "Node.h"

class DelaunayTree {
public:
    int currentOperationNb;
    Node *root;

public:
    DelaunayTree();
    ~DelaunayTree();
    void insert(Point *p);
    void output();
};

void DelaunayTree::output() {
    root->currentOperationNb = ++currentOperationNb;
    root->output();
}

DelaunayTree::DelaunayTree() {
    currentOperationNb = 0;
    root = new Node();
    new Node(root, 0);
    new Node(root, 1);
    new Node(root, 2);
    root->neighbors[0]->neighbors[1] = root->neighbors[1];
    root->neighbors[0]->neighbors[2] = root->neighbors[2];
    root->neighbors[1]->neighbors[0] = root->neighbors[0];
    root->neighbors[1]->neighbors[2] = root->neighbors[2];
    root->neighbors[2]->neighbors[0] = root->neighbors[0];
    root->neighbors[2]->neighbors[1] = root->neighbors[1];
}

void DelaunayTree::insert(Point *p) {
    Node *n;
    Node *created;
    Node *last;
    Node *first;
    Point *q;
    Point *r;
    unsigned int i;
    root->currentOperationNb = ++currentOperationNb;
    if (!(n = root->find_conflict(p))) {
        return;
    }
    for (i = 0; (int)i < 3 - (int)n->flag.is_infinite(); i++)
        if ((p->getX() == n->vertices[i]->getX()) && (p->getY() == n->vertices[i]->getY()))
            return;
    n->flag.kill();
    q = n->vertices[0];
    while (n->neighbors[i = n->point_neighbor_index(q)]->conflict(p)) {
        n = n->neighbors[i];
        n->flag.kill();
    }
    first = last = new Node(n, p, i);
    r = n->vertices[(((int)i) + 2) % 3];
    while (1) {
        i = n->point_neighbor_index(r);
        if (n->neighbors[i]->flag.is_dead()) {
            n = n->neighbors[i];
            continue;
        }
        if (n->neighbors[i]->conflict(p)) {
            n = n->neighbors[i];
            n->flag.kill();
            continue;
        }
        break;
    }
    while (1) {
        created = new Node(n, p, i);
        created->neighbors[2] = last;
        last->neighbors[1] = created;
        last = created;
        r = n->vertices[(((int)i) + 2) % 3];
        if (r == q)
            break;
        while (1) {
            i = n->point_neighbor_index(r);
            if (n->neighbors[i]->flag.is_dead()) {
                n = n->neighbors[i];
                continue;
            }
            if (n->neighbors[i]->conflict(p)) {
                n = n->neighbors[i];
                n->flag.kill();
                continue;
            }
            break;
        }
    }
    first->neighbors[2] = last;
    last->neighbors[1] = first;
    return;
}

DelaunayTree::~DelaunayTree() {
    currentOperationNb++;
}

#endif