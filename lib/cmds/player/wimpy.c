inherit M_COMMAND;

void usage() {
   string *lines;

   lines =({ "Usage: wimpy [-h] [CMD ARG]" });
   lines += ({ "" });
   lines += ({ "The wimpy command allows you to define if and when you " +
      "will run away from a fight." });
   lines += ({ "" });
   lines += ({ "If you give it no parameters print out the current wimpy " +
      "info." });
   lines += ({ "CMDS can be one of the following: on, off, dir, hp" });
   lines += ({ "ARG is only valid for dir and hp." });
   lines += ({ "For dir ARG is a string, if you run you will attempt to " +
      "run to that exit. " });
   lines += ({ "If no ARG is given for dir, clear the default direction." });
   lines += ({ "For hp ARG is an int, if your hp drop below the number " +
      "provided you will run." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twimpy" });
   lines += ({ "\twimpy off" });
   lines += ({ "\twimpy dir north" });
   lines += ({ "\twimpy dir" });
   lines += ({ "\twimpy hp 10" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, cast, eat, enter, follow, go, pray, quit" });

   this_player()->more(lines);
}

static void main(string str) {
   string dir;
   int hp;

   if (empty_str(str)) {
      if (this_player()->query_env("wimpy") == "on") {
         write("Wimpy mode: on\n");
      } else {
         write("Wimpy mode: off\n");
      }

      dir = this_player()->query_env("wimpydir");
      if (!dir) {
         dir = "\"\"";
      }
      write("Wimpy dir: " + dir + "\n");

      hp = this_player()->query_env("wimpyhp");
      if (!hp) {
         hp = 0;
      }
      write("Wimpy hp: " + hp + "\n");
   } else if (sscanf(str, "-%s", str)) {
      usage();
   } else if (str == "dir" || str == "direction") {
      this_player()->set_env("wimpydir", "");
      write("Wimpy dir: unset.\n");
   } else if (sscanf(str, "dir %s", dir) == 1) {
      this_player()->set_env("wimpydir", dir);
      write("Wimpy dir = " + dir + "\n");
   } else if (sscanf(str, "hp %d", hp) == 1) {
      this_player()->set_env("wimpyhp", hp);
      write("Wimpy hp = " + hp + "\n");
   } else if (str == "on") {
      this_player()->set_env("wimpy", "on");
      write("Wimpy mode enabled.\n");
   } else if (str == "off") {
      this_player()->set_env("wimpy", "off");
      write("Wimpy mode disabled.\n");
   } else {
      usage();
   }
}