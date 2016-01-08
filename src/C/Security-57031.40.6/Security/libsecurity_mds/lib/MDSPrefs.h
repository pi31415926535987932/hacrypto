/*
 * Copyright (c) 2000-2001,2011,2014 Apple Inc. All Rights Reserved.
 * 
 * The contents of this file constitute Original Code as defined in and are
 * subject to the Apple Public Source License Version 1.2 (the 'License').
 * You may not use this file except in compliance with the License. Please obtain
 * a copy of the License at http://www.apple.com/publicsource and read it before
 * using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS
 * OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see the License for the
 * specific language governing rights and limitations under the License.
 */


//
// MDSPrefs.h
//

#ifndef _MDS_PREFS_H
#define _MDS_PREFS_H

#include <CoreFoundation/CFArray.h>

class MDSPrefs
{
public:
    MDSPrefs();
    ~MDSPrefs();

    int getNumberOfPluginFolders() const;
    const char *getPluginFolder(int index);
    
private:
    bool readPathFromPrefs();
    bool readPathFromEnv();
    void useDefaultPath();

    CFArrayRef mPluginFolders;
    enum { kTempBufferSize = 1024 };
    char mTempBuffer[kTempBufferSize];
};

#endif // _MDS_PREFS_H
