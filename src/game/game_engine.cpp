#include "game/game_engine.h"

GameEngine::GameEngine(Arena * arena){
    this->arena = arena;
    this->score = 0;
}


ALLEGRO_COLOR getItemColor(Item * item){
    switch (item->getType())
    {
        case 0:
            return al_map_rgb(0, 0, 255);
            break;
        case 1:
            return al_map_rgb(34, 139, 34);
            break;
        case 2:
            return al_map_rgb(255, 255, 0);
            break;
        case 3: 
            return al_map_rgb(255, 69, 0);
            break;
        case 4:
            return al_map_rgb(255, 255, 255);
            break;
    }
}


bool GameEngine::inicialize(){
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }

    al_init_font_addon();

    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    fonte = al_load_font("font.ttf", 72, 0);
    if (!fonte)
    {
        fprintf(stderr, "Falha ao carregar \"fonte comic.ttf\".\n");
        al_destroy_display(janela);
        return false;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }

    al_set_window_title(janela, "Utilizando o Teclado");


    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return true;
}
int GameEngine::start () {
    bool sair = false;
    int tecla = 0;
    clock_t begin = clock();
    clock_t end = clock();
    clock_t begin_shoot = clock();
    clock_t end_shoot = clock();
    double elapsed_secs;


    if (!inicialize()){
        return -1;
    }

    while (!sair)
    {
        while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(evento.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                    tecla = 1;
                    break;
                    case ALLEGRO_KEY_DOWN:
                    tecla = 2;
                    break;
                    case ALLEGRO_KEY_LEFT:
                    tecla = 3;
                    break;
                    case ALLEGRO_KEY_RIGHT:
                    tecla = 4;
                    break;
                    case ALLEGRO_KEY_SPACE:
                    tecla = 5;
                    break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true;
            }
        }

        if (tecla)
        {

            switch (tecla)
            {
                case 1:
                    //"Seta para cima"
                    break;
                case 2:
                    //"Seta para baixo");
                    break;
                case 3:
                    //"Seta esquerda");
                    if(this->arena->getShooter()->position->x > 0){
                        this->arena->getShooter()->moveLeft();
                    }
                    break;
                case 4:
                    if(this->arena->getShooter()->position->x < this->arena->getWidth()){
                        this->arena->getShooter()->moveRight();
                    }
                    //"Seta direita");
                    break;
                case 5:
                    if(this->arena->shootedItem == NULL){
                        this->arena->shootedItem = this->arena->getShooter()->shoot();
                        this->arena->shootedItemPosition = new Position(this->arena->getShooter()->position->y, this->arena->getShooter()->position->x);
                    }
                    break;
            }

            tecla = 0;
        }
        end = clock();
        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        if(elapsed_secs>1.7){
            this->arena->show_size += 1;
            begin = clock();
        }
        end_shoot = clock();
        elapsed_secs = double(end_shoot - begin_shoot) / CLOCKS_PER_SEC;
        if(elapsed_secs>0.02 && this->arena->shootedItem){
            this->arena->shootedItemPosition->y--;
            if (this->arena->shootedItemPosition->y < 0){
                this->missShoot();
            }
            begin_shoot = clock();
        }
        this->print();
        al_flip_display();
    }

    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}
int GameEngine::start (int argc, char** argv){return 0;}

void GameEngine::print(){

    al_clear_to_color(al_map_rgb(0,0,0));
    int height = this->arena->getHeight();
    int width = this->arena->getWidth();

    for(int i = 0; i <= height; i++){
        for(int j = 0; j <= width; j++){
            int p = this->arena->searchPosition(j, i);
            // std::cout << p;
            if (this->arena->shootedItem && this->arena->shootedItemPosition->x == j && this->arena->shootedItemPosition->y == i){
                if(p <= this->arena->show_size && p > -1){
                    if(this->checkShoot(this->arena->show_size-(p-1))){
                    }
                    return;
                }else{
                    al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, 4.0,  getItemColor(this->arena->shootedItem));
                }
            }else if (p <= this->arena->show_size && p > -1){
                al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, 4.0,  getItemColor(this->arena->getItems()->get(this->arena->show_size-(p-1))));
            }else if(j == this->arena->getShooter()->position->x && i == this->arena->getShooter()->position->y){
                al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, 4.0,  al_map_rgb(255, 0, 255));
            }else if (this->arena->e_x == j && this->arena->e_y == i ){
                al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, 4.0,  al_map_rgb(255, 0, 255));
            }else if (p > -1){
                al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, 1.0,  al_map_rgb(255, 255, 255));
            }
        }
        //Imprime Score
        al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA-100, 10, ALLEGRO_ALIGN_CENTRE, "%i", this->score);
    }
}

bool GameEngine::checkShoot(int p){
    Item * item = new Item(0);
    *item = *this->arena->shootedItem;
    this->arena->getItems()->push(item, p);
    this->arena->shootedItem = NULL;
    this->arena->shootedItemPosition = NULL;
    int blowed = this->arena->checkShoot(p);
    if (blowed > 0){
        this->score += blowed*5;
        this->arena->show_size -= blowed;
        return true;
    }else{
        this->arena->show_size++;
        return false;
    }
}

void GameEngine::missShoot(){
    this->arena->shootedItem = NULL;
    this->arena->shootedItemPosition = NULL;
}