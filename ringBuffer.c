#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 5  

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} RingBuffer;


void initBuffer(RingBuffer* rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}


bool writeBuffer(RingBuffer* rb, int value) {
    if (rb->count == BUFFER_SIZE) {
        return false;  // Bufor pełny
    }
    rb->buffer[rb->head] = value;
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    rb->count++;
    return true;
}

bool readBuffer(RingBuffer* rb, int* value) {
    if (rb->count == 0) {
        return false;  // Bufor pusty
    }
    *value = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    rb->count--;
    return true;
}


void printBuffer(RingBuffer* rb) {
    int i;
    for (i = 0; i<BUFFER_SIZE; i++) {
        printf("%d ", rb->buffer[i]);
    }
    printf("\n");
}

int main() {
    RingBuffer rb;
    initBuffer(&rb);

    writeBuffer(&rb, 1);
    writeBuffer(&rb, 2);
    writeBuffer(&rb, 3);
    writeBuffer(&rb, 4);
    writeBuffer(&rb, 5);
    bool result = writeBuffer(&rb, 6);  
    if (!result) {
        printf("Bufor jest pełny!\n");
    }

    printf("Zawartość bufora: ");
    printBuffer(&rb);

    int value;
    if (readBuffer(&rb, &value)) {
        printf("Odczytano wartość: %d\n", value);
    } else {
        printf("Bufor jest pusty!\n");
    }

    printf("Zawartość bufora po odczycie: ");
    printBuffer(&rb);

    return 0;
}
