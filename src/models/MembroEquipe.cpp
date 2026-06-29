#include "../../include/models/MembroEquipe.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"
#include <iostream>
#include <fstream>
#include <string>

MembroEquipe::MembroEquipe(std::string id, std::string nome, std::string email, std::string senha, std::string cargo, std::string equipeId)
    : Usuario(id, nome, email, senha), cargoNaEquipe(cargo), equipeId(equipeId) {
    if (cargo.empty() || equipeId.empty()) {
        throw EntradaInvalidaException("Cargo e ID da equipe não podem ser vazios para um membro.");
    }
}

std::string MembroEquipe::getCargoNaEquipe() const { return cargoNaEquipe; }

std::string MembroEquipe::getEquipeId() const { return equipeId; }

void MembroEquipe::setCargoNaEquipe(const std::string& novoCargo) {
    if (novoCargo.empty()) {
        throw EntradaInvalidaException("O cargo na equipe nao pode ser vazio.");
    }
    cargoNaEquipe = novoCargo;
}

void MembroEquipe::exibirMenu() const {
    std::cout << "\n=== MENU DA EQUIPE ===\n";
    std::cout << "Competidor: " << getNome() << " | Cargo: " << cargoNaEquipe << "\n";
    std::cout << "1. Submeter nova doacao\n";
    std::cout << "2. Ver pontuacao da minha equipe\n";
    
    if (isLider()) {
        std::cout << "3. [LIDER] Editar dados da equipe\n";
    }
    
    std::cout << "4. Voltar ao menu principal\n";
    std::cout << "======================\n";
}

std::string MembroEquipe::getTipo() const {
    return "MembroEquipe";
}

bool MembroEquipe::isLider() const {
    return (cargoNaEquipe == "Líder" || cargoNaEquipe == "Lider");
}

void MembroEquipe::salvar(std::ofstream& arquivoSaida) const {
    arquivoSaida << "---MEMBRO---\n";
    arquivoSaida << getId() << "\n";
    arquivoSaida << getNome() << "\n";
    arquivoSaida << getEmail() << "\n";
    arquivoSaida << cargoNaEquipe << "\n";
    arquivoSaida << equipeId << "\n";
}

void MembroEquipe::carregar(std::ifstream& arquivoEntrada) {
    (void)arquivoEntrada;
}