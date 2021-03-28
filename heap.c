#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
  int temp = *a;

  *a = *b;
  *b = temp;
}

int left_idx(int i) { return 2 * i + 1; }
int right_idx(int i) { return 2 * i + 2; }
int parent_idx(int i) { return (i - 1) / 2; }

void PrintHeap(int heap[], int length) {
  for (int i = 0; i < length; i++) {
    printf("Heap(%d) = %d\n", i, heap[i]);
  }
}

void BubbleUp(int heap[], int k) {
  while (heap[(k - 1) / 2] > heap[k]) {
    swap(&heap[(k - 1) / 2], &heap[k]);

    k = (k - 1) / 2;
  }
}

void Insert(int heap[], int *last, int data) {
  heap[*last] = data;

  *last += 1;

  // Bubble Up
  BubbleUp(heap, *last - 1);
}

void BubbleDown(int heap[], int size, int k) {
  while (left_idx(k) < size) {
    int smallest = left_idx(k);

    if (right_idx(k) < size && heap[smallest + 1] < heap[smallest]) {
      smallest++;
    }

    if (heap[smallest] > heap[k]) {
      break;
    }

    swap(&heap[k], &heap[smallest]);

    k = smallest;
  }
}

int ExtractMin(int heap[], int *last) {
  int min = heap[0];

  *last -= 1;

  heap[0] = heap[*last];
  heap[*last] = 0;

  BubbleDown(heap, *last, 0);

  return min;
}

void RandomHeap(int heap[], int size, int max) {
  int data = rand() % max + 1;

  for (int i = 0, last = 0; i < size; i++) {
    Insert(heap, &last, data);
  }
}

int main() {
  int heap[100] = {0}, last = 0;

  for (int i = 0; i < 20; i++) {
    Insert(heap, &last, rand() % 100);
  }

  PrintHeap(heap, last);

  for (int i = last; i > 0; i--) {
    printf("Min: %d\n", ExtractMin(heap, &last));
  }
}
