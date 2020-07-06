#include <iostream>
#include <bits/stdc++.h> 

using namespace std;












int gcd(int n1, int n2){
	if(0 == n2){
		return n1;
	}
	return gcd( n2, n1 % n2);
}





int main(int argc, char** argv) {
	vector <int> v = {101,2,13,4,54,16,7,8,9};
	
	sort(v.begin() , v.end(),[](const int &a, const int &b)->bool{
	
			return a < b;
		}
	);
	
	for_each(v.begin() , v.end(),
	 	[](int x){
			cout << x << " ";
		}
		
	);
	
	auto disp = [v]() 
    { 
        for (auto p = v.begin(); p != v.end(); p++) 
        { 
            cout << *p << " -- "; 
        } 
    }; 
	
	
	disp();
	
	cout << endl;
	
	int n1 = 52,n2 =12;
	printf("%d %d %d", n1,n2, gcd(n1,n2));
	
	return 0;
	
}
