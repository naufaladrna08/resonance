#ifndef PASSTHROUGH_H
#define PASSTHROUGH_H
#include <audio_engine.h>
#include <callbacks/audio_callback.h>

class Passthrough : public AudioCallback {
  public:
    void process(jack_nframes_t nframes, void* arg) override;
};

#endif 