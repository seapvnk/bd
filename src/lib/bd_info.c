#define MSG_VERSION "brainduck - version 2.0.2"
#define BD_LOGO \
"  _____ _____ _____ _____ _____ ____  _____ _____ _____  \n\
 | __  | __  |  _  |     |   | |    \\|  |  |     |  |  |\n\
 | __ -|    -|     |-   -| | | |  |  |  |  |   --|    -|\n\
 |_____|__|__|__|__|_____|_|___|____/|_____|_____|__|__|"



void show_info_msg()
{
  puts(BD_LOGO);
  puts(MSG_VERSION);
  puts("usage: ./bd file.bd");
  puts("flags:");
  puts("\tversion : --version or -v");
  puts("\tmemory info: -d");

}

