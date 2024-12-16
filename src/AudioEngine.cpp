#include "AudioEngine.h"
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
