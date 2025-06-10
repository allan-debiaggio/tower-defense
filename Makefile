CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src/models
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

clean:
	rm -f tower_defense *.o src/models/*.o 