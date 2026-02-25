#ifndef FRAMES_H

#define FRAMES_H

char get_physical_frame(int frame_number, int offset);
int allocate_physical_frame(int virtual_frame_number, char **value);

#endif