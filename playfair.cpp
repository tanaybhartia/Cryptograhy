#include<bits/stdc++.h>
using namespace std;
int encrypt(char str[],char key[])
{
  char ct[30];
  if(strlen(str)%2)
    {
      strcat(str,"x");
    }
  int i,j,k,l,r1,r2,c1,c2,p,q;
  strcat(key,"abcdefghiklmnopqrstuvwxyz");
  int size=strlen(key);
  int n = strlen(str);
  for(i=0;i<size;i++)
  {
    if(key[i]=='j')
	  {
	   key[i]='i';
	  }
    for(j=i+1;j<size;)
	  {
  	  if(key[j]==key[i])
  	  {
  	    for(k=j;k<size;k++)
  		  {
  		    key[k]=key[k+1];
  		  }
  	    size--;
  	  }
  	  else j++;
	  }
  }
  char matrix[5][5];
  for(i=0,k=0;i<5;i++)
  {
    for(j=0;j<5;j++)
	  {
	   matrix[i][j]=key[k];
	   k++;
	  }
  }
  cout<<"The encryption matrix is: "<<endl;
  for(i=0;i<5;i++)
  {
    for(j=0;j<5;j++)
	  {
	   cout<<matrix[i][j]<<" ";
	  }
    cout<<endl;
  }
  //cout<<str<<endl;
  j=1;
  fflush(stdin);
  for(i=0;i<strlen(str);)
  {
      r1=0;r2=0;c1=0;c2=0;p=0;q=0;
      p=str[i];q=str[j];
      //printf("\t");putchar(str[i]);putchar(str[j]);printf("=");
      if(p=='j'){str[i]='i';}
      if(q=='j'){str[i]='i';}
      for(k=0;k<5;k++)
	    {
  	      for(l=0;l<5;l++)
  	      {
    	      if(matrix[k][l]==p)
    		    {
    		      r1=k;c1=l;
    		    }
    	      if(matrix[k][l]==q)
    		    {
    		      r2=k;c2=l;
    		    }
	        }
	    }
      if(r1==r2)
      {
        ct[i]=matrix[r1][(c1+1)%5];
        ct[j]=matrix[r2][(c2+1)%5];
	    //putchar(ct[i]);putchar(ct[j]);
      }
      else if(c1==c2)
      {
        ct[i]=matrix[(r1+1)%5][c1];
        ct[j]=matrix[(r2+1)%5][c2];
	     //putchar(ct[i]);putchar(ct[j]);
      }
      else
      {
        ct[i]=matrix[r1][c2];
        ct[j]=matrix[r2][c1];
	     //putchar(ct[i]);putchar(ct[j]);
      }
      i=i+2;j=j+2;
  }
  fflush(stdin);
  int x;
  cout<<"Encrypted Message: ";
  for(x=0;x<n;x++)
  {
    cout<<ct[x]<<" ";
  }
  cout<<endl;
}
int decrypt(char str[],char key[])
{
  char ct[30];
  int i,j,k,l,r1,r2,c1,c2,p,q;
  strcat(key,"abcdefghiklmnopqrstuvwxyz");
  int size=strlen(key);
  for(i=0;i<size;i++)
  {
      if(key[i]=='j')
	    {
	     key[i]='i';
	    }
      for(j=i+1;j<size;)
	    {
	     if(key[j]==key[i])
	     {
	       for(k=j;k<size;k++)
		     {
		      key[k]=key[k+1];
		     }
	       size--;
	     }
	     else j++;
	    }
  }
  char matrix[5][5];
  for(i=0,k=0;i<5;i++)
    {
      for(j=0;j<5;j++)
	    {
	     matrix[i][j]=key[k];
	     k++;
	    }
    }
  //printf("check");
  cout<<"The decryption matrix is: "<<endl;
  for(i=0;i<5;i++)
    {
      for(j=0;j<5;j++)
	    {
	     cout<<matrix[i][j]<<" ";
	    }
      cout<<endl;
    }
  j=1;
  for(i=0;i<strlen(str);)
    {
      r1=0;r2=0;c1=0;c2=0;p=0;q=0;
      p=str[i];q=str[j];
      printf("\t");putchar(str[i]);putchar(str[j]);printf("=");
      if(p=='j'){str[i]='i';}
      if(q=='j'){str[i]='i';}
      for(k=0;k<5;k++)
	    {
	     for(l=0;l<5;l++)
	     {
	      if(matrix[k][l]==p)
		    {
		      r1=k;c1=l;
		    }
	      if(matrix[k][l]==q)
		    {
		      r2=k;c2=l;
		    }
	     }
	    }
      if(r1==r2)
      {
        if(c1==0)
        {
          c1=5;
        }
        if(c2==0)
        {
          c2=5;
        }
	      ct[i]=matrix[r1][(c1-1)%5];
        ct[j]=matrix[r2][(c2-1)%5];
	      putchar(ct[i]);putchar(ct[j]);
      }
      else if(c1==c2)
      {
        ct[i]=matrix[(r1-1)%5][c1];
        ct[j]=matrix[(r2-1)%5][c2];
	      putchar(ct[i]);putchar(ct[j]);
      }
      else
      {
        ct[i]=matrix[r1][c2];
        ct[j]=matrix[r2][c1];
	      putchar(ct[i]);putchar(ct[j]);
      }
      i=i+2;j=j+2;
    }
}

int main()
{
  cout<<"1. Encrypt"<<endl;
  cout<<"2. Decrypt"<<endl;
  int i;
  cin>>i;
  if(i==1)
    {
      char str[30],key[50],c;
      cout<<"Enter plaintext"<<endl;
      cin>>str;
      cout<<"Enter key "<<endl;
      cin>>key;
      encrypt(str,key);
    }
  else if(i==2)
    {
      char str[30],key[50];
      cout<<"Enter Cipher text"<<endl;
      cin>>str;
      cout<<"Enter key "<<endl;
      cin>>key;
      decrypt(str,key);
    }
  else
    {
      cout<<"Wrong Input"<<endl;
    }
  return 0;
}
