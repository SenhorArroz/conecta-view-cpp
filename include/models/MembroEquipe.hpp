#pragma once

#include "abstratos/Usuario.hpp"
#include "../interfaces/IPersistente.hpp"
#include <string>
#include <fstream>

class MembroEquipe : public Usuario, public IPersistente {
private:
    std::string cargoNaEquipe; 
    std::string equipeId;  

public:
    MembroEquipe(std::string id, std::string nome, std::string email, std::string senha, std::string cargo, std::string equipeId);

    ~MembroEquipe() override = default;

    std::string getCargoNaEquipe() const;
    std::string getEquipeId() const;
    
    void setCargoNaEquipe(const std::string& novoCargo);

    void exibirMenu() const override;
    
    std::string getTipo() const override;

    bool isLider() const;

    void salvar(std::ofstream& arquivoSaida) const override;
    void carregar(std::ifstream& arquivoEntrada) override;
};