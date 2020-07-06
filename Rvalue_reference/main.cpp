#include <iostream>
using namespace std;

void foo(int&& a)
{
   //Some magical code...
}
int main()
{
   int b;
  // foo(b);       //Error. An rValue reference cannot be pointed to a lValue.
   foo(5);       //Compiles with no error.
   foo(b+3);     //Compiles with no error.
  // int&& c = b;  //Error. An rValue reference cannot be pointed to a lValue.
   int&& d = 5;  //Compiles with no error.
}

//https://www.internalpointers.com/post/c-rvalue-references-and-move-semantics-beginners
int main1(int argc, char** argv) {
	
	//rvalue reference, denoted by placing a double ampersand && after some type.
	// Such rvalue reference lets you modify the value of a temporary object:
	// it's like removing the const attribute 
	
	const int & x = 666;
	
	const string s1 = "Hi ";
	const string s2 = "Man";
	string &&  s_reff = s1 + s2;
	
	s_reff += "!";
	
	cout << s_reff << endl;
	
	return 0;
}
