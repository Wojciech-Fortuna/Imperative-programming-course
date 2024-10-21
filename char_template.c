#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// consider chars from [FIRST_CHAR, LAST_CHAR)
#define FIRST_CHAR 33
#define LAST_CHAR 127
#define MAX_CHARS (LAST_CHAR - FIRST_CHAR)
#define MAX_BIGRAMS ((LAST_CHAR - FIRST_CHAR) * (LAST_CHAR - FIRST_CHAR))

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define MAX_LINE 128

int count[MAX_BIGRAMS] = { 0 };

// sort indices according to their respective counts.
// sort alphabetically if counts equal
int cmp (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	if (count[va] == count[vb]) return va - vb;	return count[vb] - count[va];
}

// sort indices according to their respective counts.
// sort alphabetically if counts equal
int cmp_di (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	// sort according to second char if counts and the first char equal
	if (count[va] == count[vb] && va / MAX_CHARS == vb / MAX_CHARS) return va % MAX_CHARS - vb % MAX_CHARS;
	// sort according to first char if counts equal
	if (count[va] == count[vb]) return va / MAX_CHARS - vb / MAX_CHARS;
	return count[vb] - count[va];
}

// count lines, words & chars in a given text file
void wc(int *nl, int *nw, int *nc) {
	char line[MAX_LINE];
	*nl=0;
	*nw=0;
	*nc=0;
	while (fgets(line, MAX_LINE, stdin) && line!=EOF)
	{
		*nl+=1;
		*nc+=strlen(line);
		int i=0;
		if (!isspace(line[0]))
		{
			*nw+=1;
		}
		for (int i=1; i<strlen(line); i++)
		{
			if (isspace(line[i-1]) && ! isspace(line[i]))
			{
				*nw+=1;
			}
		}
				

	}
}

void char_count(int char_no, int *n_char, int *cnt) {
	char line[MAX_LINE];
	int krotnosc[MAX_CHARS];
	int sortowane[MAX_CHARS];
	int temp;
	for (int i=0; i<MAX_CHARS; i++)
	{
		krotnosc[i]=0;
		sortowane[i]=i;
	}
	while (fgets(line, MAX_LINE, stdin) && line!=EOF)
	{
		for (int i=0; i<strlen(line); i++)
		{
			krotnosc[line[i]-FIRST_CHAR]+=1;
		}
	}
	for (int i=0; i<MAX_CHARS-1; i++)
	{
		for (int j=i+1; j<MAX_CHARS; j++)
		{
			if (krotnosc[sortowane[i]]<krotnosc[sortowane[j]])
			{
				temp=sortowane[i];
				sortowane[i]=sortowane[j];
				sortowane[j]=temp;
			}
		}
	}
	*n_char=sortowane[char_no-1]+FIRST_CHAR;
	*cnt=krotnosc[sortowane[char_no-1]];
}

void bigram_count(int bigram_no, int bigram[]) {
	char line[MAX_LINE];
	int krotnosc[MAX_CHARS*MAX_CHARS];
	int sortowane[MAX_CHARS*MAX_CHARS];
	int temp;
	for (int i=0; i<MAX_CHARS*MAX_CHARS; i++)
	{
		krotnosc[i]=0;
		sortowane[i]=i;
	}
	while (fgets(line, MAX_LINE, stdin) && line!=EOF)
	{
		for (int i=1; i<strlen(line); i++)
		{
			if ( !isspace(line[i]) && !isspace(line[i-1]) )
			{
				krotnosc[(line[i-1]-FIRST_CHAR)*MAX_CHARS+line[i]-FIRST_CHAR]+=1;				
			}
		}
	}
	for (int i=0; i<MAX_CHARS*MAX_CHARS-1; i++)
	{
		for (int j=i+1; j<MAX_CHARS*MAX_CHARS; j++)
		{
			if (krotnosc[sortowane[i]]<krotnosc[sortowane[j]])
			{
				temp=sortowane[i];
				sortowane[i]=sortowane[j];
				sortowane[j]=temp;
			}
		}
	}
	bigram[0]=(sortowane[bigram_no-1])/MAX_CHARS+FIRST_CHAR;
	bigram[1]=sortowane[bigram_no-1]%MAX_CHARS+FIRST_CHAR;
	bigram[2]=krotnosc[sortowane[bigram_no-1]];
	return bigram;
}

void find_comments(int *line_comment_counter, int *block_comment_counter) {
	int i;
	int licznik=0;
	int stop=0;
	*line_comment_counter=0;
	*block_comment_counter=0;
	char line[MAX_LINE];
	while (fgets(line, MAX_LINE, stdin) && line!=EOF)
	{
		if (stop==1)
		{
			stop=0;
		}
		i=1;
		while (i<strlen(line) && stop!=1)
		{
			if (line[i-1]==47 && line[i]==47 && stop==0)
			{
				*line_comment_counter+=1;
				stop=1;
			}
			if (line[i-1]==47 && line[i]==42 && stop==0)
			{
				*block_comment_counter+=1;
				if (i+1<MAX_LINE && line[i+1]==47)
				{
					stop=3;
				}
				else
				{
					stop=2;
				}
			}
			if (line[i-1]==42 && line[i]==47 && stop==2)
			{
				stop=0;
			}
			if (stop==3 && line[i]==47)
			{
				stop=2;
			}
			i+=1;
		}
	}
}



int read_int() {
	char line[MAX_LINE];
	fgets(line, MAX_LINE, stdin); // to get the whole line
	
	return (int)strtol(line, NULL, 10);
}

int main(void) {
	int to_do;
	int nl, nw, nc, char_no, n_char, cnt;
	int line_comment_counter, block_comment_counter;
	int bigram[3];

	to_do = read_int();
	switch (to_do) {
		case 1: // wc()
			wc (&nl, &nw, &nc);
			printf("%d %d %d\n", nl, nw, nc);
			break;
		case 2: // char_count()
			char_no = read_int();
			char_count(char_no, &n_char, &cnt);
			printf("%c %d\n", n_char, cnt);
			break;
		case 3: // bigram_count()
			char_no = read_int();
			bigram_count(char_no, bigram);
			printf("%c%c %d\n", bigram[0], bigram[1], bigram[2]);
			break;
		case 4:
			find_comments(&line_comment_counter, &block_comment_counter);
			printf("%d %d\n", block_comment_counter, line_comment_counter);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

