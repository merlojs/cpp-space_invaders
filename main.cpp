
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "header.h"

#include "Character.h"
#include "PlayerCharacter.h"

using namespace std;

enum MOVE_DIR {
    UP, RIGHT, DOWN, LEFT
};

int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool doexit = false;

    /* START ALLEGRO LIBRARY */
   if(!al_init()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
   }

    /* START IMAGE ADD-ON */

   if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return false;
   }

       /* START IMAGE ADD-ON */

   if(!al_init_primitives_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_primitives_addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return false;
   }

    /* CREATE DISPLAY */

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if(!display){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }


    /* KEYBOARD */
    if(!al_install_keyboard()) {
        fprintf(stderr, "Failed to initialize the keyboard!\n");
        return false;
    }

    /* AUDIO */

    if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }

   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }

    GameInput *playerInput;

    // ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

    // ALLEGRO_BITMAP *buffer = al_create_bitmap(448,518);
    ALLEGRO_BITMAP *spriteNave = al_load_bitmap("Recursos/nave.bmp");
    // ALLEGRO_BITMAP *portada = al_load_bitmap("Recursos/portada.bmp");
    ALLEGRO_BITMAP *background = al_load_bitmap("Recursos/fondo.bmp");
    // ALLEGRO_BITMAP *shields = al_load_bitmap("Recursos/escudos.bmp");
    // ALLEGRO_BITMAP *game_over = al_load_bitmap("Recursos/GameOver.bmp");
    ALLEGRO_SAMPLE *song = al_load_sample("Recursos/Retribution.ogg");

    ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

   if(!background) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load background!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }

    /* CREATE TIMER */

    timer = al_create_timer(1.0 / FPS);

    if(!timer) {
      fprintf(stderr, "Failed to create timer!\n");
      return false;
    }

    /* CREATE EVENT QUEUE */

    event_queue = al_create_event_queue();

    if(!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return false;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_play_sample_instance(songInstance);

    /* START TIMER */
    al_start_timer(timer);


    //al_set_target_bitmap(background);
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(0,0,0));

    /* GAME CHARACTERS */
    Bounds playerBounds = {};
    playerBounds.w = 28;
    playerBounds.h = 20;

    Point startingPos = {};
    startingPos.x = SCREEN_WIDTH / 2 - playerBounds.w / 2;
    startingPos.y = SCREEN_HEIGHT - 70;

    PlayerCharacter *player = new PlayerCharacter(spriteNave,  startingPos, playerBounds);

    al_convert_mask_to_alpha(background, al_map_rgb(255, 0 , 255));  //HACE INVISIBLE EL COLOR MAGENTA
    al_draw_bitmap(background,0,0,0);

    al_flip_display(); //si no se ve blanco

   /* GAME ROUTINE */
    while(!doexit){
        bool redraw = true;
        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;   // Wait time for an event to occur
        al_init_timeout(&timeout, 0.06);

        // Procesamiento de eventos
        bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

        if (get_event) {
            if(get_event && ev.type == ALLEGRO_EVENT_TIMER) {
                redraw = true;
            } else if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                doexit = true;
            } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                keyboardEventHandler(true, ev.keyboard.keycode, playerInput);
            } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                keyboardEventHandler(false, ev.keyboard.keycode, playerInput);
            }
        }
        // Fin de procesamiento de eventos
        // Procesar el input
        player->processInput(playerInput);

        // Chequeo de colisiones
        // Dibujado
        if (redraw) {
            player->draw();
        }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_bitmap(spriteNave);
    al_destroy_bitmap(background);
    al_destroy_sample(song);
    al_destroy_sample_instance(songInstance);
    return 0;

}

void keyboardEventHandler(bool keyUp, int keyCode, GameInput *playerInput) {
    if (keyUp){
        if (keyCode == ALLEGRO_KEY_ESCAPE) {
          playerInput->escape = false;
        }

        if (keyCode == ALLEGRO_KEY_UP) {
          playerInput->up = false;
        }

        if (keyCode == ALLEGRO_KEY_DOWN) {
          playerInput->down = false;
        }

        if (keyCode == ALLEGRO_KEY_SPACE) {
          playerInput->action = false;
        }

        if (keyCode == ALLEGRO_KEY_LEFT) {
          playerInput->left = false;
        }

        if (keyCode == ALLEGRO_KEY_RIGHT) {
          playerInput->right = false;
        }
    } else {
        if (keyCode == ALLEGRO_KEY_ESCAPE) {
          playerInput->escape = true;
        }
        if (keyCode == ALLEGRO_KEY_UP) {
          playerInput->up = true;
        }

        if (keyCode == ALLEGRO_KEY_DOWN) {
          playerInput->down = true;
        }

        if (keyCode == ALLEGRO_KEY_SPACE) {
          playerInput->action = true;
        }

        if (keyCode == ALLEGRO_KEY_LEFT) {
          playerInput->left = true;
        }

        if (keyCode == ALLEGRO_KEY_RIGHT) {
          playerInput->right = true;
        }
    }
}
