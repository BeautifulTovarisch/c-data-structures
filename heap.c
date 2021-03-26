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

void Insert(int heap[], int *last, int data) {
  heap[*last] = data;

  *last += 1;

  // Bubble Up
  for (int i = *last - 1; i > 0 && heap[parent_idx(i)] > heap[i];
       i = parent_idx(i)) {

    swap(&heap[parent_idx(i)], &heap[i]);
  }
}

void BubbleDown(int heap[], int size) {
  for (int index = 0, smallest = 1; left_idx(index) < size; index = smallest) {
    int left = left_idx(index);
    int right = right_idx(index);
    smallest = left;

    if (right < size && heap[right] <= heap[left]) {
      smallest = right;
    }

    if (heap[smallest] > heap[index]) {
      break;
    }

    swap(&heap[index], &heap[smallest]);
  }
}

int ExtractMin(int heap[], int *last) {
  int min = heap[0];

  *last -= 1;

  heap[0] = heap[*last];
  heap[*last] = 0;

  BubbleDown(heap, *last);

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

  for (int i = 0; i < 10; i++) {
    Insert(heap, &last, rand() % 100);
  }

  PrintHeap(heap, last);

  for (int i = last; i > 0; i--) {
    printf("Min: %d\n", ExtractMin(heap, &last));
  }
}
