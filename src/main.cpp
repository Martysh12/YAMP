#include "yampplayer.h"

#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " FILE" << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	if (!file.is_open())
	{
		std::cout << "Couldn't open file " << std::quoted(argv[1]) << "." << std::endl;
	}

	YAMP::YAMPOptions options = YAMP::YAMPOptions::createDefault();
	YAMP::YAMPPlayer yamp(file, options);

	yamp.play();

	while (true) 
	{
		// ui.render();
	}
	
	return 0;
}

// #include "args.h"
// #include "ui.h"

// #include <libopenmpt/libopenmpt.h>
// #include <pulse/simple.h>

// #include <limits.h>
// #include <stdlib.h>
// #include <stdio.h>

// #define BUF_SIZE 4096

// openmpt_module* openMPTFile;

// int main(int argc, char *argv[])
// {
// 	ParsedArgs* args = parseArguments(argc, argv);

// 	if (args == NULL) // This shouldn't happen under normal circumstances, but
// 		return 1; // just to be sure...

// 	FILE* file = fopen(args->file, "rb");
	
// 	if (file == NULL)
// 	{
// 		printf("Couldn't open %s. Is the path valid?\n", args->file);
// 		return 1;
// 	}
	
// 	fseek(file, 0, SEEK_END);
// 	int fileSize = ftell(file);
// 	fseek(file, 0, SEEK_SET);
	
// 	char* fileContents = (char*) malloc(fileSize);
// 	fread(fileContents, fileSize, 1, file);

// 	fclose(file);

// 	//ModPlug_Settings settings;

// 	//settings.mResamplingMode = MODPLUG_RESAMPLE_FIR;
// 	//settings.mChannels = 2;
// 	//settings.mBits = 16;
// 	//settings.mFrequency = args->sampleRate;

// 	//ModPlug_SetSettings(&settings);

// 	pa_simple* s;
// 	pa_sample_spec ss;

// 	ss.format = PA_SAMPLE_FLOAT32NE;
// 	ss.channels = 2;
// 	ss.rate = args->sampleRate;

// 	s = pa_simple_new(
// 			NULL,
// 			"YAMP",
// 			PA_STREAM_PLAYBACK,
// 			NULL,
// 			"Music",
// 			&ss,
// 			NULL,
// 			NULL,
// 			NULL
// 	);

// 	if (s == NULL)
// 	{
// 		puts("Couldn't open playback stream.\n");
// 		return 1;
// 	}
	
// 	openMPTFile = openmpt_module_create_from_memory2(fileContents, fileSize, NULL, NULL, NULL, NULL, NULL, NULL, NULL);    
// 	float audioBuffer[BUF_SIZE * 2];
// 	int mLen;
	
// 	//ModPlug_SetMasterVolume(openMPTFile, args->volume);

// 	// Print some info

// 	printf("Filename........: %s\n", args->file);

// 	const char* song_title = openmpt_module_get_metadata(openMPTFile, "title");
// 	printf("Song Name.......: %s\n", song_title);
// 	openmpt_free_string(song_title);

// 	printf("Duration........: %g\n", openmpt_module_get_duration_seconds(openMPTFile));
// 	printf("# of Instruments: %d\n", openmpt_module_get_num_instruments(openMPTFile));
// 	printf("# of Samples....: %d\n", openmpt_module_get_num_samples(openMPTFile));
// 	printf("# of Patterns...: %d\n", openmpt_module_get_num_patterns(openMPTFile));
// 	printf("# of Channels...: %d\n", openmpt_module_get_num_channels(openMPTFile));
	
// 	if (args->useUi)
// 		initUI();

// 	bool stop = false;

// 	bool is_paused = false;
	
// 	//int j;
// 	int return_value = 0;
// 	int ui_frame = 0;

// 	for (unsigned int i = 0; i < (args->loops >= 0 ? args->loops + 1 : UINT_MAX); ++i)
// 	{
// 		openmpt_module_set_position_seconds(openMPTFile, 0.0);

// 		//j = 0;

// 		while (true)
// 		{
// 			if (!is_paused)
// 			{
// 				mLen = openmpt_module_read_interleaved_float_stereo(openMPTFile, args->sampleRate, BUF_SIZE, audioBuffer);
// 				if (!mLen)
// 					break;
// 			}

// 			if (args->useUi)
// 			{
// 				//if (j % 2 == 0)
// 				//{
// 				return_value = drawUI(args, openMPTFile, ui_frame++, fileSize);

// 				switch (return_value)
// 				{
// 					case 1:
// 						stop = true;
// 						break;
// 					case 2:
// 						is_paused = !is_paused;
// 						break;
// 				}
// 				//}
// 			}

// 			if (stop)
// 				break;

// 			if (!is_paused)
// 			{
// 				// I do not know why do I need to multiply this by 8,
// 				// and I do not want to know. All I know is that it
// 				// actually works.
// 				pa_simple_write(s, audioBuffer, mLen * 8, NULL);
// 			}
// 			else
// 			{
// 				sleep(1); // FML
// 			}

// 			//j++;
// 		}

// 		if (stop)
// 			break;
// 	}

// 	if (args->useUi)
// 		stopUI();
	
// 	openmpt_module_destroy(openMPTFile);

// 	return 0;
// }
