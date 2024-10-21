#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

int get(int cols, int row, int col, const int *A) {
	int value;
    value=A[(row*cols)+col];
    return value;
}

void set(int cols, int row, int col, int *A, int value) {
	A[row*cols+col]=value;
}

void prod_mat(int rowsA, int colsA, int colsB, int *A, int *B, int *AB) {
	int sum;
    for(int i=0; i<rowsA; i++) 
	{
        for(int j=0; j<colsB; j++) 
		{
            sum=0;
            for(int k=0; k<colsA; k++)
			{
                sum+=get(colsA,i,k,A)*get(colsB,k,j,B);
            }
            set(colsB,i,j,AB,sum);
        }
    }
}

void read_mat(int rows, int cols, int *t) {
	int r;
	for(int i=0;i<rows*cols;i++)
	{
        scanf("%d",&r);
        t[i]=r;
    }
}

void print_mat(int rows, int cols, int *t) {
	for(int i=0;i<rows;i++) 
	{
		for (int j=0; j<cols; j++)
		{
        	printf("%d ",t[i*cols+j]);
    	}
    	printf("\n");
    }
}

int read_char_lines(char *array[]) {
    int proceeded;
    int length_word=0;
    int number_of_lines=0;
    char str[BUF_SIZE];
    proceeded=getchar();
    while (proceeded!=EOF) 
	{
        if (proceeded!='\n') 
		{
        	str[length_word]=proceeded;
        	length_word+=1;
        }
        if(proceeded=='\n')
		{
            str[length_word]='\0';
            char *p1=malloc(length_word*sizeof(char));
            array[number_of_lines]=p1;
            for(int i=0; i<=length_word; i++)
			{
                *p1=str[i];
                str[i]=' ';
                p1+=1;
            }
            length_word=0;
            number_of_lines+=1;
        }
        proceeded=getchar();
    }
    return number_of_lines;
}

void write_char_line(char *array[], int n) {
    char *p=array[n];
    while(*p!='\0')
	{
        printf("%c",*p);
        p+=1;
    }
}

void delete_lines(char *array[]) {
}

int read_int_lines_cont(int *ptr_array[]) {
    int proceeded;
    int length_number=0;
    int number_of_numbers=0;
	int number_of_lines=0;
    int end_of_line=1;
    char *out;
    char str[20];
    proceeded=getchar();
    while (proceeded!=EOF) 
	{
        if (proceeded!=' ' && proceeded!='\n') 
		{
            str[length_number]=proceeded;
            length_number+=1;
        }
        if (proceeded==' ')
		{
            ptr_array[0][number_of_numbers]= strtol(str,&out,10);
        	for(int i=0; i<length_number; i++)
			{
                str[i]=' ';
            }
            if(end_of_line==0) 
			{
                ptr_array[number_of_lines+1]=&ptr_array[0][number_of_numbers];
                number_of_lines+=1;
                end_of_line=0;
            }
            length_number=0;
            number_of_numbers+=1;
        }
        if (proceeded=='\n')
		{
            ptr_array[0][number_of_numbers]= strtol(str,&out,10);
            for(int i=0; i<length_number; i++)
			{
                str[i]=' ';
            }
            length_number=0;
            number_of_numbers+=1;
            end_of_line=1;
        }
        proceeded=getchar();
    }
    ptr_array[number_of_lines+1]=&ptr_array[0][number_of_numbers];
    return number_of_lines;
}

void write_int_line_cont(int *ptr_array[], int n) {
    while ((ptr_array[n+1]!=ptr_array[n+2]))
	{
        printf("%d ",*(ptr_array[n+1]));
        ptr_array[n+1]+=1;
    }
}

typedef struct {
	int *values;
	int len;
	double average;
} line_type;

