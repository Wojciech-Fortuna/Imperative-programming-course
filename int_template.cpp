#include <stdio.h>
#include <math.h>

#define RECURS_LEVEL_MAX  10
#define N_MAX             10

// pointer to function of one variable
typedef double (*Func1vFp) (double);

// example functions of one variable
double f_poly(double x) // polynomial a[0] + a[1]x + ... + a[n]x^n
{ 
	double result;
	result=2*pow(x,5)-4*pow(x,4)+3.5*pow(x,2)+1.35*x-6.25;
	return result;
}

double f_rat(double x) 
{
	double result;
	result=1/(pow((x-0.5),2)+0.01);
	return result;
}

double f_exp(double x) {
	double result;
	result=2*x*exp(-1.5*x)-1;
	return result;
}

double f_trig(double x) {
	double result;
	result=x*tan(x);
	return result;
}

// Quadratures

// rectangle rule, leftpoint
double quad_rect_left(Func1vFp f1, double a, double b, int n) 
{
	double x;
	double width=(b-a)/n;
	double result=0;
	for (int i=0; i<n; i++)
	{
		x=a+width*i;
		result+=f1(x);
	}
	result*=width;
	return result;
}

// rectangle rule, rightpoint
double quad_rect_right(Func1vFp f1, double a, double b, int n) 
{
	double x;
	double width=(b-a)/n;
	double result=0;
	for (int i=1; i<=n; i++)
	{
		x=a+width*i;
		result+=f1(x);
	}
	result*=width;
	return result;
}

// rectangle rule, midpoint
double quad_rect_mid(Func1vFp f1, double a, double b, int n) 
{
	double x;
	double h=(b-a)/n;
	double sum=0;
	for (int i=0; i<n; i++)
	{
		x=a+h/2+h*i;
		sum+=f1(x);
	}
	return h * sum;
}

// trapezoidal rule
double quad_trap(Func1vFp func, double a, double b, int n) 
{
	double x;
	double width=(b-a)/n;
	double result=0;
	result+=func(a);
	for (int i=1; i<n; i++)
	{
		x=a+width*i;
		result+=func(x)*2;
	}
	result+=func(b);
	result=result*width/2;
	return result;
}

// Simpson's rule
double quad_simpson(Func1vFp f, double a, double b, int n) 
{
	double x;
	double width=(b-a)/n;
	double result=0;
	result+=f(a);
	for (int i=1; i<n; i++)
	{
		x=a+width*i;
		result+=f(x)*2;
	}
	result+=f(b);
	for (int i=0; i<n; i++)
	{
		x=a+width/2+width*i;
		result+=f(x)*4;
		
	}
	result=result*width/6;
	return result;	
}

// pointer to quadrature function
typedef double (*QuadratureFp) (Func1vFp f, double a, double b, int n);

// array of pointers to integrand functions
Func1vFp func_tab[] = { f_poly, f_rat, f_trig, f_exp };

// array of pointers to quadrature functions
QuadratureFp quad_tab[] = {
	quad_rect_left, quad_rect_right, quad_rect_mid, quad_trap, quad_simpson };

// calls 'quad_no' quadrature function for 'fun_no' integrand function
// on interval [a, b] and n subintervals
double quad_select(int fun_no, int quad_no, double a, double b, int n) 
{
	double result;
    result = quad_tab[quad_no]( func_tab[fun_no], a, b, n);
    return result;
}

// adaptive algorithm
double recurs(Func1vFp f, double a, double b, double S, double delta, QuadratureFp quad, int level) 
{
	if (level>RECURS_LEVEL_MAX)
	{
		return NAN;
	}
	else
	{
		double S1;
		double S2;
		
		S1=quad(f, a, (a+b)/2, 1);
		S2=quad(f, (a+b)/2, b, 1);
		if (fabs(S-S1-S2)<delta)
		{
			return S1+S2;
		}
		else
		{
			S1=recurs(f, a, (a+b)/2, S1, delta/2, quad, level+1);
			S2=recurs(f, (a+b)/2, b, S2, delta/2, quad, level+1);
			return S1+S2;
		}
	}
}

// initialization for adaptive algorithm
double init_recurs(Func1vFp f, double a, double b, double delta, QuadratureFp quad) 
{
    double S;
    double result;
    S=quad(f, a, b, 1);
    result=recurs(f, a, b, S, delta, quad, 1);
    return result;
}

// double integrals

// pointer to function of two variables
typedef double Func2vFp (double, double);

double func2v_2(double x, double y) {
	return 2 - x*x - y*y*y;
}

// sample functions to define the normal domain

