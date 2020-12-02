//https://www.geeksforgeeks.org/const_cast-in-c-type-casting-operators/


#include<iostream>

using namespace std;
class Demo {
   int val;
   public:
      Demo(int x = 0) {
         val = x;
      }
      int getValue() const {
         return val;
      }
      
      int getValueNonConst() const {
      	( const_cast <Demo*> (this) )->val++;
         return   ( const_cast <Demo*> (this) )->val;
      }
};
int main() {
   const Demo d(28);
   Demo d1(8);
   
   cout << "getValueNonConst : " << d.getValueNonConst();
   
   cout << "\nThe value using object d : " << d.getValue();
   cout << "\nThe value using object d1 : " << d1.getValue();
   return 0;
}
