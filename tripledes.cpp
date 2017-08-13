#include<bits/stdc++.h>

using namespace std;

int bin_to_hex(bool *p,int n)
{
	int i,m=0;
	for(i=n;i>0;i--)
	{
		m += p[n-i]*pow(2,i-1);
	}
	return m;
}

void hex_to_bin(int m,bool *p,int i)
{
	while(m>0)
	{
		p[i-1] = m%2;
		m = m/2;
		i--;
	}
	while(i>0)
	{
		p[i-1] = 0;
		i--;
	}
}

void permute(bool *text,int *p,int n)
{
	bool v[n];
	int i;
	for(i=0;i<n;i++)
	{
		v[i] = text[p[i]-1];
	}
	for(i=0;i<n;i++)
	{
		text[i] = v[i];
	}
}

void key_schedule(bool key[],bool KEY[][48])
{
  	bool permuted_key1[56];
  	int tmp[28];
  	bool t,u;
  	bool final[17][56];
  	int pc1[8][7]={{57,    49,    41,    33,    25,    17,    9},
		 {1 ,    58,    50,    42,    34,    26,   18},
		 {10,    2 ,    59,    51,    43,    35,   27},
		 {19,    11,    3 ,    60,    52,    44,   36},
		 {63,    55,    47,    39,    31,    23,   15},
		 {7,    62,    54,    46,    38,    30,   22},
		 {14,    6 ,    61,    53,    45,    37,   29},
		 {21,    13,    5 ,    28,    20,    12,    4}};
  	int pc2[8][6]={{14,    17,    11,    24,     1,    5},
		 {3 ,    28,    15,     6,    21,   10},
		 {23,    19,    12,     4,    26,    8},
		 {16,     7,    27,    20,    13,    2},
		 {41,    52,    31,    37,    47,   55},
		 {30,    40,    51,    45,    33,   48},
		 {44,    49,    39,    56,    34,   53},
		 {46,    42,    50,    36,    29,   32}};
  	int k=0;
  	for(int i=0;i<8;i++)
    {
      for(int j=0;j<7;j++)
		{
	  		final[0][k]=key[pc1[i][j]-1];
	  		k++;
		}
    }
  	for(int i=1;i<17;i++)
    {
	      if(i==1 || i==2 || i==9 || i==16)
			{
		  		t=final[i-1][0];
		  		for(int q=0;q<27;q++)
		    		final[i][q]=final[i-1][q+1];
		  		final[i][27]=t;
			}
	      else
			{
		  		t=final[i-1][0];
		  		u=final[i-1][1];
		  		for(int q=0;q<26;q++)
		    		final[i][q]=final[i-1][q+2];
				final[i][26]=t;
				final[i][27]=u;
			}
	}
	for(int i=1;i<17;i++)
	{
	    if(i==1 || i==2 || i==9 || i==16)
		{
		  t=final[i-1][28];
		  for(int q=28;q<27+28;q++)
		    final[i][q]=final[i-1][q+1];
		  final[i][27+28]=t;
		}
	    else
		{
		  t=final[i-1][28];
		  u=final[i-1][29];
		  for(int q=28;q<26+28;q++)
		    final[i][q]=final[i-1][q+2];
		  final[i][26+28]=t;
		  final[i][27+28]=u;
		}
    }
	k=0;
	for(int l=1;l<17;l++)
	{
	    for(int i=0;i<8;i++)
		{
		  for(int j=0;j<6;j++)
		    {
		      KEY[l][k]=final[l][pc2[i][j]-1];
		      k++;
		    }
		}
	    k=0;
	}
}


void fiestel(bool *text,bool *key)
{
	int i,j,k;
	int exc[48] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
	bool l0[32],r0[32],l1[32],r1[32],temp[48],temp1[32];
	int s[4][16] = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};
	int per[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
	for(i=0;i<32;i++)
	{
		l0[i] = text[i];
	}
	for(i=32;i<64;i++)
	{
		r0[i-32] = text[i];
		l1[i-32] = text[i];
	}
	for(i=0;i<48;i++)
	{
		temp[i] = r0[exc[i] - 1];
	}
	for(i=0;i<48;i++)
	{
		temp[i] = temp[i]^key[i];
	}
	for(i=0;i<8;i++)
	{
		//cout<<i<<endl;
		bool p[2] = {temp[6*i],temp[6*i+5]};
		int m = bin_to_hex(p,2);
		bool p1[4] = {temp[6*i+1],temp[6*i+2],temp[6*i+3],temp[6*i+4]};
		int n = bin_to_hex(p,4);
		j = s[m][n];
		hex_to_bin(j,p1,4);
		for(k=0;k<4;k++)
			temp1[4*i+k] = p1[k];
		//cout<<i<<endl;
	}
	//cout<<"fiestel"<<endl;
	permute(temp1,per,32);
	for(i=0;i<32;i++)
		r1[i] = temp1[i]^l0[i];
	for(i=0;i<32;i++)
		text[i] = l1[i];
	for(i=32;i<64;i++)
		text[i] = r1[i-32];
}

