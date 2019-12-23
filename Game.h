#ifndef GAME_H_
#define GAME_H_


enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
  GameState State;
  bool Keys[1024];
  int Width, Height;
  Game(int width,int height); //Constructor
  ~Game(); //Destructor

  void init();//Inicializador
  void render(); //Renderizador
  void update(float time); //Actualizador del tiempo
  void processInput(float time); //Procesar entradas
};
#endif
