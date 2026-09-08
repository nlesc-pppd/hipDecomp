/*
 * SPDX-FileCopyrightText: Copyright (c) 2026 The Authors.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HIPDECOMP_MACROS_H
#define HIPDECOMP_MACROS_H

#ifdef USE_CUDECOMP_NAMES
#define HIPDECOMP_TRANSPOSE_COMM_MPI_P2P CUDECOMP_TRANSPOSE_COMM_MPI_P2P 
#define HIPDECOMP_TRANSPOSE_COMM_MPI_P2P_PL CUDECOMP_TRANSPOSE_COMM_MPI_P2P_PL 
#define HIPDECOMP_TRANSPOSE_COMM_MPI_A2A CUDECOMP_TRANSPOSE_COMM_MPI_A2A 
#define HIPDECOMP_TRANSPOSE_COMM_NCCL CUDECOMP_TRANSPOSE_COMM_NCCL 
#define HIPDECOMP_TRANSPOSE_COMM_NCCL_PL CUDECOMP_TRANSPOSE_COMM_NCCL_PL 
#define HIPDECOMP_TRANSPOSE_COMM_NVSHMEM CUDECOMP_TRANSPOSE_COMM_NVSHMEM 
#define HIPDECOMP_TRANSPOSE_COMM_NVSHMEM_PL CUDECOMP_TRANSPOSE_COMM_NVSHMEM_PL 
#define hipdecompTransposeCommBackend_t cudecompTransposeCommBackend_t 
#define HIPDECOMP_HALO_COMM_MPI CUDECOMP_HALO_COMM_MPI 
#define HIPDECOMP_HALO_COMM_MPI_BLOCKING CUDECOMP_HALO_COMM_MPI_BLOCKING 
#define HIPDECOMP_HALO_COMM_NCCL CUDECOMP_HALO_COMM_NCCL 
#define HIPDECOMP_HALO_COMM_NVSHMEM CUDECOMP_HALO_COMM_NVSHMEM 
#define HIPDECOMP_HALO_COMM_NVSHMEM_BLOCKING CUDECOMP_HALO_COMM_NVSHMEM_BLOCKING 
#define hipdecompHaloCommBackend_t cudecompHaloCommBackend_t 
#define HIPDECOMP_FLOAT CUDECOMP_FLOAT 
#define HIPDECOMP_DOUBLE CUDECOMP_DOUBLE 
#define HIPDECOMP_FLOAT_COMPLEX CUDECOMP_FLOAT_COMPLEX 
#define HIPDECOMP_DOUBLE_COMPLEX CUDECOMP_DOUBLE_COMPLEX 
#define hipdecompDataType_t cudecompDataType_t 
#define HIPDECOMP_AUTOTUNE_GRID_TRANSPOSE CUDECOMP_AUTOTUNE_GRID_TRANSPOSE 
#define HIPDECOMP_AUTOTUNE_GRID_HALO CUDECOMP_AUTOTUNE_GRID_HALO 
#define hipdecompAutotuneGridMode_t cudecompAutotuneGridMode_t 
#define HIPDECOMP_RESULT_SUCCESS CUDECOMP_RESULT_SUCCESS 
#define HIPDECOMP_RESULT_INVALID_USAGE CUDECOMP_RESULT_INVALID_USAGE 
#define HIPDECOMP_RESULT_NOT_SUPPORTED CUDECOMP_RESULT_NOT_SUPPORTED 
#define HIPDECOMP_RESULT_INTERNAL_ERROR CUDECOMP_RESULT_INTERNAL_ERROR 
#define HIPDECOMP_RESULT_HIP_ERROR CUDECOMP_RESULT_CUDA_ERROR 
#define HIPDECOMP_RESULT_HIPTENSOR_ERROR CUDECOMP_RESULT_CUTENSOR_ERROR 
#define HIPDECOMP_RESULT_MPI_ERROR CUDECOMP_RESULT_MPI_ERROR 
#define HIPDECOMP_RESULT_NCCL_ERROR CUDECOMP_RESULT_NCCL_ERROR 
#define HIPDECOMP_RESULT_NVSHMEM_ERROR CUDECOMP_RESULT_NVSHMEM_ERROR 
#define hipdecompResult_t cudecompResult_t 
#define hipdecompHandle_t cudecompHandle_t 
#define hipdecompGridDesc_t cudecompGridDesc_t 
#define hipdecompTransposeCommBackend_t cudecompTransposeCommBackend_t 
#define hipdecompHaloCommBackend_t cudecompHaloCommBackend_t 
#define hipdecompGridDescConfig_t cudecompGridDescConfig_t 
#define hipdecompDataType_t cudecompDataType_t 
#define hipdecompGridDescAutotuneOptions_t cudecompGridDescAutotuneOptions_t 
#define hipdecompPencilInfo_t cudecompPencilInfo_t 
#define hipdecompInit cudecompInit 
#define hipdecompInit_F cudecompInit_F 
#define hipdecompFinalize cudecompFinalize 
#define hipdecompGridDescCreate cudecompGridDescCreate 
#define hipdecompGridDescDestroy cudecompGridDescDestroy 
#define hipdecompGridDescConfigSetDefaults cudecompGridDescConfigSetDefaults 
#define hipdecompGridDescAutotuneOptionsSetDefaults cudecompGridDescAutotuneOptionsSetDefaults 
#define hipdecompGetPencilInfo cudecompGetPencilInfo 
#define hipdecompGetTransposeWorkspaceSize cudecompGetTransposeWorkspaceSize 
#define hipdecompGetHaloWorkspaceSize cudecompGetHaloWorkspaceSize 
#define hipdecompGetDataTypeSize cudecompGetDataTypeSize 
#define hipdecompMalloc cudecompMalloc 
#define hipdecompFree cudecompFree 
#define hipdecompTransposeCommBackendToString cudecompTransposeCommBackendToString 
#define hipdecompHaloCommBackendToString cudecompHaloCommBackendToString 
#define hipdecompGetGridDescConfig cudecompGetGridDescConfig 
#define hipdecompGetShiftedRank cudecompGetShiftedRank 
#define hipdecompTransposeXToY cudecompTransposeXToY 
#define hipdecompTransposeYToZ cudecompTransposeYToZ 
#define hipdecompTransposeZToY cudecompTransposeZToY 
#define hipdecompTransposeYToX cudecompTransposeYToX 
#define hipdecompUpdateHalosX cudecompUpdateHalosX 
#define hipdecompUpdateHalosY cudecompUpdateHalosY 
#define hipdecompUpdateHalosZ cudecompUpdateHalosZ
#endif  // USE_CUDECOMP_NAMES

#endif // HIPDECOMP_MACROS_H
