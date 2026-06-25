@echo off
echo ========================================
echo Compilando o Trabalho da Gincana...
echo ========================================

g++ -Wall -Wextra -std=c++17 -Iinclude src/Main.cpp src/controllers/GincanaController.cpp src/models/Administrador.cpp src/models/AtividadePontuada.cpp src/models/Doacao.cpp src/models/Equipe.cpp src/models/Item.cpp src/models/ItemSendoDoado.cpp src/models/MembroEquipe.cpp src/models/ProvaGincana.cpp src/models/Usuario.cpp -o gincana_app.exe > log_erro.txt 2>&1

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo [ERRO CAPTURADO] O compilador falhou, mas nos pegamos o erro!
    echo Um arquivo chamado "log_erro.txt" acabou de ser criado na sua pasta.
    echo Abra esse arquivo, copie tudo o que esta la dentro e cole aqui para resolvermos.
) ELSE (
    echo.
    echo [SUCESSO] Executavel gerado! Iniciando...
    echo ========================================
    echo.
    gincana_app.exe
)