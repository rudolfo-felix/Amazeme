/******************************************************************************
 * MEEC - AED - 2ºsemestre 2017/2018
 * AMAZEME - PROJETO FINAL DE AED
 * Group:     GP25
 * Authors:   Pedro Chanca & Rudolfo Félix
              n*87101      & nº87114
 *****************************************************************************
 *****************************************************************************
 * File Name: funcs.h
 * COMMENTS: Funções de necessários para as avaliações de dados
             e resolução de problemas
 *****************************************************************************/
#include "funcs.h"

/*****************************************************************************
* first_line
* Arguments: FILE *fp, int *L, int *C, int *l1, int *c1, int *k, int *m, int *ei
* Returns: int
* COMMENTS: Função que lê a primeira linha do ficheiro de entrada de
            cada um dos problemas que esse contém. Dá return de '1' caso o numero
            de variáveis diferentes seja igual a 7, caso contrário dá return de '0'.
*****************************************************************************/
int first_line(FILE *fp, int *L, int *C, int *l1, int *c1, int *k, int *m, int *ei)
{
  if(fscanf(fp, "%d %d %d %d %d %d %d", L, C, m, l1, c1, k, ei)==7) return CORRECT;

  return 0;
}
/*****************************************************************************
* game_mode
* Arguments: int L, int C, int l1, int c1, int k, int m, int ei
* Returns: int
* COMMENTS: Função que faz return do modo de jogo, MODO_MIN ou MODO_MAX,
            caso o problema seja válido.
            No caso de este não o ser, dá return de MODE_INVLD.
*****************************************************************************/
int game_mode(int L, int C, int l1, int c1, int k, int m, int ei)
{
  if ((l1>=1)&&(l1<=L)&&(c1>=1)&&(c1<=C)&&(m==-2 || m>0)&&(k>=0)&&(ei>0))
  {
    if(m>0)   return MODE_MIN; /*variante 1*/
    if(m==-2) return MODE_MAX; /*variante 2*/
  }
  return MODE_INVLD;
}

/*****************************************************************************
* mode_invalid
* Arguments:FILE* fp_in, FILE* fp_out, int L, int C, int l1, int c1, int k, int m, int ei
* Returns: int
* COMMENTS: Função que inicialmente verifica se todos os espaços da
            matriz apresentam um inteiro. De seguida, imprime no ficheiro de saída
            que o problema é inválido caso o número de passos, 'k',
            seja maior ou igual que L*C (número de linhas*número de colunas).
            Caso contrário, imprime na primeira linha do ficheiro com a informação da primeira
            linha do ficheiro de entrada.
*****************************************************************************/
int mode_invalid(FILE* fp_in, FILE* fp_out, int L, int C, int l1, int c1, int k, int m, int ei)
{
  int i, j, valor=0;

  for (i = 1; i <=L; i++)
  {
      for (j = 1; j <=C; j++) if (fscanf(fp_in, "%d", &valor)!=1)exit(0);
  }

  if( k >= L*C)
  {
    fprintf(fp_out,"%d %d %d %d %d %d %d %d\n\n", L, C, m, l1, c1 , k , ei, -1);
    /*problema sem solução*/
  }
  else fprintf(fp_out,"%d %d %d %d %d %d %d\n\n", L, C, m, l1, c1, k, ei);/*problema mal definido*/

  return 0;
}


/*****************************************************************************
* only_invalids
* Arguments:char *fileIn
* Returns: void
* COMMENTS: Função chamada apenas na função getMaxSize caso o ficheiro
seja todo ele composto por problemas inválidos. Dentro da mesma é realizado a abertura do
ficheiro de entrada e saída, atribuição do nome do ficheiro de saída, impressão da primeira
linha dos problemas inválidos e finalmente o fecho do ficheiro de entrada e de saída tal como a
libertação de memória alocada para a atribuição do nome do ficheiro de saída.
*****************************************************************************/
void only_invalids(char *fileIn)
{
  FILE * fpIn    = NULL;
  FILE * fpOut    = NULL;
  char * fileOut  = NULL;

  int L, C, l1, c1, k, m, ei;

  fpIn  = AbreFicheiro (fileIn, "r" );
  getOutputName(fileIn, &fileOut);
  fpOut = AbreFicheiro ( fileOut, "w" );

  while(first_line(fpIn, &L, &C, &l1, &c1, &k, &m, &ei) == CORRECT)
  {
    mode_invalid(fpIn,fpOut, L, C, l1, c1, k, m, ei);
  }

  if(fpIn != NULL) fclose(fpIn);
  if(fpOut != NULL) fclose(fpOut);
  if (fileOut != NULL) free(fileOut);

  exit(0);
}

