#pragma once
/*
 *      Copyright (C) 2005-2010 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PVRCLIENT_MEDIAPORTAL_OS_POSIX_H
#define PVRCLIENT_MEDIAPORTAL_OS_POSIX_H

#include <inttypes.h>
#include <stdint.h>
#include <sys/stat.h>

typedef long        LONG;
typedef LONG        HRESULT;

#define _FILE_OFFSET_BITS 64
#define FILE_BEGIN              0
#define FILE_CURRENT            1
#define FILE_END                2

// Success codes
#define S_OK                             0L
#define S_FALSE                          1L
//
#define FAILED(Status)            ((HRESULT)(Status)<0)

// Error codes
#define ERROR_FILENAME_EXCED_RANGE       206L
#define E_OUTOFMEMORY                    0x8007000EL
#define E_FAIL                           0x8004005EL
#define ERROR_INVALID_NAME               123L

#define THREAD_FUNC_PREFIX void *
#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_BELOW_NORMAL    (THREAD_PRIORITY_LOWEST+1)
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL    (THREAD_PRIORITY_HIGHEST-1)
//#define THREAD_PRIORITY_ERROR_RETURN    (MAXLONG)

#define THREAD_PRIORITY_TIME_CRITICAL   THREAD_BASE_PRIORITY_LOWRT
#define THREAD_PRIORITY_IDLE            THREAD_BASE_PRIORITY_IDLE

//#include "File.h"

#ifdef TARGET_LINUX
#include <limits.h>
#define MAX_PATH PATH_MAX
#else
#define MAX_PATH 256
#endif

#define __stat64 stat64

#include <string.h>
#define strnicmp(X,Y,N) strncasecmp(X,Y,N)

typedef pthread_mutex_t criticalsection_t;
typedef sem_t wait_event_t;
typedef unsigned char byte;
typedef pid_t tThreadId;

// Various Windows typedefs
// Unused for Linux, but needed for compilation at the moment
//typedef struct _SECURITY_ATTRIBUTES {
//    unsigned long  nLength;
//    void*          lpSecurityDescriptor;
//    int            bInheritHandle;
//} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

/* Platform dependent path separator */
#define PATH_SEPARATOR_CHAR '/'

#ifdef TARGET_LINUX
// Retrieve the number of milliseconds that have elapsed since the system was started
#include <time.h>
inline unsigned long GetTickCount(void)
{
  struct timespec ts;
  if(clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
  {
    return 0;
  }
  return (unsigned long)( (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000) );
};
#else
#include <time.h>
inline unsigned long GetTickCount(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (unsigned long)( (tv.tv_sec * 1000) + (tv.tv_usec / 1000) );
};
#endif /* TARGET_LINUX || TARGET_DARWIN */

// For TSReader
//#include <sys/time.h>
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)

//using namespace XFILE;

typedef uint16_t Wchar_t; /* sizeof(wchar_t) = 4 bytes on Linux, but the MediaPortal buffer files have 2-byte wchars */

inline size_t WcsLen(const Wchar_t *str)
{
  const unsigned short *eos = (const unsigned short*)str;
  while( *eos++ ) ;
  return( (size_t)(eos - (const unsigned short*)str) -1);
};

inline size_t WcsToMbs(char *s, const Wchar_t *w, size_t n)
{
  size_t i = 0;
  const unsigned short *wc = (const unsigned short*) w;
  while(wc[i] && (i < n))
  {
    s[i] = wc[i];
    ++i;
  }
  if (i < n) s[i] = '\0';

  return (i);
};

inline void Sleep(long milliseconds)
{
    usleep(milliseconds * 1000);
};

#endif
