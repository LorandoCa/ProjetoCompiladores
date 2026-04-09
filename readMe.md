Ja esta tudo preparado para começar a proxima meta. Ja adicionei todos os ficheiros que devem ser adicionados para começar a proxima meta

1º objetivo: Substituir petit.l por jucompiler.l. Para isso fazer os pontos abaixo.

Ordem de trabalho:
1. Adicionar a funcionalidade de mandar o token e o seu valor editando o yy.leme, no lexer da primeira meta (Tomar como exemplo o lexer da segunda meta)
   Desta forma podemos testar o nosso novo .y com o lexer antigo e veriifcar se está mesmo funcional 

2. Reduzir a gramática no enunciado para deixar de ser ambigua 
   Notas : Estudar o q é uma gramática ambigua e estudar como fazer uma gramática ambigua ser recursiva a esquerda

3. Usar a gramática reduzida para formar a árvore

4. Fazer a função de print da arvore. A funcao tem nós especificos que pode printar( verificar no enunciado do problema )

5. Fazer o tratamento de erros (explicado no enunciado)
