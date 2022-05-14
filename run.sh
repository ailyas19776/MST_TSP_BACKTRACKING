g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG -c algorithms.cpp
g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG -c cmdLine.cpp
g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG -c main.cpp
g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -O3 -DNDEBUG main.o cmdLine.o alogrithms.o -o calculate
