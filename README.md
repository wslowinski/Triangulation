# Triangulation
C++ program to generate Delaunay triangulation of a random set of N points in a plane. The Bowyer-Watson algorithm was used to create this triangulation. Result was visualized using cairo graphics library.

## Sample result
A Delaunay triangulation of a random set of 120 points in a plane.
![example](https://github.com/wslowinski/Triangulation/blob/main/image/example.png)

## Technologies
Project is created with:
* C++14
* cairo graphics library
	
## Setup
1. To run this project, install it locally;
2. The following make command will help you in compiling the Makefile into an executable program:

   ```$ make```

3. Finally, we are ready to run the executable file we created in the last step through the Terminal. Run the following command to do so:

   ```$ ./run <N>```

   where ```<N>``` -- number of points;