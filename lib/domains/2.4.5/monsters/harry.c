#include "../domain.h"

inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("harry");
   add_id("fjant");
   set_gender( "male" );
   add_adj("affectionate");
   set_in_room_desc("Harry the affectionate");
   set_long("Harry has an agreeable look.");
   set_race("human");
   set_level(3);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

void notify(string str) {
    query_environment()->tell_room(this_object(), str);
}

// XXX get harry from vill_road2.c  Needs lots of work...
void why_did(string str) {
   string who, what;

   sscanf(str, "%s %s", who, what);
   if(who == "harry" || who == "Harry") return;
   if (sscanf(str, "%s sells %s.", who, what) == 2) {
      notify("Harry says: Why did you sell " + what + "\n");
   }
   if (sscanf(str, "%s attacks %s.", who, what) == 2) {
      notify("Harry says: Why does " + who + " attack " + what + "?\n");
   }
   if (sscanf(str, "%s left the game.", who) == 1) {
      notify("Harry says: Why did " + who + " quit the game ?\n");
   }
   if (sscanf(str, "%s takes %s.\n", who, what) == 2) {
      notify("Harry says: Why did " + who + " take " + what + " ?\n");
   }
   if (sscanf(str, "%s drops %s.\n", who, what) == 2) {
      notify("Harry says: Why did " + who + " drop " + what + " ?\n");
   }
}

void how_does_it_feel(string str) {
   string who, what;
   sscanf(str, "%s %s", who, what);
   if(who == "harry" || who == "Harry") return;
   if (sscanf(str, "%s is now level %s.\n", who, what) == 2) {
      notify("Harry says: How does it feel, being of level " + what + " ?\n");
   }
}

void smiles(string str) {
   string who, what;

   sscanf(str, "%s %s", who, what);
   if (who == "harry" || who == "Harry")
      return;
   if (sscanf(str, "%s smiles happily", who) == 1 &&
      who != "Harry") {
      notify("Harry smiles happily.\n");
   }
}

void say_hello(string str) {
   string who;

   if (sscanf(str, "%s arrives.", who) == 1) {
      notify( "Harry says: Hi " + who + ", nice to see you !\n");
   }
}

void test_say(string str) {
   string a, b, message;

   sscanf(str, "%s %s", a, b);
   if(a == "harry" || a == "Harry") return;
   if (!sscanf(str, "%s says: %s\n", a, b) == 2) return;

   str = b;

   if (str == "hello" || str == "hi" || str == "hello everybody") {
      message = "Harry says: Pleased to meet you!\n";
   }
   if (str == "shut up") {
      message = "Harry says: Why do you want me to shut up ?\n";
   }
   if (sscanf(str, "%sstay here%s", a, b) == 2 ||
      sscanf(str, "%snot follow%s", a, b) == 2 ||
      sscanf(str, "%sget lost%s", a, b) == 2) {

      message = "Harry says: Ok then.\n";
   }
   if(!message) message = "Harry says: Why do you say '" + str + "'???\n";
   notify(message);
}

void follow(string str) {
   string who, where;

   if(sscanf(str, "%s leaves %s.\n", who, where) == 2)
      call_other(this_object(), "init_command", where);
}

void gives(string str) {
   string who, what, whom;
   int rand;
   object obj, next_obj;

   if(sscanf(str, "%s gives %s to %s.\n", who, what, whom) != 3)
      return;
   if(whom != "Harry")
      return;
   if(what == "firebreather" || what == "special" ||
      what == "beer" || what == "bottle") {

      rand = random(4);

      if(rand == 0) {
         if(random(10) > 6) {
            notify("Harry sighs and says: I guess you're gonna kill me now.\n");
// XXX            obj = first_inventory(this_object());
            while(obj) {
// XXX               next_obj = next_inventory(harry);
// XXX               transfer(obj, environment(harry));
               notify("Harry drops " + call_other(obj, "short") + ".\n");
               obj = next_obj;
            }
            call_other(this_object(), "init_command", "west");
         }
      }
      if(rand == 1) {
         call_other(this_object(), "init_command", "drink " + what);
      }
      if(rand == 2) {
// XXX         obj = first_inventory(harry);
// XXX         while(!call_other(obj, "id", what))
// XXX            obj = next_inventory(obj);
// XXX         transfer(obj, environment(harry));
         notify("Harry drops the " + what + ".\n");
      }
      if(rand == 3) {
// XXX         obj = first_inventory(harry);
// XXX         while(!call_other(obj, "id", what))
// XXX            obj = next_inventory(obj);
// XXX         transfer(obj, find_living(lower_case(who)));
         notify("Harry returned the " + what + " to " + who + ".\n");
      }
   } else if(what == "corpse") {
      notify("Harry says: HEY, bury your corpses yourself, asshole.\n");
// XXX      obj = first_inventory(harry);
// XXX      while(!call_other(obj, "id", what))
// XXX         obj = next_inventory(obj);
// XXX      transfer(obj, find_living(lower_case(who)));
      notify("Harry returned the " + what + " to " + who + ".\n");
   } else {
      notify("Harry says: Thank you very much, sir.\n");
   }
}

void monster_died() {
   object obj, b;
   int num;

// XXX   obj = first_inventory(harry);
// XXX   while(obj) {
// XXX      b = next_inventory(harry);
// XXX      if (call_other(obj, "id", "bottle")) {
// XXX         obj->destruct();
// XXX         num = 1;
// XXX      }
// XXX      obj = b;
// XXX   }
   if (num) {
      notify("There is a crushing sound of bottles breaking, " +
      "as the body falls.\n");
   }
}

int down() {
   call_other(this_player(), "move_player", DIR + "/rooms/station");
   return 1;
}
