#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <jack/jack.h>
#include <vector>
#include <unordered_map>
#include <callbacks/audio_callback.h>

struct AudioEngineConfig {
  int bufferSize;
  int sampleRate;
};

class AudioEngine {
  public:
    AudioEngine();
    ~AudioEngine();
    
    void start();
    void stop();

    // Let's make process callback with another class
    void processCallback(AudioCallback* callback);

    jack_port_t* m_inputPort;
    jack_port_t* m_outputPort;

    std::vector<std::string> queryBufferSizes();
    std::vector<std::string> querySampleRates();

    void setBufferSize(int size);
    void setSampleRate(int rate);

  private:
    jack_client_t* m_client;
    int m_bufferSize = 512;
    int m_sampleRate = 44100;
};

#endif // AUDIOENGINE_H
