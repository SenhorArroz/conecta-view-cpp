#include "../../include/models/Administrador.hpp"
#include <iostream>
#include <fstream>
#include <string>

Administrador::Administrador(std::string id, std::string nome, std::string email, std::string senha, std::string nivelAcesso)
    : Usuario(id, nome, email, senha), nivelAcesso(nivelAcesso) {
}

std::string Administrador::getNivelAcesso() const {
    return nivelAcesso;
}

void Administrador::exibirMenu() const {
    std::cout << "\n== Administrador: " << getNome() 
              << " | Nivel: " << nivelAcesso << " ==\n";
}

std::string Administrador::getTipo() const {
    return "Administrador";
}

bool Administrador::podeAprovarDoacoes() const {
    return (nivelAcesso == "SUPER" || nivelAcesso == "JUIZ");
}

void Administrador::salvar(std::ofstream& arquivoSaida) const {
    arquivoSaida << "---ADMINISTRADOR---\n";
    arquivoSaida << getId() << "\n";
    arquivoSaida << getNome() << "\n";
    arquivoSaida << getEmail() << "\n";
    arquivoSaida << nivelAcesso << "\n";
}

void Administrador::carregar(std::ifstream& arquivoEntrada) {
    (void)arquivoEntrada;
}