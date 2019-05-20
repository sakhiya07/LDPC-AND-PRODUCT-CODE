// ENCODER AND DECODER FOR BINARY ERASING CODE
// CODE IN CPP
// IN ENCODER ERASING DEPEND ON PROBABILITY
#include<bits/stdc++.h>
using namespace std;
int main(){
  srand(time(NULL));
  //variables
  int n,k,i,j,p,paritybit,xoor,nonerror_index,flag=0,cnt=0,loop=0,total=0,error,messagebit;
  cout<<"enter n and k";
  cin>>n>>k;
  int r1_message[n]={0},updated_message[n],parity[n-k][n],error_message[n]={0},r_message[n];

  double pro;
  char choice;

  cout<<"L for ldpc";
  cout<<"P for product";
  cin>>choice;
  if(choice=='P')
  {

      int msg[k];
      cout<<"insert message bit";
      for(i=0;i<k;i++)
      cin>>msg[i];
       //making generator matrix for given value of n
            int generator[n][k]={0},temp;
            for(i=0;i<n;i++)
            {
                for(j=0;j<k;j++)
                {
                   generator[i][j]=0;
                }
            }
            int temp1=sqrt(k);
            int temp2=sqrt(n),temp3=0;
            int count=0;

            for(i=0;i<n && count<=k;i++)
            {
                if(temp3==temp1)
                {
                    temp3=0;
                    for(j=count-temp1;j<count;j++)
                    {
                        generator[i][j]=1;
                    }
                }
                else if(count<k)
                {
                    generator[i][count]=1;
                    count++;
                    temp3++;
                }
            }
            count=0;

            for(i=k+temp1;i<n-1;i++)
            {
                for(j=count;j<k;j+=temp1)
                {
                    generator[i][j]=1;
                }
                count++;
            }

            for(i=0;i<k;i++)
            {
                generator[n-1][i]=1;
            }
            for(i=0;i<n;i++)
            {
                for(j=0;j<k;j++)
                {
                     r1_message[i]=r1_message[i]+(msg[j]*generator[i][j]);
                }
                r1_message[i]=r1_message[i]%2;
            }

   }
   else
   {
        cout<<"enter message bits"<<endl;
        for(i=0;i<n;i++)
        cin>>r1_message[i];
   }
   cout<<"message is: ";
   for(i=0;i<n;i++)
      cout<<r1_message[i]<<" ";
   cout<<endl;
   cout<<"enter probability"<<endl;
   cin>>pro;
   pro=pro*100;
    // generating error;
    for(i=0;i<n;i++)
    {
       int r = rand()%100;
       if(r<pro)
       error_message[i]=1;

    }
    for(i=0;i<n;i++)
    {
         if(error_message[i]==1)
         r_message[i]=-1;
         else
         r_message[i]=r1_message[i];
    }
    cout<<"error message is:";
    for(i=0;i<n;i++)
    {
       cout<<r_message[i]<<" ";
       if(r_message[i]==-1)
         total++;
    }
    cout<<endl;
    if(choice=='L')
    {
        for(i=0;i<n-k;i++)
        {
           for(j=0;j<n;j++)
           cin>>parity[i][j];
        }
    }
    else
    {

         // Generating Parity Check Matrix
         int temp;
         for(i=0;i<n-k;i++)
         {
            for(j=0;j<n;j++)
            {
               parity[i][j]=0;
            }
         }
         int temp1=sqrt(k);
         int temp2=sqrt(n);
         int count=0;
         for(i=0;i<temp1;i++)
         {
             for(j=count;j<count+temp2;j++)
             {
                parity[i][j]=1;
             }
              count+=temp2;
         }
         count=0;
         for(i=temp1;i<n-k;i++)
         {
            for(j=count;j<n;j+=temp1+1)
            {
               parity[i][j]=1;
            }
              count++;
         }
    }

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
  // doing iteration
  while(loop<25 && total>0)
  {
     loop++;
     cnt=0;
     //Passing of XOR from Checknodes
     for(i=0;i<n;i++)
     {
        messagebit=i;
        xoor=0;
        for(j=0;j<mn[i].size();j++)
        {
            paritybit=mn[i][j].second;
            error=0;
            for(p=0;p<cn[paritybit].size();p++)
            {
                if(cn[paritybit][p].second!=i)
                {
                   if(cn[paritybit][p].first==-1)
                   {
                      error++;
                   }
                }
            }
            xoor=0;
            if(error==0)
            {
                for(p=0;p<cn[paritybit].size();p++)
                {
                    if(cn[paritybit][p].second!=i)
                    {
                          xoor=xoor+cn[paritybit][p].first;
                    }
                }
                xoor=xoor%2;
            }
            else
            {
                xoor=-1;
            }
            for(p=0;p<mn[i].size();p++)
            {
                 if(mn[i][p].second==paritybit)
                 {
                     mn[i][p].first=xoor;
                 }
            }
        }
    }
    //Updation of MessageBits
      for(i=0;i<n;i++)
      {
          if(r_message[i]==1 || r_message[i]==0)
          {
              updated_message[i]=r_message[i];
          }
          else
          {
              nonerror_index=-1;
              for(j=0;j<mn[i].size();j++)
              {
                 if(mn[i][j].first!=-1)
                 {
                    nonerror_index=mn[i][j].first;
                    break;
                 }
              }
              updated_message[i]=nonerror_index;
          }
      }
      cout<<endl<<"message is :";
       for(i=0;i<n;i++)
         cout<<updated_message[i]<<" ";
       //Check for decoded Message
       for(i=0;i<n;i++)
       {
          if(updated_message[i]==-1)
          {
            cnt++;
          }
       }
       //Break loop
       if(cnt==0)
       {
          cout<<endl<<"........Decoded........"<<endl;
          break;
       }

      //Updation of ParityCheckBits
      for(i=0;i<n-k;i++)
      {
        for(j=0;j<cn[i].size();j++)
        {
            cn[i][j].first=updated_message[cn[i][j].second];
        }
      }

  }
  if(loop==25 && cnt!=0){
    cout<<"<<<...SORRY,Unable To Decode...>>>";
  }
  return 0;
}
