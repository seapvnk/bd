#define MSG_VERSION "brainduck - version 2.0.2"

void show_info_msg()
{
  puts(MSG_VERSION);
  puts("usage: ./bd file.bd");
  puts("flags:");
  puts("\tversion : --version or -v");
  puts("\tmemory info: -d");

}

