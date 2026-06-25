#pragma once

#include "abstratos/Usuario.hpp"
#include "../interfaces/IPersistente.hpp"
#include <string>
#include <fstream>

class Administrador : public Usuario, public IPersistente {
private:
    std::string nivelAcesso; 

public:
    Administrador(std::string id, std::string nome, std::string email, std::string senha, std::string nivelAcesso);

    ~Administrador() override = default;

    std::string getNivelAcesso() const;

    void exibirMenu() const override;
    std::string getTipo() const override;

    bool podeAprovarDoacoes() const;

    void salvar(std::ofstream& arquivoSaida) const override;
    void carregar(std::ifstream& arquivoEntrada) override;
};