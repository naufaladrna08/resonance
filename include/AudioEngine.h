#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <jack/jack.h>
#include <Callbacks/AudioCallback.h>

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

  private:
    jack_client_t* m_client;
};

#endif // AUDIOENGINE_H
