/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _WAVESYNTH_RENDERBUFFER_H
#define _WAVESYNTH_RENDERBUFFER_H

#include "app.h"
#include <vector>

F_BEGIN_NAMESPACE

struct RenderBuffer
{
    RenderBuffer(size_t bufferLength = 512);
    ~RenderBuffer();

    void clear();

    float* pData;
    size_t length;
};

F_END_NAMESPACE

#endif // _WAVESYNTH_RENDERBUFFER_H