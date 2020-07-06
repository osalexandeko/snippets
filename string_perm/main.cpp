#include <iostream>
#include <string>

#define LEN 256
#define PASS -1
#define NO_OF_CHARS 255

using namespace std;

bool isPermute(const string & s1, const string & s2){
	bool res = false;
	int cnt[LEN] = {0};
	int i ;
	for(i = 0; s1[i] && s2[i];i++ ){
		printf(".%X.\n",(unsigned char)s1[i] );
		cnt[(unsigned char)s1[i]]++;
		cnt[(unsigned char)s2[i]]--;

	
// 		cnt[s1[i]]++;
// 		cnt[s2[i]]--;
//		printf(".%X.\n", s1[i] );
	}
	if(s1[i] == s2[i]){
 		while(i>PASS && !cnt[(unsigned char)s1[--i]] ) ;
 		//while(i>PASS && !cnt[s1[--i]] ) ;
 	}
	if(PASS == i){
		res = true;
	} 
	return res;
}


bool arePermutation(const string & str1, const string & str2) 
{ 
    int count[NO_OF_CHARS] = {0}; 
    int i; 
  	bool res = true;
    for (i = 0; str1[i] && str2[i];  i++) 
    { 
        count[str1[i]]++; 
        count[str2[i]]--; 
    } 
    if (str1[i] || str2[i]) {
    	res = false;
	}else{
	    for (i = 0;str1[i]; i++) {
	        if (0 != count[str1[i]]) {
	        	res = false;
	        	break;
			}
	   	}
	}
    return res; 
} 



 

int main(int argc, char** argv) {
	string s1 = "ABC", s2 = "CBA";
 	//s1[0] = -1;
	//printf("is %s perm of %s ?   %d \n",&s1[0],&s2[0], isPermute( s1,s2));
	printf("is %s perm of %s ?   %d \n",&s1[0],&s2[0], arePermutation( s1,s2));
	return 0;
}
