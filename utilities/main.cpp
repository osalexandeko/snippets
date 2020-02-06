#include <iostream>
 
/*
* rounding float to int
*/
int rndF(float ft){
	return (int) (ft + 0.5);
}

int main(int argc, char** argv) {
	
	printf(": %d", rndF(3.5));
	return 0;
}
