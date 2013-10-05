#ifndef _HISTORY_H
#define _HISTORY_H

#define HISTORY_LENGTH 720000

void history_append(struct sensors *h);
void history_dump();

#endif

