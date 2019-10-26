#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int searcher(char letter, const char* str);
int dupliChecker(const char* str);
int translator(const char* source, const char* dest, size_t length, char b);
void dispErr(FILE* p);
//searcher goes through the string until it finds a null byte, returning
//1 if it finds a letter that matches.
int searcher(char letter, const char* str)
{
  while(*str!=0)
    {
      if (*str==letter)
	return 1;
      str++;
    }
  return 0;
}

//This restChecker checks whether the first letter of the string matches
//the rest of the letters in the string, and then the second, etc until
//the whole string has been checked.

int dupliChecker(const char* str)
{
  while(*str!=0)
    {
      char a = *str;
      if(searcher(a,(str+1)))
	return 1;
      str++;
    }
  return 0;
}

//This function finds the index at which a certain letter appears in the 
//source file,and then returns the character in the destination file at
//that same index

int translator(const char* source, const char* dest, size_t length, char b)
{
  size_t c;
  for (c=0;c<length;c++)
    {
      if (source[c]==b)
	return dest[c];
    }
  return b;
}

inline
void dispErr(FILE *p)
{
  if (ferror(p))
    {
      fprintf(stderr, "%s Error: %d\n", "IO", errno);
      exit(1);
    }
}


int main(int argc, const char* argv[])
{
  const char* source, *dest;
  size_t length;
  char b;
  if (argc!=3)
    {
      fprintf(stderr, "Invalid number of arguments %d.\n", argc);
      exit(1);
    }
  source=argv[1];
  dest=argv[2];
  length=strlen(source);

  if (!length)
    {
      fprintf(stderr, "One operand wasn't entered\n");
      exit(1);
    }

  if (dupliChecker(source))
    {
      fprintf(stderr, "There are duplicate bytes\n");
      exit(1);
    }
  if (length !=strlen(source))
    {
      fprintf(stderr, "Arguments aren't same length\n");
      exit(1);
    }

  while(1)
    {
      b=getchar();
      dispErr(stdin);
      if (feof(stdin))
	break;
      putchar(translator(source, dest, length, b));
      dispErr(stdout);
    }
  return 0;
}
