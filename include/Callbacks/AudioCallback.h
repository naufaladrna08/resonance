#ifndef AUDIOCALLBACK_H
#define AUDIOCALLBACK_H

#include <jack/jack.h>
#include <iostream>

class AudioCallback {
  public:
    virtual void process(jack_nframes_t nframes, void* arg) = 0;
    virtual ~AudioCallback() {}
};

#endif // AUDIOCALLBACK_H