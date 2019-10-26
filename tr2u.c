#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int searcher(char letter, const char* str);
int dupliChecker(const char* str);
int translator(const char* source, const char* dest, size_t length, char b);

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


int main(int argc, const char* argv[])
{
  const char* source, *dest;
  size_t length;
  ssize_t ret_val;
  char b[2];
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
      ret_val= read(STDIN_FILENO, b, 1);
      if (!ret_val)
	break;
      else if (ret_val<0)
	{
	  fprintf(stderr, "Read error\n");
	  exit(1);
	}
      b[0] = translator(source, dest, length, b[0]);
      ret_val = write(STDOUT_FILENO, b, 1);
      if (ret_val < 0)
	{
	  fprintf (stderr, "Write error\n");
	  exit(1);
	}
    }
  return 0;
}
