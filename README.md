# Sistema de Gestão de Gincana - Conecta View

Este projeto consiste em um sistema em C++ para o gerenciamento completo de uma gincana, permitindo o controle de equipes, doações de itens, provas de apresentação e pontuações, garantindo a integridade dos dados e a persistência em arquivo.

## 🛠 Funcionalidades
- **Cadastro de Equipes**: Gestão centralizada de equipes participantes.
- **Sistema de Doações**: Cadastro de itens doados com cálculo automático de pontos.
- **Gestão de Provas**: Lançamento de notas por juízes e cálculo de pontuação por desempenho.
- **Persistência de Dados**: Salvamento e carregamento de toda a estrutura da gincana via arquivos de texto.
- **Hierarquia de Usuários**: Diferenciação entre Administradores e Membros da Equipe.

## 👥 Autores
- **Luiz Roberto Guimarães Campos**
- **Maria Mariana Varela Cavalcanti Souto**

## 🏗 Arquitetura
O sistema utiliza conceitos avançados de Orientação a Objetos:
- **Polimorfismo**: Utilizado para tratar `Doacoes` e `Provas` como `AtividadesPontuadas`.
- **Exceções Customizadas**: Tratamento de erros de lógica (ex: transições de estados inválidas ou pontuações negativas).
- **Interface IPersistente**: Padronização dos métodos `salvar` e `carregar` em todos os modelos.

## 🚀 Como Compilar e Executar
Certifique-se de ter o compilador `g++` instalado. Na raiz do projeto

Se utiliza o windows:
```bash
g++ -Wall -Wextra -std=c++17 -Iinclude   src/Main.cpp   src/controllers/GincanaController.cpp   src/models/Administrador.cpp   src/models/AtividadePontuada.cpp   src/models/Doacao.cpp   src/models/Equipe.cpp   src/models/Item.cpp   src/models/ItemSendoDoado.cpp   src/models/MembroEquipe.cpp   src/models/ProvaGincana.cpp   src/models/Usuario.cpp   -o gincana_app.exe && ./gincana_app.exe
```

Se Linux:
```bash
g++ -Wall -Wextra -std=c++17 -Iinclude \
  src/Main.cpp \
  src/controllers/GincanaController.cpp \
  src/models/Administrador.cpp \
  src/models/AtividadePontuada.cpp \
  src/models/Doacao.cpp \
  src/models/Equipe.cpp \
  src/models/Item.cpp \
  src/models/ItemSendoDoado.cpp \
  src/models/MembroEquipe.cpp \
  src/models/ProvaGincana.cpp \
  src/models/Usuario.cpp \
  -o gincana_app && ./gincana_app
```