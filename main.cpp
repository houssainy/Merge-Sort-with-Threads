#include <stdio.h>
#include <limits>
#include<fstream>
#include <stdlib.h>

/**
* Author: Mohamed El-Houssainy
* Subject: OS Lab2
* Date: 21/10/2013
*
* About: Merge sort implementation using Threads
* Refrences:
* Threads-> http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
*/

using namespace std;

void *merge_sort(void *ptr);
void _merge( int *a , int startPos , int mid , int endPos);

struct merge_sort_args{
    int *a;
    int startPos;
    int endPos;
};

int thread_count;
int main(){

    //*********Start Read File*************
    thread_count = 1;
    ifstream myReadFile;
    myReadFile.open("input.txt");
    string myString;

    //Number of elements in the file
    if (myReadFile.is_open())
        getline(myReadFile,myString);

    int n = atoi(myString.c_str());
    int a[n];

    if (myReadFile.is_open()) {
        int pos = 0;
        while (!myReadFile.eof()) {
            getline(myReadFile,myString , ',');
            a[pos++] = atoi(myString.c_str());
        }
    }

    myReadFile.close();
    //*************** End Reading of file ************

    int array_length = sizeof(a)/sizeof(a[0]);

    merge_sort_args *args = new merge_sort_args();
    args->a = a;
    args->startPos = 0;
    args->endPos = array_length-1;

    //merge_sort(a,0, array_length-1);
    merge_sort(args);

    //Print Values
    for(int i = 0 ; i < array_length ; i++ ){
        if(i!= array_length-1)
            printf("%i,",a[i]);
        else
            printf("%i",a[i]);
    }

    return 0;
}

/**
*   Mergo Sort Algorithm.
*/
void *merge_sort(void* ptr ) {

    merge_sort_args *args = (merge_sort_args*)ptr;

	if( args->endPos - args->startPos +1 > 1  ) {
		int mid = (args->startPos+args->endPos) / 2;


		/***************** Starting of Thread One*********************/
        int thread_id1, thread_id2;

		merge_sort_args *new_args1 = new merge_sort_args();
        new_args1->a = args->a;
        new_args1->startPos = args->startPos;
        new_args1->endPos = mid;

        pthread_t thread1;
		if( thread_count < 10){
            thread_count++;
            thread_id1 = pthread_create( &thread1, NULL, merge_sort, (void*) new_args1);
        }else{
            merge_sort(new_args1);
        }
		//merge_sort( a , startPos, mid);
		/*****************End of Thread One*********************/

		/***************** Starting of Thread Two *********************/

        merge_sort_args *new_args2 = new merge_sort_args();
        new_args2->a = args->a;
        new_args2->startPos = mid+1;
        new_args2->endPos = args->endPos;

        pthread_t thread2;
		if( thread_count < 10){
            thread_count++;
            thread_id2 = pthread_create( &thread2, NULL, merge_sort, (void*) new_args2);
            //merge_sort( a , mid + 1 , endPos);
        }else{
            merge_sort(new_args2);
        }
		/*****************End of Thread Two *********************/
		//Wait till the two threads finish their work
		if ( thread_id1 != 0 ){
            pthread_join( thread1, NULL);
            thread_count--;
        }
        if( thread_id2 != 0 ){
            pthread_join( thread2, NULL);
            thread_count--;
        }
        ;
        //Merge the results
		_merge(args->a , args->startPos , mid ,args->endPos);
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

    //Set last Elements in the Right and Left arrays Infinity.
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


