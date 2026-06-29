#include "../../include/controllers/GincanaController.hpp"
#include "../../include/models/Equipe.hpp"
#include "../../include/models/Administrador.hpp"
#include "../../include/models/MembroEquipe.hpp"
#include "../../include/models/Doacao.hpp"
#include "../../include/models/ProvaGincana.hpp"
#include "../../include/models/Item.hpp"
#include "../../include/models/ItemSendoDoado.hpp"
#include "../../include/exceptions/GincanaExceptions.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

// ========================== CONSTRUTOR / DESTRUTOR ==========================

GincanaController::GincanaController() {
    usuarioLogado = nullptr;
    usuarios.push_back(new Administrador("u1", "Admin Mestre", "admin@gincana.com", "123", "SUPER"));
}

GincanaController::~GincanaController() {
    for (Equipe* equipe : equipes) {
        delete equipe;
    }
    for (Usuario* usuario : usuarios) {
        delete usuario;
    }
    for (Item* item : itensCadastrados) {
        delete item;
    }
}

// ========================== UTILITARIOS ==========================

void GincanaController::limparEntradaInvalida() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Equipe* GincanaController::buscarEquipePorId(const std::string& id) const {
    for (Equipe* eq : equipes) {
        if (eq->getId() == id) {
            return eq;
        }
    }
    return nullptr;
}

Item* GincanaController::buscarItemPorId(const std::string& id) const {
    for (Item* item : itensCadastrados) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}

// ========================== SISTEMA PRINCIPAL ==========================

void GincanaController::iniciarSistema() {
    try {
        carregarDadosDeArquivo();
    } catch (const ArquivoException& e) {
        std::cout << ">> Aviso: " << e.what() << "\n";
        std::cout << ">> O sistema iniciara com dados vazios.\n";
    }

    int opcao = 0;
    while (opcao != 3) {
        std::cout << "\n=== SISTEMA DE GINCANA ===\n";
        std::cout << "1. Entrar como Administrador\n";
        std::cout << "2. Exibir Ranking Geral\n";
        std::cout << "3. Sair\n";
        std::cout << "Escolha: ";

        if (!(std::cin >> opcao)) {
            limparEntradaInvalida();
            std::cout << ">> Entrada invalida! Digite um numero.\n";
            continue;
        }

        try {
            if (opcao == 1) {
                // Login simples: pede a senha do administrador
                std::string senhaDigitada;
                std::cout << "Digite a senha do administrador: ";
                std::cin >> senhaDigitada;

                if (usuarios[0]->verificarSenha(senhaDigitada)) {
                    usuarioLogado = usuarios[0];
                    std::cout << ">> Login bem-sucedido! Bem-vindo, " << usuarioLogado->getNome() << ".\n";
                    menuAdministrador();
                } else {
                    std::cout << ">> Senha incorreta! Acesso negado.\n";
                }

            } else if (opcao == 2) {
                exibirRankingGeral();
            } else if (opcao == 3) {
                std::cout << "Salvando dados e encerrando...\n";
                try {
                    salvarDadosEmArquivo();
                } catch (const ArquivoException& e) {
                    std::cout << ">> ATENCAO: " << e.what() << "\n";
                }
            } else {
                std::cout << ">> Opcao invalida! Tente novamente.\n";
            }
        } catch (const GincanaException& e) {
            std::cout << ">> " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << ">> Erro inesperado: " << e.what() << "\n";
        }
    }
}

// ========================== MENU DO ADMINISTRADOR ==========================

