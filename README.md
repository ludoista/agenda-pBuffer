# agenda-pBuffer

Agenda em C sem variáveis e sem `struct`: todo o estado fica em um único bloco, o `void *pBuffer`, acessado por offsets. Toda função recebe só `void *pBuffer`.

**Menu:** 1 Adicionar · 2 Remover · 3 Buscar · 4 Listar · 5 Sair

## Glossário

| Nome | Significa | Uso |
| :--- | :--- | :--- |
| `MENU` | opção do menu | guarda a escolha (1 a 5) |
| `TOTAL` | total de pessoas | contador global; define o tamanho do buffer |
| `RI` | registrador *i* | índice dos loops |
| `RK` | registrador *k* | flag (0/1) ou valor de cálculo (tamanho, bytes a mover) |
| `SRC` | *source* | ponteiro de origem de uma leitura ou cópia |
| `DST` | *destination* | ponteiro de destino de uma escrita ou cópia |
| `IN_NAME` `IN_AGE` `IN_MAIL` | entrada | rascunho do que o usuário digitou |
| `R_NAME` `R_AGE` `R_MAIL` | registro | campos de uma pessoa salva |

## Offsets

| Offset | Tam. | Nome | Tipo |
| :--- | :--- | :--- | :--- |
| 000 | 4 | `MENU` | `int` |
| 004 | 4 | `TOTAL` | `int` |
| 008 | 4 | `RI` | `int` |
| 012 | 4 | `RK` | `int` |
| 016 | 8 | `SRC` | `char *` |
| 024 | 8 | `DST` | `char *` |
| 032 | 52 | `IN_NAME` | `char[]` |
| 084 | 4 | `IN_AGE` | `int` |
| 088 | 80 | `IN_MAIL` | `char[]` |
| **168** | | **início dos dados** | |
| *+000* | 52 | `R_NAME` | `char[]` |
| *+052* | 4 | `R_AGE` | `int` |
| *+056* | 80 | `R_MAIL` | `char[]` |

As três últimas linhas (em itálico) são sub-offsets dentro de cada pessoa, que ocupa 136 bytes.

```
endereço da pessoa N = pBuffer + 168 + (N * 136)       N de 0 a TOTAL - 1
endereço do campo    = endereço da pessoa N + sub-offset
```

## Pontos de atenção

* A única variável é o `pBuffer`, no `main`.
* O buffer mede `168 + TOTAL * 136` bytes. Quem muda `TOTAL` redimensiona.
* O `realloc` pode mudar o endereço: `Adicionar` e `Remover` retornam o novo `void *`, e o `main` faz `pBuffer = Funcao(pBuffer)`.
* `SRC` e `DST` ficam inválidos depois de um `realloc`: recalcule.
* `IN_NAME`, `IN_AGE` e `IN_MAIL` têm o mesmo layout de uma pessoa, então salvar é copiar 136 bytes.
