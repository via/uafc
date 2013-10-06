#include "uafc.h"
#include "shell.h"
#include "history.h"

static struct sensors history[HISTORY_LENGTH];
static unsigned int write_i = 0;
static unsigned int read_i = 0;
static unsigned int volatile dumping = 0;

static int history_read(struct sensors *s) {
  if (write_i == read_i)  /* Empty condition */
    return 0;

  *s = history[read_i];
  read_i = (read_i + 1) % HISTORY_LENGTH;
  return 1;
}

void history_dump() {
  dumping = 1;
  struct sensors s;
  while (history_read(&s)) {
    shell_dump_sensors(&s); 
  } 
  dumping = 0;
}


void history_append(struct sensors *s) {
  if (!dumping) {
    history[write_i] = *s;
    write_i = (write_i + 1) % HISTORY_LENGTH;
  }

}
