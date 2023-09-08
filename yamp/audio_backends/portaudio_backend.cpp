#include "../backend.h"

#include <portaudio.h>

#include <stdexcept>

namespace YAMP {
	struct PortAudioState : public YAMP::AudioState {
		PaStream* stream;
	};
};

static int yampPaCallback(const void* input, void* output, unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
	YAMP::Player* player = reinterpret_cast<YAMP::Player *>(userData);

	(void) input;
	(void) timeInfo;
	(void) statusFlags;

	if (player->getHasFinished())
		return 0;

	player->readNextSamples(frameCount, reinterpret_cast<float *>(output));

	return 0;
}

static void checkPaError(PaError err) {
	if (err != paNoError) {
		throw std::runtime_error(std::string{"PortAudio error: "} + Pa_GetErrorText(err));
	}
}

YAMP::AudioBackend::AudioBackend(Player* player) : player(player) {
	checkPaError(Pa_Initialize());

	YAMP::AudioBackend::state = new YAMP::PortAudioState();
	checkPaError(Pa_OpenDefaultStream(
		&dynamic_cast<YAMP::PortAudioState *>(YAMP::AudioBackend::state)->stream,
		0,
		player->options.channels,
		paFloat32,
		player->options.sampleRate,
		paFramesPerBufferUnspecified,
		yampPaCallback,
		player
	));
}

YAMP::AudioBackend::~AudioBackend() {
	this->stop();
	checkPaError(Pa_CloseStream(dynamic_cast<YAMP::PortAudioState *>(YAMP::AudioBackend::state)->stream));
	checkPaError(Pa_Terminate());
}

void YAMP::AudioBackend::start() {
	checkPaError(Pa_StartStream(dynamic_cast<YAMP::PortAudioState *>(YAMP::AudioBackend::state)->stream));
}

void YAMP::AudioBackend::stop() {
	checkPaError(Pa_StopStream(dynamic_cast<YAMP::PortAudioState *>(YAMP::AudioBackend::state)->stream));
}
