/**
 * ESP WaveSynth
 * Copyright 2021 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Engine.h"
#include "programs/TestProgram.h"

#include "net/MidiMessage.h"
#include "net/MidiController.h"

F_USE_NAMESPACE

Engine::Engine(size_t bufferSize /* = 512 */) :
    _context(44100),
    _buffer(bufferSize),
    _outBuffer(bufferSize)
{
    for (size_t i = 0; i < 16; ++i) {
        _programs[i] = nullptr;
    }

    _programs[0] = new TestProgram();
}

void Engine::render(AudioOut* pOut)
{
    _buffer.clear();
    _context.time += _buffer.length * 0.5 / double(_context.sampleRate);

    for (size_t i = 0; i < 16; ++i) {
        auto pProgram = _programs[i];
        if (pProgram) {
            pProgram->render(_context, _buffer);
        }
    }

    _outBuffer.copy(_buffer);
    pOut->write(_outBuffer.pData, _outBuffer.length);
}

void Engine::setSampleRate(size_t sampleRate)
{
    _context.sampleRate = sampleRate;
}

void Engine::onMidiMessage(const MidiMessage& message)
{
    for (size_t i = 0; i < 16; ++i) {
        auto pProgram = _programs[i];
        if (pProgram) {
            pProgram->dispatchMidiMessage(_context.time, message);
        }
    }

    //Serial.printf("[Engine] MIDI message: %s\n", message.toString().c_str());
}

void Engine::onSysEx(const std::string& sysEx)
{
    Serial.printf("[Engine] MIDI sysex message\n");
}

void Engine::onRPN(uint16_t param, uint16_t value)
{
    Serial.printf("[Engine] RPN %d, %d\n", param, value);
}

void Engine::onNRPN(uint16_t param, uint16_t value)
{
    Serial.printf("[Engine] NRPN %d, %d\n", param, value);
} 