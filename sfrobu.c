//NOTE: I apoligize for the awkward spacing in the program, I used 
//notepad++ to correct it, and hence it slightly threw off the alignment

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>
#include <sys/stat.h>


int zor(const char c);
int frobcmp(char const *c1, char const *c2);
int frobcmpUpper(char const *c1, char const *c2);
int compareWrapper(const void* c1, const void* c2);
int compareWrapperUpper(const void* c1, const void* c2);

int main(int argc, char  * const argv[]) {
    
    struct stat file_a;
    if (fstat(0,&file_a) < 0) {  
        fprintf(stderr, "Couldn't get file information");
        exit(1);
    }
    //Here, I looked up how to tell if a file input was a regular file or
    //not. This was the syntax I found. 
    char *f;
    char* word;
    char** line;
    int lineCount;
    int wordCount;
    //Variable declarations and value assignments

    lineCount = 0;
    wordCount = 0;
    word = (char*) malloc(sizeof(char));
    ssize_t fSize = file_a.st_size;
    
    if(S_ISREG(file_a.st_mode)) //The isreg method checks if the file is reg
    {
        char * temp = (char*) malloc(fSize * sizeof(char));
	//Here, I create some memory the size of the file, and then check
	//it its null. If it is, there was an error
        if (temp == NULL) 
        {
            fprintf(stderr, "Error allocating file");
            exit(1);
        }
        else 
        {
            f=temp;
        }
        
        ssize_t store;
        
        for (int c = 0; c < file_a.st_size; c++) 
        {
            store = read(0, f+c, 1);
        }
        //read all the values from file into the store
        if (store > 0) 
        {
            
            for (int c = 0; c < file_a.st_size;) 
            {
                
                if (c == file_a.st_size -1)
                {
                    if (c == 0 && f[0] == ' ') 
                    {
		      exit(0);//If the file is nothing but a ' '
                    }
                    
                    if (f[c] != ' ') 
                    {   
                        char * newFileT = (char *) realloc(f, (file_a.st_size + 1)*sizeof(char));
                        if (newFileT == NULL) 
                        {
                            fprintf(stderr, "Error allocating file");
                            exit(1);
                        }
                        else 
                        {
                            f=newFileT;
                        }//This checking of null and then transferring of
			//values will be seen repetitively 
                        wordCount++;
                        f[file_a.st_size] = ' ';//Make the last char  ' '
                    }
                }
                
                if (f[c] == ' ') 
                {
                    c++;
                    while (f[c] == ' ') 
                    {
                        c++;
                    }
                    wordCount++;//Each time a space is seen, increase wc
                    continue;
                }
                lineCount ++;//At the end, the whole line is done. Inc lc
                c++;
            }
            
            // allocate line
            
            char ** checker = (char ** ) malloc(wordCount * sizeof(char*));
            if (checker == NULL ) 
            {
                fprintf(stderr, "Error allocating file");
                exit(1);
            }
            else 
            {
                line=checker;
            }
            
            int jc = 0;
            wordCount = 0; 
            lineCount = 0;
            
            for (int i = 0; i < strlen(f);) 
            {
                
                word[lineCount] = f[i];  
                if (f[i] == ' ') 
                {
                    i++;
                    while (f[i] == ' ') 
                    {
                        i++;
                    }//Traverse through all the white spaces
                    
                    char * newWordT = (char *) realloc(word, (lineCount + 2)*sizeof(char));
                    if (newWordT != NULL) 
                    {
                        word = newWordT;
                    }
                    else {
                        fprintf(stderr, "Error allocating file");
                        exit(1);
                    }
                    word[lineCount+1] = '\0';
                    //Append a null byte to the end of the word so the 
		    //program knows where to stop
                    
                    line[wordCount] = word;
                    word = NULL;
                    jc = i;
                    word = (char* ) malloc(sizeof(char));
                    
                    wordCount++;
                    lineCount = 0;
                    continue;
                }
                
                
                lineCount++;
                char* temp = realloc(word, (lineCount+1)*sizeof(char));
                if (temp != NULL) 
                {
                    word = temp;
                }
                else 
                {
                    free(word);
                    fprintf(stderr, "Error allocating memory");
                    exit(1);
                }
		i++;
            }
        }
        
    }
    
    else 
    {
        line = (char**) malloc(sizeof(char*));
    }
    
    char currChar[1];
    ssize_t currRes = read(0, currChar, 1);
    if (currRes<0)
    {
        fprintf(stderr, "Could not read the file");
        exit(1);
    }
    
    char next[1];
    ssize_t nextRes = read(0, next, 1);
    if (nextRes<0)
    {
        fprintf(stderr, "Could not read the file");
        exit(1);
    }//Deal with errors with the curr and next char arrays (method seen on
    //piazza)
    
    int resetLCount = 0;
    
    while(currRes > 0) 
    {
        word[lineCount] = currChar[0];
        char* temp = realloc(word, (lineCount+2)*sizeof(char));
       	if (temp != NULL) 
        {
            word = temp;
        }
        else 
        {
            free(word);
            exit(1);
        }
        
        if (currRes == 0) 
        {
            exit(0);
        }
        
        if (currChar[0] == ' ') 
        {
            
            word[lineCount+1] = '\0';
	    //append null byte to end to signify the end of a word
            
            line[wordCount] = word;
            char** tempWord = realloc(line, (wordCount+2) * sizeof(char*));
            if (tempWord != NULL) 
            {
                line = tempWord;
                wordCount++;
                word = NULL;
                word = (char* ) malloc(sizeof(char));
                resetLCount = 1;
            }
            else 
            {
                free(line);
                fprintf(stderr, "Error allocating memory");
                exit(1);
            }
            
            if (nextRes == 0) 
            {
                if (wordCount == 1 && lineCount == 0) 
                {
                    exit(0);
                }//handling the base case
                break;
            }
            if (next[0] == ' ') 
            {
                while (currChar[0] == ' ') 
                {
                    currRes = read(0, currChar, 1);
                    if (currRes<0)
                    {
                        fprintf(stderr, "Could not read the file");
                        exit(1);
                    }
                }
                nextRes = read(0, next, 1);
                if (nextRes<0)
                {
                    fprintf(stderr, "Could not read the file");
                    exit(1);
                }
                
                if (currRes == 0 && wordCount == 1 && lineCount == 0) 
                {   
                    exit(0);
                }

		if (resetLCount)
		  lineCount=0;
		else
		  lineCount++;
                
                continue;
            }
        }
        
        else if (nextRes == 0) 
        {
            currChar[0] = ' ';
            lineCount++;
            continue;
        }
        
        currChar[0] = next[0];
        nextRes = read(0, next, 1);
        if (nextRes<0)
        {
            fprintf(stderr, "Could not read the file");
            exit(1);
        }
        if (resetLCount)
	  lineCount=0;
	else
	  lineCount++;
        resetLCount = 0;
    }
    
    if (argc > 2) 
    {
        fprintf(stderr, "Wrong number of arguments");
        exit(1);
    }
    
    int return_val = 0;
    
    if ((return_val = getopt(argc, argv, "f")) != -1)//code found off stackoverflow 
    {
        if (return_val == 'f') 
        {
            qsort(line, wordCount, sizeof(char*), compareWrapperUpper);
        }
    }

    else qsort(line, wordCount, sizeof(char*), compareWrapper);

    for (size_t i = 0; i < wordCount; i++)
    {
        unsigned long length = strlen(line[i]);
        write(1, line[i], length);//write to line
    }

    for (size_t i = 0; i < wordCount; i++) 
    {
        free(line[i]);
    }
    free(line);
    //free all memory once the program is over to avoid memory leaks
}




int zor (const char c)
{
  return c^0x2A;
}

int frobcmp(char const *c1, char const * c2) {
  while (*c1==*c2)
    {
      if (*c1==' ')
      return 0;
      c1++;
      c2++;
    }
  return ((zor(*c1) < (zor(*c2)) ? -1 : 1));
}


int frobcmpUpper(char const *c1, char const * c2) {
  char upperc1=zor(*c1);
  char upperc2=zor(*c2);
  if (isalpha(upperc1))
    upperc1=toupper(upperc1);
  if (isalpha(upperc2))
    upperc2=toupper(upperc2);

  while (*c1==*c2)
    {
      if (*c1==' ')
	return 0;
      c1++;
      c2++;
    }    

  return ((upperc1<upperc2) ? -1 : 1);

}

// compare the two input characters
int compareWrapperUpper(const void* c1, const void* c2) {
  return frobcmpUpper(*((const char**) c1), *((const char**) c2));
}


// compare the two input characters
int compareWrapper(const void* c1, const void* c2) {
  return frobcmp(*((const char**) c1), *((const char**) c2));
}


