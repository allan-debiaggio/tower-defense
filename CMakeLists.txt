
cmake_minimum_required(VERSION 3.14)
project(tower_defense LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compilation flags
add_compile_options(-Wall -Wextra)

# Ajouter les fichiers source
file(GLOB_RECURSE SOURCES
    main.cpp
    src/models/*.cpp
)

# Ajouter l'exécutable
add_executable(tower_defense ${SOURCES})

# Inclure le dossier headers si besoin
target_include_directories(tower_defense PRIVATE src/models)

# Trouver SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Lier SFML à l'exécutable
target_link_libraries(tower_defense PRIVATE sfml-graphics sfml-window sfml-system)