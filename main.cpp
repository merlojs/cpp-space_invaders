
#include "header.h"

#include "Bullet.h"
#include "PlayerCharacter.h"
#include "EnemyGrid.h"
#include "EnemyCharacter.h"
#include "Marquee.h"


int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

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

	/* FONTS */
	al_init_font_addon();	

	if (!al_init_ttf_addon()) {
		fprintf(stderr, "Failed to initialize the ttf addon!\n");
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


    // ALLEGRO_BITMAP *buffer = al_create_bitmap(448,518);
    ALLEGRO_BITMAP *spriteShip = al_load_bitmap("Recursos/nave.bmp");
	ALLEGRO_BITMAP *spriteEnemy = al_load_bitmap("Recursos/enemigos.bmp");
    ALLEGRO_BITMAP *marquee = al_load_bitmap("Recursos/portada.bmp");
    ALLEGRO_BITMAP *background = al_load_bitmap("Recursos/fondo.bmp");
    // ALLEGRO_BITMAP *shields = al_load_bitmap("Recursos/escudos.bmp");
    ALLEGRO_BITMAP *gameOver = al_load_bitmap("Recursos/GameOver.bmp");
	ALLEGRO_BITMAP *spriteBullet = al_load_bitmap("Recursos/Bala2.bmp");
	ALLEGRO_BITMAP *spriteEnemyBullet = al_load_bitmap("Recursos/BalaE.bmp");
	

	// Load fonts
	
	ALLEGRO_FONT * scoreFont = al_load_ttf_font("Recursos/emulogic.ttf", 10, 0);

	
	if (!scoreFont) {
		fprintf(stderr, "Could not load 'emulogic.ttf'.\n");
		return -1;
	}

	
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
	
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(0,0,0));

	int gameState = ST_SPLASH_SCREEN;
	int currentStateFrames = 0;
	bool doexit = false;

    /* GAME CHARACTERS */
    Bounds playerBounds = {};
    playerBounds.w = 28;
    playerBounds.h = 20;

    Point startingPos = {};
    startingPos.x = SCREEN_WIDTH / 2 - playerBounds.w / 2;
    startingPos.y = SCREEN_HEIGHT - 100;

	PlayerCharacter *player = new PlayerCharacter(spriteShip, spriteBullet, startingPos, playerBounds);
	EnemyGrid *enemyGrid = new EnemyGrid(ENEMY_GRID_WIDTH, ENEMY_GRID_HEIGHT, spriteEnemy, spriteEnemyBullet);
	BulletManager *bulletManager = new BulletManager();
	ScoreBoard *scoreBoard = new ScoreBoard(scoreFont);

	al_convert_mask_to_alpha(spriteShip, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(spriteEnemy, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(spriteBullet, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(spriteEnemyBullet, al_map_rgb(255, 0, 255));
    al_convert_mask_to_alpha(background, al_map_rgb(255, 0 , 255));  //HACE INVISIBLE EL COLOR MAGENTA

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
		// Fin de procesamiento de eventos
		// Procesamiento de teclado para controles globales de la aplicacion
		if (playerInput->escape) {
			doexit = true;
			break;
		}

		currentStateFrames++;

		switch (gameState) {
			case ST_SPLASH_SCREEN:
				if (playerInput->enter) {
					gameState = ST_INGAME;
				}

				if (currentStateFrames < 25) {
					al_draw_bitmap_region(marquee, 0, 0, 600, 600, 0, 0, 0);
					al_flip_display();
				}
				else {
					al_draw_bitmap_region(marquee, 600, 0, 600, 600, 0, 0, 0);
					al_flip_display();
				}

				if (currentStateFrames == 50) {
					currentStateFrames = 0;
				}
				break;
			case ST_INGAME:
				if (scoreBoard->getLives() == 0) {
					gameState = ST_GAME_OVER;
				}

				// Procesar el input
				player->processInput(playerInput, bulletManager);
				player->updatePosition();
				enemyGrid->updatePosition();
				bulletManager->shotGenerator(enemyGrid);
				bulletManager->updateBulletsPosition();

				// Limite para que la nave del jugador no pueda salir de la pantalla
				if (player->getPos().x < SCREEN_LEFT || player->getPos().x + player->getBounds().w > SCREEN_RIGHT) {
					player->resetPosition();
				}

				// Chequeo de colisiones
				bulletManager->checkPlayerBulletCollisions(enemyGrid, scoreBoard);
				if (bulletManager->checkEnemyBulletCollisions(player, scoreBoard)) {

					// Resetea el estado
					player->resetPosition();
					enemyGrid->resetEnemyPositions();
					bulletManager->clearBullets();
					redraw = false;

					currentStateFrames = 0;
					gameState = ST_PLAYER_KILLED;
				}

				// Dibujado
				if (redraw) {
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_bitmap(background, 0, 0, 0);
					enemyGrid->draw();
					player->draw();
					bulletManager->draw();
					scoreBoard->draw();

					//enemyGrid->debugDraw();

					al_flip_display(); //si no se ve blanco
				}

				break;
			case ST_PLAYER_KILLED:
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_bitmap(background, 0, 0, 0);
				scoreBoard->draw();
				al_flip_display(); //si no se ve blanco

				if (currentStateFrames == 100) {
					gameState = ST_INGAME;
				}

				break;
			case ST_GAME_OVER:
				al_draw_bitmap_region(gameOver, 0, 0, 600, 600, 0, 0, 0);
				al_flip_display();
				break;
			default:
				// ERROR!
				break;
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

		if (keyCode == ALLEGRO_KEY_ENTER) {
			playerInput->enter = true;
		}

		if (keyCode == ALLEGRO_KEY_R) {
			playerInput->replay = false;
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

		if (keyCode == ALLEGRO_KEY_ENTER) {
			playerInput->enter = true;
		}

		if (keyCode == ALLEGRO_KEY_R) {
			playerInput->replay = true;
		}
    }
}
