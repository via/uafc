#include "uafc.h"
#include "history.h"

static struct sensors history[HISTORY_LENGTH];
static unsigned int cur_history = 0;

void history_dump() {

}


void history_append(struct sensors *s) {
  history[cur_history] = *s;
  cur_history = (cur_history + 1) % HISTORY_LENGTH;

}
