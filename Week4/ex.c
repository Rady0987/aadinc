#include <stdio.h>
#include <stdlib.h>

typedef struct painting
{
    int difficulty, skill;
} painting;

typedef struct heap
{
    painting *paintings;
    int head;
    int size;
} heap;

void swap(painting *x, painting *y)
{
    painting tmp = *x;
    *x = *y;
    *y = tmp;
}

int isEmptyHeap(heap h)
{
    return (h.head == 0);
}

heap *initHeap(int n)
{
    heap *h = (heap *)malloc(sizeof(heap));
    h->paintings = calloc(n, sizeof(painting));
    if (h->paintings == NULL)
    {
        abort();
    }
    h->head = 1;
    h->size = n;
    return h;
}

void upHeap(heap *h, int n)
{
    int parentNode = (n - 1) / 2;
    if (h->paintings[parentNode].difficulty > h->paintings[n].difficulty)
    {
        swap(&(h->paintings[parentNode]), &(h->paintings[n]));
        upHeap(h, parentNode);
    }
}

void doubleHeapSize(heap *h)
{
    long int updatedSize = 2 * h->size;
    h->paintings = realloc(h->paintings, updatedSize * sizeof(heap));
    if (h->paintings == NULL)
    {
        return;
    }
    h->size = updatedSize;
}

void enqueue(heap *h, int skill, int difficulty)
{
    if (h->head == h->size)
    {
        doubleHeapSize(h);
    }
    h->paintings[h->head].skill = skill;
    h->paintings[h->head].difficulty = difficulty;
    upHeap(h, h->head);
    h->head++;
}

void downHeap(heap *h, int parentNode)
{
    int lChild = parentNode * 2 + 1;
    int rChild = parentNode * 2 + 2;
    int min;
    if (lChild >= h->head || lChild < 0)
    {
        lChild = -1;
    }
    if (rChild >= h->head || rChild < 0)
    {
        rChild = -1;
    }
    if (lChild != -1 && h->paintings[lChild].difficulty < h->paintings[parentNode].difficulty)
    {
        min = lChild;
    }
    else
    {
        min = parentNode;
    }
    if (rChild != -1 && h->paintings[rChild].difficulty < h->paintings[min].difficulty)
    {
        min = rChild;
    }
    if (min != parentNode)
    {
        swap(&(h->paintings[min]), &(h->paintings[parentNode]));
        downHeap(h, min);
    }
}

void removeMin(heap *h)
{
    if (isEmptyHeap(*h))
    {
        abort();
    }
    h->paintings[0] = h->paintings[h->head - 1];
    h->head--;
    downHeap(h, 0);
}

int main(int argc, char *argv[])
{
    int nrPaintings, skillinit, style, difficulty, reward, result1, result2;
    scanf("%d %d", &nrPaintings, &skillinit);
    heap *oilPaintings = initHeap(nrPaintings);
    heap *waterPaintings = initHeap(nrPaintings);
    heap *oilPaintings2 = initHeap(nrPaintings);
    heap *waterPaintings2 = initHeap(nrPaintings);

    for (int i = 0; i < nrPaintings; i++)
    {
        scanf("%d %d %d", &style, &difficulty, &reward);
        if (style == 0)
        {
            enqueue(oilPaintings, reward, difficulty);
            enqueue(oilPaintings2, reward, difficulty);
        }
        else
        {
            enqueue(waterPaintings, reward, difficulty);
            enqueue(waterPaintings2, reward, difficulty);
        }
    }

    int skillinit2 = skillinit, counter1 = 0, counter2 = 0, deleted1 = 0, deleted2 = 0;
    while (waterPaintings->paintings[0].difficulty == 0)
    {
        deleted1++;
        removeMin(waterPaintings);
        removeMin(waterPaintings2);
    }
    while (oilPaintings->paintings[0].difficulty == 0)
    {
        deleted2++;
        removeMin(oilPaintings);
        removeMin(oilPaintings2);
    }

    while (1)
    {
        if (skillinit2 >= oilPaintings->paintings[0].difficulty && !isEmptyHeap(*oilPaintings))
        {
            skillinit2 += oilPaintings->paintings[0].skill;
            counter1++;
            removeMin(oilPaintings);
        }
        else
        {
            break;
        }
        if (skillinit2 >= waterPaintings->paintings[0].difficulty && !isEmptyHeap(*waterPaintings))
        {
            skillinit2 += waterPaintings->paintings[0].skill;
            counter1++;
            removeMin(waterPaintings);
        }
        else
        {
            break;
        }
    }
    skillinit2 = skillinit;
    while (1)
    {
        if (skillinit2 >= waterPaintings2->paintings[0].difficulty && !isEmptyHeap(*waterPaintings2))
        {
            skillinit2 += waterPaintings2->paintings[0].skill;
            counter2++;
            removeMin(waterPaintings2);
        }
        else
        {
            break;
        }
        if (skillinit2 >= oilPaintings2->paintings[0].difficulty && !isEmptyHeap(*oilPaintings2))
        {
            skillinit2 += oilPaintings2->paintings[0].skill;
            counter2++;
            removeMin(oilPaintings2);
        }
        else
        {
            break;
        }
    }
    if (counter1 >= counter2)
    {
        printf("%d\n", counter1);
    }
    else
    {
        printf("%d\n", counter2);
    }
    free(oilPaintings->paintings);
    free(oilPaintings);
    free(waterPaintings->paintings);
    free(waterPaintings);
    free(oilPaintings2->paintings);
    free(oilPaintings2);
    free(waterPaintings2->paintings);
    free(waterPaintings2);
    return 0;
}