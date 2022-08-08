#include "class/DelaunayTree.h"

int main() {
    DelaunayTree delaunayTree;
    double x;
    double y;
    while (std::cin >> x >> y) {
        delaunayTree.insert(new Point(x, y));
    }
    delaunayTree.output();
    return 0;
}