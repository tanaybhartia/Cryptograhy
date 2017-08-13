#include<bits/stdc++.h>
using namespace std;

int bin_to_hex(bool *p)
{
	int m = p[0]*8+p[1]*4+p[2]*2+p[3]*1;
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

void spn(bool *text,bool *key,int *pies,int *piep,bool *v)
{
	int i,j,k,m,n;
	bool u[16];
	cout<<"Key = ";
	for(i=0;i<16;i++)
	{
		cout<<key[i]<<" ";
	}
	cout<<endl;
	for(i=0;i<16;i++)
	{
		u[i] = text[i]^key[i];
	}
	cout<<"U = ";
	for(i=0;i<16;i++)
	{
		cout<<u[i]<<" ";
	}
	cout<<endl;
	bool p1[4];
	for(i=0;i<4;i++)
	{
		k = 4*i;
		for(j=0;j<4;j++)
		{
			p1[j] = u[k];
			k++;
		}
		m = bin_to_hex(p1);
		n = pies[m];
		hex_to_bin(n,p1,4);
		k=4*i;
		for(j=0;j<4;j++)
		{
			v[k] = p1[j];
			k++;
		}
	}
	cout<<"V = ";
	for(i=0;i<16;i++)
	{
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	/*int i,p[4] = {0,1,1,0};
	i= bin_to_hex(p);
	cout<<i<<endl;
	int l = 12;
	hex_to_bin(l,p);
	for(int j=0;j<4;j++)
		cout<<p[j]<<" ";
	*/
	cout<<"This is an algorithm to encrypt a message using SPN."<<endl;
	cout<<"Enter the plain text and key in bits."<<endl;
	int j,k,l,i,n = 5;
	int pies[16] = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
	int piep[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
	bool text[16],key[32];
	cout<<"Enter the plaintext (16-bit):"<<endl;
	for(i=0;i<16;i++)
	{
		cin>>text[i];
		if(text[i] != 0 && text[i] != 1)
		{
			cout<<"Input Error"<<endl;
			main();
		}
	}
	cout<<"Enter the key (32-bit):"<<endl;
	for(i=0;i<32;i++)
	{
		cin>>key[i];
		if(key[i] != 0 && key[i] != 1)
		{
			cout<<"Input Error"<<endl;
			main();
		}
	}
	i=1;
	bool v[16];
	bool temp[16];
	while(i<5)
	{
		j=4*i-4;
		for(k=0;k<16;k++)
		{
			temp[k] = key[j];
			j++;
		}
		spn(text,temp,pies,piep,v);
		for(k=0;k<16;k++)
		{
			text[k] = v[piep[k]];
		}
		/*cout<<"W = ";
		for(k=0;k<16;k++)
		{
			cout<<text[k]<<" ";
		}
		cout<<endl;*/
		i++;
	}
	j = 4*5-4;
	for(k=0;k<16;k++)
	{
		temp[k] = key[j];
		j++;
	}
	for(k=0;k<16;k++)
	{
		text[k] = v[k]^temp[k];
	}
	cout<<"The Cipher text is:"<<endl;
	for(i=0;i<16;i++)
	{
		cout<<text[i]<<" ";
	}
	cout<<endl;
	return 0;
}
