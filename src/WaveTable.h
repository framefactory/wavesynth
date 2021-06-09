/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _WAVESYNTH_WAVETABLE_H
#define _WAVESYNTH_WAVETABLE_H

#include "app.h"

F_BEGIN_NAMESPACE

class WaveTable
{
public:
    enum wave_type {
        Sine,
        Triangle,
        Saw,
        Square,
        FM,
        Bell
    };

    static const size_t BIT_SIZE = 11;

    WaveTable();

    void generate(wave_type wave, float shape = 0.0f);
    void downsample2x(float* pIn, float* pOut, size_t length, size_t M, float fn);
    void computeKernel(size_t M, float fn);

    float samples[(1 << BIT_SIZE) * 2];
    float kernel[16];
};

F_END_NAMESPACE

#endif // _WAVESYNTH_WAVETABLE_H