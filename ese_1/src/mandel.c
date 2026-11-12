#include "mandel.h"

#include <stddef.h>

// The region of the complex plane in the frame (given)
#define X_MIN -2.1
#define X_MAX 0.7
#define Y_MIN -1.15
#define Y_MAX 1.15

void (*sampleHook)(long iterations) = NULL;

// Shade of a pixel from the average iterations of its samples: inside the
// set it is '@', outside it fades with the number of iterations
static char shade(long avg) {
    static const char palette[] = " .:-=+*#%@";
    static const long steps[] = {2, 3, 5, 8, 13, 25, 60, 200};
    if (avg >= MAX_ITER)
        return '@';
    int i = 0;
    while (i < 8 && avg >= steps[i])
        i++;
    return palette[i];
}

long renderRow(int y, char *out) {
    long iterations = 0;
    for (int x = 0; x < WIDTH; x++) {
        long sum = 0;
        for (int sy = 0; sy < SAMPLES; sy++) {
            for (int sx = 0; sx < SAMPLES; sx++) {
                double cr = X_MIN + (X_MAX - X_MIN) * (x + (sx + 0.5) / SAMPLES) / WIDTH;
                double ci = Y_MAX - (Y_MAX - Y_MIN) * (y + (sy + 0.5) / SAMPLES) / HEIGHT;
                double zr = 0.0, zi = 0.0;
                int it = 0;
                while (it < MAX_ITER && zr * zr + zi * zi <= 4.0) {
                    double t = zr * zr - zi * zi + cr;
                    zi = 2.0 * zr * zi + ci;
                    zr = t;
                    it++;
                }
                sum += it;
                if (sampleHook != NULL)
                    sampleHook(it);
            }
        }
        iterations += sum;
        out[x] = shade(sum / (SAMPLES * SAMPLES));
    }
    out[WIDTH] = '\0';
    return iterations;
}
