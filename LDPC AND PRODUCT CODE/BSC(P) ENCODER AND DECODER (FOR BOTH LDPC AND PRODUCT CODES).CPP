// ENCODER AND DECODER FOR BINARY SHIFING CODE
// CODE IN CPP
// IN ENCODER SHIFTING DEPEND ON PROBABILITY
#include<bits/stdc++.h>
using namespace std;
#define RECEIVED_MESSAGE cout<<endl;for(i=0;i<n;i++){cout<<r_message[i]<<"  ";};
#define UPDATED_MESSAGE cout<<endl;for(i=0;i<n;i++){cout<<updated_message[i]<<"  ";};
int main()
{
  srand(time(NULL));
  //variables
  int n,k,i,j,p,paritybit,xoor,nonerror_index,flag=0,cnt=0,loop=0,total=0,error,messagebit,rtemp;
  double pro;
  int cnt0=0,cnt1=0,l,m,r,s,t,u,v,cn_maj[1000][1000];
  cout<<"enter n and k"<<endl;
  cin>>n>>k;
  cout<<"insert probability"<<endl;
  cin>>pro;
  //Matrix of Recived Message , Parity Matrix
  int r1_message[n],updated_message[n],parity[n-k][n],error_message[n]={0},r_message[n];
  int upm[n],syn[n-k][1],paridum,sumdum=0,tempp,flagg=0,rep=0,synsum=0,temp_msg;
  int cnt0d,cnt1d;
  // error
  pro=pro*100.0;
  for(i=0;i<n;i++)
  {
      int ko=(rand()%100);
      if(ko<pro)
      {
         error_message[i]=1;
      }

  }

  cout<<"enter message bit";
  //Input  of Recived Message
  for(i=0;i<n;i++)
  {
      cin>>r1_message[i];
      //Counting Erased Bits
  }
  for(i=0;i<n;i++)
  {
       r_message[i]=r1_message[i]^error_message[i];
  }

  cout<<endl;
  //Input Of Parity Matrix
  cout<<"L for ldpc"<<endl;
  cout<<"P for product";
  char eer;
  cin>>eer;
  if(eer=='L')
  {
        cout<<endl<<"Parity Check Matrix for Ldpc Code"<<endl;
        for(i=0;i<n-k;i++)
        {
             for(j=0;j<n;j++)
             {
               cin>>parity[i][j];
             }
       }
   }
   else
   {
     int temp;
     for(int i=0;i<n-k;i++)
     {
        for(int j=0;j<n;j++)
        {
            parity[i][j]=0;
        }
     }
    // Parity Check Matrix for Product Code
    int temp1=sqrt(k);
    int temp2=sqrt(n);
    int count=0;
    for(int i=0;i<temp1;i++)
    {
        for(int j=count;j<count+temp2;j++)
        {
            parity[i][j]=1;
        }
        count+=temp2;
    }


    count=0;

    for(int i=temp1;i<n-k;i++)
    {
        for(int j=count;j<n;j+=temp1+1)
        {
            parity[i][j]=1;
        }
        count++;
    }
 }
  //Print MessageBits with error
  cout<<endl;
  //Declaration of Checknode(cn) & Messagenode(mn)
  vector< vector < pair < int,int > > > cn(n-k);
  vector< vector < pair < int,int > > > mn(n);
  //Find Messagenode connected to Checknode(i)
  for(i=0;i<n-k;i++)
  {
        for(j=0;j<n;j++)
        {
          if(parity[i][j]==1)
          {
            cn[i].push_back(make_pair(r_message[j],j));
          }
        }
  }
      for(i=0;i<n;i++)
      {
        for(j=0;j<n-k;j++)
        {
          if(parity[j][i]==1)
          {
            mn[i].push_back(make_pair(0,j));
            //Take O in pair randomly(take any)
          }
        }
      }

  while(loop<1000)
  {
      vector<vector<pair<int,int>>>maj(n);
      vector<vector< int>> maj2(n);
      cout<<endl<<"the loop no is: "<<loop<<"   ";
      loop++;
      flagg=0;
      for(i=0;i<n;i++)
      {
             for(j=0;j<mn[i].size();j++)
             {   paritybit=mn[i][j].second;   //msgnode with respective checkernode
                 xoor=0;
                 for(p=0;p<cn[paritybit].size();p++)            //xoooring xooring
                 {
                       if(cn[paritybit][p].second!=i)
                       {
                        xoor=xoor+cn[paritybit][p].first;
                       }

                  }
                  maj[i].push_back(make_pair(xoor%2,mn[i][j].second));
             }
      }
      for(l=0;l<n;l++)
      {
            for(m=0;m<maj[l].size();m++)
            {
                paridum=maj[l][m].second;
                cnt0=cnt1=0;
                for(s=0;s<maj[l].size();s++)
                {
                    if(maj[l][s].second!=paridum)
                    {
                        if(maj[l][s].first==0)
                        {
                            cnt0++;

                        }
                        else
                        {
                            cnt1++;
                        }
                    }
                }
                if(r_message[l]==0)
                {
                    cnt0++;
                }
                else
                {
                    cnt1++;
                }
                if(cnt0>cnt1)
                {
                    temp_msg=0;
                }
                else if(cnt0<cnt1)
                {
                    temp_msg=1;
                }
                else if(cnt0==cnt1)
                {
                    rtemp=(rand()%2);
                    if(rtemp==0)
                    {
                        temp_msg=0;
                    }
                    else
                    {
                        temp_msg=1;
                    }
                }

                for(t=0;t<cn[paridum].size();t++)
                {
                    if(cn[paridum][t].second==l)
                    {
                      cn[paridum][t].first=temp_msg;
                    }
                }

            }
     }
    for(l=0;l<n;l++)
    {
        cnt0=cnt1=0;
        for(m=0;m<maj[l].size();m++)
        {
            if(maj[l][m].first==1)
           {
               cnt1++;
           }
           else
           {
               cnt0++;
           }
        }
        if(r_message[l]==0)
        {
            cnt0++;
        }
        else
        {
            cnt1++;
        }
        if(cnt0>cnt1)
        {
            upm[l]=0;
        }
        else if(cnt0<cnt1)
        {
            upm[l]=1;
        }
        else if(cnt0==cnt1)
        {
            rtemp=(rand()%2);
            if(rtemp==0)
            {
                upm[l]=0;
            }
            else
            {
                    upm[l]=1;
            }
        }
    }
    flagg=0;
    sumdum=0;
    for(l=0;l<(n-k);l++)
    {
        for(m=0;m<n;m++)
        {
             sumdum=sumdum+(parity[l][m]*upm[m]);
        }
    }

    for(l=0;l<n;l++)
    {
        cout<<upm[l]<<" ";
    }
    if(sumdum==0)
    {
        cout<<"The decoded bits are succesfully: ";
        for(l=0;l<n;l++)
        {
             cout<<upm[l]<<" ";
        }
        flagg=1;
        break;
    }
    cout<<endl;
  }
  //iteration over and not decoded
  if(flagg==0)
  {
       //not decoded successfully
       cout<<"The decoded bits are unsuccessfully: ";
          for(l=0;l<n;l++)
          {
              cout<<upm[l]<<" ";

          }
  }
}

