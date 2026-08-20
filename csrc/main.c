#include "npc.h"
#include "monitor/monitor.h"
#include "sdb/sdb.h"

int main(int argc, char *argv[]) {
  npc_init(argc, argv);
  init_monitor(argc, argv);
  sdb_mainloop();
  npc_finish();
  return 0;
}
