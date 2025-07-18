#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define small 1e-9

void swapRow(double **matrix, int row1, int row2, int cols){
  for (int i = 0; i < cols; i++){
    double temp = matrix[row1][i];
    matrix[row1][i] = matrix[row2][i];
    matrix[row2][i] = temp; 
  }
}

void scaleRow(double **matrix, int row, int cols, double factor){
  for (int i = 0; i < cols; i++){
    matrix[row][i] /= factor;
  }
}

void addRow(double **matrix, int row1, int row2, int cols, double factor){
  for(int i = 0; i < cols; i++){
    matrix[row1][i] += factor * matrix[row2][i];
  }
}

void g_Elim(double **matrix, int rows, int cols){
  for(int i = 0; i < rows; i++){
    if(fabs(matrix[i][i]) < small){
      for(int j = i + 1; j < rows; j++){
        if (fabs(matrix[j][i]) > small){
          swapRow(matrix, i, j, cols); 
          break; 
        }
      }
    }

    if(fabs(matrix[i][i]) > small){
      scaleRow(matrix, i, cols, matrix[i][i]);
    }

    for(int j = 0; j < rows; j++){
      if ( j != i && fabs(matrix[j][i]) > small){
        addRow(matrix, j, i, cols, -matrix[j][i]);
      }
    }
  }
}

void print_Matrix(double **matrix, int rows, int cols){
  for(int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      if(fabs(matrix[i][j]) < small){
        matrix[i][j] = 0.0; 
        }
       printf("%lf ", matrix[i][j]);
    }
   printf("\n");
  }
}

void free_matrix(double **matrix, int rows){
    for (int i = 0; i < rows; i++){
      free(matrix[i]);
    }
    free(matrix);
}

void read_file(const char *filename, double ***matrix, int *rows, int *cols){
  FILE *file = fopen(filename, "r");
  if(!file){
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  fscanf(file, "%d", rows); 
  fscanf(file, "%d", cols); 
//
  //allocate memory
  *matrix = (double **)malloc(*rows * sizeof(double *)); 
  for (int i = 0; i < *rows; i++){
    (*matrix)[i] = (double *)malloc(*cols * sizeof(double));
      for(int j = 0; j < *cols; j++){
        fscanf(file, "%lf", &((*matrix)[i][j]));
      }
  }
  fclose(file); 
}

int main(int argc, char **argv){
    if (argc < 2)
  {
    fprintf(stderr, "./third {text file}\n");
    exit(1);
  }

    double **matrix; 
    int rows; 
    int cols; 


  //read file
  read_file(argv[1], &matrix, &rows, &cols); 

//then do Guassian Elimination on the matrix
  g_Elim(matrix, rows, cols);

// print the final matrix

print_Matrix(matrix, rows, cols);

//then free the memory
free_matrix(matrix, rows);

return EXIT_SUCCESS;

}
