#ifndef MPI_DEBUG_H
#define MPI_DEBUG_H

#include <mpi.h>

namespace mpi_debug {

namespace {
static int get_rank() {
        int rank;
        // always get global rank
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        return rank;
}
}

static int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, 
             int tag, MPI_Comm comm) {
    std::stringstream ss;
    const int rank = get_rank();
    std::cerr << "rank " << rank << "  MPI_Send\n";
    return ::MPI_Send(buf, count, datatype, dest, tag, comm);

}

static int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source,
             int tag, MPI_Comm comm, MPI_Status *status) {
    std::stringstream ss;
    const int rank = get_rank();
    std::cerr << "rank " << rank << " MPI_Recv\n";
    return ::MPI_Recv(buf, count, datatype, source, tag, comm, status);

}

template <typename T>
static int MPI_Isend(const T *buf, int count, MPI_Datatype datatype, int dest, 
              int tag, MPI_Comm comm, MPI_Request *request) {
    std::stringstream ss;
    const int rank = get_rank();
    ss << "rank " << rank << " MPI_Isend; count=" << count << " values=";
    for (int i = 0; i < count; ++i) {
        ss << " " << buf[i];
    }
    ss << "\n";
    std::cerr << ss.str();
    return ::MPI_Isend(buf, count, datatype, dest, tag, comm, request);

}

template <typename T>
static int MPI_Irecv(T *buf, int count, MPI_Datatype datatype, int source,
              int tag, MPI_Comm comm, MPI_Request *request) {
    std::stringstream ss;
    const int rank = get_rank();
    ss << "rank " << rank << " MPI_Irecv (call); count=" << count << "\n";
    std::cerr << ss.str();
    return ::MPI_Irecv(buf, count, datatype, source, tag ,comm, request);
}

// because irecv is non-blocking
template <typename T>
static void print_irecv(T *buf, int count) {
    std::stringstream ss;
    const int rank = get_rank();
    ss << "rank " << rank << " MPI_Irecv (print); count=" << count << " values=";
    for (int i = 0; i < count; ++i) {
        ss << " " << buf[i];
    }
    ss << "\n";
    std::cerr << ss.str();
}

static int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                 void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) {
    const int rank = get_rank();
    std::cerr << "rank " << rank << " MPI_Alltoall\n";
    return ::MPI_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);

}

static int MPI_Alltoallv(const void *sendbuf, const int sendcounts[], const int sdispls[], MPI_Datatype sendtype,
                  void *recvbuf, const int recvcounts[], const int rdispls[], MPI_Datatype recvtype,
                  MPI_Comm comm) {
    const int rank = get_rank();
    std::cerr << "rank " << rank << " MPI_AlltoAllv\n";
    return ::MPI_Alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
}

static int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root,
              MPI_Comm comm) {
    const int rank = get_rank();
    std::cerr << "rank " << rank << " MPI_Bcast\n";
    return ::MPI_Bcast(buffer, count, datatype, root, comm);

}

}
#endif