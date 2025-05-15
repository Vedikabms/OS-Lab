#include <stdio.h>
#include <stdlib.h>

int search(int key, int frame[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == key)
            return 1;
    }
    return 0;
}

void fifo(int pages[], int n, int frames) {
    int *frame = (int *)malloc(frames * sizeof(int));
    int page_faults = 0, page_hits = 0, index = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!search(pages[i], frame, frames)) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            page_faults++;
        } else {
            page_hits++;
        }
    }

    printf("FIFO Page Faults: %d, Page Hits: %d\n", page_faults, page_hits);
    free(frame);
}

int main() {
    int pages[100], n, frames;

    printf("Enter the size of the pages:\n");
    scanf("%d", &n);

    printf("Enter the page strings:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the number of page frames:\n");
    scanf("%d", &frames);

    fifo(pages, n, frames);

    return 0;
}
