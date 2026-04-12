#ifndef MUSIC_H
#define MUSIC_H

#include <stdbool.h>

void music_init(void);
bool music_set_track(const char *path);
void music_update(void);

#endif
