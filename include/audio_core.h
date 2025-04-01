#define AUDIOCORE_H
#define AUDIOCORE_H

#include <audio_engine.h>
#include <jack/jack.h>

class AudioCore {
  public:
    AudioCore();
    ~AudioCore();

    void start();
    void stop();

    void process(jack_nframes_t nframes, void* arg);

  private:
    jack_client_t* m_client;
    jack_port_t* m_inputPort;
    jack_port_t* m_outputPort;
};