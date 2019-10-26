#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define initial_size 19

char zor(const char c);
int frobcmp(char const* c1, char const*c2);
int compareWrapper(const void* c1, const void* c2);
void IOChecker(FILE* f);
void memErrChecker(void* ptr);
void stWrite(const char* s);
void errDisplay(const char* m);
void lBuf(char** lbufvar, char* buf, size_t size);

int main(void)
{
  int (* cmp) (const void*, const void*);
  size_t lSize, bSize, c, fSize, noLine;
  int isEOF, isSpace;
  char* input, * input2, ** linebuf, curChar;

  bSize = 0; 
  lSize = 0; 
  noLine = 0; 
  isEOF = feof(stdin);
  fSize=initial_size;

  cmp=&compareWrapper;
  int x = sizeof(char)*fSize;
  input=(char*) malloc(x);
  memErrChecker(input);
  while(!isEOF)
    {
      curChar = getchar();
      IOChecker(stdin);
      isEOF=feof(stdin);
      isSpace = (curChar == ' ');
      if (!lSize && isSpace)
	continue;//disregard all the spaces

      if(bSize == fSize)
	{
	  fSize=fSize*2;
	  input2=(char*) realloc(input, sizeof(char)*fSize);
	  //using the variable x that I created here didn't work?
	  memErrChecker(input2);
	  input=input2;
	}

      if (!isEOF)
	{
	  input[bSize++]=curChar;
	  lSize=lSize+1;

	  if(!isSpace)
	    continue;
	}
      else
	{
	  if (!bSize)
	    {
	      free(input);
	      return 0;//free the memory allocated for the file
	    }
	  if (input[bSize-1] != ' ')
	    input[bSize++] = ' ';
	  if (!lSize)
	    break;
	}
      lSize=0;
      noLine=noLine+1;
    }

  linebuf=(char**)malloc(sizeof(char*) * noLine);
  memErrChecker(linebuf);

  lBuf(linebuf, input, bSize);
  qsort(linebuf, noLine, sizeof(char*), cmp);

  for (c=0;c<noLine;c++)
    stWrite(linebuf[c]);

  free(linebuf);
  free(input);

  return 0;
}

//This function is simply to xor a value with 0x2A (which is 00101010)
//That value was specified from the memfrob link in the spec
inline
char zor(const char c)
{
  return c^0x2A;
}

//This function was written to compare the wrappers of two constants that 
//are cast to double char pointers, so that they may be passed to frobcmp
inline
int compareWrapper(const void* c1, const void* c2)
{
  return frobcmp(*((const char**) c1), *((const char**) c2));
}



//Checks if there is an input output error in the file passed through
//a pointer to the function
inline
void IOChecker(FILE* f)
{
  if (ferror(f))
    errDisplay("IOError");
}


//Checks if the pointer passed to the function is null or not
inline
void memErrChecker(void* ptr)
{
  if (ptr==NULL)
    errDisplay("Memory Allocation Error");
}

//Reports an arrer and prints it, then exits the program with a failed status
inline
void errDisplay(const char* m)
{
  fprintf(stderr, "%s The Error is: %d\n", m, errno);
  exit(1);
}

//This function is used to compare two frobnicated characters, returns 1
//if c1>c2 and -1 if not

int frobcmp(char const* c1, char const* c2)
{
  while(*c1==*c2)
    {
      if (*c1== ' ')
	return 0;
      c1++;
      c2++;
    }
  return ((zor(*c1) < (zor(*c2)) ? -1 : 1));
}


//This function checks if there is an IOError in any of the characters in the
//string

void stWrite(const char* s)
{
  for(;;)
    {
      putchar(*s);
      IOChecker(stdout);
      if (*s++ == ' ')
	return;
    }
}

void lBuf(char** lbufvar, char* buf, size_t size)
{
  size_t c, lNum;
  char* line=buf;
  for (c=0,lNum=0;c<size;c++)
    {
      if (buf[c] == ' ')
	{
	  lbufvar[lNum++] = line;
	  line=buf+1+c;
	}
    }
}
