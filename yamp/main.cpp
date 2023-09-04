#include "yampplayer.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[])
{

	YAMP::PlaybackOptions options = YAMP::PlaybackOptions::fromArguments(argc, argv);
	
	try
	{
		YAMP::YAMPPlayer yamp(options);

		// Print some info
		std::cout << "Filename........: " <<
			std::filesystem::path(options.file).filename().string() << std::endl;
		std::cout << "Title...........: " <<
			yamp.getMetadata("title") << std::endl;
		std::cout << "Artist..........: " <<
			yamp.getMetadata("artist") << std::endl;
		std::cout << "Type............: " <<
			yamp.getMetadata("type_long") << std::endl;
		std::cout << "Duration........: " <<
			yamp.getDuration() << std::endl;
		std::cout << "# of Channels...: " <<
			yamp.getNumOf("channels") << std::endl;
		std::cout << "# of Instruments: " <<
			yamp.getNumOf("instruments") << std::endl;
		std::cout << "# of Patterns...: " <<
			yamp.getNumOf("patterns") << std::endl;
		std::cout << "# of Samples....: " <<
			yamp.getNumOf("samples") << std::endl;

		yamp.play();

		while (true) 
		{
			if (yamp.hasFinished())
			{
				break;
			}
			// ui.render();
		}
	}
	catch (std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
	}
	
	
	return 0;
}
