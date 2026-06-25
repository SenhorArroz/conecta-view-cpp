#pragma once
#include <exception>
#include <string>

class GincanaException : public std::exception {
protected:
    std::string mensagem;
public:
    GincanaException(const std::string& msg) : mensagem(msg) {}

    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

class RegraNegocioException : public GincanaException {
public:
    RegraNegocioException(const std::string& msg) : GincanaException(msg) {}
};

class TransicaoEstadoInvalidaException : public RegraNegocioException {
public:
    TransicaoEstadoInvalidaException()
        : RegraNegocioException("Erro: Nao eh possivel pular estados ou alterar uma doacao ja finalizada.") {}
};

class PontuacaoInvalidaException : public RegraNegocioException {
public:
    PontuacaoInvalidaException()
        : RegraNegocioException("Erro: A pontuacao nao pode ser negativa.") {}
};

class IdDuplicadoException : public RegraNegocioException {
public:
    IdDuplicadoException(const std::string& tipo, const std::string& id)
        : RegraNegocioException("Erro: Ja existe um(a) " + tipo + " com o ID '" + id + "'.") {}
};

class EntidadeNaoEncontradaException : public RegraNegocioException {
public:
    EntidadeNaoEncontradaException(const std::string& tipo, const std::string& id)
        : RegraNegocioException("Erro: " + tipo + " com ID '" + id + "' nao foi encontrado(a).") {}
};

class EntradaInvalidaException : public GincanaException {
public:
    EntradaInvalidaException(const std::string& detalhe)
        : GincanaException("Erro de entrada: " + detalhe) {}
};

class ArquivoException : public GincanaException {
public:
    ArquivoException(const std::string& detalhe)
        : GincanaException("Erro de arquivo: " + detalhe) {}
};