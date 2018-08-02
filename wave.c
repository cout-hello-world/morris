#include "wave.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

const double Pi = acos(-1.0);
#define Samples ((int)2000)
#define FadeSamples ((int)(Samples / 20))
#define SamplesPerCycle ((int)80)

static void sound_dit(bool fade_in, bool fade_out)
{
	unsigned char buffer[2 * SamplesPerCycle];
	for (int i = 0; i != Samples; ++i) {
		int delta = i % SamplesPerCycle;
		double temp_double = 3200.0 * sin(2.0 * Pi / SamplesPerCycle * delta);
		if (fade_in) {
			if (i < FadeSamples) {
				temp_double *= i / (double)FadeSamples;
			}
		}
		if (fade_out) {
			if (i > Samples - FadeSamples) { // should be >= ?
				temp_double *= (Samples - i) / (double)FadeSamples;
			}
		}
		int16_t temp = (int16_t)lround(temp_double);
		buffer[2 * delta] = temp & 0xff;
		buffer[2 * delta + 1] = (temp >> 8) & 0xff;
		if (delta == SamplesPerCycle - 1) {
			fwrite(buffer, 2 * SamplesPerCycle, 1, stdout);
			fflush(stdout);
		}
	}
}

void silence(int duration)
{
	unsigned char buffer[2 * SamplesPerCycle] = {0};
	for (int j = 0; j != duration; ++j) {
		for (int i = 0; i != Samples; ++i) {
			if (i % SamplesPerCycle == SamplesPerCycle - 1) {
				fwrite(buffer, 2 * SamplesPerCycle, 1, stdout);
				fflush(stdout);
			}
		}
	}
}

void dit(void)
{
	sound_dit(true, true);
}

void dah(void)
{
	sound_dit(true, false);
	sound_dit(false, false);
	sound_dit(false, true);
}
