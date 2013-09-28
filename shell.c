#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "uafc.h"
#include "tables.h"


void 
shell_init(struct shell *s) {
  s->bufpos = 0;
  s->state = SHELLSTATE_PROMPT;
}

void
shell_writebyte(struct shell *s, unsigned char b) {
  s->typebuf[s->bufpos] = b;
  if (s->bufpos == TYPEBUFSIZE - 1) {
    /* buffer fule... don't increment, set error condition */
  } else {
    s->bufpos++;
  }

  if (b == '\n')
    s->runnable = 1;

}


void shell_run(struct shell *s)  {

  char buf[TYPEBUFSIZE];
  struct sensors *i;

  if (!s->runnable) 
    return;
  
  switch (s->state) {
  case SHELLSTATE_PROMPT:
    memcpy(s->typebuf, buf, TYPEBUFSIZE);
    s->bufpos = 0;

    switch (buf[0]) {
    case 'i':
      i = get_sensors();
      printf("RPM: %d\tAFM: %d\tTPS: %f\tAFR: %f",
        i->rpm, i->afm, i->throttle, i->afr);
      break;
    case 'd':
      /* Placeholder to dump recorded history */
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
    default:
     break;
    }
    s->runnable = 0;
    break;
  case SHELLSTATE_TABLE_READ:
    /* Write this line to fuel table */
    break;
  }

  

}