void GincanaController::menuAdministrador() {
    Administrador* admin = dynamic_cast<Administrador*>(usuarioLogado);
    if (admin == nullptr) {
        std::cout << ">> Erro interno: usuario nao eh um administrador.\n";
        return;
    }

    int opcao = 0;
    while (opcao != 9) {
        std::cout << "\n=== MENU DO ADMINISTRADOR ===\n";
        std::cout << "Bem-vindo, " << admin->getNome() << " | Nivel: " << admin->getNivelAcesso() << "\n";
        std::cout << "1. Cadastrar nova equipe\n";
        std::cout << "2. Listar equipes cadastradas\n";
        std::cout << "3. Cadastrar novo item doavel\n";
        std::cout << "4. Listar itens cadastrados\n";
        std::cout << "5. Registrar doacao para uma equipe\n";
        std::cout << "6. Lancar nota de apresentacao\n";
        std::cout << "7. Exibir ranking geral\n";
        std::cout << "8. Aprovar doacoes pendentes\n";
        std::cout << "9. Voltar ao menu principal\n";
        std::cout << "=============================\n";
        std::cout << "Escolha: ";

        if (!(std::cin >> opcao)) {
            limparEntradaInvalida();
            std::cout << ">> Entrada invalida! Digite um numero.\n";
            continue;
        }

        try {
            switch (opcao) {
                case 1: cadastrarEquipe(); break;
                case 2: listarEquipes(); break;
                case 3: cadastrarItem(); break;
                case 4: listarItens(); break;
                case 5: registrarDoacao(); break;
                case 6: lancarNotaProva(); break;
                case 7: exibirRankingGeral(); break;
                case 8: aprovarDoacao(); break;
                case 9:
                    std::cout << ">> Voltando ao menu principal...\n";
                    break;
                default:
                    std::cout << ">> Opcao invalida! Tente novamente.\n";
                    break;
            }
        } catch (const GincanaException& e) {
            std::cout << ">> " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << ">> Erro inesperado: " << e.what() << "\n";
        }
    }
}

// ========================== OPERACOES DE EQUIPE ==========================

void GincanaController::cadastrarEquipe() {
    std::string idEquipe, nomeEquipe;
    std::cout << "\n-- CADASTRAR EQUIPE --\n";
    std::cout << "Digite o ID da nova equipe: ";
    std::cin >> idEquipe;

    if (idEquipe.empty()) {
        throw EntradaInvalidaException("O ID da equipe nao pode ser vazio.");
    }

    // Verifica se ja existe uma equipe com esse ID
    if (buscarEquipePorId(idEquipe) != nullptr) {
        throw IdDuplicadoException("equipe", idEquipe);
    }

    std::cout << "Digite o nome da equipe: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nomeEquipe);

    if (nomeEquipe.empty()) {
        throw EntradaInvalidaException("O nome da equipe nao pode ser vazio.");
    }

    Equipe* novaEquipe = new Equipe(idEquipe, nomeEquipe, usuarioLogado);
    equipes.push_back(novaEquipe);

    std::cout << ">> Sucesso! A equipe '" << nomeEquipe << "' (ID: " << idEquipe << ") foi cadastrada.\n";
    std::cout << ">> Total de equipes no sistema: " << equipes.size() << "\n";
}

void GincanaController::listarEquipes() const {
    if (equipes.empty()) {
        std::cout << "\n>> Nenhuma equipe cadastrada ainda.\n";
        return;
    }

    std::cout << "\n=== EQUIPES CADASTRADAS (" << equipes.size() << ") ===\n";
    for (size_t i = 0; i < equipes.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << *equipes[i]
                  << " | Pontuacao: " << equipes[i]->calcularPontuacaoTotal() << " pts\n";
    }
    std::cout << "================================\n";
}

// ========================== OPERACOES DE ITEM ==========================

