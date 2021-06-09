/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "EngineTask.h"
#include <cmath>

F_USE_NAMESPACE

EngineTask::EngineTask() :
    Task("Engine", CORE_1, portPRIVILEGE_BIT | 1, 65536),
    _audioOut(27, 12, 14),
    _midiPort("ESP WaveSynth"),
    _engine(512)
    {
        _midiPort.setListener(&_engine);
    }

void EngineTask::run()
{
    _audioOut.open();
    _midiPort.begin();

    while(1) {
        _midiPort.dispatch();
        _engine.render(&_audioOut);
    }
}