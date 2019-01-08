#include <stdio.h>

void deleter(int level,int size,int i,int j,int array[100][100],int carrot_array[100][100])
{
	if(i+1<=size)
	{
		if(array[i][j]==level && carrot_array[i][j]==level)
		{
			array[i][j]=0;
			
		}		
	deleter(level,size,i+1,j,array,carrot_array);
	}
	if(i==size && j+1<=size)
	{
		deleter(level,size,0,j+1,array,carrot_array);
	}
	if(i==size && j==size)
	{
		return;
	}
}

void carrot_leveler(int level,int x,int y,int array[100][100],int carrot_array[100][100],int size,int *counter,int stopper)
{
	
	carrot_array[x][y]=level;
	if(x+1<=size)
	{
		if(array[x+1][y]==level)
		{
			if(carrot_array[x+1][y]!=level && array[x+1][y]==level)
			{
			*counter=*counter+1;
			carrot_leveler(level,x+1,y,array,carrot_array,size,counter,stopper+1);	
			}
		}
	}
	if(x-1>=0)
	{
		if(array[x-1][y]==level)
		{
			if(carrot_array[x-1][y]!=level && array[x-1][y]==level)
			{
			*counter=*counter+1;
			carrot_leveler(level,x-1,y,array,carrot_array,size,counter,stopper+1);	
			}
		}
	}
	if(y+1<=size)
	{
		if(array[x][y+1]==level)
		{
			if(carrot_array[x][y+1]!=level && array[x][y+1]==level)
			{
			*counter=*counter+1;
			carrot_leveler(level,x,y+1,array,carrot_array,size,counter,stopper+1);	
			}
		}
	}
	if(y-1>=0)
	{
		if(array[x][y-1]==level)
		{
			if(carrot_array[x][y-1]!=level && array[x][y-1]==level)
			{
			*counter=*counter+1;
			carrot_leveler(level,x,y-1,array,carrot_array,size,counter,stopper+1);	
			}
		}
	}
	printf("%d-%d\n",*counter,stopper);
	if (*counter>=2 && stopper==0)
	{

		array[x][y]=level+1;
		carrot_array[x][y]=0;
		deleter(level,size,0,0,array,carrot_array);
	}
	if(stopper==0)
	{
		*counter=0;
	}
}
	


void carrot_placer(int array[100][100],int size)
{
	int a,b,c;
	while(scanf("%d",&a)!=EOF)
	{
		int carrot_array[100][100]={{0}};
		int *counter;
		int m=0;
		counter=&m;
		scanf("%d %d",&b,&c);
		array[b][c]=a;
				
		carrot_leveler(a,b,c,array,carrot_array,size,counter,0);
		carrot_leveler(a+1,b,c,array,carrot_array,size,counter,0);
		carrot_leveler(a+2,b,c,array,carrot_array,size,counter,0);
		carrot_leveler(a+3,b,c,array,carrot_array,size,counter,0);
		
	}
	
}

int main(void)

{
	int i,j;
	int array[100][100]={{0}};
	int size;
	scanf("%d",&size);
	carrot_placer(array,size);
	for (i=0;i<size;i++) 
	{
		for (j=0;j<size;j++)
		printf("%d ",array[j][i]);
		printf("\n");
	}
	/**
	input_reader(arr,a,b,c);
	printf("%d %d %d",array[0],array[1],array[2]);
	**/
	return 0;
}