double lower_bound2(double x) {
	return 0.7*exp(-2*x*x);
}
double upper_bound2(double x) {
	return sin(10*x);
}

// rectangle rule (leftpoint) - double integral over rectangular domain
double dbl_integr(Func2vFp f, double x1, double x2, int nx, double y1, double y2, int ny) 
{
	double x;
	double y;
	double width_x=(x2-x1)/nx;
	double width_y=(y2-y1)/ny;
	double result=0;
	double temp_result;
	for (int i=0; i<nx; i++)
	{
		x=x1+width_x*i;
		for (int j=0; j<ny; j++)
		{
			y=y1+width_y*j;
			result+=f(x,y);
		}
	}
	result=result*width_x*width_y;
	return result;	
}

// rectangle rule (midpoint) - double integral over normal domain with respect to the x-axis
double dbl_integr_normal_1(Func2vFp f, double x1, double x2, int nx, double hy,
						   Func1vFp fg, Func1vFp fh) 
{
	int ny;
	double x;
	double y;
	double result=0;
	double temp_result;
	double width_y;
	double width_x=(x2-x1)/nx;
	double min_y;
	double max_y;
	for (int i=0; i<nx; i++)
	{
		x=x1+width_x*i+width_x/2;
		min_y=fg(x);
		max_y=fh(x);
		temp_result=0;
		ny=ceil((max_y-min_y)/hy);
		width_y=(max_y-min_y)/ny;
		for (int j=0; j<ny; j++)
		{
			y=min_y+width_y*j+width_y/2;
			temp_result+=f(x,y);
		}
		temp_result*=width_y;
		result+=temp_result;
	}
	result*=width_x;
	return result;
}


// rectangle rule (leftpoint) - double integral over multiple normal
// domains with respect to the x-axis
double dbl_integr_normal_n(Func2vFp f, double x1, double x2, int nx, double y1, double y2,
		int ny, Func1vFp fg, Func1vFp fh)  
{
	double temp_result;
	double result;
	double hy=(y2-y1)/ny;
	double width_x=(x2-x1)/nx;
	double width_y;
	double x;
	double y;
	double max_y;
	double min_y;
	int nny;
	
	for (int i=0; i<nx; i++)
	{
		x=x1+width_x*i;
		if (y2<fh(x))
		{
			max_y=y2;
		}
		else
		{
			max_y=fh(x);
		}
		if (y1>fg(x))
		{
			min_y=y1;
		}
		else
		{
			min_y=fg(x);
		}
		
		if (min_y<max_y)
		{
			temp_result=0;
			nny=ceil((max_y-min_y)/hy);
			width_y=(max_y-min_y)/nny;
			for (int j=0; j<nny; j++)
			{
				y=min_y+width_y*j;
				temp_result+=f(x,y);
			}
			temp_result*=width_y;
			result+=temp_result;
		}
	}
	result*=width_x;
	return result;
}


// multiple quadratures

typedef double (*FuncNvFp)(const double*, int);
typedef int (*BoundNvFp)(const double*, int);

// sample function of three variables
double func3v(const double v[], int n) {
	return v[0] - v[1] + 2*v[2];
}

// sample predicate in 3D
int bound3v(const double v[], int n) { // a cylinder
	return v[0] > 0 && v[0] < 0.5 && v[1]*v[1] + (v[2]-1)*(v[2]-1) < 1;
}

// sample function of n variables
double funcNv(const double v[], int n) {
	double fv = 1.;
	for (int i = 1; i < n; ++i) {
		fv += sin(i*v[i]);
	}
	return fv;
}
// sample n-dimensional predicate (n-dim hypersphere)
int boundNv(const double v[], int n) {
	double r = 0.0;
	for (int i = 0; i < n; ++i) r += (v[i]-1)*(v[i]-1);
	return r <= 1.;
}

// multiple integrals over a cuboid with predicate (if boundary != NULL)
// rectangular rule (rightpoint)
double trpl_quad_rect(FuncNvFp f, double variable_lim[][2], const int tn[], BoundNvFp boundary) 
{
	double width_x=(variable_lim[0][1]-variable_lim[0][0])/tn[0];
	double width_y=(variable_lim[1][1]-variable_lim[1][0])/tn[1];
	double width_z=(variable_lim[2][1]-variable_lim[2][0])/tn[2];
	double x;
	double y;
	double z;
	double result=0;
	double array[3];
    
    x=variable_lim[0][0]+width_x;
    for (int i=0; i<tn[0]; i++)
	{
        y=variable_lim[1][0]+width_y;
        for (int j=0; j<tn[1]; j++)
		{
            z=variable_lim[2][0]+width_z;
            for (int k=0; k<tn[2]; k++){
                array[0]=x;
                array[1]=y;
                array[2]=z;

                if (boundary==NULL || boundary(array,3))
				{
                    result+=f(array, 3);
                }
                z+=width_z;
            }
            y+=width_y;
        }
        x+=width_x;
    }
	result=result*width_x*width_y*width_z;
	return result;
}