void GincanaController::cadastrarItem() {
    std::string idItem, nomeItem, descItem;
    int pontosBase;

    std::cout << "\n-- CADASTRAR ITEM DOAVEL --\n";
    std::cout << "Digite o ID do item: ";
    std::cin >> idItem;

    if (buscarItemPorId(idItem) != nullptr) {
        throw IdDuplicadoException("item", idItem);
    }

    std::cout << "Digite o nome do item: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nomeItem);

    if (nomeItem.empty()) {
        throw EntradaInvalidaException("O nome do item nao pode ser vazio.");
    }

    std::cout << "Digite a descricao do item: ";
    std::getline(std::cin, descItem);

    std::cout << "Digite a pontuacao base por unidade: ";
    if (!(std::cin >> pontosBase)) {
        limparEntradaInvalida();
        throw EntradaInvalidaException("Pontuacao base deve ser um numero valido.");
    }

    if (pontosBase < 0) {
        throw PontuacaoInvalidaException();
    }

    Item* novoItem = new Item(idItem, nomeItem, descItem, pontosBase, usuarioLogado);
    itensCadastrados.push_back(novoItem);

    std::cout << ">> Item '" << nomeItem << "' cadastrado com " << pontosBase << " pontos por unidade.\n";
}

void GincanaController::listarItens() const {
    if (itensCadastrados.empty()) {
        std::cout << "\n>> Nenhum item cadastrado ainda.\n";
        return;
    }

    std::cout << "\n=== ITENS DOACIVEIS CADASTRADOS (" << itensCadastrados.size() << ") ===\n";
    for (size_t i = 0; i < itensCadastrados.size(); ++i) {
        std::cout << "  " << (i + 1) << ". [" << itensCadastrados[i]->getId() << "] "
                  << itensCadastrados[i]->getNome()
                  << " - " << itensCadastrados[i]->getPontosBase() << " pts/unidade\n";
    }
    std::cout << "=======================================\n";
}

// ========================== OPERACOES DE DOACAO ==========================

void GincanaController::registrarDoacao() {
    if (equipes.empty()) {
        throw RegraNegocioException("Erro: Nao ha equipes cadastradas. Cadastre uma equipe primeiro.");
    }
    if (itensCadastrados.empty()) {
        throw RegraNegocioException("Erro: Nao ha itens cadastrados. Cadastre um item primeiro.");
    }

    std::string idDoacao, tituloDoacao, equipeId, nomeDoador, descDoacao;

    std::cout << "\n-- REGISTRAR DOACAO --\n";
    listarEquipes();
    std::cout << "ID da equipe que esta fazendo a doacao: ";
    std::cin >> equipeId;

    Equipe* equipe = buscarEquipePorId(equipeId);
    if (equipe == nullptr) {
        throw EntidadeNaoEncontradaException("Equipe", equipeId);
    }

    std::cout << "ID da doacao: ";
    std::cin >> idDoacao;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Titulo da doacao: ";
    std::getline(std::cin, tituloDoacao);

    std::cout << "Nome do doador: ";
    std::getline(std::cin, nomeDoador);

    std::cout << "Descricao: ";
    std::getline(std::cin, descDoacao);

    Doacao* novaDoacao = new Doacao(idDoacao, tituloDoacao, equipeId, nomeDoador, descDoacao);

    // Adicionar itens a doacao
    std::string continuar = "s";
    while (continuar == "s" || continuar == "S") {
        listarItens();
        std::string idItem;
        int quantidade;

        std::cout << "ID do item sendo doado: ";
        std::cin >> idItem;

        Item* item = buscarItemPorId(idItem);
        if (item == nullptr) {
            std::cout << ">> Item nao encontrado. Tente novamente.\n";
            continue;
        }

        std::cout << "Quantidade: ";
        if (!(std::cin >> quantidade) || quantidade <= 0) {
            limparEntradaInvalida();
            std::cout << ">> Quantidade invalida. Deve ser um numero positivo.\n";
            continue;
        }

        std::string idItemDoado = idDoacao + "_" + idItem;
        ItemSendoDoado* itemDoado = new ItemSendoDoado(idItemDoado, item, quantidade);
        novaDoacao->adicionarItem(itemDoado);

        std::cout << ">> " << quantidade << "x '" << item->getNome() << "' adicionado(s). "
                  << "Subtotal: " << itemDoado->calcularSubtotalPontos() << " pts.\n";

        std::cout << "Adicionar mais itens? (s/n): ";
        std::cin >> continuar;
    }

    equipe->adicionarAtividade(novaDoacao);
    std::cout << ">> Doacao '" << tituloDoacao << "' registrada e aguardando APROVACAO para a equipe '" << equipe->getNome() << "'!\n";
    std::cout << ">> Pontos serao contabilizados apos aprovacao.\n";
}

