/*
 * Copyright (c) 2013-2014 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */


#include <CoreFoundation/CoreFoundation.h>
#include <Security/SecCertificate.h>
#include <Security/SecCertificatePriv.h>
#include <Security/SecCertificateInternal.h>
#include <Security/SecItem.h>
#include <Security/SecItemPriv.h>
#include <Security/SecIdentityPriv.h>
#include <Security/SecIdentity.h>
#include <Security/SecPolicy.h>
#include <Security/SecPolicyPriv.h>
#include <Security/SecPolicyInternal.h>
#include <Security/SecCMS.h>
#include <utilities/SecCFWrappers.h>
#include <stdlib.h>
#include <unistd.h>

#include "Security_regressions.h"

static const UInt8 kLeafCert[] = {
	0x30, 0x82, 0x05, 0x11, 0x30, 0x82, 0x03, 0xf9, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x08, 0x3d,
	0x73, 0xc1, 0x2f, 0x55, 0xba, 0x4c, 0x53, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
	0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00, 0x30, 0x81, 0x8a, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55,
	0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x0c,
	0x0a, 0x41, 0x70, 0x70, 0x6c, 0x65, 0x20, 0x49, 0x6e, 0x63, 0x2e, 0x31, 0x26, 0x30, 0x24, 0x06,
	0x03, 0x55, 0x04, 0x0b, 0x0c, 0x1d, 0x41, 0x70, 0x70, 0x6c, 0x65, 0x20, 0x43, 0x65, 0x72, 0x74,
	0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72,
	0x69, 0x74, 0x79, 0x31, 0x3e, 0x30, 0x3c, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c, 0x35, 0x41, 0x70,
	0x70, 0x6c, 0x65, 0x20, 0x41, 0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20,
	0x49, 0x6e, 0x74, 0x65, 0x67, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x43, 0x65, 0x72, 0x74,
	0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72,
	0x69, 0x74, 0x79, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x33, 0x30, 0x37, 0x32, 0x39, 0x31, 0x39, 0x33,
	0x36, 0x31, 0x38, 0x5a, 0x17, 0x0d, 0x31, 0x35, 0x30, 0x37, 0x32, 0x39, 0x31, 0x39, 0x33, 0x36,
	0x31, 0x38, 0x5a, 0x30, 0x30, 0x31, 0x2e, 0x30, 0x2c, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c, 0x25,
	0x41, 0x70, 0x70, 0x6c, 0x65, 0x20, 0x49, 0x44, 0x20, 0x56, 0x61, 0x6c, 0x69, 0x64, 0x61, 0x74,
	0x69, 0x6f, 0x6e, 0x20, 0x52, 0x65, 0x63, 0x6f, 0x72, 0x64, 0x20, 0x53, 0x69, 0x67, 0x6e, 0x69,
	0x6e, 0x67, 0x20, 0x30, 0x31, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48,
	0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01,
	0x0a, 0x02, 0x82, 0x01, 0x01, 0x00, 0xb1, 0x13, 0xc4, 0x56, 0xe4, 0x16, 0x44, 0x9e, 0xbd, 0x35,
	0x6a, 0x2e, 0xce, 0x47, 0x03, 0x3c, 0x28, 0x25, 0xcd, 0x89, 0x90, 0xc8, 0xfe, 0xb5, 0x02, 0x1f,
	0xc3, 0x20, 0x04, 0xf6, 0x34, 0x74, 0x1f, 0x2a, 0xd3, 0x67, 0xe5, 0x90, 0xb8, 0x43, 0xad, 0x1c,
	0xf0, 0xa0, 0x8e, 0xd5, 0x63, 0xff, 0x7c, 0x60, 0x03, 0x5b, 0x18, 0x02, 0x01, 0x56, 0x69, 0xda,
	0xff, 0x08, 0xdd, 0x56, 0x22, 0x38, 0x09, 0xd8, 0xe8, 0x1e, 0x2f, 0xda, 0x57, 0x93, 0x36, 0xa1,
	0x4d, 0x24, 0x72, 0x4d, 0x3c, 0x89, 0xde, 0x66, 0x61, 0x4c, 0xe2, 0x42, 0x2f, 0x09, 0x7d, 0x43,
	0x49, 0xe0, 0x8b, 0x25, 0x34, 0x89, 0x8b, 0x3b, 0x8d, 0xd5, 0xbd, 0x24, 0x81, 0xf8, 0xc5, 0x99,
	0x3a, 0x36, 0xfc, 0xf2, 0x20, 0x7d, 0xc7, 0xcb, 0xf5, 0x29, 0x3c, 0xc4, 0xed, 0x2d, 0xa2, 0xca,
	0xa2, 0x21, 0x4f, 0x0b, 0x4b, 0xf6, 0xb5, 0x6b, 0x45, 0xa0, 0x4a, 0xeb, 0x5f, 0x47, 0x1f, 0xb5,
	0x4d, 0x44, 0x10, 0xc6, 0xc4, 0xa4, 0x5a, 0x97, 0x70, 0x26, 0x62, 0x27, 0xba, 0xcc, 0xdd, 0x42,
	0x46, 0xd7, 0x78, 0x3d, 0xe8, 0xe3, 0x6f, 0x46, 0x0b, 0xe6, 0xa2, 0xe8, 0x01, 0x83, 0xfb, 0xe3,
	0x8c, 0xba, 0x76, 0x86, 0x56, 0xa7, 0x85, 0xf9, 0x18, 0xcb, 0x86, 0xc1, 0x31, 0x0d, 0xee, 0x56,
	0x98, 0x4c, 0x63, 0x05, 0x3d, 0xbc, 0xcd, 0x96, 0x83, 0x37, 0x74, 0x86, 0xa4, 0x73, 0x44, 0x4c,
	0x9d, 0x4e, 0x5a, 0xe8, 0x9d, 0xdf, 0x3e, 0xfe, 0x00, 0x61, 0x45, 0xd8, 0xf5, 0x5c, 0x30, 0x82,
	0x95, 0x5b, 0xdc, 0x92, 0x2d, 0x15, 0x29, 0x8c, 0x61, 0xec, 0xbc, 0x6b, 0x0a, 0xf0, 0xb6, 0x74,
	0xf2, 0x64, 0xe6, 0xf1, 0xd4, 0x01, 0x8b, 0x2f, 0x80, 0xe8, 0x5b, 0x5d, 0xe7, 0xa7, 0xa1, 0x68,
	0xc1, 0x6b, 0x1d, 0x5e, 0x1d, 0xb7, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x82, 0x01, 0xd2, 0x30,
	0x82, 0x01, 0xce, 0x30, 0x40, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x01, 0x04,
	0x34, 0x30, 0x32, 0x30, 0x30, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x01, 0x86,
	0x24, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x6f, 0x63, 0x73, 0x70, 0x2e, 0x61, 0x70, 0x70,
	0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x6f, 0x63, 0x73, 0x70, 0x30, 0x34, 0x2d, 0x61, 0x61,
	0x69, 0x63, 0x61, 0x30, 0x34, 0x30, 0x1d, 0x06, 0x03, 0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14,
	0x3b, 0xea, 0x41, 0x8f, 0x09, 0xf9, 0x35, 0xf8, 0xe3, 0x61, 0xcd, 0x8b, 0x40, 0xc7, 0x9f, 0x8d,
	0x4a, 0x1e, 0x0c, 0x27, 0x30, 0x09, 0x06, 0x03, 0x55, 0x1d, 0x13, 0x04, 0x02, 0x30, 0x00, 0x30,
	0x1f, 0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0x31, 0xea, 0x76, 0xa9,
	0x23, 0x74, 0xa5, 0xdf, 0xd4, 0xfd, 0xee, 0xa0, 0xc1, 0xa6, 0x9e, 0xc6, 0x11, 0x0e, 0x11, 0xec,
	0x30, 0x82, 0x01, 0x1c, 0x06, 0x03, 0x55, 0x1d, 0x20, 0x04, 0x82, 0x01, 0x13, 0x30, 0x82, 0x01,
	0x0f, 0x30, 0x82, 0x01, 0x0b, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x63, 0x64, 0x05, 0x01,
	0x30, 0x81, 0xfd, 0x30, 0x81, 0xc3, 0x06, 0x08, 0x2b, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02, 0x02,
	0x30, 0x81, 0xb6, 0x0c, 0x81, 0xb3, 0x52, 0x65, 0x6c, 0x69, 0x61, 0x6e, 0x63, 0x65, 0x20, 0x6f,
	0x6e, 0x20, 0x74, 0x68, 0x69, 0x73, 0x20, 0x63, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61,
	0x74, 0x65, 0x20, 0x62, 0x79, 0x20, 0x61, 0x6e, 0x79, 0x20, 0x70, 0x61, 0x72, 0x74, 0x79, 0x20,
	0x61, 0x73, 0x73, 0x75, 0x6d, 0x65, 0x73, 0x20, 0x61, 0x63, 0x63, 0x65, 0x70, 0x74, 0x61, 0x6e,
	0x63, 0x65, 0x20, 0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x74, 0x68, 0x65, 0x6e, 0x20, 0x61,
	0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 0x62, 0x6c, 0x65, 0x20, 0x73, 0x74, 0x61, 0x6e, 0x64, 0x61,
	0x72, 0x64, 0x20, 0x74, 0x65, 0x72, 0x6d, 0x73, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x63, 0x6f, 0x6e,
	0x64, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x73, 0x20, 0x6f, 0x66, 0x20, 0x75, 0x73, 0x65, 0x2c, 0x20,
	0x63, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x20, 0x70, 0x6f, 0x6c, 0x69,
	0x63, 0x79, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x63, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61,
	0x74, 0x69, 0x6f, 0x6e, 0x20, 0x70, 0x72, 0x61, 0x63, 0x74, 0x69, 0x63, 0x65, 0x20, 0x73, 0x74,
	0x61, 0x74, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0x2e, 0x30, 0x35, 0x06, 0x08, 0x2b, 0x06, 0x01,
	0x05, 0x05, 0x07, 0x02, 0x01, 0x16, 0x29, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77,
	0x77, 0x2e, 0x61, 0x70, 0x70, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x63, 0x65, 0x72, 0x74,
	0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x65, 0x61, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79,
	0x30, 0x0e, 0x06, 0x03, 0x55, 0x1d, 0x0f, 0x01, 0x01, 0xff, 0x04, 0x04, 0x03, 0x02, 0x07, 0x80,
	0x30, 0x0f, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x63, 0x64, 0x06, 0x19, 0x04, 0x02, 0x05,
	0x00, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b, 0x05, 0x00,
	0x03, 0x82, 0x01, 0x01, 0x00, 0x97, 0xda, 0x8f, 0xab, 0x57, 0xa2, 0xfb, 0x85, 0xa5, 0x64, 0xbb,
	0xe9, 0xed, 0x6c, 0x13, 0x54, 0x3e, 0x3c, 0x00, 0xb5, 0xa4, 0xd2, 0x8a, 0xd9, 0xe6, 0xda, 0x9e,
	0x2b, 0x49, 0xc4, 0x80, 0x09, 0xa9, 0x0e, 0xda, 0xf3, 0xb1, 0x16, 0xa7, 0xbb, 0x14, 0x4e, 0xdf,
	0x95, 0xca, 0x3e, 0xc1, 0x2f, 0xcf, 0x0d, 0xa3, 0x0c, 0x5b, 0x36, 0x6f, 0x48, 0xe3, 0x44, 0x6e,
	0x96, 0xb1, 0x1c, 0xfc, 0x71, 0x3f, 0x88, 0xb0, 0x07, 0x20, 0x62, 0x62, 0x3d, 0x96, 0x56, 0x84,
	0xb2, 0x5e, 0xa6, 0x1b, 0x57, 0xca, 0x53, 0x75, 0xda, 0x11, 0x9c, 0xb4, 0x14, 0x57, 0x49, 0x07,
	0x14, 0xa3, 0xda, 0xd5, 0xe4, 0x1e, 0xb6, 0x14, 0xd4, 0x67, 0x7a, 0x0a, 0xf3, 0xcc, 0xc1, 0x23,
	0x5c, 0x53, 0x62, 0x61, 0x6a, 0x94, 0x37, 0xfb, 0x6b, 0x87, 0xcf, 0xc2, 0xa6, 0x13, 0xbc, 0x49,
	0x42, 0x21, 0xde, 0x98, 0x83, 0x45, 0xf4, 0x9e, 0xc4, 0x67, 0x14, 0xc4, 0x4b, 0x26, 0xed, 0xf8,
	0xb5, 0xd7, 0x22, 0xaa, 0x54, 0x93, 0x60, 0xf6, 0xaf, 0x23, 0xd0, 0x8e, 0xe8, 0xa0, 0x94, 0xfa,
	0xf6, 0x96, 0x12, 0x14, 0x24, 0xe0, 0x46, 0xbb, 0xf4, 0xf2, 0x7b, 0xe1, 0x76, 0x84, 0xc0, 0x38,
	0x72, 0x83, 0x35, 0x09, 0xc8, 0xb2, 0xe7, 0x5c, 0x00, 0xbe, 0xb2, 0x0e, 0x20, 0x33, 0x00, 0x4d,
	0x09, 0xde, 0xdf, 0x1e, 0x09, 0xd0, 0xa5, 0xf8, 0x60, 0x05, 0x72, 0x26, 0x72, 0x2b, 0xc5, 0x05,
	0xf7, 0xd0, 0xe7, 0xa8, 0xc7, 0x54, 0x77, 0x2a, 0x84, 0xe5, 0xf9, 0x4f, 0x83, 0x96, 0x67, 0x2d,
	0x3d, 0x36, 0xf5, 0xba, 0x42, 0xa6, 0x21, 0x77, 0x87, 0x8e, 0xa4, 0xa6, 0xf3, 0xa8, 0x90, 0x4b,
	0x27, 0x25, 0x8c, 0x78, 0x45, 0xd8, 0x95, 0x2c, 0x0e, 0x19, 0xef, 0xc9, 0x80, 0x7a, 0x97, 0xb6,
	0x37, 0x1e, 0x31, 0x59, 0x3c                                
};

