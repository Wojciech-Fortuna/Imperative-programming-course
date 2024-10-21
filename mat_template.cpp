#include <stdio.h>
#include <math.h>

#define SIZE 40

void read_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			printf("%.4f ", A[i][j]);
		}
		printf("\n");
	}
}

// 1. Calculate matrix product, AB = A X B
// A[m][p], B[p][n], AB[m][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n) {
	for (int i=0; i<m; i++)
	{
		for (int j=0; j<n; j++)
		{
			for (int k=0; k<p; k++)
			{
				AB[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}


// 2. Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n) {
	double mnoznik;
	double wyznacznik=1;
	
	for (int i=0; i<n-1; i++)
	{
		if (A[i][i]==0)
		{
			return NAN;
		}
		for (int j=i+1; j<n; j++)
		{
			mnoznik=A[j][i]/A[i][i];
			for (int k=i; k<n; k++)
			{
				A[j][k]-=mnoznik*A[i][k];
			}
		}
	}
	if (A[n-1][n-1]==0)
	{
		return NAN;
	}
	for (int i=0; i<n; i++)
	{
		wyznacznik=wyznacznik*A[i][i];
	}
	
	return wyznacznik;
}

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n) {
	double temp[n];
	
	for (int i=n-1; i>0; i--)
	{
		x[indices[i]]=x[indices[i]]/A[indices[i]][i];
		for (int j=i-1; j>=0; j--)
		{
			x[indices[j]]-=A[indices[j]][i]*x[indices[i]];
		}
	}
	x[indices[0]]=x[indices[0]]/A[indices[0]][0];
	
	for (int i=0; i<n; i++)
	{
		temp[i]=x[indices[i]];
	}
	for (int i=0; i<n; i++)
	{
		x[i]=temp[i];
	}
}

// 3. Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n, const double eps) {
	double mnoznik;
	double wyznacznik=1;
	double maks;
	int maks_index;
	double temp;
	int liczba_zmian=0;
	int flaga;
	int ind[n];
	
	for (int i=0; i<n; i++)
	{
		x[i]=b[i];
	}
	
	for (int i=0; i<n; i++)
	{
		ind[i]=i;
	}
	
	for (int i=0; i<n-1; i++)
	{
		maks=A[ind[i]][i];
		maks_index=i;
		flaga=0;
		for (int j=i+1; j<n; j++)
		{
			if (fabs(A[ind[j]][i])>fabs(maks))
			{
				maks=A[ind[j]][i];
				maks_index=j;
				flaga=1;
			}
		}
		if (flaga==1)
		{
			liczba_zmian+=1;
		}
		temp=ind[maks_index];
		ind[maks_index]=ind[i];
		ind[i]=temp;
		
		if (fabs(A[ind[i]][i])<eps)
		{
			return 0;
		}

		for (int j=i+1; j<n; j++)
		{
			mnoznik=A[ind[j]][i]/A[ind[i]][i];
			for (int k=i; k<n; k++)
			{
				A[ind[j]][k]-=mnoznik*A[ind[i]][k];
			}
			x[ind[j]]-=mnoznik*x[ind[i]];
		}	
	}
	
	if (fabs(A[ind[n-1]][n-1])<eps)
	{
		return 0;
	}
	for (int i=0; i<n; i++)
	{
		wyznacznik=wyznacznik*A[ind[i]][i];
	}
	if (liczba_zmian%2==1)
	{
		wyznacznik=-wyznacznik;
	}
	backward_substitution_index(A,ind,x,n);
	return wyznacznik;
}

// 4. Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps) {
	double mnoznik;
	double wyznacznik=1;
	double maks;
	int maks_index;
	double temp;
	int liczba_zmian=0;
	int flaga;
	int ind[n];
	double temp_arr[n];
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			B[i][j]=0;
		}
	}
	for (int i=0; i<n; i++)
	{
		B[i][i]=1;
	}
	
	for (int i=0; i<n; i++)
	{
		ind[i]=i;
	}
	
	for (int i=0; i<n-1; i++)
	{
		maks=A[ind[i]][i];
		maks_index=i;
		flaga=0;
		for (int j=i+1; j<n; j++)
		{
			if (fabs(A[ind[j]][i])>fabs(maks))
			{
				maks=A[ind[j]][i];
				maks_index=j;
				flaga=1;
			}
		}
		if (flaga==1)
		{
			liczba_zmian+=1;
		}
		temp=ind[maks_index];
		ind[maks_index]=ind[i];
		ind[i]=temp;
		
		if (fabs(A[ind[i]][i])<eps)
		{
			return 0;
		}

		for (int j=i+1; j<n; j++)
		{
			mnoznik=A[ind[j]][i]/A[ind[i]][i];
			for (int k=i; k<n; k++)
			{
				A[ind[j]][k]-=mnoznik*A[ind[i]][k];
			}
			for (int k=0; k<n; k++)
			{
				B[ind[j]][k]-=mnoznik*B[ind[i]][k];
			}
		}	
	}
	
	if (fabs(A[ind[n-1]][n-1])<eps)
	{
		return 0;
	}
	for (int i=0; i<n; i++)
	{
		wyznacznik=wyznacznik*A[ind[i]][i];
	}
	if (liczba_zmian%2==1)
	{
		wyznacznik=-wyznacznik;
	}
	
	for (int i=n-1; i>=1; i--)
	{	
		for (int j=i-1; j>=0; j--)
		{
			mnoznik=A[ind[j]][i]/A[ind[i]][i];
			A[ind[j]][i]=0;
			for (int k=0; k<n; k++)
			{
				B[ind[j]][k]-=mnoznik*B[ind[i]][k];
			}
		}	
	}
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			B[ind[i]][j]=B[ind[i]][j]/A[ind[i]][i];
		}
	}
	for (int k=0; k<n; k++)
	{
		for (int i=0; i<n; i++)
		{
			temp_arr[i]=B[ind[i]][k];
		}
		for (int i=0; i<n; i++)
		{
			B[i][k]=temp_arr[i];
		}
	}
	
	return wyznacznik;
}	


int main(void) {

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf ("%d", &to_do);

	switch (to_do) {
		case 1:
			scanf("%d %d %d", &m, &p, &n);
			read_mat(A, m, p);
			read_mat(B, p, n);
			mat_product(A, B, C, m, p, n);
			print_mat(C, m, n);
			break;
		case 2:
			scanf("%d", &n);
			read_mat(A, n, n);
			printf("%.4f\n", gauss_simplified(A, n));
			break;
		case 3:
			scanf("%d", &n);
			read_mat(A,n, n);
			read_vector(b, n);
			det = gauss(A, b, x, n, eps);
			printf("%.4f\n", det);
			if (det) print_vector(x, n);
			break;
		case 4:
			scanf("%d", &n);
			read_mat(A, n, n);
			det = matrix_inv(A, B, n, eps);
			printf("%.4f\n", det);
			if (det) print_mat(B, n, n);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

