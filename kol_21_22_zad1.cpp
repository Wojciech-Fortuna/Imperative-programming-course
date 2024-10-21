#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _matrix{
    int rows;
    int cols;
    double **data;
}Matrix;

int create_matrix(Matrix *pmatrix,int rows, int cols)
{
	//zaimplementowana
	return 0;
}

int get(Matrix*pm,int row,int col,double*pvalue)
{
	if (row<0 || col<0 || row>=pm->rows || col>=pm->cols || pm->data!=NULL)
	{
		return 0;
	}
	else
	{
		*pvalue=pm->data[row][col];
		return 1;
	}
}

int set(Matrix *pm,int row,int col,double value)
{
	if (row<0 || col<0 || row>=pm->rows || col>=pm->cols || pm->data!=NULL)
	{
		return 0;
	}
	else
	{
		pm->data[row][col]=value;
		return 1;
	}
}

void crete_identity_matrix(Matrix *pm,int size)
{
	create_matrix(pm, size, size);
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			if (i==j)
			{
				set(pm,i,j,1);
			}
			else
			{
				set(pm,i,j,0);	
			}
		}
	}
}

double dot_prod_vect(const double*v1,const double*v2,int size)
{
	double result=0;
	for (int i=0; i<size; i++)
	{
		result+=(v1[i])*(v2[i]);
	}
	return result;
}

void mul_vect(double *result,const Matrix *pm,const double*vect)
{
	for (int i=0; i<pm->rows; i++)
	{
		result[i]=dot_prod_vect(vect, pm->data[i], pm->cols);
	}
}

void max_element_in_rows(double*maxdata,const Matrix*pm)
{
	double max_el;
	for (int i=0; i<pm->rows; i++)
	{
		max_el=pm->data[i][0];
		for (int j=1; j<pm->cols; j++)
		{
			if (pm->data[i][j]>max_el)
			{
				max_el=pm->data[i][j];
			}
		}
		maxdata[i]=max_el;
	}
}





























int main(){
}
