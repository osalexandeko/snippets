#include <iostream>
#include <vector>
#include <stack>
#include  <cstring>

using namespace std;
 
int mxSbStrCom(char const * const s1,char const * const s2){
	int max =0;
	int j_max =0;
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	vector<vector<int> > t(l1+1,vector<int>(l2 + 1));
	for(int i = 0; i < l1 + 1; i++){
		for(int j = 0; j < l2 + 1; j++){
			if(0 == i || 0 == j){
				t[i][j] = 0;
			}else{
				if(s1[i-1] == s2[j-1]){
					t[i][j] = t[i-1][j-1]+1;
					if(max < t[i][j]){
						max = t[i][j];
						j_max = j-1;
					}
				}else{
					t[i][j] = 0;
				}
			}
		}
	}
	stack<char> st;
	for(int i = 0; i < max; i++){
		st.push(s2[j_max--]);
	}
	printf("\n");
	for(int i = 0; i < max; i++){
		printf("%c",st.top());
		st.pop();
	}
	printf("\n");
	return max;
} 

int main(int argc, char** argv) {
	char s1[100] = "alex1234";
	char s2[100] = "54321alex";
	cout  << mxSbStrCom(s1,s2) << endl;
	return 0;
}
