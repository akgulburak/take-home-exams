#include <stdio.h>


void deleter(int array[100][100],int carrot_array[100][100],int size,int x,int y)
{
	int i,j;
	/**
	int ctx1=0,cty1=0;
	int ctx2=0,cty2=0;
	
	for(i=1;i<3;i++)
	{
		if(x-i>=0)
		{
			ctx1=x-i;
		}
		if(y-i>=0)
		{
			cty1=y-i;
		}
		if(x+i<=size)
		{
			ctx2=x+i;
		}
		if(y+i<=size)
		{
			cty2=y+i;
		}
		
	}
	**/
	
	for(i=0;i<=size;i++)
	{

		for(j=0;j<=size;j++)
		{
		
			if(carrot_array[j][i]!=0)
			{
				array[j][i]=0;
				carrot_array[j][i]=0;
			}
		}
		
	}
	
}


void carrot_leveler(int level,int x,int y,int array[100][100],int carrot_array[100][100],int size)
{
	int i,j,k,l;
	int counter=0;
	
	for(i=1;i<3;i++)
	{

		if(x+i>size || array[x+i][y]!=level )
		{
			break;
		}
		
		if(carrot_array[x+i][y]!=level)
		{
		carrot_array[x+i][y]=level;
		counter++;
		}
		if(y+1<=size && array[x+i][y+1]==level)
		{
			if(carrot_array[x+i][y+1]!=level)
			{
				carrot_array[x+i][y+1]=level;
				counter++;
			}
		}
		if(y-1>=0 && array[x+i][y-1]==level)
		{
			if(carrot_array[x+i][y-1]!=level)
			{
				carrot_array[x+i][y-1]=level;;
				counter++;
			}
		}
	}
	
	for(j=1;j<3;j++)
	{
		
		if(y+j>size || array[x][y+j]!=level )
		{
			break;
		}
		if(carrot_array[x][y+j]!=level)
		{
		carrot_array[x][y+j]=level;
		counter++;
		}
		if(x+1<=size && array[x+1][y+j]==level)
		{
			if(carrot_array[x+1][y+j]!=level)
			{
			carrot_array[x+1][y+j]=level;
			counter++;
			}
		}
		if(x-1>=0 && array[x-1][y+j]==level)
		{
			if(carrot_array[x-1][y+j]!=level)
			{
			carrot_array[x-1][y+j]=level;;
			counter++;
			}
		}
	}
	for(k=1;k<3;k++)
	{
		
		if(x-k<0 || array[x-k][y]!=level )
		{
			break;
		}
		if(carrot_array[x-k][y]!=level)
		{
		carrot_array[x-k][y]=level;
		counter++;
		}
		if(y+1<=size && array[x-k][y+1]==level)
		{
			if(carrot_array[x-k][y+1]!=level)
			{
				carrot_array[x-k][y+1]=level;
				counter++;
			}
		}
		if(y-1>=0 && array[x-k][y-1]==level)
		{
			if(carrot_array[x-k][y-1]!=level)
			{
				carrot_array[x-k][y-1]=level;;
				counter++;
			}
		}
	}
	for(l=1;l<3;l++)
	{
		if(y-l<0 || array[x][y-l]!=level )
		{
			break;
		}
		if(carrot_array[x][y-l]!=level)
		{
		carrot_array[x][y-l]=level;
		counter++;
		}
		if(x+1<=size && array[x+1][y-l]==level)
		{
			if(carrot_array[x+1][y-l]!=level)
			{
				carrot_array[x+1][y-l]=level;
				counter++;
			}
		}
		if(x-1>=0 && array[x-1][y-l]==level)
		{
			if(carrot_array[x-1][y-l]!=level)
			{
				carrot_array[x-1][y-l]=level;;
				counter++;
			}
		}
	}
			

	if(counter>=2)
	{
		array[x][y]=level+1;

	}
}
	

	


void carrot_placer(int array[100][100],int size)
{
	int a,b,c;
	while(scanf("%d",&a)!=EOF)
	{
		int i;
		int control_var;
		int carrot_array[100][100]={{0}};
		/** check the carrot_array
		int p,v;
		**/
		scanf("%d %d",&b,&c);
		array[b][c]=a;
		
		for(i=0;i<4;i++)
		{		
		
		control_var=array[b][c];
		carrot_leveler(a+i,b,c,array,carrot_array,size);
		if(control_var!=array[b][c])
		{
		deleter(array,carrot_array,size,b,c);
		}
		if(control_var==array[b][c])
		{
			break;
		}
		}
		
	/**
		for (p=0;p<size;p++) 
	{
		for (v=0;v<size;v++)
		printf("%d ",carrot_array[v][p]);
		printf("\n");
	} to check the carrot_array
	**/
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
