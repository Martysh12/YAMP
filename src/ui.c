#include "ui.h"

int compact_mode = 0;

void getNoteStringFromValue(char* s, int note)
{
	int o;
	int n;

	switch (note)
	{
		case 0:   strcpy(s, " - "); break;
		case 255: strcpy(s, "==="); break;

		default:
			o = (note / 12) % 10;
			n = (note - 1) % 12;

			switch (n)
			{
				case 0:
					strcpy(s, "C- ");
					break;
				case 1:
					strcpy(s, "C# ");
					break;
				case 2:
					strcpy(s, "D- ");
					break;
				case 3:
					strcpy(s, "D# ");
					break;
				case 4:
					strcpy(s, "E- ");
					break;
				case 5:
					strcpy(s, "F- ");
					break;
				case 6:
					strcpy(s, "F# ");
					break;
				case 7:
					strcpy(s, "G- ");
					break;
				case 8:
					strcpy(s, "G# ");
					break;
				case 9:
					strcpy(s, "A- ");
					break;
				case 10:
					strcpy(s, "A# ");
					break;
				case 11:
					strcpy(s, "B- ");
					break;
				
				//default: // useless lmaoooo
				//	strcpy(s, "?- ");
				//	break;
			}

			sprintf(&s[2], "%d", o);

			break;
	}
}

void getInstStringFromValue(char* s, int inst)
{
	if (inst == 0)
	{
		strcpy(s, "- ");
		return;
	}

	sprintf(s, "%02d", inst % 100);
}

void getTimeStringFromSeconds(char* s, double val)
{
	int seconds = (int) val;
	int minutes = seconds / 60;
	int hours   = (minutes / 60) % 100;
	
	seconds %= 60;
	minutes %= 60;

	sprintf(s, "%02d:%02d:%02d", hours, minutes, seconds);
}

double clamp(double val, double min, double max)
{
	return val < min ? min : (val > max ? max : val);
}

void getReadableFS(int size, char* buf)
{
	int i = 0;
	double new_size = size;

	char* units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};

	while (new_size > 1024)
	{
		new_size /= 1024;
		i++;
	}

	sprintf(buf, "%.2f %s", new_size, units[i]);
}

void initUI(void)
{
	compact_mode = 0;

	initscr();
	curs_set(0);
	nodelay(stdscr, true);
	noecho();
	cbreak();
}

