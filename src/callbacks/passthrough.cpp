#include <callbacks/passthrough.h>

void Passthrough::process(jack_nframes_t nframes, void* arg) {
  std::cout << "Passthrough callback" << std::endl;
  AudioEngine* engine = (AudioEngine*) arg;
  if (engine == NULL) {
    std::cerr << "Engine is NULL" << std::endl;
    return;
  }

  jack_default_audio_sample_t* in = (jack_default_audio_sample_t*)jack_port_get_buffer(engine->m_inputPort, nframes);
  jack_default_audio_sample_t* out = (jack_default_audio_sample_t*)jack_port_get_buffer(engine->m_outputPort, nframes);

  for (int i = 0; i < nframes; i++) {
    out[i] = in[i];
    std::cout << "In: " << in[i] << " Out: " << out[i] << std::endl;
  }
}