/*****************************************************************************
* getMaxSize
* Arguments: FILE* fpIn, char * fileIn, int * lines, int * cols
* Returns: void
* COMMENTS:Função \textit{void} que cálcula a maior matriz útil através do auxílio da
primeira linha de cada um dos problemas que se encontram no ficheiro de entrada '.maps'.
Se o ficheiro só tiver problemas for mal definidos, é chamada a função only_invalids
 que escreve no ficheiro de saída a primeira linha de cada problema e o programa termina,
 não havendo alocação de memória para qualquer matriz.
Após o cálculo ter sido executado, a função irá retornar os valores
do número máximo de linhas(line) e colunas(cols) da matriz útil.
*****************************************************************************/
void getMaxSize(FILE* fpIn, char * fileIn, int * lines, int * cols)
{
    int dummy, i, j;
    int max_cols = 0, max_lines = 0;
    int L, C, l1, c1, k, m, ei, mode;

    int flag_lines = 0, flag_cols = 0, u_lines = 0, d_lines = 0, l_cols = 0, r_cols = 0;

    int flag_problems=0;/* numero de problemas*/
    int flag_invalids=0;/* numero de problemas invalidos*/

    while(first_line(fpIn, &L, &C, &l1, &c1, &k, &m, &ei)==CORRECT)
    {
      flag_problems++;

      mode = game_mode(L, C, l1, c1, k, m, ei);
      /*Lê a matriz sem guardar valores para avaliar a proxima primeir linha do seguinte problema*/
      for(i = 1; i <=L; i++)
      {
        for(j = 1; j <=C; j++) if(fscanf(fpIn, "%d", &dummy)!=1)exit(0);
      }

      if(mode ==MODE_INVLD) flag_invalids++;/*numero de problemas invalidos*/

      if(mode ==MODE_MIN || mode == MODE_MAX)/*avaliação da matiz util pela variavel k(passos)*/
      {
        u_lines = k;
        if(l1-u_lines<1)u_lines=l1-1;
        d_lines = k;
        if(l1+d_lines>L)d_lines=L-l1;
        l_cols = k;
        if(c1-l_cols<1)l_cols=c1-1;
        r_cols = k;
        if(c1+r_cols>C)r_cols=C-c1;

        flag_lines = u_lines+d_lines+1;/*maximo de 2k+1*/
        flag_cols = l_cols+r_cols+1;/*maximo de 2k+1*/

        if(flag_lines>max_lines)max_lines = flag_lines;
        if(flag_cols>max_cols) max_cols = flag_cols;
      }
    }

    /*se um ficheiro tiver só problemas invalidos*/
    if((flag_problems-flag_invalids)==0)
    {
      fclose(fpIn);
      only_invalids(fileIn);
    }


    (*lines) = max_lines;
    (*cols) = max_cols;
    return;
}

/*****************************************************************************
* min_max
* Arguments:MAZE* maze, int *min_orig_line, int *min_orig_col, int *max_orig_line, int *max_orig_col, int mode
* Returns: void
* COMMENTS: Função \textit{void} cujo objetivo é definir os limites originais da matriz útil
na matriz original de cada problema, calculado entre a diferença da menor e
maior linha(min_orig_line/max_orig_line) e coluna(min_orig_col/max_orig_col) original.
\item É de ter em conta que o a menor de linha e coluna nunca poderá ser menor que 1
e para a maior linha e coluna da matriz útil não poderá ser maior que L e C, respetivamente.
*****************************************************************************/
void min_max (MAZE* maze, int *min_orig_line, int *min_orig_col, int *max_orig_line, int *max_orig_col, int mode)
{
  int L, C, l1, c1, k;

  L = getNumLines(maze);
  C = getNumCols(maze);

  l1= getStartLine(maze);
  c1= getStartCol(maze);

  k = getK(maze);

  /*calculo dos limites da matriz util na matriz original,
  tendo um tamho maximo de [2k+1 x 2k+1]*/
  if(mode ==MODE_MIN || mode ==MODE_MAX)
  {
    *min_orig_line =l1-k;
    if(*min_orig_line<1)*min_orig_line=1;

    *min_orig_col =c1-k;
    if(*min_orig_col<1)*min_orig_col=1;

    *max_orig_line=l1+k;
    if(*max_orig_line>L)*max_orig_line=L;

    *max_orig_col =c1+k;
    if(*max_orig_col>C)*max_orig_col=C;

    return;
  }
  return;
}

