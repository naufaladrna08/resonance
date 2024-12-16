#ifndef PASSTHROUGH_H
#define PASSTHROUGH_H
#include <AudioEngine.h>
#include <Callbacks/AudioCallback.h>

class Passthrough : public AudioCallback {
  public:
    void process(jack_nframes_t nframes, void* arg) override;
};

#endif 