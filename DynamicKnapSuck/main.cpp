
 

/*Given weights and values of n items, put these items in a knapsack of
capacity W to get the maximum total value in the knapsack. In other words,
given two integer arrays val[0..n-1] and wt[0..n-1] which represent values
and weights associated with n items respectively. Also given an integer
W which represents knapsack capacity, find out the maximum value subset
of val[] such that sum of the weights of this subset is smaller than or
equal to W. You cannot break an item, either pick the complete item or
don’t pick it (0-1 property).*/


#include <iostream>
#include <vector>

using namespace std;
 
 
#define M_I_N 4 //number of elements
#define M_W 10  //capacity

void printT(int ar[M_I_N][M_W]){
	for(int i = 0; i < M_I_N; i++){
		for(int j = 0; j < M_W; j++){
			if(ar[i][j] < 9 )
				printf(" %d ", ar[i][j]);
			else
				printf("%d ", ar[i][j]);
		}
		printf("\n");
	}
}


int max(int i , int j){
	return (i > j)?i:j;
}
 
int getMV(int const * const v, int const * const w,  int const mxW){
	int t[M_I_N][M_W] = {0};
//	for(int j = 0; j < M_W; j++){
//		t[0][j] = 0;
//	}
	for(int i = 1; i <= M_I_N; i++){
		for(int j = 0; j <= mxW; j++){
			if(w[i - 1] > j){
				t[i][j] = t[i-1][j];
			}else{
				t[i][j] = max(t[i-1][j], t[i-1][j - w[i - 1]] + v[i - 1]);
			}
		}
	}
	
	printT(t);
	
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
	printf("\n max %d \n",  getMV(v,w,4));
	//printf("max %d \n", vectGetMV(v,w,3,sizeof(v)/sizeof(v[0])));
	return 0;
}
