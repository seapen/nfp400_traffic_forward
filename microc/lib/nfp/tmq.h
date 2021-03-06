/*
 * Copyright (C) 2015,  Netronome Systems, Inc.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file          lib/nfp/tmq.h
 * @brief         TM queue utilities.
 *
 */
#ifndef _NFP__TMQ_H_
#define _NFP__TMQ_H_

#include <nfp.h>
#include <stdint.h>

/**
 * Reads, and optionally clears, a single queue drop counter.
 * @param nbi       NBI to read from (0/1)
 * @param counter   Read value (if no error)
 * @param qnum      Queue number (0-1023)
 * @param clear     Clear on read flag
 * @return 0 on success, -1 on error
 */
__intrinsic int tmq_cnt_read(uint32_t nbi, __gpr uint32_t *counter,
                             uint32_t qnum, int clear);

#endif /* !_NFP__TMQ_H_ */