/*****************************************************************************
* readFromFileToMatrix
* Arguments: FILE * fp, MAZE *maze, int mode
* Returns: void
* COMMENTS: Função \textit{void} tem como objetivo copiar a matriz que se encontra no ficheiro de entrada '.maps' para a estrutura MATRIX.
\item Inicialmente, é cálculado o número de linhas e colunas da matriz útil do problema através do recurso da função min{\_}max, explicada
anteriormente. Recorrendo a dois ciclos for's, a matriz útil é preenchida com os seguintes dados:
energia da posição, a qual é copiada do ficheiro através do comando 'fscanf', a linha
e coluna da matriz original de cada uma das posições e inicialização da variável 'lamp' a 0,
sendo que a posição inicial inicia com a variável 'lamp' a 1.
*****************************************************************************/
void readFromFileToMatrix (FILE * fp, MAZE *maze, int mode)
{
  int L, C, l1, c1;

  L=getNumLines(maze);
  C=getNumCols(maze);
  l1=getStartLine(maze);
  c1=getStartCol(maze);

  int i, j, valor=0, _l=0, _c=0;

  int min_orig_col = 1, min_orig_line = 1;
  int max_orig_col = C, max_orig_line = L;

  /*limites da matriz util*/
  min_max (maze, &min_orig_line, &min_orig_col, &max_orig_line, &max_orig_col, mode);

  int newNumlines, newNumCols;

  newNumlines = (max_orig_line - min_orig_line+1);/*linhas da matriz util*/
  newNumCols = (max_orig_col - min_orig_col+1);/*colunas da matriz util*/
  updateNewNumLines(maze, newNumlines);
  updateNewNumCols(maze, newNumCols);

  int flag_newstartcol=0;

  for (i = 0; i < L; i++)
  {
      for (j = 0; j < C; j++)
      {
        if (fscanf(fp, "%d", &valor)!=1)exit(0);

        if((i>=min_orig_line-1)&&(i<max_orig_line)&&(j>=min_orig_col-1)&&(j<max_orig_col))
        {/*se estiver dentro dos limites da matriz util, guardados os valores*/
          if ((j==c1-1)&&(flag_newstartcol==0))
          {
            updateNewStartCol(maze, _c);/*coluna da posicção inicial na matriz util*/
            flag_newstartcol = 1;
          }
          updatePrize(maze, _l, _c, valor);
          updateOrigLine(maze, _l, _c, i+1);
          updateOrigCol(maze, _l, _c, j+1);
          updateLamp(maze, _l, _c, 0);
          _c++;
        }
      }
      _c=0;

      if((i>=min_orig_line-1)&&(i<max_orig_line))
      {
        if (i==l1-1) updateNewStartLine (maze, _l);/*linha da posicção inicial na matriz util*/
        _l++;
      }
  }
  updateLamp(maze, getNewStartLine(maze), getNewStartCol(maze), 1);/*a posição inicial é visitada*/

  return;
}

