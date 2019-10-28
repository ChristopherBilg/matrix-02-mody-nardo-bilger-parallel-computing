#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getNumberOfLines(char *filename);
double* extractMatrixFromFile(char *filename, int nrows);
int getArrayLength(int nrow);

int getNumberOfLines(char *filename)
{
    FILE *fp;
    char c;
    int count = 1;
    
    fp = fopen(filename, "r");
    
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }else
    {
       while((c = fgetc(fp)) != '\n') {
           //printf("%c", c);
           if (c == ' ') {
                count++;
            }
        }
    }
    
    fclose(fp);
    return count;
}

//gets the matrix from the file sent via command line in the main
//filename is the pointer to the string file name, nrows is the number of rows
double* extractMatrixFromFile(char *filename, int nrows)
{
    //printf("extractMatrixFromFile\n");
    FILE *fp = fopen(filename, "r");
    char str[256];
    int i = 0;
    char *delim = ", \n";
    char *tok;
    double *extractedMatrix = malloc(sizeof(double) * nrows * nrows);
    //printf("after malloc\n");
    
    if (fp != NULL)
    {
        while (fgets(str, 256, fp) != NULL)
        {
            sscanf(str, filename, "%s");
            //printf("\nB4 TOK: %s\n", str);
            
            tok = strtok(str, " ");
            while(tok != NULL)
            {
                //printf("NUM: %s\n", tok);
                double tempVal = atof(tok);
                //printf("DOUB: %lf\n", tempVal);
                
                extractedMatrix[i] = tempVal;
                //printf("\nAFTER ADD: %lf\n", extractedMatrix[i]);
                i = i + 1;
                
                tok = strtok(NULL, delim);
                
            }
        }
    }
    else
    {
        printf("Could not open file %s", filename);
    }
    
    rewind(fp);
    fclose(fp);
    
    return extractedMatrix;
}

int getArrayLength(int nrow)
{
    return (nrow * nrow);
}
/*
//printf("main\n");
    int nrows;
    int i = 0;
    
    //printf("after malloc\n");
    
    if (argc > 1) {
        //printf("in if\n");
        nrows = getNumberOfLines(argv[1]);
        printf("Rows: %d\n", nrows);
        
        //printf("Extract\n");
        double *extractedMatrix = extractMatrixFromFile(argv[1], nrows);
        //printf("\nExtracted\n");
        
        printf("Matrix:\n");
        for(i = 0; i < (nrows * nrows); i++)
        {
            printf("%lf ", extractedMatrix[i]);
        }
        printf("\n");
        free(extractedMatrix);
    }
*/