// ========================== APROVAR DOACAO ==========================

void GincanaController::aprovarDoacao() {
    std::cout << "\n-- APROVAR DOACOES PENDENTES --\n";
    
    std::vector<Doacao*> doacoesPendentes;
    
    // Coleta todas as doacoes pendentes
    for (Equipe* eq : equipes) {
        for (AtividadePontuada* atv : eq->getAtividades()) {
            Doacao* doacao = dynamic_cast<Doacao*>(atv);
            if (doacao != nullptr && doacao->getStatus() == StatusDoacao::PENDENTE_AVALIACAO) {
                doacoesPendentes.push_back(doacao);
            }
        }
    }
    
    if (doacoesPendentes.empty()) {
        std::cout << ">> Nao ha doacoes pendentes de aprovacao.\n";
        return;
    }
    
    for (size_t i = 0; i < doacoesPendentes.size(); ++i) {
        std::cout << (i + 1) << ". " << *doacoesPendentes[i] << " (Equipe ID: " << doacoesPendentes[i]->getEquipeId() << ")\n";
    }
    
    std::cout << "Digite o numero da doacao que deseja avaliar (ou 0 para cancelar): ";
    int escolha;
    if (!(std::cin >> escolha) || escolha < 0 || escolha > (int)doacoesPendentes.size()) {
        limparEntradaInvalida();
        std::cout << ">> Escolha invalida.\n";
        return;
    }
    
    if (escolha == 0) return;
    
    Doacao* selecionada = doacoesPendentes[escolha - 1];
    
    std::cout << "1. Aprovar\n2. Rejeitar\nEscolha: ";
    int acao;
    if (!(std::cin >> acao)) {
        limparEntradaInvalida();
        std::cout << ">> Acao invalida.\n";
        return;
    }
    
    try {
        if (acao == 1) {
            selecionada->aprovar();
            std::cout << ">> Doacao aprovada com sucesso! Pontos contabilizados.\n";
        } else if (acao == 2) {
            selecionada->rejeitar();
            std::cout << ">> Doacao rejeitada.\n";
        } else {
            std::cout << ">> Acao invalida.\n";
        }
    } catch (const GincanaException& e) {
        std::cout << ">> Erro ao avaliar doacao: " << e.what() << "\n";
    }
}

// ========================== PROVA / NOTA ==========================

void GincanaController::lancarNotaProva() {
    if (equipes.empty()) {
        throw RegraNegocioException("Erro: Nao ha equipes cadastradas para lancar nota.");
    }

    std::string idProva, tituloProva, equipeId, descricao;
    int nota;

    std::cout << "\n-- LANCAR NOTA DE APRESENTACAO --\n";
    listarEquipes();

    std::cout << "ID da equipe: ";
    std::cin >> equipeId;

    Equipe* equipe = buscarEquipePorId(equipeId);
    if (equipe == nullptr) {
        throw EntidadeNaoEncontradaException("Equipe", equipeId);
    }

    std::cout << "ID da prova/apresentacao: ";
    std::cin >> idProva;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Titulo da prova: ";
    std::getline(std::cin, tituloProva);

    std::cout << "Descricao: ";
    std::getline(std::cin, descricao);

    std::cout << "Digite a nota a ser atribuida (0 a 100): ";
    if (!(std::cin >> nota)) {
        limparEntradaInvalida();
        throw EntradaInvalidaException("A nota deve ser um numero valido.");
    }

    if (nota < 0) {
        throw PontuacaoInvalidaException();
    }
    if (nota > 100) {
        throw EntradaInvalidaException("A nota nao pode ser maior que 100.");
    }

    ProvaGincana* prova = new ProvaGincana(idProva, tituloProva, equipeId, descricao);
    prova->avaliarApresentacao(nota, usuarioLogado->getNome());
    equipe->adicionarAtividade(prova);

    std::cout << ">> Sucesso! A nota " << nota << " foi atribuida a prova '" << tituloProva
              << "' para a equipe '" << equipe->getNome() << "'.\n";
}

