/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _WAVESYNTH_PROGRAM_H
#define _WAVESYNTH_PROGRAM_H

#include "app.h"
#include "RenderContext.h"
#include "RenderBuffer.h"
#include "net/MidiMessage.h"

#include <list>

F_BEGIN_NAMESPACE

class Voice
{
public:
    Voice(double time, uint8_t note, float velocity);

    uint8_t note;
    float velocity;

    double startTime;
    double releaseTime;

    bool isActive;
    bool isHeld;
};

class Program
{
public:
    Program();
    virtual ~Program();

    virtual void render(const RenderContext& context, const RenderBuffer& buffer);

    void dispatchMidiMessage(double time, const MidiMessage& message);

    void startNote(double time, uint8_t note, float velocity);
    void releaseNote(double time, uint8_t note, float velocity);
    void enableHold(double time, bool enabled);

    bool holdEnabled() const { return _holdEnabled; }

protected:
    virtual bool renderVoice(const RenderContext& context, const RenderBuffer& buffer, Voice* pVoice) = 0;
    virtual Voice* createVoice(double time, uint8_t note, float velocity) = 0;

private:
    typedef std::list<Voice*> voiceList_t;
    voiceList_t _voices;

    bool _holdEnabled;
};

F_END_NAMESPACE

#endif // _WAVESYNTH_PROGRAM_H