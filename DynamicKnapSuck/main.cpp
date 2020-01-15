#include <iostream>
#include <vector>

using namespace std;
 
 
#define M_I_N 10
#define M_W 100

int max(int i , int j){
	return (i > j)?i:j;
}
 
int getMV(int const * const v, int const * const w,  int const mxW){
	int t[M_I_N][M_W];
	for(int j = 0; j < M_W; j++){
		t[0][j] = 0;
	}
	for(int i = 1; i < M_I_N; i++){
		for(int j = 0; j <= mxW; j++){
			if(w[i - 1] > j){
				t[i][j] = t[i-1][j];
			}else{
				t[i][j] = max(t[i-1][j], t[i-1][j - w[i - 1]] + v[i - 1]);
			}
		}
	}
	return t[M_I_N-1][mxW];
} 

int vectGetMV(int const * const v, int const * const w,  int const mxW, int elNum){
	vector< vector<int> > t(elNum,vector<int>(mxW + 1)) ;
	for(int j = 0; j < mxW; j++){
		t[0][j] = 0;
	}
	for(int i = 1; i < elNum; i++){
		for(int j = 0; j <= mxW; j++){
			if(w[i - 1] > j){
				t[i][j] = t[i-1][j];
			}else{
				t[i][j] = max(t[i-1][j],t[i-1][j-w[i-1]]+v[i-1]);
			}
		}
	}
	return t[M_I_N-1][mxW];
} 


int main(int argc, char** argv) {
	int v[M_I_N] = {5,2,3};
	int w[M_I_N] = {1,2,3};
	//printf("max %d \n",  getMV(v,w,16));
	printf("max %d \n", vectGetMV(v,w,3,sizeof(v)/sizeof(v[0])));
	return 0;
}
