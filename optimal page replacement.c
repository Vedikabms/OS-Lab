#include <stdio.h>
#include <stdlib.h>

int search(int key, int frame[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == key) {
            return 1;
        }
    }
    return 0;
}

int findOptimal(int pages[], int frame[], int frames, int index, int n) {
    int farthest = index, pos = -1, i, j;
    for (i = 0; i < frames; i++) {
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }
    return (pos == -1) ? 0 : pos;
}

void optimal(int pages[], int n, int frames) {
    int *frame = (int *)malloc(frames * sizeof(int));
    int page_faults = 0, page_hits = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        if (search(page, frame, frames)) {
            page_hits++;
        } else {
            int pos = -1;

            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                pos = findOptimal(pages, frame, frames, i + 1, n);
            }

            frame[pos] = page;
            page_faults++;
        }
    }

    printf("Optimal Page Faults: %d, Page Hits: %d\n", page_faults, page_hits);
    free(frame);
}

int main() {
    int pages[100], n, frames;

    printf("Enter the size of the pages:\n");
    scanf("%d", &n);

    printf("Enter the page strings:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of page frames:\n");
    scanf("%d", &frames);

    optimal(pages, n, frames);

    return 0;
}
