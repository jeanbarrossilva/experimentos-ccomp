/*
Copyright © 2026 Jean Silva

Este arquivo faz parte do projeto de código aberto experimentos-ccomp.

Este programa é software livre: você pode redistribuí-lo e/ou modificá-lo sob os
termos da Licença Pública Geral GNU, conforme publicada pela Free Software
Foundation, seja na versão 3 da Licença, ou (à sua escolha) qualquer versão
posterior.

Este programa é distribuído na esperança de que seja útil, mas SEM QUAISQUER
GARANTIAS; sem sequer a garantia implícita de COMERCIALIZAÇÃO ou ADEQUAÇÃO A UM
FIM ESPECÍFICO. Consulte a Licença Pública Geral GNU para mais detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este
programa. Senão, consulte https://www.gnu.org/licenses.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
24 de fevereiro de 2026

Na aula de Algoritmos e Estrutura de Dados, perguntei ao professor se o
compilador que ele estava usando (que aparentava ser o MinGW) otimizava uma
variável de tipo numérico se o tipo definido ocupar mais memória do que a que é
necessária para a constante durante toda a execução de um programa.

Por exemplo: considere uma constante "n" declarada como float, mas cujas casas
decimais permancem sempre zeradas. Na fase de otimização da compilação, a
declaração poderia ser convertida para a de um long, int ou short int?

Apesar de eu ter mencionado o MinGW, por eu ter mais familiaridade com o Clang,
esse será o compilador com o qual este experimento será realizado. O
comportamento, portanto, pode diferir em outros compiladores.
*/

int main(void) {
  const char *sufixo_do_caminho_do_arquivo_gerado = ".gerado.c";
  char caminho_do_arquivo_gerado[
    sizeof(__FILE__)
      - sizeof(char)
      + sizeof(sufixo_do_caminho_do_arquivo_gerado)
  ];
  strncpy(
    caminho_do_arquivo_gerado,
    __FILE__,
    sizeof(__FILE__) - 3 * sizeof(char)
  );
  strcat(caminho_do_arquivo_gerado, sufixo_do_caminho_do_arquivo_gerado);
  FILE *arquivo_gerado = fopen(caminho_do_arquivo_gerado, "w");
  fprintf(
    arquivo_gerado,
    "#include <stdio.h>\n"
    "\n"
    "int main(void) {\n"
    "  const float n = 2;\n"

    // A impressão não é necessária funcionalmente; ela é uma mera tentativa de
    // sinalizar ao compilador que a constante é, de fato, referenciada pelo
    // programa, na esperança de que ela não seja descartada na fase de
    // otimização (caso fosse sê-lo).
    "  printf(\"%%f\", n);\n"

    "}\n"
  );
  fclose(arquivo_gerado);
  char *caminho_do_ir[sizeof(caminho_do_arquivo_gerado) + sizeof(char)];
  strncopy(
    caminho_do_ir,
    caminho_do_arquivo_gerado,
    sizeof(caminho_do_arquivo_gerado) - 2 * sizeof(char)
  );
  strcat(caminho_do_ir, "ll");
  char *comando_de_emissao_do_ir[
    25
      + sizeof(caminho_do_arquivo_gerado)
      - sizeof(char)
      + sizeof(caminho_do_ir)
  ];
  sprintf(
    comando_de_emissao_do_ir,

    // Existem três níveis de otimização do Clang (na verdade, hão mais alguns,
    // mas, para todos os efeitos e propósitos, consideraremos apenas estes):
    //
    // - O0, comum enquanto em depuração, no qual nenhuma otimização é
    // realizada;
    // - O1, descrito na documentação redundantemente apenas como "algo entre O0
    // e O2";
    // - O2, em que é realizada otimização moderada; e
    // - O3, caracterizado por habilitar todas as otimizações. Pode ter impacto
    // negativo no tempo de geração de código quanto produzir códigos mais
    // longos.
    //
    // Códigos de produção são, majoritariamente, otimizados em O2.
    "clang -emit-llvm %s -O2 -o %s",

    caminho_do_arquivo_gerado,
    caminho_do_ir
  );
  system(comando_de_emissao_do_ir);
}
