#ifndef TRACK_H
#define TRACK_H

#include <string>
#include <vector>
#include <memory>

#include <AudioCore.h>

class Track {
  public:
    Track(std::string name);
    ~Track();

    void start();
    void stop();

  private:
    std::string m_name;
    AudioCore* m_core;
    bool m_isRecording;
};

#endif // TRACK_H