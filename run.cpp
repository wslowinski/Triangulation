#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

#define N 100

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "\n\n*** \033[1;31mPlease enter a random integer number\033[0m ***\n\n" << std::endl;
        return -1;
    }
    else {
        int n = atoi(argv[1]);
        std::srand(std::time(nullptr));
        std::vector<double> vecX;
        std::vector<double> vecY;
        for (int i = 0; i < n; i++) {
            int x = std::rand() % N + 10;
            vecX.push_back(x);
            int y = std::rand() % N + 15;
            vecY.push_back(y);
        }
        std::ofstream data("./data/points.txt");
        for (int i = 0; i < vecX.size(); i++) {
            data << vecX[i] << " " << vecY[i] << std::endl; 
        }
        data.close();
        system("./DelaunayTree.x < ./data/points.txt > ./data/results.txt");
        system("./TriangulationOutline.x < ./data/results.txt");
    }
    return 0;
}
