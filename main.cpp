#include <stdio.h>
#include <limits>

using namespace std;

void merge_sort(int * a , int startPos, int endPos);
void _merge( int *a , int startPos , int mid , int endPos);

int main(){
    int a[] = {8,7,9,5,4};
    int array_length = sizeof(a)/sizeof(a[0]);

    merge_sort(a,0, array_length-1);

    //Print Values
    for(int i = 0 ; i < array_length ; i++ ){
        printf("%i",a[i]);
    }
    return 0;
}

/**
*   Mergo Sort Algorithm.
*/
void merge_sort(int * a , int startPos, int endPos ) {
	if( endPos - startPos +1 > 1  ) {
		int mid = (startPos+endPos) / 2;
		merge_sort( a , startPos, mid);
		merge_sort( a , mid + 1 , endPos);
		_merge(a , startPos , mid ,endPos);
    }
}

/**
*   Merge method , to merge two sorted arrays into one big sorted array of size LArray+RArray
*/
void _merge( int *a , int startPos , int mid , int endPos){

    //Left Array
	int n1 = mid-startPos +1 ;
	int L[n1+1];
	for(int i = 0 ; i < n1 ; i++)
		L[i] = a[i+startPos];

    //Right Array
    int n2 = endPos-mid;
    int R[n2+1];
    for(int i = 0 ; i < n2 ; i++)
        R[i] = a[i+mid+1];

    L[n1] = std::numeric_limits<int>::max();
    R[n2] = std::numeric_limits<int>::max();
    //Merge procedure
    int i = 0;
    int j = 0;
	for(int k = startPos ; k <= endPos ; k++){
		if( L[i] <= R[j] )
			a[k] = L[i++];
        else
            a[k] = R[j++];
	}
}


