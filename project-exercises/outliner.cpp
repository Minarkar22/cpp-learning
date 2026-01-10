#include<iostream>
#include<array>
int get_outliner(int arr[], int n);
using namespace std;
int main(){
    int Arrsize = 6;
    int arr[Arrsize] = {3,7,6,9,11,1};
    int number = get_outliner(arr, Arrsize);
    cout << number << endl;
    return 0;
}

int get_outliner(int arr[], int n){
    int even = 0;
    int odd = 0;
    for (int i = 0; i < 3; i++)
    {   
        if (arr[i] % 2 == 0)
            even++;
        else
            odd++;
    }

    bool majorityEven = (even > odd);

    for (int i = 0; i < n; i++){
        if(majorityEven && arr[i] % 2 != 0)
            return arr[i];
        
        if (!majorityEven && arr[i] % 2 == 0)
            return arr[i];
    }
    return -1;
}

// int FindOutlier(std::vector<int> arr)
// {
//     int even;
//   	int odd;
  
//   	int evenCount = 0;
//   	int oddCount = 0;
  
//   	for (auto a : arr)
//   	  	a % 2 == 0 ? (evenCount++, even = a) : (oddCount++, odd = a);
  
//   	return evenCount < oddCount ? even : odd;
// }