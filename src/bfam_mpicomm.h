#ifndef BFAM_MPICOMM_H
#define BFAM_MPICOMM_H

#include<mpi.h>

/**
 * base structure for all mpicomm types. Any new mpi comm should have this as
 * its first member with the name base, i.e.,
 * \code{.c}
 * typedef struct new_mpicomm_type
 * {
 *   bfam_mpicomm_t base;
 *   ...
 * }
 */
typedef struct bfam_mpicomm
{
  MPI_Comm comm;
  int isMember;
} bfam_mpicomm_t;

#endif