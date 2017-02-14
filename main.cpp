
#include "header.h"

#include "Bullet.h"
#include "PlayerCharacter.h"
#include "EnemyGrid.h"
#include "EnemyCharacter.h"

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

	GameInput input = {};
	GameInput *playerInput = &input;

    // ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

    // ALLEGRO_BITMAP *buffer = al_create_bitmap(448,518);
    ALLEGRO_BITMAP *spriteShip = al_load_bitmap("Recursos/nave.bmp");
	ALLEGRO_BITMAP *spriteEnemy = al_load_bitmap("Recursos/enemigos.bmp");
    // ALLEGRO_BITMAP *portada = al_load_bitmap("Recursos/portada.bmp");
    ALLEGRO_BITMAP *background = al_load_bitmap("Recursos/fondo.bmp");
    // ALLEGRO_BITMAP *shields = al_load_bitmap("Recursos/escudos.bmp");
    // ALLEGRO_BITMAP *game_over = al_load_bitmap("Recursos/GameOver.bmp");
	ALLEGRO_BITMAP *spriteBullet = al_load_bitmap("Recursos/bala.bmp");
	
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
	
	// TODO: DESCOMENTAR!!!!!
    //al_play_sample_instance(songInstance);

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

	PlayerCharacter *player = new PlayerCharacter(spriteShip, startingPos, playerBounds);
	//EnemyCharacter **enemyGrid = new EnemyCharacter*;

	Bounds enemyBounds = {};
	enemyBounds.w = ENEMY_WIDTH;
	enemyBounds.h = ENEMY_HEIGHT;

	Point enemyPos = {};
	enemyPos.x = ENEMY_GRID_STARTING_X;
	enemyPos.y = ENEMY_GRID_STARTING_Y;
	
	EnemyGrid *enemyGrid = new EnemyGrid(ENEMY_GRID_WIDTH, ENEMY_GRID_HEIGHT, spriteEnemy);
/*
	EnemyCharacter *firstEnemyRow[5] = {
		new EnemyCharacter(spriteEnemy, enemyPos, enemyBounds),
		new EnemyCharacter(spriteEnemy, enemyPos, enemyBounds),
		new EnemyCharacter(spriteEnemy, enemyPos, enemyBounds),
		new EnemyCharacter(spriteEnemy, enemyPos, enemyBounds),
		new EnemyCharacter(spriteEnemy, enemyPos, enemyBounds)
	};
	

	(firstEnemyRow[1])->setPos(ENEMY_GRID_STARTING_X + (ENEMY_SPACING_H + ENEMY_WIDTH), ENEMY_GRID_STARTING_Y);
	(firstEnemyRow[2])->setPos(ENEMY_GRID_STARTING_X + (ENEMY_SPACING_H + ENEMY_WIDTH) * 2, ENEMY_GRID_STARTING_Y);
	(firstEnemyRow[3])->setPos(ENEMY_GRID_STARTING_X + (ENEMY_SPACING_H + ENEMY_WIDTH) * 3, ENEMY_GRID_STARTING_Y);
	(firstEnemyRow[4])->setPos(ENEMY_GRID_STARTING_X + (ENEMY_SPACING_H + ENEMY_WIDTH) * 3, ENEMY_GRID_STARTING_Y);
	*/
	/*
	for (int i = 0; i < ENEMY_GRID_HEIGHT; i++) {
		Point enemyPos = {};
		enemyPos.y = ENEMY_GRID_STARTING_Y + i * (ENEMY_SPACING_V + ENEMY_HEIGHT);

		for (int j = 0; j < ENEMY_GRID_WIDTH; j++) {
			enemyPos.x = ENEMY_GRID_STARTING_X + j * (ENEMY_SPACING_H + ENEMY_WIDTH);

			EnemyCharacter *enemyShip = new EnemyCharacter(spriteEnemy, enemyPos, enemyBounds);
			enemyGrid[i][j] = enemyShip;
		}
	}
	*/

    al_convert_mask_to_alpha(background, al_map_rgb(255, 0 , 255));  //HACE INVISIBLE EL COLOR MAGENTA
    //al_draw_bitmap(background,0,0,0);

   /* GAME ROUTINE */
    while(!doexit){
        bool redraw = false;
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

		// TODO: Agregar tope de FPS
			// Fin de procesamiento de eventos
			// Procesar el input
			player->processInput(playerInput);
			player->updatePosition();
			enemyGrid->updatePosition();

			// Limite para que la nave del jugador no pueda salir de la pantalla
			if (player->getPos().x < SCREEN_LEFT || player->getPos().x + player->getBounds().w > SCREEN_RIGHT) {
				player->resetPosition();
			}

			// Chequeo de colisiones
			//player->chequeoColisiones()

			// Dibujado
			if (redraw) {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(background, 0, 0, 0);
				player->draw();

				enemyGrid->draw();
				enemyGrid->debugDraw();

				al_flip_display(); //si no se ve blanco
			}

    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_bitmap(spriteShip);
	al_destroy_bitmap(spriteEnemy);
	al_destroy_bitmap(spriteBullet);
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
