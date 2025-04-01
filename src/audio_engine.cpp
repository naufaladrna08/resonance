#include "audio_engine.h"
#include <iostream>

AudioEngine::AudioEngine() {
  m_client = jack_client_open("DAWgong", JackNullOption, NULL);
  if (m_client == NULL) {
    std::cerr << "Failed to initialize JACK client" << std::endl;
    return;
  }

  // m_inputPort = jack_port_register(m_client, "Master/Audio In", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
  // m_outputPort = jack_port_register(m_client, "Master/Audio Out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
}

void AudioEngine::processCallback(AudioCallback* callback) {
}

AudioEngine::~AudioEngine() {
  // jack_client_close(m_client);
}

void AudioEngine::start() {
  if (jack_activate(m_client)) {
    std::cerr << "Failed to activate JACK client" << std::endl;
  }
}

void AudioEngine::stop() {
  jack_deactivate(m_client);
}

std::vector<std::string> AudioEngine::queryBufferSizes() {
  std::vector<std::string> bufferSizes;
  for (int i = 1; i <= 2048; i *= 2) {
    bufferSizes.push_back(std::to_string(i));
  }

  return bufferSizes;
}

std::vector<std::string> AudioEngine::querySampleRates() {
  std::vector<std::string> sampleRates;
  for (int i = 44100; i <= 192000; i += 1000) {
    sampleRates.push_back(std::to_string(i));
  }
  return sampleRates;
}

void AudioEngine::setBufferSize(int size) {
  m_bufferSize = size;
}

void AudioEngine::setSampleRate(int rate) {
  m_sampleRate = rate;
}