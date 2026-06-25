#pragma once

#include "abstratos/AtividadePontuada.hpp"
#include "../interfaces/IPersistente.hpp"
#include <vector>
#include <string>
#include <iostream>

class ItemSendoDoado;

enum class StatusDoacao {
    PENDENTE_AVALIACAO,
    APROVADA,
    REJEITADA
};

class Doacao : public AtividadePontuada, public IPersistente {
private:
    std::string nomeDoador; 
    std::string descricao;  
    StatusDoacao status;
    
    std::vector<ItemSendoDoado*> itensDoados;

public:
    Doacao(std::string id, std::string titulo, std::string equipeId, std::string nomeDoador, std::string descricao);
    
    ~Doacao() override;

    void aprovar();
    void rejeitar();
    StatusDoacao getStatus() const;

    void adicionarItem(ItemSendoDoado* item);
    const std::vector<ItemSendoDoado*>& getItens() const;

    int calcularPontos() const override;
    void exibirResumo() const override;

    void salvar(std::ofstream& arquivoSaida) const override;
    void carregar(std::ifstream& arquivoEntrada) override;

    friend std::ostream& operator<<(std::ostream& os, const Doacao& doacao);
    friend std::istream& operator>>(std::istream& is, Doacao& doacao);
};