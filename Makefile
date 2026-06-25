# Nome do executavel
TARGET = gincana_app.exe

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRCS = $(wildcard src/*.cpp) \
       $(wildcard src/controllers/*.cpp) \
       $(wildcard src/models/*.cpp) \
       $(wildcard src/models/abstratos/*.cpp)

all:
	@echo ========================================
	@echo Compilando todo o projeto diretamente para o Windows...
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)
	@echo ========================================
	@echo Compilacao concluida com sucesso!
	@echo Para executar, digite no terminal: .\$(TARGET)

clean:
	@if exist $(TARGET) del /q $(TARGET)
	@echo Limpeza concluida!