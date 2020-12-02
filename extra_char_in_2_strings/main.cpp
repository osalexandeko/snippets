#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

char extra_char(string s1, string s2){
	char extr_ch = 0; 
	unordered_map <char, int> ht;
	for(int i = 0; i < s1.length();i++){
		ht[s1[i]]++;
	}
	for(int i = 0; i < s2.length();i++){
		ht[s2[i]]--;
	}
	for(auto it = ht.begin(); it != ht.end();it++){
		 if(it->second == 1){
		 	extr_ch = it->first;
		 }
	}
	return extr_ch;
}


int main(int argc, char** argv) {
	string s1 = "qwertyb";
	string s2 = "ytrewq";
	cout << extra_char(s1,s2) << endl;
	return 0;
}