static const UInt8 kIntermediateCert[] = {
	0x30, 0x82, 0x04, 0x17, 0x30, 0x82, 0x02, 0xff, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x01, 0x1b,
	0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x30,
	0x62, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02, 0x55, 0x53, 0x31, 0x13,
	0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x13, 0x0a, 0x41, 0x70, 0x70, 0x6c, 0x65, 0x20, 0x49,
	0x6e, 0x63, 0x2e, 0x31, 0x26, 0x30, 0x24, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x1d, 0x41, 0x70,
	0x70, 0x6c, 0x65, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f,
	0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x31, 0x16, 0x30, 0x14, 0x06,
	0x03, 0x55, 0x04, 0x03, 0x13, 0x0d, 0x41, 0x70, 0x70, 0x6c, 0x65, 0x20, 0x52, 0x6f, 0x6f, 0x74,
	0x20, 0x43, 0x41, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x30, 0x30, 0x35, 0x32, 0x36, 0x31, 0x39, 0x31,
	0x36, 0x30, 0x39, 0x5a, 0x17, 0x0d, 0x31, 0x37, 0x30, 0x37, 0x32, 0x36, 0x31, 0x39, 0x31, 0x36,
	0x30, 0x39, 0x5a, 0x30, 0x81, 0x8a, 0x31, 0x0b, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
	0x02, 0x55, 0x53, 0x31, 0x13, 0x30, 0x11, 0x06, 0x03, 0x55, 0x04, 0x0a, 0x0c, 0x0a, 0x41, 0x70,
	0x70, 0x6c, 0x65, 0x20, 0x49, 0x6e, 0x63, 0x2e, 0x31, 0x26, 0x30, 0x24, 0x06, 0x03, 0x55, 0x04,
	0x0b, 0x0c, 0x1d, 0x41, 0x70, 0x70, 0x6c, 0x65, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69,
	0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79,
	0x31, 0x3e, 0x30, 0x3c, 0x06, 0x03, 0x55, 0x04, 0x03, 0x0c, 0x35, 0x41, 0x70, 0x70, 0x6c, 0x65,
	0x20, 0x41, 0x70, 0x70, 0x6c, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x49, 0x6e, 0x74,
	0x65, 0x67, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x43, 0x65, 0x72, 0x74, 0x69, 0x66, 0x69,
	0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79,
	0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
	0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01,
	0x00, 0xe3, 0x5b, 0xb3, 0x27, 0x6a, 0x0c, 0xbf, 0x6e, 0xaa, 0x4c, 0xe7, 0xc5, 0x3f, 0x6f, 0x6d,
	0x4c, 0xe6, 0xa2, 0x95, 0xd5, 0xeb, 0xd5, 0x02, 0xaf, 0x70, 0x74, 0x46, 0xb9, 0xd1, 0x8f, 0xac,
	0x3b, 0xb7, 0xde, 0x0c, 0x84, 0xd0, 0x90, 0x5f, 0xff, 0xe7, 0x59, 0x43, 0xce, 0xba, 0xd5, 0xc6,
	0xc5, 0xed, 0x4f, 0xfc, 0xbf, 0xc3, 0x97, 0x59, 0x39, 0xf9, 0x64, 0xe8, 0x0e, 0x4a, 0x9f, 0x9f,
	0xf6, 0xec, 0x7a, 0x88, 0xea, 0xdf, 0xb6, 0xe7, 0x62, 0x01, 0x7f, 0x9a, 0x0f, 0xc5, 0x4a, 0x16,
	0xeb, 0xac, 0xe6, 0x98, 0x5f, 0x42, 0x3e, 0x82, 0xcb, 0x1d, 0xb3, 0x6a, 0xef, 0x1b, 0xc2, 0x8b,
	0xb6, 0x09, 0x99, 0xc9, 0xf0, 0x2c, 0x12, 0xd7, 0x2b, 0x88, 0xbe, 0x2a, 0xa8, 0xf6, 0x61, 0x3b,
	0x89, 0xea, 0xbf, 0x7f, 0x69, 0x46, 0x02, 0xcc, 0x64, 0x3e, 0x24, 0xe9, 0x5f, 0x8e, 0xf4, 0xfb,
	0xe2, 0x8a, 0xfe, 0x03, 0xfa, 0x29, 0x2c, 0xda, 0xc9, 0x94, 0x48, 0xd0, 0xde, 0xee, 0x2f, 0x88,
	0x4c, 0xf7, 0x20, 0xb5, 0x6c, 0x22, 0xca, 0xe9, 0x86, 0xc5, 0x4b, 0x5d, 0xcf, 0x83, 0xaf, 0x4f,
	0xc6, 0xb0, 0x0c, 0xb3, 0xeb, 0xd0, 0x99, 0x6d, 0xad, 0xf7, 0x26, 0x6f, 0x09, 0x2f, 0x87, 0xb8,
	0xe2, 0xb4, 0x32, 0x51, 0x8d, 0xf6, 0xcc, 0x2f, 0x88, 0x97, 0xdc, 0xd7, 0x0c, 0x6b, 0x92, 0xca,
	0xa7, 0x1e, 0xd2, 0xfa, 0x23, 0x3e, 0x81, 0xf6, 0x09, 0xa6, 0x89, 0x8a, 0x3d, 0x48, 0x09, 0x8d,
	0x08, 0x0d, 0xb0, 0x5d, 0xba, 0x05, 0x59, 0xf1, 0x79, 0x05, 0xa4, 0x09, 0x5b, 0x66, 0xa6, 0xed,
	0x8b, 0x93, 0xbc, 0xc7, 0x5d, 0x79, 0x37, 0xe1, 0x44, 0x35, 0x91, 0x8e, 0xd8, 0xd7, 0x0f, 0x95,
	0x92, 0x67, 0x43, 0xac, 0x75, 0x2b, 0x12, 0x49, 0x23, 0x36, 0x11, 0x5d, 0xd3, 0xf2, 0x82, 0xb8,
	0x13, 0x02, 0x03, 0x01, 0x00, 0x01, 0xa3, 0x81, 0xae, 0x30, 0x81, 0xab, 0x30, 0x0e, 0x06, 0x03,
	0x55, 0x1d, 0x0f, 0x01, 0x01, 0xff, 0x04, 0x04, 0x03, 0x02, 0x01, 0x86, 0x30, 0x0f, 0x06, 0x03,
	0x55, 0x1d, 0x13, 0x01, 0x01, 0xff, 0x04, 0x05, 0x30, 0x03, 0x01, 0x01, 0xff, 0x30, 0x1d, 0x06,
	0x03, 0x55, 0x1d, 0x0e, 0x04, 0x16, 0x04, 0x14, 0x31, 0xea, 0x76, 0xa9, 0x23, 0x74, 0xa5, 0xdf,
	0xd4, 0xfd, 0xee, 0xa0, 0xc1, 0xa6, 0x9e, 0xc6, 0x11, 0x0e, 0x11, 0xec, 0x30, 0x1f, 0x06, 0x03,
	0x55, 0x1d, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0x2b, 0xd0, 0x69, 0x47, 0x94, 0x76, 0x09,
	0xfe, 0xf4, 0x6b, 0x8d, 0x2e, 0x40, 0xa6, 0xf7, 0x47, 0x4d, 0x7f, 0x08, 0x5e, 0x30, 0x36, 0x06,
	0x03, 0x55, 0x1d, 0x1f, 0x04, 0x2f, 0x30, 0x2d, 0x30, 0x2b, 0xa0, 0x29, 0xa0, 0x27, 0x86, 0x25,
	0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x77, 0x77, 0x77, 0x2e, 0x61, 0x70, 0x70, 0x6c, 0x65,
	0x2e, 0x63, 0x6f, 0x6d, 0x2f, 0x61, 0x70, 0x70, 0x6c, 0x65, 0x63, 0x61, 0x2f, 0x72, 0x6f, 0x6f,
	0x74, 0x2e, 0x63, 0x72, 0x6c, 0x30, 0x10, 0x06, 0x0a, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x63, 0x64,
	0x06, 0x02, 0x03, 0x04, 0x02, 0x05, 0x00, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7,
	0x0d, 0x01, 0x01, 0x05, 0x05, 0x00, 0x03, 0x82, 0x01, 0x01, 0x00, 0x8d, 0x65, 0x84, 0xd1, 0xff,
	0x3b, 0x3d, 0x27, 0x62, 0x90, 0x15, 0xf6, 0x59, 0xce, 0x3b, 0xc9, 0xc2, 0xff, 0x9c, 0x45, 0x3c,
	0x8f, 0xc6, 0xf9, 0x44, 0x87, 0xcb, 0xfd, 0xe0, 0x79, 0x36, 0x20, 0x2d, 0x1e, 0xf7, 0x2a, 0xca,
	0x09, 0x4d, 0x28, 0xf4, 0xfe, 0xbf, 0x30, 0x13, 0xc1, 0x91, 0x76, 0x59, 0x19, 0x8a, 0xc0, 0x4c,
	0x99, 0xef, 0x5a, 0xf5, 0xbd, 0x8e, 0x87, 0x93, 0x70, 0x3b, 0x9c, 0xcc, 0x16, 0x74, 0x49, 0x55,
	0x65, 0x3a, 0xf5, 0x5b, 0x6a, 0xca, 0x17, 0x2b, 0xe7, 0x9d, 0x28, 0x93, 0x98, 0xa0, 0x67, 0x34,
	0x1a, 0xe2, 0xe9, 0x96, 0x0d, 0x47, 0xef, 0xc8, 0x9c, 0x37, 0xe4, 0xd3, 0xda, 0xf5, 0xa1, 0xd8,
	0x42, 0xeb, 0xbd, 0x51, 0x16, 0x03, 0x35, 0x94, 0x1d, 0x5a, 0x31, 0x42, 0x3d, 0x78, 0x81, 0xfe,
	0x4f, 0xa2, 0xbf, 0x3a, 0xbc, 0x78, 0x09, 0xe4, 0xcb, 0x28, 0x6e, 0x66, 0x4f, 0xe9, 0x4f, 0xb7,
	0xb5, 0xd2, 0xa2, 0x3d, 0x19, 0xb1, 0x23, 0x1d, 0x3f, 0x66, 0x93, 0xb2, 0x51, 0xc3, 0x00, 0x3b,
	0x92, 0xaa, 0xe3, 0xfd, 0x2c, 0x17, 0x22, 0xd9, 0x40, 0x94, 0x28, 0x30, 0x08, 0x54, 0xf8, 0x29,
	0x2a, 0xd5, 0xae, 0xed, 0x77, 0xc3, 0xd4, 0x80, 0x32, 0xa0, 0xc2, 0x67, 0xa3, 0x61, 0xd1, 0xb1,
	0x67, 0x99, 0x5a, 0x05, 0xd7, 0xbb, 0x5d, 0x25, 0x55, 0xbc, 0x16, 0xfd, 0x0e, 0x4e, 0x86, 0x6a,
	0x9e, 0x90, 0x9d, 0xc8, 0x34, 0x80, 0x01, 0xf4, 0x2b, 0x50, 0x52, 0xea, 0x46, 0x33, 0x20, 0x54,
	0xb8, 0x7b, 0x23, 0xce, 0x4d, 0x45, 0x32, 0x2e, 0x66, 0x5b, 0x1d, 0x8c, 0xd9, 0x16, 0xca, 0x6c,
	0xad, 0x83, 0xdd, 0x04, 0xcf, 0xb6, 0x51, 0x8d, 0xa3, 0xb6, 0xa1, 0x37, 0xa8, 0xa9, 0x8b, 0x94,
	0xb6, 0xc4, 0xc0, 0x5a, 0x2e, 0xf8, 0xd4, 0xa3, 0x28, 0x9d, 0xaa,               

	
};

