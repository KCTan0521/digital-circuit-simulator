#!/bin/bash
clear

# G++: The classic GNU compiler (mature optimizations for the final binary)
# G++: Use for final testing (usually generates the fastest execution)
# g++ Main.cpp Lexer.cpp -o Main.obj

# Clang++: The LLVM-based compiler (modular design, great for tooling)
# Clang++: Use for development (faster builds and clearer error messages)
# clang++ Main.cpp Lexer.cpp Parser.cpp -o Main.obj && ./Main.obj
# clang++ Parser.cpp -o Main.obj && ./Main.obj
# clang++ LogicEngine.cpp Parser.cpp -o Main.obj && ./Main.obj
# clang++ VariableMap.cpp -o Main.obj && ./Main.obj
# clang++ Main.cpp Lexer.cpp Parser.cpp -o Main.obj && ./Main.obj
clang++ *.cpp -o Main.obj && ./Main.obj