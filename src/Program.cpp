/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Program.h"
#include "net/MidiController.h"

F_USE_NAMESPACE

Voice::Voice(double time, uint8_t _note, float _velocity) :
    note(_note),
    velocity(_velocity),
    startTime(time),
    isActive(true),
    isHeld(false)
{        
}

Program::Program()
{
}

Program::~Program()
{
    for (auto it = _voices.begin(); it != _voices.end(); ++it) {
        delete *it;
    }
}

void Program::render(const RenderContext& context, const RenderBuffer& buffer)
{
    auto it = _voices.begin();
    while (it != _voices.end()) {
        auto pVoice = *it;
        if (renderVoice(context, buffer, pVoice)) {
            ++it;
        }
        else {
            it = _voices.erase(it);
            Serial.printf("[Program] voice terminated, note %d - voices running: %d\n", pVoice->note, _voices.size());
            delete pVoice;
        }
    }
}

void Program::dispatchMidiMessage(double time, const MidiMessage& message)
{
    if (message.isChannelMessage()) {
        uint8_t status = message.status();

        switch(status) {
            case MidiStatus::NoteOn:
                startNote(time, message.note(), message.velocity() / 127.0f);
                break;

            case MidiStatus::NoteOff:
                releaseNote(time, message.note(), message.velocity() / 127.0f);
                break;

            case MidiStatus::ControlChange:
                uint8_t controller = message.controller();
                uint8_t value = message.value();
                if (controller == MidiController::SustainPedalSwitch) {
                    enableHold(time, value > 64);
                }
                break;
        }
    }
}

void Program::startNote(double time, uint8_t note, float velocity)
{
    _voices.push_back(createVoice(time, note, velocity));
    //Serial.printf("[Program] voice created, note %d, velocity %f - running voices: %d\n", note, velocity, _voices.size());
}

void Program::releaseNote(double time, uint8_t note, float velocity)
{
    for (auto it = _voices.begin(); it != _voices.end(); ++it) {
        auto pVoice = *it;
        if (pVoice->note == note && pVoice->isActive) {
            if (_holdEnabled) {
                pVoice->isHeld = true;
            }
            else {
                pVoice->isActive = false;
                pVoice->isHeld = false;
                pVoice->releaseTime = time;
            }
        }
    }
}

void Program::enableHold(double time, bool enabled)
{
    if (enabled != _holdEnabled) {
        _holdEnabled = enabled;

        if (!enabled) {
            for (auto it = _voices.begin(); it != _voices.end(); ++it) {
                auto pVoice = *it;
                if (pVoice->isHeld) {
                    pVoice->isActive = false;
                    pVoice->isHeld = false;
                    pVoice->releaseTime = time;
                }
            }
        }
    }
}
