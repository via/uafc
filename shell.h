#ifndef _SHELL_H
#define _SHELL_H

#define TYPEBUFSIZE 256

typedef enum {
  SHELLSTATE_PROMPT,
  SHELLSTATE_TABLE_READ  
} shellstate;

struct shell {
  shellstate state;
};

void shell_init(struct shell *);
void shell_writebyte(struct shell *, unsigned char b);
void shell_run(struct shell *s);
void shell_dump_sensors(struct sensors *);

#endif

