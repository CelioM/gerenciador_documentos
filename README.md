# Gerenciador Eletrônico de Documentos para Aprovação de Projetos

## Descrição do problema

Este projeto em C++ simula um sistema de gerenciamento de documentos, onde é possível criar, atualizar, aprovar ou reprovar documentos de um projeto de engenharia. Os dados são armazenados em um arquivo CSV e os documentos simulam arquivos PDF em formato `.txt`, todos armazenados em uma pasta na área de trabalho.

## Funcionalidades

- Criar documento com nome e título imutáveis.
- Estados de revisão: 00A → 00B → 00C → aprovado.
- Reprovação gera reinício do processo de revisão.
- Cada documento criado gera um "PDF simulado" com nome e título.
- Pasta e CSV são criados automaticamente na área de trabalho.

## Estrutura

- `main.cpp`: ponto de entrada.
- `documentmanager.h`: declaração da classe `DocumentManager`.
- `documentmanager.cpp`: implementação das funções do gerenciador.

## Como compilar

```bash
g++ main.cpp documentmanager.cpp -o gerenciador
./gerenciador
```

## Como usar com GitHub

1. **Criar repositório:**
   ```bash
   git init
   git add .
   git commit -m "Primeiro commit"
   git branch -M main
   git remote add origin https://github.com/seuusuario/seurepo.git
   git push -u origin main
   ```

2. **Novos commits:**
   ```bash
   git add .
   git commit -m "Atualizações"
   git push
   ```

## Autor

Desenvolvido como parte de um trabalho prático de PDS2 (Programação e Desenvolvimento de Software 2).