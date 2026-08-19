// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
int main() {
    // Write C++ code here
    //finding maximum subarray

    std::cout << "Try programiz.pro\n";
    int start,end;
    int num;
   cout<<"enter num of elements:";
   cin>>num;
   int array[num];
    cout<<"numbers are:\n";
   for(int i=0; i<num; i++)
   {

       cin>>array[i];
   }
  cout<<"\n SUBARRAYS\n";
       for(start=0; start<num; start++)
       {
           for(end=start; end<num; end++)
           {
             for(int i=start; i<=end; i++)
             {
                 cout<<array[i];
             }
             cout<<" ";
           }
           cout<<endl;
       }
int maxsum=INT_MIN;
   for(start=0; start<num; start++)
       {
       	int sum=0;
           for(end=start; end<num; end++)
           {
             sum=sum+array[end];
             maxsum=max(sum,maxsum);
		} } cout<<"\n max subarray sum is: "<<maxsum<<endl;
	}