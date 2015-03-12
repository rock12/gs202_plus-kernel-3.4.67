/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 * 
 * MediaTek Inc. (C) 2010. All rights reserved.
 * 
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#include <idp_define.h>
#include "idp_bmp_ut.h"

#ifdef TEST_OVL_MASK_UNCOMPRESS_13X13


#if 0
#pragma arm section rwdata = "NONCACHEDRW_RAM2", zidata = "NONCACHEDZI_RAM2"
#endif // MDP_C_MODEL

unsigned int const
ovl_mask_uncompress_13x13_palette[256]=
{
  0x4d8c49, 0x596cc6, 0x5564d2, 0x545cdf, 0x575bed, 0x5a59ea, 0x6b5fdb, 0x7e67d0, 0x9b799f, 0x937ca0, 0x6961cb, 0x496ebc, 
  0xf2817f, 0xf88077, 0xfc827a, 0xfa8379, 0xf98377, 0xf88474, 0xf88474, 0xf48673, 0xf18872, 0xf98377, 0xee896f, 0xec8a6d, 
  0xef896f, 0x3d6dad, 0x36759e, 0x9179ae, 0xd67d85, 0xcd8187, 0xd0867c, 0xec8675, 0xf88474, 0xf98377, 0x63a04f, 0xba8274, 
  0xe78770, 0x5d71bd, 0xf88374, 0xf68579, 0xf08580, 0xef867e, 0xe48586, 0xe68e64, 0x507e8c, 0xe26c8d, 0x546a6f, 0xed8774, 
  0xa77a9a, 0xfa8379, 0xcd868f, 0x8978c0, 0x8d6fc1, 0xd87f8c, 0x758a78, 0xf45d80, 0xf5627f, 0x867971, 0x608380, 0x5865b1, 
  0xad6ea6, 0x969665, 0x648e76, 0x85709b, 0x6163ba, 0xf88177, 0xb3985d, 0xf25681, 0xf5667f, 0xf15282, 0x7b5fba, 0x9864b2, 
  0x8a5ab3, 0x715cb9, 0x576aa0, 0xb5718c, 0xe1835d, 0xcf913c, 0xcb8e3a, 0xdd8951, 0xf3856c, 0xdd728b, 0xf06d7a, 0xf04f83, 
  0xc94a9f, 0xeb5486, 0xed5385, 0xde418d, 0xcf3d95, 0xc34896, 0x845ba0, 0x745672, 0x856d2b, 0x9c711b, 0xa27a16, 0xb18d16, 
  0x409d68, 0xec3b86, 0xa446a9, 0xe3218c, 0xce1498, 0x7c4886, 0x7b4b3e, 0xa25c2c, 0xbc8c68, 0xdc6e8c, 0xe2198a, 0xe31d8c, 
  0xad28a3, 0xa2549a, 0x8f6524, 0xe36d6b, 0xf5727c, 0xf7797b, 0xf38074, 0xe93685, 0xec3b86, 0x417a68, 0x5a7a56, 0x657b63, 
  0xe18263, 0xde8c65, 0x95986d, 0xbf5380, 0xdd218b, 0xc24893, 0x685f4c, 0x80763a, 0x6967a5, 0x5b6e9d, 0xad7e7e, 0xf3876c, 
  0x998f6a, 0xfc827a, 0xeb8b69, 0xa5856e, 0xa18576, 0x7c6665, 0x8a4632, 0x6058eb, 0x6c58e2, 0x7858da, 0x845dd1, 0x8a62cc, 
  0xa66bb8, 0x9a65a8, 0xe97d88, 0xc27f7e, 0x93768b, 0xd1846e, 0xe8886b, 0xf48673, 0xa27b70, 0x8a7786, 0xc88b6a, 0xdb8f6c, 
  0xeb8a6d, 0xed8670, 0x917a7c, 0xbc8d68, 0xe98c6a, 0x809170, 0xa7674c, 0xe68e69, 0xdb9462, 0xb3975d, 0xea8b6a, 0xad9c62, 
  0x966860, 0xa28649, 0xf28771, 0xa96c52, 0xfa8379, 0x6660e1, 0xe78e6c, 0x91824c, 0xe28f6c, 0xe38e6b, 0xcc8a62, 0xa6913c, 
  0x984c3e, 0xb2543d, 0xc6596c, 0xda5972, 0xf78575, 0xc2675e, 0xa55d55, 0xf27b71, 0x9b544e, 0xeb8669, 0xb87eab, 0x957a8f, 
  0xd57a79, 0xed8078, 0xf08676, 0xf28771, 0xed797f, 0xfb7e7b, 0xfb807b, 0xf88274, 0xed7882, 0xf6757f, 0xf6797c, 0xf0797a, 
  0xf4797d, 0xe48677, 0xf77f78, 0xdc8078, 0xbb778c, 0xac7193, 0xf0787a, 0xe57776, 0xad78b3, 0x5e5fed, 0x9f6c92, 0xe96d7f, 
  0xf36e81, 0xf26c81, 0xf77878, 0x6866d8, 0xf8817d, 0xf27274, 0xec6d7d, 0xe37e66, 0xd14a6e, 0xe2686f, 0xe8726f, 0x9b3675, 
  0xe64081, 0x9d5cbf, 0x7979cc, 0xe23d80, 0xab5db4, 0xda4775, 0xa56155, 0xb24a3d, 0xf67a76, 0xe44b77, 0x8d4c25, 0xa15717, 
  0xc1295f, 0xe53182, 0xf5717a, 0xdc677c, 0xce5a86, 0xe9507f, 0xdd6073, 0xe75679, 0xc68866, 0x4d8c49, 0x4d8c49, 0x4d8c49, 
  0x4d8c49, 0x4d8c49, 0x4d8c49, 0x4d8c49
};

#if 0
__align(8) unsigned int const
#else
__declspec(align(8)) unsigned int const
#endif  //MDP_C_MODEL
ovl_mask_uncompress_13x13[169]=
{
  0x0f020901, 0x14141110, 0x120c0e16, 0x48644a10, 0x5e020b19,
  0x53226322, 0x49192253, 0x00000e48, 0x22000000, 0x19000000,
  0x00000e48, 0x00000000, 0x00000000, 0x00000e03, 0x00000000,
  0x00000000, 0x01040500, 0x00000022, 0x00000000, 0xa7a60000,
  0x00000e0e, 0x00000000, 0x00000000, 0x008f0e94, 0x00000000,
  0x00000000, 0x7eaf0e00, 0x00000000, 0x00000000, 0x17960000,
  0x0000007f, 0x00000000, 0x02000000, 0x000ebb92, 0x00000000,
  0x0e002222, 0x0e0e0c02, 0x26c60000, 0x25018e0e, 0x0e13940e,
  0x7615720e, 0x1a3976ef, 0x0000008b
};
#if 0
#pragma arm section
#endif // MDP_C_MODEL

#endif
