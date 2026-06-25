#include <iostream>
#include "../include/controllers/GincanaController.hpp"

int main() {
    std::cout << "Inicializando o Sistema Conecta View...\n";
    
    GincanaController app;
    
    app.iniciarSistema();
    
    return 0;
}