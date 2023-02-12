#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int compare_column(const void *a, const void *b) {
  char *column1 = strtok(*(char **)a, ",");
  int column_to_sort = 1; // Assume the column to sort is the second one
  int i;
  for (i = 1; i <= column_to_sort; i++) {
    column1 = strtok(NULL, ",");
  }
  char *column2 = strtok(*(char **)b, ",");
  for (i = 1; i <= column_to_sort; i++) {
    column2 = strtok(NULL, ",");
  }
  return strcmp(column1, column2);
}

void selection_sort(char *lines[], int num_lines) {
  int i, j, min_index;
  char *temp;
  for (i = 0; i < num_lines - 1; i++) {
    min_index = i;
    for (j = i + 1; j < num_lines; j++) {
      if (compare_column(&lines[j], &lines[min_index]) < 0) {
        min_index = j;
      }
    }
    temp = lines[min_index];
    lines[min_index] = lines[i];
    lines[i] = temp;
  }
}

int main() {
  char *lines[20000];
  int num_lines = 0;

  // Read the CSV file into memory
  FILE *fp;
  fp = fopen("Airlines.csv", "r");
  if (fp == NULL) {
    printf("Could not open file.\n");
    return 1;
  }
  while (fgets(lines[num_lines], MAX_LINE_LENGTH, fp) != NULL) {
    num_lines++;
  }
  fclose(fp);

  // Sort the column using selection sort
  selection_sort(lines, num_lines);

  // Write the sorted column back to the file
  fp = fopen("Airlines.csv", "w");
  if (fp == NULL) {
    printf("Could not open file.\n");
    return 1;
  }
  int i;
  for (i = 0; i < num_lines; i++) {
    fprintf(fp, "%s", lines[i]);
  }
  fclose(fp);

  return 0;
}