// ========================== RANKING ==========================

void GincanaController::exibirRankingGeral() {
    if (equipes.empty()) {
        std::cout << "\nNenhuma equipe cadastrada ainda.\n";
        return;
    }

    std::cout << "\n=== RANKING GERAL DA GINCANA ===\n";

    // Insertion sort por pontuacao (decrescente)
    for (size_t i = 1; i < equipes.size(); ++i) {
        Equipe* chave = equipes[i];
        int j = i - 1;

        while (j >= 0 && equipes[j]->calcularPontuacaoTotal() < chave->calcularPontuacaoTotal()) {
            equipes[j + 1] = equipes[j];
            j = j - 1;
        }
        equipes[j + 1] = chave;
    }

    int posicao = 1;
    for (Equipe* eq : equipes) {
        std::cout << posicao << "o Lugar: " << *eq << " - "
                  << eq->calcularPontuacaoTotal() << " pontos\n";
        posicao++;
    }
}

// ========================== PERSISTENCIA ==========================

void GincanaController::salvarDadosEmArquivo() {
    std::ofstream arquivoEquipes("equipes.txt");
    if (!arquivoEquipes.is_open()) {
        throw ArquivoException("Nao foi possivel abrir 'equipes.txt' para escrita.");
    }

    for (Equipe* eq : equipes) {
        eq->salvar(arquivoEquipes);
    }
    arquivoEquipes.close();

    std::ofstream arquivoItens("itens.txt");
    if (!arquivoItens.is_open()) {
        throw ArquivoException("Nao foi possivel abrir 'itens.txt' para escrita.");
    }

    for (Item* item : itensCadastrados) {
        item->salvar(arquivoItens);
    }
    arquivoItens.close();

    std::cout << ">> Dados salvos com sucesso! (" << equipes.size() << " equipes, "
              << itensCadastrados.size() << " itens)\n";
}

void GincanaController::carregarDadosDeArquivo() {
    // Carregar equipes
    std::ifstream arquivoEquipes("equipes.txt");
    if (arquivoEquipes.is_open()) {
        std::string linhaAtual;
        std::string idLido, nomeLido;

        while (std::getline(arquivoEquipes, linhaAtual)) {
            if (linhaAtual == "---EQUIPE---") {
                if (std::getline(arquivoEquipes, idLido) && std::getline(arquivoEquipes, nomeLido)) {
                    Equipe* equipeRecuperada = new Equipe(idLido, nomeLido, nullptr);
                    equipes.push_back(equipeRecuperada);
                }
            }
        }
        arquivoEquipes.close();
        std::cout << ">> Equipes carregadas: " << equipes.size() << " encontrada(s).\n";
    }

    // Carregar itens
    std::ifstream arquivoItens("itens.txt");
    if (arquivoItens.is_open()) {
        std::string linhaAtual;
        std::string idLido, nomeLido, pontosStr;

        while (std::getline(arquivoItens, linhaAtual)) {
            if (linhaAtual == "---ITEM---") {
                if (std::getline(arquivoItens, idLido) &&
                    std::getline(arquivoItens, nomeLido) &&
                    std::getline(arquivoItens, pontosStr)) {
                    try {
                        int pontos = std::stoi(pontosStr);
                        Item* itemRecuperado = new Item(idLido, nomeLido, "", pontos, nullptr);
                        itensCadastrados.push_back(itemRecuperado);
                    } catch (const std::invalid_argument&) {
                        std::cout << ">> Aviso: Pontuacao invalida ao carregar item '" << idLido << "'. Ignorado.\n";
                    }
                }
            }
        }
        arquivoItens.close();
        std::cout << ">> Itens carregados: " << itensCadastrados.size() << " encontrado(s).\n";
    }
}