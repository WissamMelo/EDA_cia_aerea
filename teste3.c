#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_NUM_COLUMNS 50
#define MEDIA_COLUMN 50
#define NUM_ID_STRINGS 18

const char* id_strings[NUM_ID_STRINGS] = {"9E", "AA", "AS", "B6", "CO", "DL", "EV", "F9", "FL", "HA", "MQ", "OH", "OO", "UA", "US", "WN", "XE", "YV"};

int id_count[NUM_ID_STRINGS];
int id_delay[NUM_ID_STRINGS];

void selection_sort(int column, int num_rows, char data[num_rows][MAX_NUM_COLUMNS][MAX_LINE_LENGTH]) {
int i, j, min_index;
char temp[MAX_LINE_LENGTH];
for (i = 0; i < num_rows - 1; i++) {
min_index = i;
for (j = i + 1; j < num_rows; j++) {
if (strcmp(data[j][column], data[min_index][column]) < 0) {
min_index = j;
}
}
if (min_index != i) {
for (j = 0; j < MAX_NUM_COLUMNS; j++) {
strcpy(temp, data[i][j]);
strcpy(data[i][j], data[min_index][j]);
strcpy(data[min_index][j], temp);
}
}
}
}

int main(int argc, char* argv[]) {
char ***data;
int num_rows = 0;
int num_columns = 0;
int column = 3; // specify the column to be sorted here
char line[MAX_LINE_LENGTH];
char* token;
FILE* fp;
for (int i = 0; i < NUM_ID_STRINGS; i++) {
    id_count[i] = 0;
}

for (int i = 0; i < NUM_ID_STRINGS; i++) {
  id_delay[i] = 0;
}

fp = fopen("Airlines.csv", "r"); // specify the input csv file here
if (!fp) {
printf("Error: Unable to open file %s\n", "Airlines.csv");
return 1;
}

while (fgets(line, MAX_LINE_LENGTH, fp)) {
  num_rows++;
}

fclose(fp);
fp = fopen("Airlines.csv", "r");

data = (char ***)malloc(num_rows * sizeof(char **));
for (int i = 0; i < num_rows; i++) {
  data[i] = (char **)malloc(MAX_NUM_COLUMNS * sizeof(char *));
  for (int j = 0; j < MAX_NUM_COLUMNS; j++) {
    data[i][j] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
  }
}

num_rows = 0;
while (fgets(line, MAX_LINE_LENGTH, fp)) {
  num_columns = 0;
  token = strtok(line, ",");
  while (token) {
    strcpy(data[num_rows][num_columns], token);
    num_columns++;
    token = strtok(NULL, ",");

    for (int i = 0; i < NUM_ID_STRINGS; i++) {
      if (strcmp(token, id_strings[i]) == 0) {
        id_count[i]++;
        strcpy(data[num_rows][MEDIA_COLUMN], "Media");
      }
    }
  }
  num_rows++;
}

fclose(fp);

selection_sort(column, num_rows, data);

FILE *output_file;
output_file = fopen("sorted_data.csv", "w"); // specify the output csv file here

for (int i = 0; i < num_rows; i++) {
  for (int j = 0; j < num_columns + 1; j++) {
    if (j == MEDIA_COLUMN) {
      fprintf(output_file, "%s", data[i][MEDIA_COLUMN]);
    } else {
      fprintf(output_file, "%s", data[i][j]);
    }
    if (j != num_columns) {
      printf(",");
    }
  }
  printf("\n");
}

fclose(output_file);

for (int i = 0; i < num_rows; i++) {
  for (int j = 0; j < MAX_NUM_COLUMNS; j++) {
    free(data[i][j]);
  }
  free(data[i]);
}
free(data);
}