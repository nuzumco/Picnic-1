/*
 *  This file is part of the optimized implementation of the Picnic signature scheme.
 *  See the accompanying documentation for complete details.
 *
 *  The code is provided under the MIT license, see LICENSE for
 *  more details.
 *  SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <stdint.h>
#include "KeccakHash.h"
#include "KeccakHashtimes4.h"

int main(void) {
  const uint8_t data1[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
  const uint8_t data2[8] = {0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};

  const uint8_t* data_ptrs[4] = {data1, data2, data2, data1};
  uint8_t output1[32] = {0,};
  uint8_t output2[32] = {0,};
  uint8_t output3[32] = {0,};
  uint8_t output4[32] = {0,};
  uint8_t* output_ptrs[4] = {output1, output2, output3, output4};

  Keccak_HashInstancetimes4 ctx;
  if(Keccak_HashInitializetimes4_SHAKE256(&ctx))
    perror("Initialization 4x failed.");
  if(Keccak_HashUpdatetimes4(&ctx, data_ptrs, 64))
    perror("Update 4x failed");
  if(Keccak_HashFinaltimes4(&ctx, NULL))
    perror("Final 4x failed");
  if(Keccak_HashSqueezetimes4(&ctx, output_ptrs, 256))
    perror("Squeeze 4x failed");

  uint8_t out1[32] = {0,};
  uint8_t out2[32] = {0,};
  Keccak_HashInstance ctx1;
  if(Keccak_HashInitialize_SHAKE256(&ctx1))
    perror("Init 1 failed");
  if(Keccak_HashUpdate(&ctx1, data1, 64))
    perror("Update 1 failed");
  if(Keccak_HashFinal(&ctx1, NULL))
    perror("Final 1 failed");
  if(Keccak_HashSqueeze(&ctx1, out1, 256))
    perror("Squeeze 1 failed");

  Keccak_HashInstance ctx2;
  if(Keccak_HashInitialize_SHAKE256(&ctx2))
    perror("Init 2 failed");
  if(Keccak_HashUpdate(&ctx2, data2, 64))
    perror("Update 2 failed");
  if(Keccak_HashFinal(&ctx2, NULL))
    perror("Final 2 failed");
  if(Keccak_HashSqueeze(&ctx2, out2, 256))
    perror("Squeeze 2 failed");


  const uint8_t expected_output1[32] = {0xd5, 0x9c, 0x54, 0x97, 0x73, 0xd2, 0xb3, 0x91,
                                        0x57, 0x49, 0x76, 0xb9, 0x59, 0xeb, 0xf6, 0xe0,
                                        0xcf, 0x23, 0xdd, 0xf3, 0x01, 0xb4, 0x55, 0xac,
                                        0x60, 0x0d, 0xb8, 0xe5, 0xa3, 0xd3, 0xab, 0xf1,};
  const uint8_t expected_output2[32] = {0x00, 0xd2, 0xd4, 0x1b, 0xe6, 0xc7, 0xc2, 0xf4,
                                        0x7f, 0xf9, 0x4c, 0x7d, 0x1c, 0x50, 0x70, 0x8c,
                                        0xe3, 0x8d, 0xc7, 0x36, 0x4c, 0xbd, 0xa3, 0xb7,
                                        0xfb, 0x66, 0xfc, 0x05, 0x25, 0xfe, 0xef, 0xc8,};

  if(memcmp(out1, expected_output1, 32) != 0)
    return -1;
  if(memcmp(out2, expected_output2, 32) != 0)
    return -1;

  if(memcmp(output1, expected_output1, 32) != 0)
    return -1;
  if(memcmp(output2, expected_output2, 32) != 0)
    return -1;
  if(memcmp(output3, expected_output2, 32) != 0)
    return -1;
  if(memcmp(output4, expected_output1, 32) != 0)
    return -1;

  return 0;
}
