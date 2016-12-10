#include "view.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>

const float FPS = 60;

/* ALLEGRO STARTUP FUNCTIONS */

bool allegro_start(int WIDTH_ , int HEIGHT_, ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer){



    /* LOAD IMAGES */


    /* START KEYBOARD */





    return true;

}



/* START AUDIO */

void start_audio(){

    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
    }

    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
    }

    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
    }
}

void load_music(){

}

