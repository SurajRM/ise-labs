#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct page_data {
    int ref_string_len;
    int *ref_string;
    int frames_count;
} PageData;

PageData *input_data();
bool is_hit(int *, int, int);
void display_pages(int *, int);
void fifo(PageData *);
void lru(PageData *);
void optimal(PageData *);

int main() {
    printf("\t\tPage replacement algorithms\n");
    PageData *pd = input_data();

    fifo(pd);
    lru(pd);
    optimal(pd);
}

PageData *input_data() {
    PageData *pd = (PageData *) malloc(sizeof(PageData));

    printf("Enter the number of frames: ");
    scanf("%d", &pd->frames_count);

    printf("Enter the length of page reference string: ");
    scanf("%d", &pd->ref_string_len);
    pd->ref_string = (int *) malloc(pd->ref_string_len * sizeof(int));
    printf("Enter the page reference string: ");
    for (int i = 0; i < pd->ref_string_len; i++)
        scanf("%d", &pd->ref_string[i]);

    return pd;
}

bool is_hit(int *page_frame, int size, int data) {
    for (int i = 0; i < size; i++) {
        if (page_frame[i] == data)
            return true;
    }
    return false;
}

void display_pages(int *page_frame, int size) {
    for (int i = 0; i < size; i++) {
        if (page_frame[i] != -1)
            printf("%d ", page_frame[i]);
    }
    printf("\n");
}

void fifo(PageData *pd) {
    printf("\nFifo page replacement\n");
    int page_faults = 0;
    int page_frame[pd->frames_count];
    for (int i = 0; i < pd->frames_count; i++)
        page_frame[i] = -1;

    for (int i = 0; i < pd->ref_string_len; i++) {
        printf("\tFor page %d: ", pd->ref_string[i]);
        if (!is_hit(page_frame, pd->frames_count, pd->ref_string[i])) {
            for (int j = 0; j < pd->frames_count - 1; j++)
                page_frame[j] = page_frame[j + 1];
            page_frame[pd->frames_count - 1] = pd->ref_string[i];
            page_faults++;
            display_pages(page_frame, pd->frames_count);
        } else
            printf("No page fault\n");
    }
    printf("\tTotal number of page faults: %d\n", page_faults);
}

void lru(PageData *pd) {
    printf("\nLRU page replacement\n");
    int page_faults = 0, page, min, rep_index = 0;
    bool found;
    int page_frame[pd->frames_count], least[pd->frames_count];
    for (int i = 0; i < pd->frames_count; i++)
        page_frame[i] = -1;

    for (int i = 0; i < pd->ref_string_len; i++) {
        printf("\tFor page %d: ", pd->ref_string[i]);
        if (!is_hit(page_frame, pd->frames_count, pd->ref_string[i])) {
            for (int j = 0; j < pd->frames_count; j++) {
                page = page_frame[j];
                found = false;
                for (int k = i - 1; k >= 0; k--) {
                    if (page == pd->ref_string[k]) {
                        least[j] = k;
                        found = true;
                        break;
                    } else
                        found = false;
                }
                if (!found)
                    least[j] = INT_MIN;
            }
            min = INT_MAX;
            for (int j = 0; j < pd->frames_count; j++) {
                if (least[j] < min) {
                    min = least[j];
                    rep_index = j;
                }
            }
            page_frame[rep_index] = pd->ref_string[i];
            page_faults++;
            display_pages(page_frame, pd->frames_count);
        } else
            printf("No page fault\n");
    }
    printf("\tTotal number of page faults: %d\n", page_faults);
}

void optimal(PageData *pd) {
    printf("\nOptimal page replacement\n");
    int page_faults = 0, page, max, rep_index;
    int page_frame[pd->frames_count], near[pd->frames_count];
    bool found;
    for (int i = 0; i < pd->frames_count; i++)
        page_frame[i] = -1;

    for (int i = 0; i < pd->ref_string_len; i++) {
        printf("\tFor page %d: ", pd->ref_string[i]);
        if (!is_hit(page_frame, pd->frames_count, pd->ref_string[i])) {
            for (int j = 0; j < pd->frames_count; j++) {
                page = page_frame[j];
                found = false;
                for (int k = i; k < pd->ref_string_len; k++) {
                    if (page == pd->ref_string[k]) {
                        near[j] = k;
                        found = true;
                        break;
                    } else
                        found = false;
                }
                if (!found)
                    near[j] = INT_MAX;
            }
            max = INT_MIN;
            for (int j = 0; j < pd->frames_count; j++) {
                if (near[j] > max) {
                    max = near[j];
                    rep_index = j;
                }
            }
            page_frame[rep_index] = pd->ref_string[i];
            page_faults++;
            display_pages(page_frame, pd->frames_count);
        } else
            printf("No page fault\n");
    }
    printf("\tTotal number of page faults: %d\n", page_faults);
}
