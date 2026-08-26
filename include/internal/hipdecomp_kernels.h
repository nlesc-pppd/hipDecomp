/*
 * SPDX-FileCopyrightText: Copyright (c) 2022-2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef HIPDECOMP_KERNELS_H
#define HIPDECOMP_KERNELS_H

#include <complex>

#ifdef ENABLE_ROCSHMEM
#include <rocshmem/rocshmem.hpp>
#endif

namespace hipdecomp {

#ifdef ENABLE_ROCSHMEM
#define HIPDECOMP_ROCSHMEM_A2A_PARAM_CAPACITY 96
template <typename T> struct hipdecompRocshmemA2AParams {
  int ntransfers;
  T* send_buff = nullptr;
  T* recv_buff = nullptr;
  size_t send_offsets[HIPDECOMP_ROCSHMEM_A2A_PARAM_CAPACITY];
  size_t recv_offsets[HIPDECOMP_ROCSHMEM_A2A_PARAM_CAPACITY];
  size_t send_counts[HIPDECOMP_ROCSHMEM_A2A_PARAM_CAPACITY];
  int peer_ranks[HIPDECOMP_ROCSHMEM_A2A_PARAM_CAPACITY];
};

void hipdecomp_rocshmem_alltoallv(const hipdecompRocshmemA2AParams<float>& params, hipStream_t stream);
void hipdecomp_rocshmem_alltoallv(const hipdecompRocshmemA2AParams<double>& params, hipStream_t stream);
void hipdecomp_rocshmem_alltoallv(const hipdecompRocshmemA2AParams<std::complex<float>>& params, hipStream_t stream);
void hipdecomp_rocshmem_alltoallv(const hipdecompRocshmemA2AParams<std::complex<double>>& params, hipStream_t stream);

// Kernel-launch wrappers bridging host-issued, stream-ordered calls to rocSHMEM's device-only RMA/sync API
// (rocSHMEM, unlike NVSHMEM, does not provide host-callable "on_stream" put/quiet/sync convenience functions).
void hipdecomp_rocshmem_putmem(void* dest, const void* source, size_t nbytes, int pe, hipStream_t stream);
void hipdecomp_rocshmem_putmem_nbi(void* dest, const void* source, size_t nbytes, int pe, hipStream_t stream);
void hipdecomp_rocshmem_quiet(hipStream_t stream);
void hipdecomp_rocshmem_sync_all(hipStream_t stream);
void hipdecomp_rocshmem_team_sync(rocshmem::rocshmem_team_t team, hipStream_t stream);
#endif

#define HIPDECOMP_BATCHED_D2D_3D_PARAM_CAPACITY 56
template <typename T> struct hipdecompBatchedD2DMemcpy3DParams {
  int ncopies;
  T* src[HIPDECOMP_BATCHED_D2D_3D_PARAM_CAPACITY];
  T* dest[HIPDECOMP_BATCHED_D2D_3D_PARAM_CAPACITY];
  size_t src_strides[2][HIPDECOMP_BATCHED_D2D_3D_PARAM_CAPACITY];  // [depth stride, row stride] col_stride=1 assumed
  size_t dest_strides[2][HIPDECOMP_BATCHED_D2D_3D_PARAM_CAPACITY]; // [depth stride, row stride] col_stride=1 assumed
  size_t extents[3][HIPDECOMP_BATCHED_D2D_3D_PARAM_CAPACITY];      // [depth, height, width]
};

void hipdecomp_batched_d2d_memcpy_3d(hipdecompBatchedD2DMemcpy3DParams<float>& params, hipStream_t stream);
void hipdecomp_batched_d2d_memcpy_3d(hipdecompBatchedD2DMemcpy3DParams<double>& params, hipStream_t stream);
void hipdecomp_batched_d2d_memcpy_3d(hipdecompBatchedD2DMemcpy3DParams<std::complex<float>>& params,
                                     hipStream_t stream);
void hipdecomp_batched_d2d_memcpy_3d(hipdecompBatchedD2DMemcpy3DParams<std::complex<double>>& params,
                                     hipStream_t stream);

template <typename T> struct hipdecompPermuteD2DParams {
  T* input;
  T* output;
  size_t extent_in[3];
  size_t order_out[3];
  size_t strides_in[3];
  size_t strides_out[3];
};

void hipdecomp_permute_d2d(hipdecompPermuteD2DParams<float>& params, hipStream_t stream);
void hipdecomp_permute_d2d(hipdecompPermuteD2DParams<double>& params, hipStream_t stream);
void hipdecomp_permute_d2d(hipdecompPermuteD2DParams<std::complex<float>>& params, hipStream_t stream);
void hipdecomp_permute_d2d(hipdecompPermuteD2DParams<std::complex<double>>& params, hipStream_t stream);

} // namespace hipdecomp

#endif // HIPDECOMP_KERNELS_H
