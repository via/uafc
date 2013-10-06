#include <stdio.h>
#include <string.h>

#include "uafc.h"
#include "shell.h"
#include "history.h"
#include "tables.h"

static void
showprompt() {
  printf("uafc> ");
  fflush(stdout);
}

void 
shell_init(struct shell *s) {
  s->state = SHELLSTATE_PROMPT;
}

void shell_dump_sensors(struct sensors *s) {
  printf("RPM: %d\tAFM: %d\tTPS: %f\tAFR: %f\r\n",
    s->rpm, s->afm, s->throttle, s->afr);
}

void shell_run(struct shell *s)  {

  char cmd[128];
  struct sensors *i;

  switch (s->state) {
  case SHELLSTATE_PROMPT:
    showprompt();
    scanf("%s", cmd);
    printf("recvd %s\r\n", cmd);

    switch (cmd[0]) {
    case 'i':
      i = get_sensors();
      shell_dump_sensors(i);
      break;
    case 'd':
      history_dump();
      break;
    case 'p':
      /* Placeholder to dump fuel table */
      break;
    case 'r':
      /* Placeholder to read in new fuel table */
      s->state = SHELLSTATE_TABLE_READ;
      break;
    case 'w':
      /* Placeholder to write fuel table to flash */
      break;
    case 'n':
      /* Placeholder to reload fuel table from flash */
      break;
    case '?':
      printf("uafc 0.0\r\n");
      printf(" i\tDump current sensors to uart\r\n");
      printf("d\tDump sensor history to uart\r\n");
      printf("p\tDump fuel table to uart\r\n");
      printf("r\tRead fuel table from uart\r\n");
      printf("w\tWrite fuel table to flash memory\r\n");
      printf("n\tReload fuel table from flash memory\r\n");
      printf("\r\n");
      break; 
    default:
     break;
    }
    break;
  case SHELLSTATE_TABLE_READ:
    /* Write this line to fuel table */
    break;
  }

  

}

