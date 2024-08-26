
#include <stdio.h>

void qsort(int[], int left, int right);
void swap(int v[], int i, int j);
void printar(int ar[], int length);

int main(void) {
  int ar[7] = {1, 4, 5, 3, 7, 2, 5};
  printar(ar, 7);

  qsort(ar, 0, 6);
  printar(ar, 7);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right) {
  int i, last;
  void swap(int v[], int i, int j);

  if (left >= right) /* do nothing if array contains fewer than two elements */
    return;
  swap(v, left, (left + right) / 2); /* move partition elem to v[0]*/
  last = left;
  for (i = left + 1; i <= right; i++) { /* partition */
    printar(v, right - left + 1);
    if (v[i] < v[left]) {

      swap(v, ++last, i);
      printf("   Swapped! %i, %i\n", i, last);
    }
  }
  printf("Restore partition");
  swap(v, left, last); /* restore partition elem*/
  printar(v, right - left + 1);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j) {
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* printar: print an integer array */
void printar(int ar[], int length) {
  for (int i = 0; i < length; i++) {
    printf("%i ", ar[i]);
  }
  printf("\n");
}