static void tests(void)
{
    SecTrustResultType trustResult = kSecTrustResultProceed;
	SecPolicyRef policy = NULL;
	SecTrustRef trust = NULL;
	CFArrayRef certs = NULL;
	
	CFDataRef appleid_record_signing_cert_data = NULL;
	isnt(appleid_record_signing_cert_data = CFDataCreate(kCFAllocatorDefault, kLeafCert, sizeof(kLeafCert)), 
		NULL, "Get the AppleID Record Signing Leaf Certificate Data");
		
	SecCertificateRef appleid_record_signing_cert = NULL;
	isnt(appleid_record_signing_cert = SecCertificateCreateWithData(kCFAllocatorDefault, appleid_record_signing_cert_data),
		NULL, "Get the AppleID Record Signing Leaf Certificate Data");
		
	CFDataRef appleid_intermediate_cert_data = NULL;
	isnt(appleid_intermediate_cert_data = CFDataCreate(kCFAllocatorDefault, kIntermediateCert, sizeof(kIntermediateCert)), 
		NULL, "Get the AppleID Intermediate Certificate Data");
		
	SecCertificateRef appleid_intermediate_cert = NULL;
	isnt(appleid_intermediate_cert = SecCertificateCreateWithData(kCFAllocatorDefault, appleid_intermediate_cert_data),
		NULL, "Get the AppleID Intermediate Certificate");
		
	SecCertificateRef certs_to_use[] = {appleid_record_signing_cert, appleid_intermediate_cert};
		
	certs = CFArrayCreate(NULL, (const void **)certs_to_use, 2, NULL);
		
	isnt(policy = SecPolicyCreateAppleIDValidationRecordSigningPolicy(),
		NULL, "Create AppleID Record signing policy SecPolicyRef");
				
	ok_status(SecTrustCreateWithCertificates(certs, policy, &trust),
        "Create AppleID record signing leaf");

	ok_status(SecTrustEvaluate(trust, &trustResult), "evaluate escrow service trust for club 1");
		
	is_status(trustResult, kSecTrustResultUnspecified,
		"Trust is kSecTrustResultUnspecified AppleID record signing leaf");
		
	CFReleaseSafe(trust);
	CFReleaseSafe(policy);
	CFReleaseSafe(certs);
	CFReleaseSafe(appleid_record_signing_cert);
    CFReleaseSafe(appleid_intermediate_cert_data);
    CFReleaseSafe(appleid_record_signing_cert_data);
}


int si_75_AppleIDRecordSigning(int argc, char *const *argv)
{
		plan_tests(8);
		tests();
		return 0;
}
