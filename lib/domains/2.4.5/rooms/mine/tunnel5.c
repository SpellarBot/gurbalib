inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Stone tunnel");
   set_long("In the tunnel into the mines.  There is a big stone table here.");

   add_exit("north","/domains/2.4.5/rooms/tunnel_room.c");
   add_exit("south","/domains/2.4.5/rooms/tunnel4.c");

   add_item("table","You see nothing special about it.");
   add_item("stone table","You see nothing special about it.");
}