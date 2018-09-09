#include <stdlib.h>
#include <string.h>
#include "../include/string.h"

size_t index_KMP(const char *S, const char *T, size_t pos)
{	//pos is human position
	size_t SL=strlen(S), TL=strlen(T);

	size_t *next=(size_t*)malloc(sizeof(size_t)*TL);

	next[0]=0;			//save human position
	size_t i=1, j=0;	//save human position

	while(i<=TL)
	{
		if(j==0 || T[i-1]==T[j-1])
		{
			++i;
			++j;
			if(T[i-1]==T[j-1])
			{
				next[i-1]=next[j-1];
			}
			else
			{
				next[i-1]=j;
			}
		}
		else
		{
			j=next[j-1];
		}
	}
	
	i=pos;
	j=1;
	while(i<=SL && j<=TL)
	{
		if(j==0 || S[i-1]==T[j-1])
		{
			++i;
			++j;
		}
		else
		{
			j=next[j-1];
		}
	}

	if(j>TL)
	{
		return i-TL;
	}	
	else
	{
		return 0;
	}
}

size_t index_BM(const char* S, const char* T, size_t pos)
{
	size_t SL=strlen(S), TL=strlen(T);
	size_t i=pos-1, j=0;	//save machine position
	
	while(i<SL && j<TL)
	{
		if(S[i]==T[j])
		{
			++i;
			++j;
		}
		else
		{
			i=i-j+1;
			j=0;
		}
	}

	if(j==TL)
	{
		return i-TL+1;
	}
	else
	{
		return 0;
	}
}