// multiple integrals over a n-dim hypercuboid with predicate (if boundary != NULL)
// rectangular rule (midpoint)
void recur_quad_rect_mid(double *p_sum, FuncNvFp f, int variable_no, double t_variable[],
         double variable_lim[][2], const int tn[], int level, BoundNvFp boundary) 
{
	if (level==variable_no)
	{
		if (boundary==NULL || boundary(t_variable,variable_no))
		{
			*p_sum+=f(t_variable,variable_no);
		}
	}
	
	else 
	{
		double width=(variable_lim[level][1]-variable_lim[level][0])/tn[level];
		for (int i=0; i<tn[level]; i++)
		{
			t_variable[level]=variable_lim[level][0]+width/2+width*i;
			recur_quad_rect_mid(p_sum,f,variable_no,t_variable,variable_lim,tn,level+1,boundary);
		}
	}

	if (level==0)
	{
		for (int i=0; i<variable_no; i++)
		{
			double width=(variable_lim[level][1]-variable_lim[level][0])/tn[level];
			*p_sum*=width;
		}
	}
}

int main(void) {
	int to_do, n, nx, ny, integrand_fun_no, method_no, flag;
	int no_funcs = sizeof(func_tab) / sizeof(Func1vFp);
	int no_quads = sizeof(quad_tab) / sizeof(QuadratureFp);
	double a, b, x1, x2, y1, y2, hy, sum, delta;
	double t_variable[N_MAX], variable_lim[N_MAX][2];
	int tn[N_MAX];

	scanf("%d", &to_do);
	switch (to_do) {
		case 1: // loop over quadratures and integrands
			scanf("%lf %lf %d", &a, &b, &n);
			for(int q = 0; q < no_quads; ++q) {
				for(int f = 0; f < no_funcs; ++f) {
					printf("%.5f ",quad_select(f, q, a, b, n));
				}
				printf("\n");
			}
			break;
		case 2: // adaptive algorithm
			scanf("%d %d",&integrand_fun_no,&method_no);
			scanf("%lf %lf %lf", &a, &b, &delta);
			printf("%.5f\n", init_recurs(func_tab[integrand_fun_no],a,b,delta,quad_tab[method_no]));
			break;
		case 3: // double integral over a rectangle
			scanf("%lf %lf %d", &x1, &x2, &nx);
			scanf("%lf %lf %d", &y1, &y2, &ny);
			printf("%.5f\n", dbl_integr(func2v_2, x1, x2, nx, y1, y2, ny));
			break;
		case 4: // double integral over normal domain
			scanf("%lf %lf %d", &x1, &x2, &nx);
			scanf("%lf", &hy);
			printf("%.5f\n", dbl_integr_normal_1(func2v_2, x1, x2, nx, hy, lower_bound2, upper_bound2));
			break;
		case 5: // double integral over multiple normal domains
			scanf("%lf %lf %d", &x1, &x2, &nx);
			scanf("%lf %lf %d", &y1, &y2, &ny);
			printf("%.5f\n",dbl_integr_normal_n(func2v_2, x1, x2, nx, y1, y2, ny, lower_bound2, upper_bound2));
			break;
		case 6: // triple integral over a cuboid
			scanf("%lf %lf %d", &variable_lim[0][0], &variable_lim[0][1], tn);
			scanf("%lf %lf %d", &variable_lim[1][0], &variable_lim[1][1], tn+1);
			scanf("%lf %lf %d", &variable_lim[2][0], &variable_lim[2][1], tn+2);
			scanf("%d", &flag);
			printf("%.5f\n", trpl_quad_rect(func3v, variable_lim, tn, flag ? bound3v : NULL));
			break;
		case 7: // multiple integral over hyper-cuboid
			scanf("%d", &n);
			if(n > N_MAX) break;
			for(int i = 0; i < n; ++i) {
				scanf("%lf %lf %d", &variable_lim[i][0], &variable_lim[i][1], tn+i);
			}
			scanf("%d", &flag);
			sum = 0.;
			recur_quad_rect_mid(&sum, funcNv, n, t_variable, variable_lim, tn, 0, flag ? boundNv : NULL);
			printf("%.5f\n", sum);
			break;
		default:
			printf("Nothing to do for %d\n", to_do);
			break;
	}
	return 0;
}

