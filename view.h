#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED
#include <allegro5/allegro.h>

bool allegro_start(int WIDTH_ , int HEIGHT_, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer);
void start_audio();
void load_music();

#endif // INIT_H_INCLUDED