int read_int_lines(line_type lines_array[]) {
    int proceeded;
    int length_number=0;
    int number_of_numbers=0;
	int number_of_lines=0;
    char *out;
    char str[20];
    line_type line;
    double sum;
    int buf[BUF_SIZE];
    proceeded=getchar();
    while (proceeded!=EOF) 
	{
        if (proceeded!=' ' && proceeded!='\n') 
		{
            str[length_number]=proceeded;
            length_number+=1;
        }
        if (proceeded==' ')
		{
            buf[number_of_numbers]= strtol(str,&out,10);
        	for(int i=0;i<length_number;i++)
			{
                str[i]=' ';
            }
            length_number=0;
            number_of_numbers+=1;
        }
        if (proceeded=='\n')
		{
			for(int i=0;i<length_number;i++)
			{
                str[i]=' ';
            }
			buf[number_of_numbers] = strtol(str, &out, 10);
            int *p1=malloc(number_of_numbers*sizeof(int));
            line.values=p1;
            line.len=number_of_numbers;
            sum=0;
            for(int i=0;i<=number_of_numbers;i++){
                *p1=buf[i];
                sum+=buf[i];
                p1+=1;
            }
            sum=sum/(number_of_numbers+1);

            line.average=sum;
            lines_array[number_of_lines]=line;
            length_number=0;
            number_of_numbers=0;
            number_of_lines+=1;
		}
		proceeded=getchar();
	}
	return number_of_lines;
}

void write_int_line(line_type lines_array[], int n) {
    int *p1=lines_array[n].values;
    int len=lines_array[n].len;
    for (int i=0; i<len; i++)
	{
        printf("%d ",*p1);
        p1+=1;
    }
    printf("\n%.2f",lines_array[n].average);
}

void delete_int_lines(line_type array[], int line_count) {
}

int cmp (const void *a, const void *b) {
    line_type *a1=(line_type*)a;
    line_type *b1=(line_type*)b;
    if(a1->average>b1->average)
	{
        return 1;
    }
    if(a1->average<b1->average)
	{
        return -1;
    }
    return 0;
}

void sort_by_average(line_type lines_array[], int line_count) {
	qsort(lines_array,line_count,sizeof(line_type),cmp);
}

typedef struct {
	int r, c, v;
} triplet;

int read_sparse(triplet *triplet_array, int n_triplets) {
    int proceeded;
    int length_number=0;
    int number_of_numbers=0;
    int number_of_lines=0;
    char *out;
    int buf[BUF_SIZE];
    char str[20];
    int first=0;
    triplet trio;
    proceeded=getchar();
    while (proceeded!=EOF) 
	{
        if (first==1) 
		{
            if (proceeded!='\n' && proceeded!=' ') 
			{
                str[length_number]=proceeded;
                length_number+=1;
            }
            if (proceeded==' ') 
			{
                buf[number_of_numbers]=strtol(str, &out, 10);
                for (int n=0; n<length_number; n++) 
				{
                    str[n]=' ';
                }
                number_of_numbers+=1;
                length_number=0;
            }
            if (proceeded=='\n') 
			{
                buf[number_of_numbers]=strtol(str, &out, 10);
                for (int n=0; n<length_number; n++) 
				{
                    str[n]=' ';
                }
                trio.r=buf[0];
                trio.c=buf[1];
                trio.v=buf[2];
                triplet_array[number_of_lines]=trio;
                length_number=0;
                number_of_numbers=0;
                number_of_lines+=1;
                if (number_of_lines>=n_triplets)
				{
                    break;
                }
            }
        }
        if (proceeded=='\n') 
		{
            first=1;
        }
        proceeded=getchar();
	}
}

int cmp_triplets(const void *t1, const void *t2) {
    triplet* tri1=(triplet *)t1;
    triplet* tri2=(triplet *)t2;
    if(tri1->r>tri2->r)
	{
        return 1;
    }
    if(tri1->r<tri2->r)
	{
        return -1;
    }
    if(tri1->c>tri2->c)
	{
        return 1;
    }
	if(tri1->c<tri2->c)
	{
        return -1;
    }
    return 0;
}