int drawUI(ParsedArgs* args, openmpt_module* file, int frame, int file_size)
{
	clear();

	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	
	int h_center = cols / 2;
	//int v_center = rows / 2;
	
	const char* song_title = openmpt_module_get_metadata(file, "title");
	const char* song_author = openmpt_module_get_metadata(file, "artist");
	const char* song_type = openmpt_module_get_metadata(file, "type_long");
	const char* song_tracker = openmpt_module_get_metadata(file, "tracker");
	const char* song_date = openmpt_module_get_metadata(file, "date");

	int i = rows - 1;
	
	mvprintw(i--, 0, "# of Channels...: %d\n", openmpt_module_get_num_channels(file));
	mvprintw(i--, 0, "# of Patterns...: %d\n", openmpt_module_get_num_patterns(file));
	mvprintw(i--, 0, "# of Samples....: %d\n", openmpt_module_get_num_samples(file));
	mvprintw(i--, 0, "# of Instruments: %d\n", openmpt_module_get_num_instruments(file));
	mvprintw(i--, 0, "Duration........: %g\n", openmpt_module_get_duration_seconds(file));
	mvprintw(i--, 0, "Song Name.......: %s\n", song_title);

	mvprintw(i--, 0, "Filename........: %s\n", basename(args->file));

	int cur_pattern = openmpt_module_get_current_pattern(file);
	unsigned int cur_row = openmpt_module_get_current_row(file);

	int num_channels = openmpt_module_get_num_channels(file);
	unsigned int num_rows = openmpt_module_get_pattern_num_rows(file, cur_pattern);

	int max_y = i;

	double pos_seconds = openmpt_module_get_position_seconds(file);
	double dur_seconds = openmpt_module_get_duration_seconds(file);

	char buf_position[9];
	char buf_duration[9];
	
	mvprintw(++i, h_center, "Current Pattern.: %d", cur_pattern);
	mvprintw(++i, h_center, "Current Row.....: %d", cur_row);
	mvprintw(++i, h_center, "Channels Playing: %d", openmpt_module_get_current_playing_channels(file));

	getTimeStringFromSeconds(buf_position, pos_seconds);
	getTimeStringFromSeconds(buf_duration, dur_seconds);

	mvprintw(++i, h_center, "Progress........: %s/%s (%.1f%%)", buf_position, buf_duration, (pos_seconds / dur_seconds) * 100);

	// Drawing the pattern
	
	attron(A_UNDERLINE);
	mvprintw(max_y - 1, 0, "%*s", cols, "");
	attroff(A_UNDERLINE);
	
	int y;

	int v_center_accurate = (max_y) / 2;

	int note;
	char note_buf[4];

	int instrument;
	char instrument_buf[3];
	
	for (unsigned int row = 0; row < num_rows; row++)
	{
		// Calculate desired Y position
		y = row - cur_row + v_center_accurate;

		if (y <= max_y - 1 && y > 0)
		{

			if (row == cur_row)
				attron(A_STANDOUT);
			
			if (y == max_y - 1)
				attron(A_UNDERLINE);

			for (int chn = 0; chn < num_channels; chn++)
			{
				note = openmpt_module_get_pattern_row_channel_command(file, cur_pattern, row, chn, OPENMPT_MODULE_COMMAND_NOTE);
				instrument = openmpt_module_get_pattern_row_channel_command(file, cur_pattern, row, chn, OPENMPT_MODULE_COMMAND_INSTRUMENT);

				getNoteStringFromValue(note_buf, note);
				getInstStringFromValue(instrument_buf, instrument);

				switch (compact_mode)
				{
					case 0:
						mvprintw(y, chn * 4, "%s ", note_buf);
						break;
					case 1:
						mvprintw(y, chn * 8, "%s %s  ", note_buf, instrument_buf);
						break;
				}
			}


			if (row == cur_row)
				attroff(A_STANDOUT);

			if (y == max_y - 1)
				attroff(A_UNDERLINE);
		}
	}

	attron(A_STANDOUT);

	mvprintw(0, 0, "%*s", cols, "");

	int current_state = (frame / 64) % 6;

	char s[1024]; // XXX: very unsafe and stupid
	char buf[20]; // this too
	
	int chars_wrote;

	switch (current_state)
	{
		case 0:
			chars_wrote = sprintf(s, "currently playing: %s", song_title);
			break;
		case 1:
			chars_wrote = sprintf(s, "artist: %s", song_author);
			break;
		case 2:
			chars_wrote = sprintf(s, "module type: %s", song_type);
			break;
		case 3:
			chars_wrote = sprintf(s, "tracker: %s", song_tracker);
			break;
		case 4:
			chars_wrote = sprintf(s, "last saved: %s", song_date);
			break;
		case 5:
			getReadableFS(file_size, buf);
			chars_wrote = sprintf(s, "module size: %s", buf);
			break;
	}

	mvprintw(0, (cols - chars_wrote) / 2, "%s", s);

	attroff(A_STANDOUT);

	openmpt_free_string(song_title);
	openmpt_free_string(song_author);
	openmpt_free_string(song_type);
	openmpt_free_string(song_tracker);
	openmpt_free_string(song_date);

	int c = getch();

	int return_val = 0;

	switch (c)
	{
		case 'q':
			return_val = 1;
			break;

		case 'a':
			compact_mode = 0;
			break;
		case 's':
			compact_mode = 1;
			break;

		case 'k':
			openmpt_module_set_position_seconds(file, clamp(pos_seconds - 5, 0, dur_seconds));
			break;
		case 'l':
			openmpt_module_set_position_seconds(file, clamp(pos_seconds + 5, 0, dur_seconds));
			break;
		case ' ':
			return_val = 2;
			break;
	}

	refresh();

	return return_val;
}

void stopUI(void)
{
	endwin();
}

