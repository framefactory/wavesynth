/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _WAVESYNTH_OUTBUFFER_H
#define _WAVESYNTH_OUTBUFFER_H

#include "app.h"
#include "RenderBuffer.h"
#include <vector>

F_BEGIN_NAMESPACE

struct OutBuffer
{
    OutBuffer(size_t bufferLength = 512);
    ~OutBuffer();

    void copy(const RenderBuffer& renderBuffer);

    int16_t* pData;
    size_t length;
};

F_END_NAMESPACE

#endif // _WAVESYNTH_OUTBUFFER_H