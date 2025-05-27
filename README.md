# Gerenciador Eletrônico de Documentos para Aprovação de Projetos

## Descrição do problema

Este projeto em C++ simula um sistema de gerenciamento de documentos (GED), onde é possível criar, atualizar, aprovar ou reprovar documentos de um projeto de engenharia. Os dados são armazenados em um arquivo CSV e os documentos simulam arquivos PDF em formato `.txt`, todos armazenados em uma pasta na área de trabalho. Essa aplicação é importante para o registro de análise de documentos de projetos de engenharia, desde comentários técnicos até a aprovação do documento, que pode ser utilizado para orientação e aplicação em obra, construção, ligações de equipamentos e afins.

## Funcionalidades

- Criar documento com nome e título imutáveis.
- Estados de revisão: 00A → 00B → 00C → aprovado(00).
- Reprovação gera reinício do processo de revisão.
- Cada documento criado gera um "PDF simulado" com nome e título (o PDF terá o nome como taxonomia).
- Pasta e CSV são criados automaticamente na área de trabalho pelo programa.

## Estrutura

- `main.cpp`: ponto de entrada.
- `documentmanager.h`: declaração da classe `DocumentManager`.
- `documentmanager.cpp`: implementação das funções do gerenciador.

## Como compilar

```bash
g++ main.cpp documentmanager.cpp -o gerenciador./gerenciador
```

## Autor

grupo gerenciador de documentos (PDS2)