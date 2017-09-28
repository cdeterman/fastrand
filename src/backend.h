#ifndef __FASTRAND_BACKEND__
#define __FASTRAND_BACKEND__


#include <thrust/detail/config.h>


#if THRUST_VERSION >= 100700
  #if THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_OMP
    #include <omp.h>
    #define FASTRAND_OMP 1
  #elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_TBB
    #include "tbb/task_scheduler_init.h"
    #define FASTRAND_TBB 1
  #elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_SYSTEM_CUDA
    #define FASTRAND_CUDA 1
  #endif
#else
  #if THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_OMP
    #include <omp.h>
    #define FASTRAND_OMP 1
  #elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_TBB
    #include "tbb/task_scheduler_init.h"
    #define FASTRAND_TBB 1
  #elif THRUST_DEVICE_SYSTEM == THRUST_DEVICE_BACKEND_CUDA
    #define FASTRAND_CUDA 1
  #endif
#endif


#endif
