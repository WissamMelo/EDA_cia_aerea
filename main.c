#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
int id;
char company[3];
int delay;
} Record;

void selection_sort(Record *records, int n) {
int i, j, min_idx;
for (i = 0; i < n-1; i++) {
min_idx = i;
for (j = i+1; j < n; j++) {
if (records[j].delay < records[min_idx].delay) {
min_idx = j;
}
}
Record temp = records[min_idx];
records[min_idx] = records[i];
records[i] = temp;
}
}

int main() {
int n_delays = 0;
Record *records;
char company[3];
int delay;
clock_t start, end;
double cpu_time_used;

start = clock();
FILE *fp = fopen("Airlines.csv", "r");
if (fp == NULL) {
    printf("Failed to open file Airlines.csv\n");
    return 1;
}

while (fscanf(fp, "%*d, %2s, %d\n", company, &delay) != EOF) {
    n_delays++;
}
rewind(fp);
records = (Record*)malloc(n_delays * sizeof(Record));

for (int i = 0; i < n_delays; i++) {
    fscanf(fp, "%d, %2s, %d\n", &records[i].id, company, &records[i].delay);
}

selection_sort(records, n_delays);

end = clock();
cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

printf("Time used: %f seconds\n", cpu_time_used);

fclose(fp);

FILE *ofp = fopen("SortedAirlines.csv", "w");
for (int i = 0; i < n_delays; i++) {
    fprintf(ofp, "%d, %s, %d\n", records[i].id, records[i].company, records[i].delay);
}
fclose(ofp);

return 0;
}
