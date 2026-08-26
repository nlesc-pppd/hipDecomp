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

#include <complex>

#include "internal/checks.h"
#include "internal/hipdecomp_kernels.hiph"

namespace hipdecomp {

#ifdef ENABLE_ROCSHMEM
void hipdecomp_rocshmem_alltoallv(const hipdecompRocshmemA2AParams<float>& params, hipStream_t stream) {
  hipdecomp_rocshmem_alltoallv_k<<<1, HIPDECOMP_HIP_NTHREADS, 0, stream>>>(params);
  CHECK_HIP_LAUNCH();
}

void hipdecomp_rocshmem_alltoallv(const hipdecompRocshmemA2AParams<double>& params, hipStream_t stream) {
  hipdecomp_rocshmem_alltoallv_k<<<1, HIPDECOMP_HIP_NTHREADS, 0, stream>>>(params);
  CHECK_HIP_LAUNCH();
}

void hipdecomp_rocshmem_alltoallv(const hipdecompRocshmemA2AParams<std::complex<float>>& params, hipStream_t stream) {
  hipdecomp_rocshmem_alltoallv_k<<<1, HIPDECOMP_HIP_NTHREADS, 0, stream>>>(params);
  CHECK_HIP_LAUNCH();
}

void hipdecomp_rocshmem_alltoallv(const hipdecompRocshmemA2AParams<std::complex<double>>& params, hipStream_t stream) {
  hipdecomp_rocshmem_alltoallv_k<<<1, HIPDECOMP_HIP_NTHREADS, 0, stream>>>(params);
  CHECK_HIP_LAUNCH();
}

void hipdecomp_rocshmem_putmem(void* dest, const void* source, size_t nbytes, int pe, hipStream_t stream) {
  hipdecomp_rocshmem_putmem_k<<<1, 1, 0, stream>>>(dest, source, nbytes, pe);
  CHECK_HIP_LAUNCH();
}

void hipdecomp_rocshmem_putmem_nbi(void* dest, const void* source, size_t nbytes, int pe, hipStream_t stream) {
  hipdecomp_rocshmem_putmem_nbi_k<<<1, 1, 0, stream>>>(dest, source, nbytes, pe);
  CHECK_HIP_LAUNCH();
}

void hipdecomp_rocshmem_quiet(hipStream_t stream) {
  hipdecomp_rocshmem_quiet_k<<<1, 1, 0, stream>>>();
  CHECK_HIP_LAUNCH();
}

void hipdecomp_rocshmem_sync_all(hipStream_t stream) {
  hipdecomp_rocshmem_sync_all_k<<<1, 1, 0, stream>>>();
  CHECK_HIP_LAUNCH();
}

void hipdecomp_rocshmem_team_sync(rocshmem::rocshmem_team_t team, hipStream_t stream) {
  hipdecomp_rocshmem_team_sync_k<<<1, 1, 0, stream>>>(team);
  CHECK_HIP_LAUNCH();
}
#endif

} // namespace hipdecomp
