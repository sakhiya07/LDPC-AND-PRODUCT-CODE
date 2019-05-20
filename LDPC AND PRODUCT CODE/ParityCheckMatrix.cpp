// PARITYCHECK MATRIX FOR PRODUCT CODE
// IT GIVES PARITY CHECK MATRIX FOR ANY N VALUE
// CODE IN CPP

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,k;

    cin>>n;

    k=pow(sqrt(n)-1,2);

    int a[n-k][n]={0},temp;

    for(int i=0;i<n-k;i++)
    {
        for(int j=0;j<n;j++)
        {
            a[i][j]=0;
        }
    }

    int temp1=sqrt(k);
    int temp2=sqrt(n);
    int count=0;

    for(int i=0;i<temp1;i++)
    {
        for(int j=count;j<count+temp2;j++)
        {
            a[i][j]=1;
        }
        count+=temp2;
    }


    count=0;

    for(int i=temp1;i<n-k;i++)
    {
        for(int j=count;j<n;j+=temp1+1)
        {
            a[i][j]=1;
        }
        count++;
    }

    for(int i=0;i<n-k;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
