/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "TestProgram.h"
#include "core/Math.h"

F_USE_NAMESPACE

static const float _f = 1.05946309f;

TestVoice::TestVoice(double time, uint8_t note, float velocity) :
    Voice(time, note, velocity)
{
}

bool TestProgram::renderVoice(const RenderContext& context, const RenderBuffer& buffer, Voice* pVoice)
{
    float freq = 440 * powf(_f, pVoice->note - 57);

    for (size_t i = 0; i < buffer.length; i += 2) {
        float time = context.time + float(i) * 0.5f / context.sampleRate;
        float val = sinf(time * freq * F_2PI) * 0.1f;
        //float val = sinf(float(i) / buffer.length * F_2PI * 4.0f);
        buffer.pData[i] += val;
        buffer.pData[i+1] += val;
    }

    return pVoice->isActive;
}

Voice* TestProgram::createVoice(double time, uint8_t note, float velocity)
{
    return new TestVoice(time, note, velocity);
}