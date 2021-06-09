/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_WAVE_ENGINETASK_H
#define _ESP_WAVE_ENGINETASK_H

#include "app.h"
#include "Engine.h"
#include "core/Task.h"
#include "media/AudioOut.h"
#include "net/BLEMidi.h"

F_BEGIN_NAMESPACE

class EngineTask : Task
{
public:
    EngineTask();

protected:
    void run() override;

private:
    AudioOut _audioOut;
    BLEMidi _midiPort;
    Engine _engine;
};

F_END_NAMESPACE

#endif // _ESP_WAVE_ENGINETASK_H