/*****************************************************************************
* upper_bond
* Arguments: MAZE* maze, int l_atual, int c_atual
* Returns: int
* COMMENTS: Função \textit{int} calcula o maior ganho posível no diamante da coordenada recebida.
Este ganho é a variavél majorante que é a soma dos k{\_}atual( número de passos restantes à
coordenada recebida, k{\_}) maiores prémios positivos e ainda não visitados.
Retornando assim o valor de majorante.
*****************************************************************************/
int upper_bond (MAZE* maze, int l_atual, int c_atual)
{
  int j=0,flag_c=0, i=0;

  int _l, _c;

  int _L=getNewNumLines(maze), _C=getNewNumCols(maze);

  int k_atual=0;
  k_atual=getK_r(maze);

  int majorante =0, minorante= 0, menor_casa = 0;

  int s[k_atual];
  for(i=0; i<k_atual; i++) s[i]=minorante;


  for(_c= c_atual;(_c>=0)&&(_c>= c_atual-k_atual);_c--)
  {/*lado esquerdo*/
    j=k_atual-flag_c;
    _l= l_atual-j;
    if(_l<0) _l=0;
    while((_l<=l_atual+j)&&(_l<_L))
    {
      if(getLamp(maze, _l, _c )==0 && getPrize(maze, _l, _c)>0)
      {
        if(s[menor_casa]!=minorante)
        {
          for(i=0; i<k_atual; i++)
          {
            if(s[i]<s[menor_casa]) menor_casa = i;
          }
        }
        if(getPrize(maze, _l, _c)>s[menor_casa])s[menor_casa]=getPrize(maze, _l, _c);
      }
      _l++;
      }
    flag_c++;
  }

  flag_c=1;

  for(_c= c_atual+1;(_c< _C)&&(_c<= c_atual+ k_atual);_c++)
  {/*lado direito*/
    j=k_atual-flag_c;
    _l= l_atual-j;
    if(_l<0) _l=0;
    while((_l<= l_atual+j)&&(_l< _L))
    {
      if( getLamp(maze, _l, _c )==0 && getPrize(maze, _l, _c)>0)
      {
        if(s[menor_casa]!=minorante)
        {
          for(i=0; i<k_atual; i++)
          {
            if(s[i]<s[menor_casa] ) menor_casa = i;
          }
        }
        if(getPrize(maze, _l, _c)>s[menor_casa] ) s[menor_casa]=getPrize(maze, _l, _c);
      }
      _l++;
      }
    flag_c++;
  }

  for(i=0; i<k_atual; i++) majorante = majorante + s[i];

  return majorante;

}
/*****************************************************************************
* positive_update
* Arguments: MAZE *maze, MATRIX* path, int l_atual, int c_atual
* Returns: void
* COMMENTS: Função que tem como propósito a atualização de variáveis após a ocorrência de um passo válido na variante 1 ou 2.
 Contém assim as seguintes atualizações:
- Energia final (ef) e diminuição do número de passos restantes(k{\_}r) na estrutura tipo MAZE;
- Adiciona uma nova posição no array 'path', através da função increasePath, com os valores da coordenadas da matriz original,
energia da posição e ativação da flag 'lamp' (variáveis pertencentes à estrutura tipo MATRIX).

Para que ocorra as atualizações acima, o número de passos dados até ao momento têm de ser menores que o número de passos máximos e maiores ou iguais a '0'.
Para além de atualização de dados, também ocorre a verificação se a variante 1 ou 2 já alcançou a solução final desejada.
*****************************************************************************/
void positive_update(MAZE *maze, MATRIX* path, int l_atual, int c_atual)
{
  int step = getK(maze)-getK_r(maze);
  int k_restante = getK_r(maze)-1;
  int target = getM(maze);

  updateLamp(maze, l_atual, c_atual, 1);/*passa a visitado*/
  updateEf(maze, getEf(maze)+getPrize(maze, l_atual, c_atual));/*a energia atual é atualizada*/
  updateK_r(maze, k_restante);/*há menos um passo*/


  if(step<getK(maze) && step>=0)/*adiciona o passo ao caminho*/
    increasePath(path, step, getOrigLine(maze, l_atual, c_atual), getOrigCol(maze, l_atual, c_atual), getPrize(maze, l_atual, c_atual));

  /*se o caminho for preenchido, o problema tem solução*/
  if(target>0)/*variante 1*/
  {
    if(getK_r(maze)==0 &&(getEf(maze) >= target)) updateSolved(maze, 1);
  }
  else/*variante 2*/
  {
    if(getK_r(maze)==0 &&(getEf(maze) > 0)) updateSolved(maze, 1);
  }

  return;
}
/*****************************************************************************
* negative_update
* Arguments:MAZE *maze, MATRIX* path, int l_atual, int c_atual
* Returns: void
* COMMENTS: Função \textit{void} que tem como propósito a atualização de variáveis, tal como a função positive{\_}update,
mas nesta as atualizações ocorrem quando há um passo atrás na matriz, sendo válida a sua utilização tanto na variante 1 como na 2.
 Contém assim as seguintes atualizações:
- Energia final (ef) e aumento do número de passos restantes(k{\_}r) na estrutura tipo MAZE;
- Coloca na última posição do array 'path', através da função reduzePath, os valores da coordenadas da matriz original e energia da posição a '0'
 e é desativada a flag 'lamp' (variáveis pertencentes à estrutura tipo MATRIX).
 Para além de atualização de dados, também ocorre a verificação se a variante 1 ou 2 já alcançou a solução final desejada.
*****************************************************************************/
void negative_update(MAZE *maze, MATRIX* path, int l_atual, int c_atual)
{
  int step = getK(maze)-getK_r(maze)-1;
  int k_restante = getK_r(maze)+1;

  updateLamp(maze, l_atual, c_atual, 0);/*passa a nao visitado*/
  updateEf(maze, getEf(maze)-getPrize(maze, l_atual, c_atual));/*energia final é desatualizado*/
  updateK_r(maze, k_restante);/*há mais um passo restante*/

  if(step<getK(maze) && step>=0) reduzePath(path, step);/*elimina o passo o ultimo do caminho guardado*/

  return;
}
/*****************************************************************************
* sub_mode_min
* Arguments: MAZE* maze, MATRIX* path, int l_direction, int c_direction
* Returns: int
* COMMENTS: função que avalia se cada bloco  para adicionar ao caminho ou retirar se os seus caminhos
          possiveis forem invalidos. Procura em DFS
          Retorna 1 se for o vetor que guarda o caminho for preenchido
*****************************************************************************/
int sub_mode_min(MAZE* maze, MATRIX* path, int l_direction, int c_direction)
{
  int _L =getNewNumLines(maze), _C =getNewNumCols(maze);
  /*quaqlquer direção*/
  if(l_direction>=0 && l_direction <_L && c_direction>=0 && c_direction<_C)
  {
    int target = getM(maze);
    int somaDirection = getEf(maze)+getPrize(maze, l_direction, c_direction);
    int maxSomaDirection = getEf(maze)+upper_bond (maze, l_direction, c_direction);

    if(getLamp(maze, l_direction, c_direction)==0 && somaDirection>0 && maxSomaDirection>= target)
    {
      if(getSolved(maze) == 0) positive_update(maze, path, l_direction, c_direction);
      if(getSolved(maze) == 1) return 1;
      else if(mode_min( maze, path, l_direction, c_direction)==0) negative_update(maze, path, l_direction, c_direction);
    }
  }
  return 0;
}
/*****************************************************************************
* mode_min
* Arguments: MAZE* maze, MATRIX* path, int l_atual, int c_atual
* Returns: int
* COMMENTS: Função recursiva que encontra o primeiro caminho que atinge um certo objetivo de energia
*****************************************************************************/
int mode_min(MAZE* maze, MATRIX* path, int l_atual, int c_atual)
{
  int target = getM(maze);

  if(getK_r(maze)==0 && getEf(maze)>=target)
  {/*problema resolvido que nao houver passos restante e se a energia final for maior ou igual que o objetivo*/
    updateSolved(maze, 1);
    return 1;
  }
  else
  {
    int _L =getNewNumLines(maze), _C =getNewNumCols(maze);
    int maxSomaAtual = getEf(maze)+upper_bond (maze, l_atual, c_atual);

    if(getSolved(maze)==0 &&(maxSomaAtual>=target)&&(getK_r(maze)>0))
    {/*blocos adjacentes a analisar por DFS*/
      int l_direction = 0, c_direction = 0;
      /*up*/
      if(l_atual-1>=0)
      {
        l_direction = l_atual-1;
        c_direction = c_atual;
        if(sub_mode_min(maze, path, l_direction,  c_direction) == 1) return 1;
      }

      /*down*/
      if(l_atual+1 < _L)
      {
        l_direction = l_atual+1;
        c_direction = c_atual;
        if(sub_mode_min(maze, path, l_direction,  c_direction) == 1) return 1;
      }

      /*left*/
      if(c_atual-1>=0)
      {
        l_direction = l_atual;
        c_direction = c_atual-1;
        if(sub_mode_min(maze, path, l_direction,  c_direction) == 1) return 1;
      }

      /*right*/
      if(c_atual+1 < _C)
      {
        l_direction = l_atual;
        c_direction = c_atual+1;
        if(sub_mode_min(maze, path, l_direction,  c_direction) == 1) return 1;
      }
    }
  }

  if(getSolved(maze)==1) return 1;
  else return 0;
}

