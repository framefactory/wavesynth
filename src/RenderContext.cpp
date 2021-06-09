/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "RenderContext.h"
#include <math.h>

F_USE_NAMESPACE

static const float _f = 1.05946309;

RenderContext::RenderContext(size_t _sampleRate) :
    time(0.0),
    sampleRate(_sampleRate)
{
}
