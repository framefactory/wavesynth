/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _WAVESYNTH_ENGINE_H
#define _WAVESYNTH_ENGINE_H

#include "app.h"
#include "RenderContext.h"
#include "RenderBuffer.h"
#include "OutBuffer.h"
#include "Program.h"

#include "media/AudioOut.h"
#include "net/MidiListener.h"

F_BEGIN_NAMESPACE

class Engine : public MidiListener
{
public:
    Engine(size_t bufferSize = 512);

    void render(AudioOut* pOut);

    void setSampleRate(size_t sampleRate);

    virtual void onMidiMessage(const MidiMessage& message);
    virtual void onSysEx(const std::string& sysEx);
    virtual void onRPN(uint16_t param, uint16_t value);
    virtual void onNRPN(uint16_t param, uint16_t value);  

private:
    RenderContext _context;
    RenderBuffer _buffer;
    OutBuffer _outBuffer;
    Program* _programs[16];
};

F_END_NAMESPACE

#endif // _WAVESYNTH_ENGINE_H