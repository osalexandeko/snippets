
// C++ program to find out maximum subarray 
// sum in linear time using prefix sum. 
#include <iostream> 
#include <limits> 
using namespace std; 

void print_arr(int * arr, int sz){
	printf("\n");
	for(int i = 0; i < sz; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}
  
// Function to compute maximum subarray 
// sum in linear time. 
int maximumSumSubarray(int arr[], int n) 
{ 
    // Initialize minimum prefix sum to 0. 
    int min_prefix_sum = 0; 
  
    // Initialize maximum subarray sum so  
    // far to -infinity. 
    int res = numeric_limits<int>::min(); 
  
    // Initialize and compute the prefix  
    // sum array. 
    int prefix_sum[n]; 
    prefix_sum[0] = arr[0]; 
    for (int i = 1; i < n; i++)  {
	
        prefix_sum[i] = prefix_sum[i - 1] + arr[i];         
    }
    
    //dbg
    print_arr(prefix_sum, n);
  
    // loop through the array, keep track 
    // of minimum prefix sum so far and 
    // maximum subarray sum. 
    printf("res = %d, min_prefix_sum =  %d \n", res,min_prefix_sum );
    for (int i = 0; i < n; i++) { 
    	
        res = max(res, prefix_sum[i] -  
                       min_prefix_sum); 
        min_prefix_sum = min(min_prefix_sum,  
                             prefix_sum[i]); 
                             
        printf("res = %d, min_prefix_sum =  %d \n", res,min_prefix_sum );                     
    } 
      
    return res; 
} 
  
// Driver Program 
int main() 
{ 
    // Test case 1 
    int arr1[] = { -2, -3, 4, -1, -2, 1, 5, -3 }; 
    int n1 = sizeof(arr1) / sizeof(arr1[0]); 
    cout << maximumSumSubarray(arr1, n1) << endl; 
  
    // Test case 2 
    int arr2[] = { 4, -8, 9, -4, 1, -8, -1, 6 }; 
    int n2 = sizeof(arr2) / sizeof(arr2[0]); 
    cout << maximumSumSubarray(arr2, n2); 
  
    return 0; 
} 

