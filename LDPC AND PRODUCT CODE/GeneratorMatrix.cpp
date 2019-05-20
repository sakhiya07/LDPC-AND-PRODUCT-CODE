// FOR PRODUCT CODE
// GENERATOR MATRIX FOR ANY VALUE OF N
// GIVES YOU GENERATOR MATRIX FOR PRODUCT CODES
// CODE IN CPP
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,k;
    cin>>n;

    k=pow(sqrt(n)-1,2);

    int a[n][k]={0},temp;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            a[i][j]=0;
        }
    }

    int temp1=sqrt(k);
    int temp2=sqrt(n),temp3=0;
    int count=0;

    for(int i=0;i<n && count<=k;i++)
    {
        if(temp3==temp1)
        {
            temp3=0;
            for(int j=count-temp1;j<count;j++)
            {
                a[i][j]=1;
            }
        }
        else if(count<k)
        {
            a[i][count]=1;
            count++;
            temp3++;
        }
    }

    count=0;

    for(int i=k+temp1;i<n-1;i++)
    {
        for(int j=count;j<k;j+=temp1)
        {
            a[i][j]=1;
        }
        count++;
    }

    for(int i=0;i<k;i++)
    {
        a[n-1][i]=1;
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<k;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
