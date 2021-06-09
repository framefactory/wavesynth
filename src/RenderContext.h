/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _WAVESYNTH_RENDERCONTEXT_H
#define _WAVESYNTH_RENDERCONTEXT_H

#include "app.h"
#include <vector>

F_BEGIN_NAMESPACE

struct RenderContext
{
    RenderContext(size_t sampleRate = 44100);

    double time;
    size_t sampleRate;
};

F_END_NAMESPACE

#endif // _WAVESYNTH_RENDERCONTEXT_H