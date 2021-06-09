/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _WAVESYNTH_TESTPROGRAM_H
#define _WAVESYNTH_TESTPROGRAM_H

#include "../app.h"
#include "../Program.h"

F_BEGIN_NAMESPACE

class TestVoice : public Voice
{
public:
    TestVoice(double time, uint8_t note, float velocity);
};

class TestProgram : public Program
{
protected:
    bool renderVoice(const RenderContext& context, const RenderBuffer& buffer, Voice* pVoice) override;
    Voice* createVoice(double time, uint8_t note, float velocity) override;
};

F_END_NAMESPACE

#endif // _WAVESYNTH_TESTPROGRAM_H