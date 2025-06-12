CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src/models -I/opt/homebrew/include
SRC = main.cpp \
  src/models/Enemy.cpp \
  src/models/GameManager.cpp \
  src/models/LevelManager.cpp \
  src/models/Path.cpp \
  src/models/Player.cpp \
  src/models/Projectile.cpp \
  src/models/Tower.cpp \
  src/models/WaveManager.cpp \
  src/models/GameOverState.cpp \
  src/models/LevelSelectState.cpp \
  src/models/MainMenuState.cpp \
  src/models/PausedState.cpp \
  src/models/PlayingState.cpp \
  src/models/TowerPlacementState.cpp \
  src/models/VictoryState.cpp

OBJS = $(SRC:.cpp=.o)

all: tower_defense

tower_defense: $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

SFML_SOURCES = main_sfml.cpp src/views/GameView.cpp src/views/LevelView.cpp src/views/EnemyView.cpp src/views/TowerView.cpp src/views/HUDView.cpp
MODEL_SOURCES = src/models/LevelManager.cpp src/models/Path.cpp src/models/Tower.cpp src/models/WaveManager.cpp src/models/Enemy.cpp \
    src/models/Projectile.cpp src/models/Player.cpp
LDFLAGS_SFML = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

main_sfml: $(SFML_SOURCES) $(MODEL_SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS_SFML)

clean:
	rm -f tower_defense *.o src/models/*.o 