# VotacaoAEDS
Este trabalho consiste na implementação de um sistema de votação na linguagem de programação C que permite o cadastro de eleitores/candidatos que poderão votar e também ser votado através de seu título de eleitor. O programa foi feito utilizando árvores binárias de busca (ABB) e todas suas operações auxiliares básicas.

Menu: 
- Cadastrar um título: insere o título e nome na árvore de títulos válidos.
- Descadastrar um título: retira o título da árvore de títulos válidos (se esse estiver lá) e apaga os dados.
- Iniciar nova votação: inicializa/esvazia a ABB que guarda os títulos que já votaram.
- Votar: lê o número do título e o voto. Se o número é válido e se ainda não votou, atualiza a ABB que armazena
os títulos de quem já votou e computa o voto (em quem votou). Se o número não é válido ou já votou, emite
mensagem de erro.
- Retirar voto: lê o número do título e verifica se já votou. Se já votou, retira o título e o voto. Caso contrário,
emite mensagem de erro.
- Mostrar resultado parcial das eleições: mostra o resultado da eleição ordenado pelo mais votado até o menos votado.
- Listar todos os números de títulos e nomes das pessoas que já votaram.
- Sair: libera todas as estruturas e encerra o programa.

