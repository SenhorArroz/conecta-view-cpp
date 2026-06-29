#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "../interfaces/IPersistente.hpp"

class AtividadePontuada;
class Usuario;

class Equipe : public IPersistente {
private:
    std::string id;
    std::string nome;
    
    Usuario* criador; 

    std::vector<AtividadePontuada*> atividades;

public:
    Equipe(std::string id, std::string nome, Usuario* criador);

    ~Equipe() override;

    std::string getId() const;
    std::string getNome() const;
    Usuario* getCriador() const;

    void adicionarAtividade(AtividadePontuada* atividade);
    const std::vector<AtividadePontuada*>& getAtividades() const;
    
    int calcularPontuacaoTotal() const;

    void salvar(std::ofstream& arquivoSaida) const override;
    void carregar(std::ifstream& arquivoEntrada) override;

    friend std::ostream& operator<<(std::ostream& os, const Equipe& equipe);
};