#[[
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
programa. Se não, consulte https://www.gnu.org/licenses.
]]

cmake_minimum_required(VERSION 4.0.2)
project(ExperimentosCComp LANGUAGES C)
add_executable(experimentos-ccomp PRIVATE src/otimizacao-de-tipo-numerico)
