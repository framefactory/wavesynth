/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "RenderBuffer.h"

F_USE_NAMESPACE

RenderBuffer::RenderBuffer(size_t bufferLength)
{
    pData = new float[bufferLength];
    length = bufferLength;
}

RenderBuffer::~RenderBuffer()
{
    delete[] pData;
    pData = nullptr;
    length = 0;
}

void RenderBuffer::clear()
{
    for (size_t i = 0; i < length; ++i) {
        pData[i] = 0.0f;
    }
}