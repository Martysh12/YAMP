#pragma once

#include "playbackoptions.h"
#include "player.h"

#include <memory>

namespace YAMP {
	class Player;

	struct AudioState {
		virtual ~AudioState() = default;
	};

	class AudioBackend {
		Player* player;
		AudioState* state;
	public:
		AudioBackend(Player* player);
		~AudioBackend();
		void start();
		void stop();
	};
};