void fiesteld(bool *text,bool *key)
{
	int i,j,k;
	int exc[48] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
	bool l0[32],r0[32],l1[32],r1[32],temp[48],temp1[32];
	int s[4][16] = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};
	int per[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
	//cout<<s[1][5]<<endl;
	for(i=0;i<32;i++)
	{
		l1[i] = text[i];
		r0[i] = text[i];
	}
	for(i=32;i<64;i++)
	{
		r1[i-32] = text[i];
	}
	for(i=0;i<48;i++)
	{
		temp[i] = l1[exc[i] - 1];
	}
	for(i=0;i<48;i++)
	{
		temp[i] = temp[i]^key[i];
	}
	for(i=0;i<8;i++)
	{
		bool p[2] = {temp[6*i],temp[6*i+5]};
		int m = bin_to_hex(p,2);
		bool p1[4] = {temp[6*i+1],temp[6*i+2],temp[6*i+3],temp[6*i+4]};
		int n = bin_to_hex(p,4);
		j = s[m][n];
		hex_to_bin(j,p1,4);
		for(k=0;k<4;k++)
			temp1[4*i+k] = p1[k];
	}
	permute(temp1,per,32);
	for(i=0;i<32;i++)
		l0[i] = temp1[i]^r1[i];
	for(i=0;i<32;i++)
		text[i] = l0[i];
	for(i=32;i<64;i++)
		text[i] = r0[i-32];
}

void encrypt(bool *text,int *ip,int *ipi,bool *key)
{
	int i;
	permute(text,ip,64);
	bool KEY[17][48];
	key_schedule(key,KEY);
	bool k[48];
	for(i=1;i<17;i++)
	{
		for(int j=0;j<48;j++)
		{
			k[j] = KEY[i][j];
		}
		fiestel(text,k);
	}
	bool l[32],r[32];
	for(i=0;i<32;i++)
		l[i] = text[i];
	for(i=32;i<64;i++)
		r[i-32] = text[i];
	for(i=0;i<32;i++)
		text[i] = r[i];
	for(i=32;i<64;i++)
		text[i] = l[i-32];
	permute(text,ipi,64);
}

void decrypt(bool *text,int *ip,int *ipi,bool *key)
{
	int i;
	bool l[32],r[32];
	permute(text,ip,64);
	bool KEY[17][48];
	for(i=0;i<32;i++)
		l[i] = text[i];
	for(i=32;i<64;i++)
		r[i-32] = text[i];
	for(i=0;i<32;i++)
		text[i] = r[i];
	for(i=32;i<64;i++)
		text[i] = l[i-32];
	key_schedule(key,KEY);
	bool k[48];
	for(i=16;i>0;i--)
	{
		for(int j=0;j<48;j++)
		{
			k[j] = KEY[i][j];
		}
		fiesteld(text,k);
	}
	permute(text,ipi,64);
}

int main()
{
	int i;
	bool text[64],key1[64],key2[64];
	cout<<"This is an algorithm for Triple DES showing both encryption and decryption."<<endl;
	cout<<"Enter the Plain-text (64-bit): "<<endl;
	for(i=0;i<64;i++)
	{
		cin>>text[i];
	}
	cout<<"Enter the Key 1 (56-bit): "<<endl;
	for(i=0;i<64;i++)
	{
		cin>>key1[i];
	}
	cout<<"Enter the Key 2 (56-bit): "<<endl;
	for(i=0;i<64;i++)
	{
		cin>>key2[i];
	}
	int ip[64] = {58, 50, 42, 34, 26, 18, 10, 2,
60, 	52, 	44, 	36, 	28, 	20, 	12, 	4,
62, 	54, 	46, 	38, 	30, 	22, 	14, 	6,
64, 	56, 	48, 	40, 	32, 	24, 	16, 	8,
57, 	49, 	41, 	33, 	25, 	17, 	9, 		1,
59, 	51, 	43, 	35, 	27, 	19, 	11, 	3,
61, 	53, 	45, 	37, 	29, 	21, 	13, 	5,
63, 	55, 	47, 	39, 	31, 	23, 	15, 	7};
	int ipi[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
	cout<<"Encryption Process: "<<endl;
	encrypt(text,ip,ipi,key1);
	cout<<"A: "<<endl;
	for(i=0;i<64;i++)
		cout<<text[i]<<" ";
	cout<<endl;
	decrypt(text,ip,ipi,key2);
	cout<<"B: "<<endl;
	for(i=0;i<64;i++)
		cout<<text[i]<<" ";
	cout<<endl;
	encrypt(text,ip,ipi,key1);
	cout<<"Encrypted Message:"<<endl;
	for(i=0;i<64;i++)
		cout<<text[i]<<" ";
	cout<<endl;
	cout<<"\nDecryption Process: "<<endl;
	decrypt(text,ip,ipi,key1);
	cout<<"B: "<<endl;
	for(i=0;i<64;i++)
		cout<<text[i]<<" ";
	cout<<endl;
	encrypt(text,ip,ipi,key2);
	cout<<"A: "<<endl;
	for(i=0;i<64;i++)
		cout<<text[i]<<" ";
	cout<<endl;
	decrypt(text,ip,ipi,key1);	
	cout<<"Decrypted Message: "<<endl;
	for(i=0;i<64;i++)
		cout<<text[i]<<" ";
	cout<<endl;
	return 0;
	
}
