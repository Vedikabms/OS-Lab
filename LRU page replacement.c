#include <stdio.h>
#include <stdlib.h>

int findLRU(int time[], int frames) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frames; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int pages[], int n, int frames) {
    int *frame = (int *)malloc(frames * sizeof(int));
    int *recent = (int *)malloc(frames * sizeof(int));
    int page_faults = 0, page_hits = 0;
    int time = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        recent[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                hit = 1;
                page_hits++;
                recent[j] = time;
                break;
            }
        }

        if (!hit) {
            int pos = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1)
                pos = findLRU(recent, frames);

            frame[pos] = page;
            recent[pos] = time;
            page_faults++;
        }

        time++;
    }

    printf("LRU Page Faults: %d, Page Hits: %d\n", page_faults, page_hits);
    free(frame);
    free(recent);
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

    lru(pages, n, frames);

    return 0;
}