/*****************************************************************************
* sub_mode_max
* Arguments:MAZE* maze, MATRIX *path, MATRIX *b_path, int l_direction, int c_direction
* Returns: int
* COMMENTS: função que avalia se cada bloco  para adicionar ao caminho ou retirar se os seus caminhos
          possiveis forem invalidos. Procura em DFS
          Substitui o vetor b_path pelo path se este ultimo tive uma energia final maior que o de b_path
*****************************************************************************/
int sub_mode_max(MAZE* maze, MATRIX *path, MATRIX *b_path, int l_direction, int c_direction)
{
  int _L =getNewNumLines(maze), _C =getNewNumCols(maze);

  /*qualquer direção*/
  if(l_direction>=0 && l_direction <_L && c_direction>=0 && c_direction<_C)
  {
    int i = 0;
    int somaDirection    = getEf(maze)+getPrize(maze, l_direction, c_direction);
    int maxSomaDirection = getEf(maze)+upper_bond (maze, l_direction, c_direction);

    if(getLamp(maze, l_direction, c_direction)==0 && somaDirection >0  && maxSomaDirection >= getEb(maze) )
    {
      positive_update(maze, path, l_direction, c_direction);

      if(getK_r(maze)==0 && getEf(maze) > getEb(maze))
      {
        for(i=0; i<getK(maze);i++)
        {/*melhor caminho*/
          subMAX(path,b_path,i);
          updateEb(maze, getEf(maze));
        }
        negative_update(maze, path, l_direction, c_direction);
      }
      else if(mode_max( maze, path, b_path, l_direction, c_direction)==0 ) negative_update(maze, path, l_direction, c_direction);
    }
  }
  return 0;
}
/*****************************************************************************
* mode_max
* Arguments: MAZE* maze, MATRIX *path, MATRIX *b_path, int l_atual, int c_atual
* Returns: int
* COMMENTS: Função que encontra o melhor caminho possivel do problema
*****************************************************************************/
int mode_max(MAZE* maze, MATRIX *path, MATRIX *b_path, int l_atual, int c_atual)
{
  if(getK(maze)==0 && getEi(maze)>0)
  {/*problema resolvido se não há passos e a energia incial é maior que zero*/
    updateSolved(maze, 1);
    return 0;
  }
  else
  {
    int _L =getNewNumLines(maze), _C =getNewNumCols(maze);
    int maxSomaAtual = getEf(maze)+upper_bond(maze, l_atual, c_atual);

    if( maxSomaAtual > getEb(maze) && getK_r(maze)>0)
    {/*blocos adjacentes a analisar por DFS*/
      int l_direction = 0, c_direction = 0;
      /*up*/
      if(l_atual-1>=0)
      {
        l_direction = l_atual-1;
        c_direction = c_atual;
        sub_mode_max(maze, path, b_path, l_direction,  c_direction);
      }

      /*down*/
      if(l_atual+1 < _L)
      {
        l_direction = l_atual+1;
        c_direction = c_atual;
        sub_mode_max(maze, path, b_path, l_direction,  c_direction);
      }

      /*left*/
      if(c_atual-1>=0)
      {
        l_direction = l_atual;
        c_direction = c_atual-1;
        sub_mode_max(maze, path, b_path, l_direction,  c_direction);
      }

      /*right*/
      if(c_atual+1 < _C)
      {
        l_direction = l_atual;
        c_direction = c_atual+1;
        sub_mode_max(maze, path, b_path, l_direction,  c_direction);
      }
    }
  }

  return 0;
}
/*****************************************************************************
* unsolved
* Arguments: FILE* fp_out, MAZE*maze
* Returns: int
* COMMENTS: função que escreve no ficheiro de saída a primeira linha e -1 que nao houver solução
*****************************************************************************/
int unsolved(FILE* fp_out, MAZE*maze)
{
  int L=  getNumLines(maze);
  int C=  getNumCols(maze);
  int m=  getM(maze);
  int l1= getStartLine(maze);
  int c1= getStartCol(maze);
  int k = getK(maze);
  int ei= getEi(maze);

  fprintf(fp_out,"%d %d %d %d %d %d %d %d\n\n", L, C, m, l1, c1 , k , ei, -1);

  updateEf(maze, 0);

  return 0;
}
/*****************************************************************************
* solved
* Arguments: FILE* fp_out, MAZE*maze, MATRIX* path
* Returns: int
* COMMENTS: Função que escreve no ficheiro de saída a resolução do problema.
            -Primeira linha + oitavo inteiro com a energial finalmente
            -Apresenta k passsos dados com as coordenadas e o seu custo.

            Na variante 1, o path é o vetor do caminho atual que foi preenchido
            Na variante 2, o path é o vetor do melhor caminho que foi preenchido
*****************************************************************************/
int solved(FILE* fp_out, MAZE*maze, MATRIX* path)
{
  int L= getNumLines(maze);
  int C= getNumCols(maze);
  int m= getM(maze);
  int l1= getStartLine(maze);
  int c1= getStartCol(maze);
  int k = getK(maze);
  int ei= getEi(maze);
  int ef = getEf(maze);

  if(k==0 && (m==-MODE_MAX||(m>0 && ei>=m))) fprintf(fp_out,"%d %d %d %d %d %d %d %d\n", L, C, m, l1, c1 , k , ei, ei);

  if(k>0)
  {
    if(m==-2) ef=getEb(maze);/*na variante 2, a energia final será a melhor energia encontrada*/

    fprintf(fp_out,"%d %d %d %d %d %d %d %d\n", L, C, m, l1, c1 , k , ei, ef);

    int i=0, l=0, c=0, pr=0;
    for(i=0; i<getK(maze); i++)
    {
      l = getStepLine(path, i);
      c = getStepCol(path, i);
      pr = getStepPrize(path, i);
      fprintf(fp_out,"%d %d %d\n", l , c, pr);
    }

    fprintf(fp_out,"\n" );
  }

  updateEb(maze, 0);
  updateEf(maze, 0);
  updateSolved(maze, 0);

  return 0;
}
/*****************************************************************************
* play_game
* Arguments:FILE *fp_out, MAZE* maze,  int mode
* Returns: int
* COMMENTS:  Função que chama as funções necessárias para a resolução
do tabuleiro consoante o modo de jogo e liberta os vetores alocados para guardar os caminhos.
*****************************************************************************/
int play_game(FILE *fp_out, MAZE* maze,  int mode)
{
 /*variante 1*/
  if(mode==MODE_MIN)
  {
    MATRIX* path = newPath(getK(maze));/*vetor do caminho atual*/

    mode_min( maze, path, getNewStartLine(maze), getNewStartCol(maze));

    if(getSolved(maze)==1)
    {/*com solução*/
      solved(fp_out, maze, path);
      freePath(path);
      return 0;
    }
    else
    {/*sem solução*/
      unsolved(fp_out, maze);
      freePath(path);
      return 0;
    }
  }

  /*variante 2*/
  if(mode==MODE_MAX)
  {
    MATRIX *path   = newPath(getK(maze));/*vetor do caminho atual*/
    MATRIX *b_path = newPath(getK(maze));/*vetor do melhor caminho*/

    mode_max(maze, path, b_path, getNewStartLine(maze), getNewStartCol(maze));

    if(getSolved(maze)==1)
    {/*com soluão*/
      solved(fp_out, maze, b_path);
      freePath(b_path);
      freePath(path);
      return 0;
    }
    else
    {/*sem solução*/
      unsolved(fp_out, maze);
      freePath(b_path);
      freePath(path);
      return 0;
    }
  }
  return 0;
}
