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

/* 
 * data path: virtual memory -> m4u -> LCDC_R
 * LCD_R read BufAddr through M4U, then LCD_W write the data to PMEM PA 
 * test APP dump PMEM_VA image to verify
 */

#include "stdio.h"
#include "errno.h"
#include "fcntl.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <cutils/log.h>

#include <cutils/pmem.h>    //pmem
#include <m4u_lib.h>
#include <mtkfb.h>

#undef LOG_TAG
#define LOG_TAG "[m4u_ut]"

#define MTKM4UDEBUG
#ifdef MTKM4UDEBUG
  #define M4UDBG(string, args...) printf("[M4U_N]"string,##args)
#else
  #define M4UDBG(string, args...)
#endif

extern unsigned char const rgb565_390x210[];

//#define M4U_MEM_USE_NEW
#define M4U_MEM_USE_PMEM

int main (int argc, char *argv[])
{
    M4UDBG("enter m4u_ut main \n");
    
    unsigned int i;
    M4UDBG("argc=%d \n", argc);
    for(i=0;i<argc;i++)
    {
    	  M4UDBG("argv[%d]=%s \n", i, argv[i]);
    }
    
    unsigned int* pDataIn = new unsigned int[argc];
    for(i=0;i<argc;i++)
    {
    	  sscanf(argv[i],"%d",pDataIn+i);
    }
    for(i=0;i<argc;i++)
    {
    	  M4UDBG("pDataIn[%d]=%d \n", i, *(pDataIn+i));
    }
    delete[] pDataIn;
        
    ///> --------------------1. allocate memory as LCD's source buffer
    unsigned int BufSize = 390*210*2;
    int pmem_fd_src, pmem_fd_dst;
    
#ifdef M4U_MEM_USE_PMEM    
    unsigned int BufAddr = (unsigned int)pmem_alloc_sync(BufSize, &pmem_fd_src );
    if(BufAddr==NULL)
    {
        M4UDBG("alloc pmem failed! \n");
    }
    else
    {
    	  M4UDBG("alloc pmem success! BufAddrDst=0x%x\n", BufAddr);
    }    
    unsigned int BufAddrPA = (unsigned int)pmem_get_phys(pmem_fd_src);
    M4UDBG("src use pmem, BufAddr=0x%x,  BufAddrPA=0x%x \n", BufAddr, BufAddrPA);
#else
    unsigned int BufAddr = (unsigned int)new unsigned char[BufSize];
    M4UDBG("src use new, BufAddr=0x%x \n", BufAddr);
#endif    


    unsigned int BufMVA;
    FILE *fp;
    fp = fopen("/system/bin/data_rgb565_720x480.bin", "r");
    if(NULL==fp)
    {
        M4UDBG("open /system/bin/data_rgb565_720x480.bin failed! \n");
        //memset((unsigned char*)BufAddr, 0xff, BufSize);
        memcpy((unsigned char*)BufAddr, rgb565_390x210, BufSize);
    }
    else
    {
        fread((unsigned char*)BufAddr , 1 , BufSize , fp);
        fclose(fp);
    }

    // save image
    {
        char* pFile;
        unsigned int index=0;
        pFile = new char[30];
        memset(pFile, 0, 30);
        sprintf(pFile, "/data/source_rgb_%d.bin", 1);
        fp = fopen(pFile, "w");
        for(index = 0 ; index < BufSize ; index++)
        {
            fprintf(fp, "%c", *(unsigned char*)(BufAddr+index));
        }
        fclose(fp);
    } 
    
    unsigned int BufSizeDst = 390*210*2;

#ifdef M4U_MEM_USE_PMEM   
    unsigned int BufAddrDstPA;
    unsigned int BufAddrDst = (unsigned int)pmem_alloc_sync(BufSize, &pmem_fd_dst );
    if(BufAddrDst==NULL)
    {
        M4UDBG("alloc pmem failed! \n");
    }
    else
    {
    	  M4UDBG("alloc pmem success! BufAddrDst=0x%x\n", BufAddrDst);
    }
    BufAddrDstPA = (unsigned int)pmem_get_phys(pmem_fd_dst);
    M4UDBG("dst use pmem, BufAddrDst=0x%x,  BufAddrDstPA=0x%x \n", BufAddrDst, BufAddrDstPA);
#else
    unsigned int BufAddrDst = (unsigned int)new unsigned char[BufSize];
#endif
    
    memset((unsigned char*)BufAddrDst, 0x55, BufSizeDst);
    M4UDBG("src addr=0x%x, dst addr=0x%x \r\n", BufAddr, BufAddrDst);

    ///> --------------------2. allocate MVA
    MTKM4UDrv CM4u;
    CM4u.m4u_power_on(M4U_CLNTMOD_LCDC);
    // allocate MVA buffer for LCDC module                    
    CM4u.m4u_alloc_mva(M4U_CLNTMOD_LCDC,     // Module ID
                       BufAddr,              // buffer virtual start address
                       BufSize,              // buffer size
                       &BufMVA);             // return MVA address
    M4UDBG(" after m4u_alloc_mva(), BufMVA=0x%x \r\n", BufMVA);
    
    ///> --------------------3. insert tlb range and tlb entry
    // manual insert MVA start page address
    CM4u.m4u_manual_insert_entry(M4U_CLNTMOD_LCDC, 
                                 BufMVA,   // MVA address
                                 true);    // lock the entry for circuling access

    // insert TLB uni-update range
    CM4u.m4u_insert_tlb_range(M4U_CLNTMOD_LCDC, 
                              BufMVA,                // range start MVA
                              BufMVA + BufSize - 1,  // range end MVA
                              RT_RANGE_HIGH_PRIORITY,
                              1);
    M4UDBG(" after m4u_manual_insert_entry() and m4u_insert_tlb_range() \r\n");
    CM4u.m4u_dump_reg(M4U_CLNTMOD_LCDC);
    CM4u.m4u_dump_info(M4U_CLNTMOD_LCDC);

    ///> --------------------4. config LCD port                       
    // config LCD port 
    M4U_PORT_STRUCT M4uPort;
    M4uPort.ePortID = M4U_PORT_LCD_R;
    M4uPort.Virtuality = 1;						   
    M4uPort.Security = 0;
    M4uPort.Distance = 1;
    M4uPort.Direction = 0;
    CM4u.m4u_config_port(&M4uPort);

/*
    M4uPort.ePortID = M4U_PORT_LCD_W;
    M4uPort.Virtuality = 1;						   
    M4uPort.Security = 0;
    M4uPort.Distance = 1;
    M4uPort.Direction = 0;
    CM4u.m4u_config_port(&M4uPort);
*/

/*
    CM4u.m4u_dump_reg(M4U_CLNTMOD_LCDC);
    CM4u.m4u_dump_info(M4U_CLNTMOD_LCDC);

    ///> --------------------5. start hardware engine
    // ...
    CM4u.m4u_monitor_start(M4U_PORT_LCD_R);
    int fp_fb;
    struct fb_overlay_layer ut_layer;
    fp_fb = open("/dev/graphics/fb0",O_RDONLY);
    if(fp_fb<0) return 0;
    	
    ut_layer.src_fmt = MTK_FB_FORMAT_RGB565;
    ut_layer.layer_id = 0;
    ut_layer.layer_enable = 1;
    ut_layer.src_base_addr = (void*)BufMVA;
    ut_layer.src_phy_addr = (void*)BufAddrDstPA; //////////////dest addr
    ut_layer.src_direct_link = 0;
    ut_layer.src_offset_x = ut_layer.src_offset_y = 0;
    ut_layer.tgt_offset_x = ut_layer.tgt_offset_y = 0;
    ut_layer.tgt_height = ut_layer.src_height = 390;
    ut_layer.tgt_width = ut_layer.src_width = ut_layer.src_pitch = 210;
    ut_layer.src_color_key = 0;
    ut_layer.layer_rotation = MTK_FB_ORIENTATION_0;
    
    ioctl(fp_fb, MTKFB_M4U_UT, &ut_layer);
    CM4u.m4u_monitor_stop(M4U_PORT_LCD_R);
*/

    M4UDBG("src_va=0x%x, dst_va=0x%x, *dst_va=0x%x \n", 
        BufAddr, BufAddrDst, *(unsigned char*)BufAddrDst);
    
    // save image
    {
        char* pFile;
        unsigned int index=0;
        pFile = new char[30];
        memset(pFile, 0, 30);
        sprintf(pFile, "/data/result_rgb_%d.bin", 1);
        fp = fopen(pFile, "w");
        for(index = 0 ; index < BufSize ; index++)
        {
            fprintf(fp, "%c", *(unsigned char*)(BufAddrDst+index));
        }
        fclose(fp);
    }    

    ///> --------------------6. de-allocate MVA and release tlb resource
    CM4u.m4u_invalid_tlb_range(M4U_CLNTMOD_LCDC, BufMVA, BufMVA+BufSize-1);
    CM4u.m4u_dealloc_mva(M4U_CLNTMOD_LCDC, BufAddr, BufSize, BufMVA);
    M4UDBG(" after m4u_dealloc_mva() \r\n");
    CM4u.m4u_dump_reg(M4U_CLNTMOD_LCDC);
    CM4u.m4u_dump_info(M4U_CLNTMOD_LCDC);
    CM4u.m4u_power_off(M4U_CLNTMOD_LCDC);
    
    int cnt=0;
    //while(1)
    {
    	sleep(2);
    	M4UDBG("m4u_ut sleep! %d\n", cnt++);
    }

#ifdef M4U_MEM_USE_PMEM     

#else
    delete[] (unsigned char*)BufAddr;
    delete[] (unsigned char*)BufAddrDst;
#endif
    
    return 0;
}


