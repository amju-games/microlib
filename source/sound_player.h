#pragma once

#include <string>

class sound_player 
{
public:
  virtual ~sound_player() = default;

  virtual bool play_wav(const std::string& wavFile, bool loop = false) = 0;
  virtual bool play_song(const std::string& songFile) = 0;
  virtual void stop_song() = 0;
  virtual void update() = 0;
  virtual void set_song_max_volume(float) = 0;
};

