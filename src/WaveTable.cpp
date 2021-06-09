/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "WaveTable.h"
#include "core/Math.h"
#include <cstdlib>

F_USE_NAMESPACE

static inline float blackmanWindow(float i, float M, float fn) {
    return 0.42 - 0.5 * cosf(F_PI * 2.0f * i / M) + 0.08f * cosf(4 * F_PI * i / M);
}

WaveTable::WaveTable()
{

}

void WaveTable::generate(wave_type wave, float shape /* = 0.0f */)
{
    size_t s = 1 << BIT_SIZE;
    for (size_t i = 0; i < s; ++i) {
        float p = i / float(s);
        switch(wave) {
            case Sine:
                samples[i] = sinf(p * F_2PI);
                break;
            case Triangle:
                samples[i] = p < 0.25 ? p * 4 : (p < 0.75 ? 2 - p * 4 : -4 + p * 4);
                break;
            case Saw:
                samples[i] = p * 2 - 1;
                break;
            case Square:
                samples[i] = p < shape ? -1 : 1;
                break;
            case FM:
                samples[i] = (float(rand()) / RAND_MAX) * 2.0f - 1.0f;
                break;
            case Bell:
                samples[i] = 0.5f * sinf(p * F_2PI) + 0.5f * sinf(p * 2.0f * F_2PI) + 0.2f * sinf(p * 5.0f * F_2PI) + 0.2f * sinf(p * 8.0f * F_2PI);
                break;
        }
    }

    size_t inPos = 0;
    for (int b = BIT_SIZE; b >= 0; --b) {
        size_t s = 1 << b;
        size_t outPos = inPos + s;
        downsample2x(samples + inPos, samples + outPos, s, 16, float(s) / 8192.0f);
        inPos = outPos;
    }
}

void WaveTable::downsample2x(float* pIn, float* pOut, size_t length, size_t M, float fn)
{
    computeKernel(M, fn);
    size_t Mh = M / 2;

    for (size_t i = 0, ii = 0; i < length; i += 2, ++ii) {
        float v = 0.0f;
        for (size_t j = 0; j < M; ++j) {
            v += kernel[j] * pIn[(i + length + j - Mh) % length];
        }
        pOut[ii] = v;
    }
}

void WaveTable::computeKernel(size_t M, float fn)
{
    float sum = 0.0f;

    for (size_t i = 0; i <= M; ++i) {
        float denom = F_PI * (i - M * 0.5);
        float c = denom ? sinf(F_PI * 2.0f * fn * (i - M * 0.5f)) / denom : 2.0f * fn;
        c = c * blackmanWindow(i, M, fn);
        sum += c;
        kernel[i] = c;
    }

    for (size_t i = 0; i <= M; ++i) {
        kernel[i] /= sum;
    }
}