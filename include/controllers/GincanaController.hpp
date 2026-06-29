#pragma once 

#include <vector>
#include <string>

class Equipe;
class Usuario;
class Item;

class GincanaController {
private:
    std::vector<Equipe*> equipes;
    std::vector<Usuario*> usuarios;
    std::vector<Item*> itensCadastrados;
    
    Usuario* usuarioLogado;

    void menuAdministrador();
    
    void cadastrarEquipe();
    void listarEquipes() const;
    void cadastrarItem();
    void listarItens() const;
    void registrarDoacao();
    void lancarNotaProva();
    void exibirRankingGeral();
    void aprovarDoacao();

    void salvarDadosEmArquivo();
    void carregarDadosDeArquivo();

    Equipe* buscarEquipePorId(const std::string& id) const;
    Item* buscarItemPorId(const std::string& id) const;
    void limparEntradaInvalida();

public:
    GincanaController();
    ~GincanaController();

    void iniciarSistema();
};