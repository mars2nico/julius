/**
 * @file   adin_mic_openal.c
 *
 * <JA>
 * @brief  マイク入力 (OpenAL)
 *
 * マイク入力のための低レベル関数です．
 * インタフェースを明示指定しない (-input mic) 場合に呼ばれます．
 * </JA>
 * <EN>
 * @brief  Microphone input on OpenAL
 *
 * Low level I/O functions for microphone input on Linux.
 * This will be called when no device was explicitly specified ("-input mic").
 * </EN>
 *
 * @author <AUTHOR>
 * @date   <DATE>
 *
 * $Revision: <#.##> $
 * 
 */
/*
 * Copyright (c) <YEAR> <COPYRIGHT HOLDER>
 * All rights reserved
 */

#include <sent/stddefs.h>
#include <sent/adin.h>

/** 
 * Device initialization: check device capability and open for recording.
 * 
 * @param sfreq [in] required sampling frequency.
 * @param dummy [in] a dummy data
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_standby(int sfreq, void *dummy)
{
#if defined(HAS_OPENAL)
  return FALSE;
#else  /* otherwise */
  jlog("OpenAL feature is not available\n");
  return FALSE;
#endif
}

/** 
 * Start recording.
 * 
 * @param pathname [in] path name to open or NULL for default
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_begin(char *pathname)
{
#if defined(HAS_OPENAL)
  return FALSE;
#else  /* otherwise */
  jlog("OpenAL feature is not available\n");
  return FALSE;
#endif
}

/** 
 * Stop recording.
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_end()
{
#if defined(HAS_OPENAL)
  return FALSE;
#else  /* otherwise */
  jlog("OpenAL feature is not available\n");
  return FALSE;
#endif
}

/**
 * @brief  Read samples from device
 * 
 * Try to read @a sampnum samples and returns actual number of recorded
 * samples currently available.  This function will block until
 * at least one sample can be obtained.
 * 
 * @param buf [out] samples obtained in this function
 * @param sampnum [in] wanted number of samples to be read
 * 
 * @return actural number of read samples, -2 if an error occured.
 */
int
adin_mic_read(SP16 *buf, int sampnum)
{
#if defined(HAS_OPENAL)
  return FALSE;
#else  /* otherwise */
  jlog("OpenAL feature is not available\n");
  return -2;
#endif
}

/** 
 * Function to pause audio input (wait for buffer flush)
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_pause()
{
  return TRUE;
}

/** 
 * Function to terminate audio input (disgard buffer)
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_terminate()
{
  return TRUE;
}
/** 
 * Function to resume the paused / terminated audio input
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_resume()
{
  return TRUE;
}

/** 
 * 
 * Function to return current input source device name
 * 
 * @return string of current input device name.
 * 
 */
char *
adin_mic_input_name()
{
#if defined(HAS_OPENAL)
  return FALSE;
#else  /* otherwise */
  return("Error: OpenAL feature is not available\n");
#endif
}
