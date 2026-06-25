#pragma once

#include "abstratos/AtividadePontuada.hpp"
#include "../interfaces/IPersistente.hpp"
#include <string>
#include <fstream>

class ProvaGincana : public AtividadePontuada, public IPersistente {
private:
    std::string descricao;
    
    int pontosObtidos;     
    
    std::string avaliador; 

public:
    ProvaGincana(std::string id, std::string titulo, std::string equipeId, std::string descricao);

    ~ProvaGincana() override = default;

    std::string getDescricao() const;
    int getPontosObtidos() const;
    std::string getAvaliador() const;

    void avaliarApresentacao(int nota, const std::string& nomeAvaliador);

    int calcularPontos() const override;
    
    void exibirResumo() const override;

    void salvar(std::ofstream& arquivoSaida) const override;
    void carregar(std::ifstream& arquivoEntrada) override;
};