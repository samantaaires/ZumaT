//Arquivo de corpo game_engine.cpp

#include "game/game_engine.h"

GameEngine::GameEngine(Arena * arena){
    this->arena = arena;
    this->score = 0;
    this->timeToMove = 1.7; //Velocidade de movimento jogo
    this->itemRenderSize = 5.0; //Tamanho do circulo que representa o item na allegro
    this->gameOver = false; //Verifica se o jogo cabou
}

//Retorna uma cor baseada no tipo do item
ALLEGRO_COLOR getItemColor(Item * item){
    switch (item->getType())
    {
        case 0:
            return al_map_rgb(0, 0, 255); //azul
            break;
        case 1:
            return al_map_rgb(34, 139, 34); //verde
            break;
        case 2:
            return al_map_rgb(255, 255, 0); //amarela
            break;
        case 3: 
            return al_map_rgb(255, 69, 0); //laranja
            break;
        case 4:
            return al_map_rgb(255, 255, 255); //branco
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
    bool sair = false; //Verificador se o usuário apertou sair

    //Relogio para contar o tempo e avançar os itens na arena
    clock_t begin = clock(); 
    clock_t end = clock(); 

    //Relogio para contar o tempo e avançar o item atirado na arena
    clock_t begin_shoot = clock();
    clock_t end_shoot = clock();

    //Variável para contabilizar o tempo
    double elapsed_secs = 0.0;


    std::cout << "iniializing allegro -";
    if (!inicialize()){
        return -1;
    }
    std::cout << "done" << std::endl;

    while (!gameOver && !sair)
    {   
        //Loop de eventos da allegro
        while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(evento.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT:
                        if(this->arena->getShooter()->position->x > 0){
                            this->arena->getShooter()->moveLeft();
                        }
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        if(this->arena->getShooter()->position->x < this->arena->getWidth()){
                            this->arena->getShooter()->moveRight();
                        }
                        break;
                    case ALLEGRO_KEY_SPACE:
                        //So atira se o jogo nao tiver acabado
                        if(!this->arena->gameEnded()){
                            this->arena->shoot();
                        }
                        break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true;
            }
        }

        //Algoritimo de avançar os itens na arena
        end = clock();
        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        if(elapsed_secs>this->timeToMove){
            this->arena->show_size += 1;
            //Se 1 item encostar no final puxa todos os itens
            if(this->arena->gameEnded() && this->timeToMove > 0.1){
                this->timeToMove = 0.1;
            }
            //Se o ultimo item passar pelo final finaliza o jogo
            if(this->arena->show_size - this->arena->getItems()->length() > this->arena->getPathLength())
                this->gameOver = true;
            begin = clock();
        }

        //Algoritimo de avançar o item atirado
        end_shoot = clock();
        elapsed_secs = double(end_shoot - begin_shoot) / CLOCKS_PER_SEC;
        if(elapsed_secs>0.02 && this->arena->shootedItem){
            this->arena->shootedItemPosition->y--;
            //se o item passar do limite superior da arena invoca o missShoot e libera o atirador
            if (this->arena->shootedItemPosition->y < 0){
                this->missShoot();
            }
            begin_shoot = clock();
        }
        this->print();
        al_flip_display();//função da allegro que nao sei o que faz, mas estava no tutorial.
    }
    std::cout << "game over" << std::endl;
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}

//Função para "desbugar" a allegro. Por algum motivo só funciona se colocar assim.
int GameEngine::start (int argc, char** argv){
    return 0;
}


//Imprime tudo na allegro
void GameEngine::print(){

    al_clear_to_color(al_map_rgb(0,0,0));
    int height = this->arena->getHeight();
    int width = this->arena->getWidth();

    //Procura a arena inteira
    for(int i = 0; i <= height; i++){
        for(int j = 0; j <= width; j++){

            //Procura se a posição em questão é um caminho ou não
            int p = this->arena->searchPosition(j, i);

            if (this->arena->shootedItem && this->arena->shootedItemPosition->x == j && this->arena->shootedItemPosition->y == i){
                //Draw shooted item
                if(p <= this->arena->show_size && p > -1 && this->arena->getItems()->length() > this->arena->show_size-(p-1)){
                    //Se colidir com a lista de itens invoca GameEngine::checkShoot()
                    if(this->checkShoot(this->arena->show_size-(p-1))){}
                    return;
                }else{
                    al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, itemRenderSize,  getItemColor(this->arena->shootedItem));
                }
            }else if (p <= this->arena->show_size && p > -1 && this->arena->getItems()->length() > this->arena->show_size-(p-1)){
                //Draw items
                al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, itemRenderSize,  getItemColor(this->arena->getItems()->get(this->arena->show_size-(p-1))));
            }else if(j == this->arena->getShooter()->position->x && i == this->arena->getShooter()->position->y){
                //Draw shooter
                al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, itemRenderSize,  getItemColor(this->arena->getShooter()->shoot()));
            }else if (this->arena->e_x == j && this->arena->e_y == i ){
                //Draw end of arena
                al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, itemRenderSize,  al_map_rgb(255, 0, 255));
            }else if (p > -1){
                //Draw path
                al_draw_filled_circle(LARGURA_TELA/width*j, ALTURA_TELA/height*i+10, 1.0,  al_map_rgb(255, 255, 255));
            }
        }
        //Imprime Score
        al_draw_textf(fonte, al_map_rgb(255, 255, 255), LARGURA_TELA-100, 10, ALLEGRO_ALIGN_CENTRE, "%i", this->score);
    }
}

//Quando o item colide com a lista na posição "p"
bool GameEngine::checkShoot(int p){
    //copia o item e o insere na lista
    Item * item = new Item(0);
    *item = *this->arena->shootedItem;
    this->arena->getItems()->push(item, p);
    this->arena->shootedItem = NULL;
    this->arena->shootedItemPosition = NULL;
    //Verifica se estorou algum item
    int blowed = this->arena->checkShoot(p);
    if (blowed > 0){
        //calcula a pontuação
        this->score += this->calculateScore(blowed);
        //se estourou diminui a quantidade de itens na arena pela quantidade estourada
        this->arena->show_size -= blowed;
        return true;
    }else{
        //se nao estourar nada aumenta a quantidade de itens na arena em 1
        this->arena->show_size++;
        return false;
    }
}

//Evento chamado quando o usuário erro o tipo
void GameEngine::missShoot(){
    this->arena->shootedItem = NULL;
    this->arena->shootedItemPosition = NULL;
}

//Função para calcular a pontuação baseado na quantidade de itens estourados
int GameEngine::calculateScore(int blowed){
    long factN = 1;
    int i;
    for (i = 1; i <= blowed; i++)
       factN = factN * i;
    return factN;
}