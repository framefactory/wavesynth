/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "OutBuffer.h"

F_USE_NAMESPACE

OutBuffer::OutBuffer(size_t bufferLength)
{
    pData = new int16_t[bufferLength];
    length = bufferLength;
}

OutBuffer::~OutBuffer()
{
    delete[] pData;
    pData = nullptr;
    length = 0;
}

void OutBuffer::copy(const RenderBuffer& renderBuffer)
{
    for (size_t i = 0; i < length; ++i) {
        pData[i] = renderBuffer.pData[i] * 32767.0f;
    }
}