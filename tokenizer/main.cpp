#include <iostream>
#include <vector>
#include <string>
using namespace std;



void tokenize(string const & str, const char delim, vector<string>  out){
	size_t start = 0;
	size_t end = 0;
//	while(start = str.find_first_not_of(delim,end) != string::npos){
//		printf("%d",start);
//		end = str.find(delim,start);
//		printf(" %d",end);
//		out.push_back(str.substr(start,end));
//	}
	string substr;
	while(end != string::npos){
		end = str.find(delim,start);
	//	printf("s:%d  ",start);
	//	printf("e:%d ",end);
		substr = str.substr(start,end - start);
	//	cout << substr << endl;
		out.push_back(str.substr(start,end - start));
		start = end+1;
	}
	
	for(vector<string>::iterator it = out.begin();it != out.end();it++){
		cout <<"->"<<*it << endl;
	} 
	
}

int main(int argc, char** argv) {
	
	string const  str = "123.245.1.16";
	const char delim = '.'	;
	vector<string>  out;
	tokenize(str, delim, out);
//	for(vector<string>::iterator it = out.begin();it != out.end();it++){
//		cout <<"->"<<*it << endl;
//	} 
	
	
	return 0;
}
