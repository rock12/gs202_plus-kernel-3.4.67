/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#ifndef _CAM_EXIF_N3D_H_
#define _CAM_EXIF_N3D_H_


/*******************************************************************************
*
********************************************************************************/
#include <scenario_types.h>
#include <cam_types.h>


/*******************************************************************************
*
********************************************************************************/
struct mhalCamExifParam_s;
struct mhalCam3AParam_s;
struct exifAPP1Info_s;
//
class Hal3ABase;


/*******************************************************************************
*
********************************************************************************/
struct CamExifParam : public mhalCamExifParam_s, public mhalCam3AParam_s
{
public:     ////    Data Members.
    //  Zoom Ratio x 100
    //  For example, 100, 114, and 132 refer to 1.00, 1.14, and 1.32 respectively.
    MUINT32     u4ZoomRatio;

public:     ////    Operations.
    CamExifParam()  { ::memset(this, 0, sizeof(CamExifParam)); }

    CamExifParam(
        mhalCamExifParam_s const& rmhalCamExifParam, 
        mhalCam3AParam_s const& rmhalCam3AParam, 
        MUINT32 const _u4ZoomRatio
    )
        : mhalCamExifParam_s(rmhalCamExifParam)
        , mhalCam3AParam_s(rmhalCam3AParam)
        , u4ZoomRatio(_u4ZoomRatio)
    {}
};


/*******************************************************************************
* (Basic) Camera Exif
********************************************************************************/
class CamExifN3D
{
public:     ////
    typedef NSCamera::ESensorType   ESensorType_t;
    typedef NSCamera::EDeviceId     EDeviceId_t;

public:     ////    Constructor/Destructor
    virtual ~CamExifN3D();
    CamExifN3D(ESensorType_t const eSensorType, EDeviceId_t const eDeviceId);

public:     ////    Interfaces.

    virtual MBOOL   init(CamExifParam const& rCamExifParam, Hal3ABase*const pHal3A);
    virtual MBOOL   uninit();

    virtual
    MBOOL
    makeExifApp1(
        MUINT32 const u4ImgWidth,           //  [I] Image Width
        MUINT32 const u4ImgHeight,          //  [I] Image Height
        MUINT32 const u4ThumbSize,          //  [I] Thumb Size
        MUINT8* const puApp1Buf,            //  [O] Pointer to APP1 Buffer
        MUINT32*const pu4App1HeaderSize     //  [O] Pointer to APP1 Header Size
    );

#ifdef MTK_NATIVE_3D_SUPPORT
    // new interface
    // use n3d compiler option for MP patch back
    virtual
    MBOOL
    makeExifApp3(
        MBOOL   const bIsN3dEnable,     //  [I] Native3D(AC) Enable
        MUINT8* const puApp3Buf,        //  [O] Pointer to APP3 Buffer
        MUINT32*const pu4App3Size       //  [O] Pointer to APP3 Size
    );
#else
    // old interface
    virtual
    MBOOL
    makeExifApp3(
        MUINT8* const puApp3Buf,        //  [O] Pointer to APP3 Buffer
        MUINT32*const pu4App3Size       //  [O] Pointer to APP3 Size
    );
#endif

    virtual
    MBOOL
    queryExifApp1Info(exifAPP1Info_s*const pexifApp1Info);

    virtual
    MINT32
    determineExifOrientation(
        MUINT32 const   u4DeviceOrientation, 
        MBOOL const     bIsFacing, 
        MBOOL const     bIsFacingFlip = MFALSE
    );

private:
    MUINT32
        mapCapTypeIdx(MUINT32 const u4CapType);

    MUINT32
        mapExpProgramIdx(MUINT32 const u4ExpProgram);


protected:  ////    Data Members.
    ESensorType_t const meSensorType;   //  sensor type.
    EDeviceId_t const   meDeviceId;     //  device id.
    CamExifParam        mCamExifParam;
    Hal3ABase*          mpHal3A;
};


#endif  //  _CAM_EXIF_N3D_H_
