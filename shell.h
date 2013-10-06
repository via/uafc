#ifndef _SHELL_H
#define _SHELL_H

#define TYPEBUFSIZE 256

typedef enum {
  SHELLSTATE_PROMPT,
  SHELLSTATE_TABLE_READ  
} shellstate;

struct shell {
  char typebuf[TYPEBUFSIZE];
  unsigned short bufpos;
  shellstate state;
  int runnable;
};

void shell_init(struct shell *);
void shell_writebyte(struct shell *, unsigned char b);
void shell_run(struct shell *s);

#endif

