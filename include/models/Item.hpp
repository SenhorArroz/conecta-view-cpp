#pragma once

#include <string>
#include <fstream>
#include "../interfaces/IPersistente.hpp"

class Usuario;

class Item : public IPersistente {
private:
    std::string id;
    std::string nome;
    std::string descricao;
    
    int pontosBase; 
    
    Usuario* criador;

public:
    Item(std::string id, std::string nome, std::string descricao, int pontosBase, Usuario* criador);

    ~Item() override = default;

    std::string getId() const;
    std::string getNome() const;
    std::string getDescricao() const;
    int getPontosBase() const;
    Usuario* getCriador() const;

    void salvar(std::ofstream& arquivoSaida) const override;
    void carregar(std::ifstream& arquivoEntrada) override;
};