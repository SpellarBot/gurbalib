#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("Tunnel");
   set_long("In the tunnel into the mines.");

   add_exit("east", DIR + "/rooms/mine/tunnel9.c");
   add_exit("west", DIR + "/rooms/mine/tunnel11.c");
}
