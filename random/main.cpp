#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
 

int main(int argc, char** argv) {
	
	char input[10];
	scanf("%s",input);
	
	cout << input << endl;
 
	srand(time(NULL));
	
	cout << rand();
	
	return 0;
}
