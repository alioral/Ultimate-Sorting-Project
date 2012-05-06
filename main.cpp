#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <ostream>

using namespace std;

bool compare(string a,string b)
{
    int limit=a.size()>b.size()?b.size():a.size();
    for(int i=0;i<limit;i++)
    {
        if(a[i]!=b[i])
        {
            if(a[i]>b[i])
                return false;
            else
                return true;
        }
    }
   return limit==b.size()?false:true;
}

void insertionSort(vector<string>& arr)
{
    int j;
    string key;
    for(int i=1;i<arr.size();i++)
    {
        key=arr[i];
        for(j=i-1;j>=0 && compare(key,arr[j]);j--)
        {
            arr[j+1]=arr[j];
        }
        arr[j+1]=key;
    }
}

vector< vector<string> >createBuckets()
{
    vector< vector<string> > buckets;
    buckets.resize(26);
    return buckets;
}

void printVector(vector<string>& vec){ for(int i=0;i<vec.size();i++) cout<<vec[i]<<" "; cout<<endl; }

vector<string>concatenate(vector< vector<string> >&vec)
{
    vector<string>dummy=vec[0];
    for(int i=0;i<vec.size()-1;i++) dummy.insert(dummy.end(),vec[i+1].begin(),vec[i+1].end());
    return dummy;
}

vector<string> bucketSort(vector<string>&vec)
{
    vector< vector<string> >numbersOfTest=createBuckets();
    for(int i=0;i<vec.size();i++) if(vec[i][0]-97>0 && vec[i][0]-97<26) numbersOfTest[vec[i][0]-97].push_back(vec[i]);
    for(int i=0;i<numbersOfTest.size();i++) insertionSort(numbersOfTest[i]);
    return concatenate(numbersOfTest);
}

vector<string> merge(vector<string>a,vector<string>b)
{
    vector<string>merged;
    int limit=a.size()<=b.size()?b.size():a.size();
    int k=0;
    int j=0;
    while(k<a.size() && j<b.size()){
        if(compare(a[k],b[j]))
        {
            merged.push_back(a[k]);
            k++;
        }
        else
        {
            merged.push_back(b[j]);
            j++;
        }
    }
    if(k>=a.size()) for(int i=j;i<b.size();i++) merged.push_back(b[i]);
    else for(int i=k;i<a.size();i++) merged.push_back(a[i]);
    return merged;
}
vector<string>partition(vector<string>&a,int start,int finish)
{
    vector<string>parted;
    int size=finish-start+1;
    for(int i=0;i<size;i++) parted.push_back(a[i+start]);
    return parted;
}
int uniqueId=0;
vector<string>mergeSort(vector<string>a)
{
    if(a.size()<=1)
        return a;
    else
    {
        vector<string>partition1=partition(a,0,a.size()/2-1);
        vector<string>partition2=partition(a,a.size()/2,a.size()-1);
        return merge(mergeSort(partition1),mergeSort(partition2));
    }
}

vector<string> mergeForQuickSort(vector<string>a,string pivot,vector<string>b)
{
    a.push_back(pivot);
    a.insert(a.end(),b.begin(),b.end());
    return a;
}
vector<string> quickSort(vector<string>& a)
{
    srand(time(0));
    string pivot;
    vector<string>left;
    vector<string>right;
    if(a.size()<=1)
        return a;
    else
    {
        int pivotIndex=rand()%a.size();
        pivot=a[pivotIndex];
        a.erase(a.begin()+pivotIndex);
        for(int i=0;i<a.size();i++)
        {
            if(compare(a[i],pivot))
                left.push_back(a[i]);
            else
                right.push_back(a[i]);
        }
        return mergeForQuickSort(quickSort(left),pivot,quickSort(right));
    }
}

int main()
{
    time_t start_time_quick,end_time_quick,start_time_bucket,end_time_bucket,start_time_merge,end_time_merge;
    string word;
    vector<string>arr;
    ifstream file("input_30250.txt");
    while(!file.eof()){
        file >> word;
        arr.push_back(word);
    }
    start_time_merge=clock();
    vector<string>sortedArr=mergeSort(arr);
    end_time_merge=clock();
    cout<<"Time elapsed in milliseconds in MergeSort:"<<difftime(end_time_merge,start_time_merge)<<endl;

    start_time_bucket=clock();
    sortedArr=bucketSort(arr);
    end_time_bucket=clock();
    cout<<"Time elapsed in milliseconds in BucketSort:"<<difftime(end_time_bucket,start_time_bucket)<<endl;

    start_time_quick=clock();
    sortedArr=quickSort(arr);
    end_time_quick=clock();
    cout<<"Time elapsed in milliseconds in QuickSort:"<<difftime(end_time_quick,start_time_quick)<<endl;

    ofstream fileWrite;
	fileWrite.open("sorted9.txt");
	for(int i=0; i<sortedArr.size(); i++){
		fileWrite << sortedArr[i]<<endl;
	}
    return 0;
}
