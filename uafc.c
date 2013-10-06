#include <or1k-support.h>
#include <spr-defs.h>

#include <stdio.h>

#include "uafc.h"
#include "history.h"
#include "shell.h"

#include "board.h"

static struct sensors sensors;
static struct calculated_values cvals __attribute__((unused)) /* for now */;

struct sensors *
get_sensors() {
  return &sensors;
}



static void acquire_inputs() {
#ifdef KVAFM
  sensors.afm = get_kvafm();
#elif MAP
#error MAP Not Implement
#else
#error Air flow source unconfigured
#endif
  sensors.rpm = get_rpm();
  sensors.throttle = get_throttle();
  sensors.afr = get_o2();
#ifdef BARGRAPH
  set_bar(sensors.afm);
#endif
  history_append(&sensors);
}  



static void tick() {
  acquire_inputs();
}


int
main(void) {
  struct shell shell;

  printf("main() enter\r\n");
  shell_init(&shell);
  board_init(tick);

  while (1) {
    shell_run(&shell);
  }

  return 0;
}
