// Code made by:
//  - Marco Antonio de Camargo, RA: 10418309
//  - Natan Moreira Passos, RA: 10417916
//  - Nicolas Henriques de Almeida, RA: 10418357


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define DATA_SIZE 100

int main();
int transform_data(int x);


int main() {
    int id, ProcessAmount;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcessAmount);

    int local_data[DATA_SIZE / ProcessAmount];

    int* original_data = NULL;
    int* gathered_data = NULL;

    // Process 0 initializes original data and allocates space for gathered data
    if (id == 0) {
        original_data = (int *)malloc(sizeof(int) * DATA_SIZE);
        for (int i = 0; i < DATA_SIZE; ++i) {
            original_data[i] = i + 1;
        }

        gathered_data = (int *)malloc(sizeof(int) * DATA_SIZE);
    }

    MPI_Scatter(
        original_data,             // sendbuf: buffer with data to distribute (only valid at root)
        DATA_SIZE / ProcessAmount, // sendcount: number of elements sent to each process
        MPI_INT,                   // sendtype: data type of elements in send buffer
        local_data,                // recvbuf: buffer where each process will receive its portion
        DATA_SIZE / ProcessAmount, // recvcount: number of elements received by each process
        MPI_INT,                   // recvtype: data type of elements in receive buffer
        0,                         // root: rank of sending process (root process)
        MPI_COMM_WORLD             // comm: communicator
    );


    for (int i = 0; i < DATA_SIZE / ProcessAmount; ++i) {
        local_data[i] = transform_data(local_data[i]);
    }

    MPI_Gather(
        local_data,                // sendbuf: transformed data from each process
        DATA_SIZE / ProcessAmount, // sendcount: number of elements sent by each process
        MPI_INT,                   // sendtype: data type of elements being sent
        gathered_data,             // recvbuf: final buffer (only on process 0)
        DATA_SIZE / ProcessAmount, // recvcount: number of elements received from each process
        MPI_INT,                   // recvtype: data type of elements being received
        0,                         // root: root process
        MPI_COMM_WORLD             // comm: communicator
    );

    // proccess 0 prints the results
    if (id == 0) {
        printf("Original Data: ");
        for (int i = 0; i < DATA_SIZE; ++i) {
            printf("%d ", original_data[i]);
        }
        printf("\n");

        printf("Transformed Data: ");
        for (int i = 0; i < DATA_SIZE; ++i) {
            printf("%d ", gathered_data[i]);
        }
        printf("\n");

        free(original_data);
        free(gathered_data);
    }

    MPI_Finalize();
}
