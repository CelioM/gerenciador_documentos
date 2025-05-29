# Gerenciador Eletrônico de Documentos para Aprovação de Projetos

## Descrição do problema

Este projeto em C++ simula um sistema de gerenciamento de documentos (GED), onde é possível criar, excluir, aprovar/reprovar (com comentário) e atender comentários de documentos de um projeto de engenharia. Os dados são armazenados em um arquivo CSV e são criados documentos que simulam arquivos PDF em formato `.txt`, todos armazenados em uma pasta na área de trabalho pelo programa. Essa aplicação é importante para registro de toda análise de documentos e projetos de engenharia, desde comentários técnicos até a aprovação do documento, que pode ser utilizado para orientação e aplicação em construção, ligações de equipamentos, instruções de montagem e funcionamento e afins.

O documento criado terá nome, titulo, status, revisão, comentários, horário da revisão, atribuído à. O "atribuído à" permite o analista e document manager atribuir à alguem que consta na lista de usuários de login, mas qualquer um pode acessar ou alterar o documento (desde que seguindo o fluxo abaixo), o atribuído é apenas uma sugestão (pode ser implementado restrição de acesso ao documento apenas para o analista atribuído, mas não é o intuito da aplicação deste trabalho). 

Neste programa, é possivel o analista, após o document manager inserir um documento, reprovar o projeto e inserir um comentário do por que foi reprovado, e quando outro analista faz a correção e atende o comentário (status atendido), muda-se a revisão automaticamente (00A -> 00B), e esse fluxo vai até a revisão 00C, depois disso o documento está pronto para aprovação, e chega à revisão 00, pronto para ser utilizado por um engenheiro ou técnico em campo/chão de fábrica. Essa correção seria um upload do arquivo corrigido, mas aqui estamos preocupados com fluxo de revisão na aplicação, a revisão alterada é o que demonstra que o documento foi corrigido e altera o histórico do documento, permitindo acompanhar o avanço da análise do projeto.

Cada usuário pode executar uma ação por vez no documento, o analista 1 pode reprovar ou aprovar, caso reprove e insira o motivo da reprovação, ele somente poderá voltar a alterar o documento após o projetista/analista X atender o comentário (e automaticamente sua revisão será alterada), assim o analista que fez o comentário e reprova pode voltar à aprovar ou reprovar o documento. O Document Manager pode criar e excluir o documento quando ele quiser.

## Funcionalidades

- Criar documento com nome (taxonomia: duf-quadroqpc1.pdf) e título (diagrama unifilar - quadro qpc1) imutáveis.
- Estados de revisão: 00A → 00B → 00C → aprovado(00).
- Reprovação gera reinício do processo de revisão, quando atendido a reprovação, altera revisão.
- Cada documento criado gera um "PDF simulado" com nome e título (o PDF terá o nome igual a taxonomia do documento).
- Pasta e CSV são criados automaticamente na área de trabalho pelo programa.
- Horário da ultima revisão do documento é gerada automaticamente pelo programa.
- O analista pode atribuir ou não à algum analista específico (opcional), mas não restringe outros analistas da empresa a alterarem/corrigir o documento.


## Estrutura

- `main.cpp`: ponto de entrada.
- `documentmanager.h`: declaração da classe `DocumentManager`.
- `documentmanager.cpp`: implementação das funções do gerenciador.
- `usuario.cpp`: implementação das funções de login.
- `util.cpp`: implementação das funções de criação de pasta na área de trabalho e buscar  informações do sistema operacional.

## Como compilar

```bash
g++ main.cpp documentmanager.cpp -o gerenciador./gerenciador
```

## Autor

grupo gerenciador de documentos (PDS2)