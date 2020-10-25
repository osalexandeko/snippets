//https://www.geeksforgeeks.org/virtual-functions-and-runtime-polymorphism-in-c-set-1-introduction/

#include <iostream> 
using namespace std; 
  
class Base { 
public: 
	virtual void show() 
	{ 
	    cout << " In Base \n"; 
	} 
	
	virtual void go() 
	{ 
	    cout << "go In Base \n"; 
	} 
}; 
  
class Derived : public Base { 
public: 
    void show() 
    { 
        cout << "In Derived \n"; 
    } 
}; 

class Derived_from_Derived : public Derived { 
public: 
    void show() 
    { 
        cout << "In Derived from derived \n"; 
    } 
}; 
  
int main(void) 
{ 
    Base* bp = new Derived; 
    // RUN-TIME POLYMORPHISM 
    bp->show(); 
    Base* bpd = new Derived_from_Derived; 
    // RUN-TIME POLYMORPHISM 
    bpd->show(); 
    void (**vt)() = *(void (***)())bpd;
    return 0; 
} 

