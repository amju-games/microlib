#pragma once

#include <string>
#include "sound_player.h"

class sound_player_bass23 : public sound_player
{
public:
  sound_player_bass23();
  ~sound_player_bass23();

  bool play_wav(const std::string& wavFile, bool loop = false) override;
  bool play_song(const std::string& songFile) override;
  void stop_song() override;
  void update() override;
  void set_song_max_volume(float) override;

private:
  // Channel for current song
  unsigned long m_chan;
};

