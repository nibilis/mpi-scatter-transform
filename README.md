# Transformação Paralela de Dados com MPI

## Feito Por:
- Marco Antonio de Camargo - 10418309  
- Natan Moreira Passos - 10417916  
- Nicolas Henriques de Almeida - 10418357 <br> <br>
Sala 06G - Mackenzie

## Objetivo
Desenvolver um programa em **C com MPI** que distribui um vetor de inteiros igualmente entre os processos utilizando `MPI_Scatter`, aplica uma transformação sobre os dados localmente em cada processo e, em seguida, coleta os resultados com `MPI_Gather` para exibição no processo raiz.

---

## Funcionamento
1. O ambiente MPI é inicializado.
2. O processo 0 cria um vetor com **100 elementos sequenciais**.
3. O vetor é dividido igualmente entre todos os processos com `MPI_Scatter`.
4. Cada processo aplica uma função de transformação aos elementos recebidos.
5. Os dados transformados são enviados de volta ao processo 0 com `MPI_Gather`.
6. O processo 0 exibe o vetor original e o vetor transformado.

---

## Compilação e execução

### Compilar o código
- **Usando mpicc manualmente:**
```bash
mpicc atividade4.c -o atividade4
```
### Execução
```bash
mpirun -np <Numero_de_Processos> ./atividade4
```
