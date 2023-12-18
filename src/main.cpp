#include "../include/octree.h" //
#include "../include/reporter.h"

int main(int argc, char* argv[]) {
	Reporter reporter; //create reporter (singleton?)
	reporter.create_space(); //reporter create default empty space
	reporter.read_file_data(argv[1]); //reporter will make reader to read data to space
	reporter.run(); //reporter will start simulation and make writer to write data to file in specific time intervals


	//Octant octant ({ 0,0,0 }, 100);
	//Octree octree(octant);



	//Body b1; b1.position = { 0, 0, 0 };  b1.mass = 1;
	//Body b2; b2.position = { 10, 10, 10 };  b2.mass = 1;
	//Body b3; b3.position = { 20, 20, 20 };  b3.mass = 1;
	//Body b4; b4.position = { 30, 30, 30 };  b4.mass = 1;
	//Body b5; b5.position = { 40, 40, 40 };  b5.mass = 1;
	//Body b6; b6.position = { 50, 50, 50 };  b6.mass = 1;
	//Body b7; b7.position = { 60, 60, 60 };  b7.mass = 1;
	//Body b8; b8.position = { 70, 70, 70 };  b8.mass = 1;

	//std::vector<Body> bodies = { b1,b2,b3,b4,b5,b6,b7,b8 };

	//

	//Node n1(&b1);
	//Node n2(&b2);
	//Node n3(&b3);
	//Node n4(&b4);
	//Node n5(&b5);
	//Node n6(&b6);
	//Node n7(&b7);
	//Node n8(&b8);
	//
	//octree.insert(n3);
	//octree.insert(n4);
	//octree.insert(n6);
	//octree.insert(n7);
	//octree.insert(n8);
	//octree.insert(n1);
	//octree.insert(n2);
	//octree.insert(n5);
	//


	//

	////musze teraz je jakos wyprintowac
	//octree.print();
	//octree.update_acceleration(&b1);
	


	return 0;
}







//reporter.stop(); //reporter will stop simulation