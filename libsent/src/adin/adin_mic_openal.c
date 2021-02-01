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

#include <AL/al.h>
#include <AL/alc.h>

#define MINSAMPLES 3000 /// TODO: add comment
#define MAXPOLLINTERVAL 300	///< Read timeout in msec.

static ALCdevice *mic = NULL;
static ALCuint srate;		        ///< Required sampling rate
static ALCuint latency = 1024;	///< Lantency time in msec
static boolean need_swap;	      ///< Whether samples need byte swap

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
  srate = sfreq;
  need_swap = FALSE;
  return TRUE;
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
  ALCsizei buffersize = srate * latency / 1000;
  mic = alcCaptureOpenDevice(NULL, srate, AL_FORMAT_MONO16, buffersize);
  if( !mic ){
    fprintf(stderr, "Failed to open a device\n");
    return FALSE;
  }
  alcCaptureStart(mic);
  return TRUE;
}

/** 
 * Stop recording.
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_end()
{
  alcCaptureStop(mic);
  if( alcCloseDevice(mic) == ALC_FALSE ){
    return FALSE;
  }
  mic = NULL;
  return TRUE;
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
  ALint sample = -1;
  while( sample < MINSAMPLES ){
    if( 0 <= sample ) emscripten_sleep(MAXPOLLINTERVAL);
    sample = -1;
    alcGetIntegerv(mic, ALC_CAPTURE_SAMPLES, sizeof(sample), &sample);
    if( sample < 0 || sampnum < sample ){
      fprintf(stderr, "Error: adin_openal: failed to read buffer (%d:%d)\n", sample, sampnum);
      return(-2);
    }
  }
  alcCaptureSamples(mic, (ALCvoid*)buf, (ALCsizei)sample);
  if (need_swap) {
    swap_sample_bytes(buf, sample);
  }

  return sample;
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
  return("Error: not implemented\n");
}