void make_CSR(triplet *triplet_array, int n_triplets, int rows, int *V, int *C, int *R) {
    qsort(triplet_array,n_triplets,sizeof(triplet),cmp_triplets);
    for(int i=0; i<=rows; i++)
	{
        V[i]=triplet_array[i].v;
        C[i]=triplet_array[i].c;
    }
    int sum;
    for(int i=0; i<=rows; i++)
	{
        sum=0;
        for(int j=0; j<n_triplets; j++)
		{
            if(triplet_array[j].r<i)
			{
                sum+=1;
            }
        }
        R[i]=sum;
    }
}

void multiply_by_vector(int rows, const int *V, const int *C, const int *R, const int *x, int *y) {
    for(int i=0; i<rows; i++)
	{
        y[i]=0;
        int start=R[i];
        int end=R[i+1];
        for(int j=start; j<end; j++)
		{
            y[i]+=V[j]*x[C[j]];
        }
    }
}

void read_vector(int *v, int n) {
    int proceeded;
    int length_number=0;
    int number_of_numbers=0;
    char *out;
    int buf[BUF_SIZE];
    char str[20];
    proceeded=getchar();
    while (proceeded!=EOF) 
	{
        if (proceeded!='\n' && proceeded!=' ') 
		{
            str[length_number]=proceeded;
            length_number+=1;
        }

        if (proceeded==' ') 
		{
            buf[number_of_numbers]=strtol(str, &out, 10);
            for (int i=0; i<length_number; i++) 
			{
                str[i]=' ';
            }
            length_number=0;
            number_of_numbers+=1;
        }

        if (proceeded=='\n') 
		{
            buf[number_of_numbers]=strtol(str, &out, 10);
            for(int i=0; i<n; i++)
			{
                v[i]=buf[i];
            }
        }
		proceeded=getchar();
    }
}

void write_vector(int *v, int n) {
    for (int i=0; i<n; i++)
	{
        printf("%d ",v[i]);
    }
    printf("\n");
}

int read_int() {
	char c_buf[BUF_SIZE];
	fgets(c_buf, BUF_SIZE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
	int to_do = read_int();

	int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
	int n, lines_counter, rowsA, colsA, rowsB, colsB;
	int rows, cols, n_triplets;
	char *char_lines_array[TAB_SIZE] = { NULL };
	int continuous_array[TAB_SIZE];
	int *ptr_array[TAB_SIZE];
	triplet triplet_array[TAB_SIZE];
	int V[TAB_SIZE], C[TAB_SIZE], R[TAB_SIZE];
	int x[TAB_SIZE], y[TAB_SIZE];
	line_type int_lines_array[TAB_SIZE];

	switch (to_do) {
		case 1:
			scanf("%d %d", &rowsA, &colsA);
			read_mat(rowsA, colsA, A);
			scanf("%d %d", &rowsB, &colsB);
			read_mat(rowsB, colsB, B);
			prod_mat(rowsA, colsA, colsB, A, B, AB);
			print_mat(rowsA, colsB, AB);
			break;
		case 2:
			n = read_int() - 1; // we count from 1 :)
			ptr_array[0] = continuous_array;
			read_int_lines_cont(ptr_array);
			write_int_line_cont(ptr_array, n);
			break;
		case 3:
			n = read_int() - 1;
			read_char_lines(char_lines_array);
			write_char_line(char_lines_array, n);
			delete_lines(char_lines_array);
			break;
		case 4:
			n = read_int() - 1;
			lines_counter = read_int_lines(int_lines_array);
			sort_by_average(int_lines_array, lines_counter);
			write_int_line(int_lines_array, n);
			delete_int_lines(int_lines_array, lines_counter);
			break;
		case 5:
			scanf("%d %d %d", &rows, &cols, &n_triplets);
			n_triplets = read_sparse(triplet_array, n_triplets);
			read_vector(x, cols);
			make_CSR(triplet_array, n_triplets, rows, V, C, R);
			multiply_by_vector(rows, V, C, R, x, y);
			write_vector(V, n_triplets);
			write_vector(C, n_triplets);
			write_vector(R, rows + 1);
			write_vector(y, rows);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

