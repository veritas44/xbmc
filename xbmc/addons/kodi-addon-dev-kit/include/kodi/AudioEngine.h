/*
 *  Copyright (C) 2005-2019 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "AddonBase.h"

//==============================================================================
///
/// \defgroup cpp_kodi_audioengine  Interface - kodi::audioengine
/// \ingroup cpp
/// @brief **Audio engine functions**
///
///
/// It has the header \ref AudioEngine.h "#include <kodi/AudioEngine.h>" be included
/// to enjoy it.
///
//------------------------------------------------------------------------------

//==============================================================================
///
/// \defgroup cpp_kodi_audioengine_Defs Definitions, structures and enumerators
/// \ingroup cpp_kodi_audioengine
/// @brief **Library definition values**
///
//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

//============================================================================
/// \ingroup cpp_kodi_audioengine_Defs
/// @brief Bit options to pass to CAddonAEStream
///
typedef enum AudioEngineStreamOptions
{
  /// force resample even if rates match
  AUDIO_STREAM_FORCE_RESAMPLE = 1 << 0,
  /// create the stream paused
  AUDIO_STREAM_PAUSED         = 1 << 1,
  /// autostart the stream when enough data is buffered
  AUDIO_STREAM_AUTOSTART      = 1 << 2,
} AudioEngineStreamOptions;
//----------------------------------------------------------------------------

//============================================================================
/// \ingroup cpp_kodi_audioengine_Defs
/// @brief The possible channels
///
enum AudioEngineChannel
{
  AUDIOENGINE_CH_NULL = -1,
  AUDIOENGINE_CH_RAW,

  AUDIOENGINE_CH_FL,
  AUDIOENGINE_CH_FR,
  AUDIOENGINE_CH_FC,
  AUDIOENGINE_CH_LFE,
  AUDIOENGINE_CH_BL,
  AUDIOENGINE_CH_BR,
  AUDIOENGINE_CH_FLOC,
  AUDIOENGINE_CH_FROC,
  AUDIOENGINE_CH_BC,
  AUDIOENGINE_CH_SL,
  AUDIOENGINE_CH_SR,
  AUDIOENGINE_CH_TFL,
  AUDIOENGINE_CH_TFR,
  AUDIOENGINE_CH_TFC,
  AUDIOENGINE_CH_TC,
  AUDIOENGINE_CH_TBL,
  AUDIOENGINE_CH_TBR,
  AUDIOENGINE_CH_TBC,
  AUDIOENGINE_CH_BLOC,
  AUDIOENGINE_CH_BROC,

  AUDIOENGINE_CH_MAX
};

//============================================================================
/// \ingroup cpp_kodi_audioengine_Defs
/// @brief The various data formats
///
/// LE = Little Endian, BE = Big Endian, NE = Native Endian
/// @note This is ordered from the worst to best preferred formats
///
enum AudioEngineDataFormat
{
  AUDIOENGINE_FMT_INVALID = -1,

  AUDIOENGINE_FMT_U8,

  AUDIOENGINE_FMT_S16BE,
  AUDIOENGINE_FMT_S16LE,
  AUDIOENGINE_FMT_S16NE,

  AUDIOENGINE_FMT_S32BE,
  AUDIOENGINE_FMT_S32LE,
  AUDIOENGINE_FMT_S32NE,

  AUDIOENGINE_FMT_S24BE4,
  AUDIOENGINE_FMT_S24LE4,
  AUDIOENGINE_FMT_S24NE4, // 24 bits in lower 3 bytes
  AUDIOENGINE_FMT_S24NE4MSB, // S32 with bits_per_sample < 32

  AUDIOENGINE_FMT_S24BE3,
  AUDIOENGINE_FMT_S24LE3,
  AUDIOENGINE_FMT_S24NE3, /* S24 in 3 bytes */

  AUDIOENGINE_FMT_DOUBLE,
  AUDIOENGINE_FMT_FLOAT,

  // Bitstream
  AUDIOENGINE_FMT_RAW,

  /* planar formats */
  AUDIOENGINE_FMT_U8P,
  AUDIOENGINE_FMT_S16NEP,
  AUDIOENGINE_FMT_S32NEP,
  AUDIOENGINE_FMT_S24NE4P,
  AUDIOENGINE_FMT_S24NE4MSBP,
  AUDIOENGINE_FMT_S24NE3P,
  AUDIOENGINE_FMT_DOUBLEP,
  AUDIOENGINE_FMT_FLOATP,

  AUDIOENGINE_FMT_MAX
};

struct AUDIO_ENGINE_FORMAT
{
  /// The stream's data format (eg, AUDIOENGINE_FMT_S16LE)
  enum AudioEngineDataFormat m_dataFormat;

  /// The stream's sample rate (eg, 48000)
  unsigned int m_sampleRate;

  /// The encoded streams sample rate if a bitstream, otherwise undefined
  unsigned int m_encodedRate;

  /// The amount of used speaker channels
  unsigned int m_channelCount;

  /// The stream's channel layout
  enum AudioEngineChannel m_channels[AUDIOENGINE_CH_MAX];

  /// The number of frames per period
  unsigned int m_frames;

  /// The size of one frame in bytes
  unsigned int m_frameSize;
};

/* A stream handle pointer, which is only used internally by the addon stream handle */
typedef void AEStreamHandle;

/*
  * Function address structure, not need to visible on dev kit doxygen
  * documentation
  */
typedef struct AddonToKodiFuncTable_kodi_audioengine
{
  AEStreamHandle* (*make_stream)(void *kodiBase, struct AUDIO_ENGINE_FORMAT* format, unsigned int options);
  void (*free_stream)(void *kodiBase, AEStreamHandle *stream);
  bool (*get_current_sink_format)(void *kodiBase, struct AUDIO_ENGINE_FORMAT* sink_format);

  // Audio Engine Stream definitions
  unsigned int (*aestream_get_space)(void *kodiBase, AEStreamHandle *handle);
  unsigned int (*aestream_add_data)(void *kodiBase, AEStreamHandle *handle, uint8_t* const *data,
                                    unsigned int offset, unsigned int frames, double pts, bool hasDownmix,
                                    double centerMixLevel);
  double (*aestream_get_delay)(void *kodiBase, AEStreamHandle *handle);
  bool (*aestream_is_buffering)(void *kodiBase, AEStreamHandle *handle);
  double (*aestream_get_cache_time)(void *kodiBase, AEStreamHandle *handle);
  double (*aestream_get_cache_total)(void *kodiBase, AEStreamHandle *handle);
  void (*aestream_pause)(void *kodiBase, AEStreamHandle *handle);
  void (*aestream_resume)(void *kodiBase, AEStreamHandle *handle);
  void (*aestream_drain)(void *kodiBase, AEStreamHandle *handle, bool wait);
  bool (*aestream_is_draining)(void *kodiBase, AEStreamHandle *handle);
  bool (*aestream_is_drained)(void *kodiBase, AEStreamHandle *handle);
  void (*aestream_flush)(void *kodiBase, AEStreamHandle *handle);
  float (*aestream_get_volume)(void *kodiBase, AEStreamHandle *handle);
  void (*aestream_set_volume)(void *kodiBase, AEStreamHandle *handle, float volume);
  float (*aestream_get_amplification)(void *kodiBase, AEStreamHandle *handle);
  void (*aestream_set_amplification)(void *kodiBase, AEStreamHandle *handle, float amplify);
  unsigned int (*aestream_get_frame_size)(void *kodiBase, AEStreamHandle *handle);
  unsigned int (*aestream_get_channel_count)(void *kodiBase, AEStreamHandle *handle);
  unsigned int (*aestream_get_sample_rate)(void *kodiBase, AEStreamHandle *handle);
  enum AudioEngineDataFormat (*aestream_get_data_format)(void* kodiBase, AEStreamHandle* handle);
  double (*aestream_get_resample_ratio)(void *kodiBase, AEStreamHandle *handle);
  void (*aestream_set_resample_ratio)(void *kodiBase, AEStreamHandle *handle, double ratio);
} AddonToKodiFuncTable_kodi_audioengine;

#ifdef __cplusplus
} /* extern "C" */

namespace kodi
{
namespace audioengine
{

//============================================================================
/// \defgroup cpp_kodi_audioengine_Defs_AudioEngineFormat struct AudioEngineFormat
/// \ingroup cpp_kodi_audioengine_Defs
/// @brief The audio format structure that fully defines a stream's audio
/// information
///
//@{
class AudioEngineFormat : public addon::CStructHdl<AudioEngineFormat, AUDIO_ENGINE_FORMAT>
{
public:
  AudioEngineFormat()
  {
    m_cStructure->m_dataFormat = AUDIOENGINE_FMT_INVALID;
    m_cStructure->m_sampleRate = 0;
    m_cStructure->m_encodedRate = 0;
    m_cStructure->m_frames = 0;
    m_cStructure->m_frameSize = 0;
    m_cStructure->m_channelCount = 0;

    for (size_t ch = 0; ch < AUDIOENGINE_CH_MAX; ++ch)
      m_cStructure->m_channels[ch] = AUDIOENGINE_CH_NULL;
  }
  AudioEngineFormat(const AudioEngineFormat& channel) : CStructHdl(channel) {}
  AudioEngineFormat(const AUDIO_ENGINE_FORMAT* channel) : CStructHdl(channel) {}
  AudioEngineFormat(AUDIO_ENGINE_FORMAT* channel) : CStructHdl(channel) {}

  /// The stream's data format (eg, AUDIOENGINE_FMT_S16LE)
  void SetDataFormat(enum AudioEngineDataFormat format) { m_cStructure->m_dataFormat = format; }

  enum AudioEngineDataFormat GetDataFormat() const { return m_cStructure->m_dataFormat; }

  /// The stream's sample rate (eg, 48000)
  void SetSampleRate(unsigned int rate) { m_cStructure->m_sampleRate = rate; }

  unsigned int GetSampleRate() const { return m_cStructure->m_sampleRate; }

  /// The encoded streams sample rate if a bitstream, otherwise undefined
  void SetEncodedRate(unsigned int rate) { m_cStructure->m_encodedRate = rate; }

  unsigned int GetEncodedRate() const { return m_cStructure->m_encodedRate; }

  /// The stream's channel layout
  void SetChannelLayout(const std::vector<enum AudioEngineChannel>& layout)
  {
    // Reset first all to empty values to AUDIOENGINE_CH_NULL, in case given list is empty
    m_cStructure->m_channelCount = 0;
    for (size_t ch = 0; ch < AUDIOENGINE_CH_MAX; ++ch)
      m_cStructure->m_channels[ch] = AUDIOENGINE_CH_NULL;

    for (size_t ch = 0; ch < layout.size() && ch < AUDIOENGINE_CH_MAX; ++ch)
    {
      m_cStructure->m_channels[ch] = layout[ch];
      m_cStructure->m_channelCount++;
    }
  }
  std::vector<enum AudioEngineChannel> GetChannelLayout() const
  {
    std::vector<enum AudioEngineChannel> channels;
    for (size_t ch = 0; ch < AUDIOENGINE_CH_MAX; ++ch)
    {
      if (m_cStructure->m_channels[ch] == AUDIOENGINE_CH_NULL)
        break;

      channels.push_back(m_cStructure->m_channels[ch]);
    }
    return channels;
  }

  /// The number of frames per period
  void SetFramesAmount(unsigned int frames) { m_cStructure->m_frames = frames; }

  unsigned int GetFramesAmount() const { return m_cStructure->m_frames; }

  /// The size of one frame in bytes
  void SetFrameSize(unsigned int frameSize) { m_cStructure->m_frameSize = frameSize; }

  unsigned int GetFrameSize() const { return m_cStructure->m_frameSize; }

  /// Function to compare the format structure with another
  bool CompareFormat(const AudioEngineFormat *fmt)
  {
    if (!fmt)
    {
      return false;
    }

    if (m_cStructure->m_dataFormat    != fmt->m_cStructure->m_dataFormat    ||
        m_cStructure->m_sampleRate    != fmt->m_cStructure->m_sampleRate    ||
        m_cStructure->m_encodedRate   != fmt->m_cStructure->m_encodedRate   ||
        m_cStructure->m_frames        != fmt->m_cStructure->m_frames        ||
        m_cStructure->m_frameSize     != fmt->m_cStructure->m_frameSize     ||
        m_cStructure->m_channelCount  != fmt->m_cStructure->m_channelCount)
    {
      return false;
    }

    for (unsigned int ch = 0; ch < AUDIOENGINE_CH_MAX; ++ch)
    {
      if (fmt->m_cStructure->m_channels[ch] != m_cStructure->m_channels[ch])
      {
        return false;
      }
    }

    return true;
  }
};
//@}
//----------------------------------------------------------------------------

//============================================================================
///
/// \defgroup cpp_kodi_audioengine_CAddonAEStream class CAddonAEStream
/// \ingroup cpp_kodi_audioengine
/// @brief **Audio Engine Stream Class**
///
///
/// It has the header \ref AudioEngine.h "#include <kodi/AudioEngine.h>" be
/// included to enjoy it.
///
//----------------------------------------------------------------------------
class CAddonAEStream
{
public:
  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Contructs new class to an Kodi IAEStream in the format specified.
  ///
  /// @param[in] format       The data format the incoming audio will be in
  ///                         (e.g. \ref AUDIOENGINE_FMT_S16LE)
  /// @param[in] options      [opt] A bit field of stream options (see: enum \ref AudioEngineStreamOptions)
  ///
  ///
  /// ------------------------------------------------------------------------
  ///
  /// **Audio engine format information:**
  /// @code
  /// /*
  ///  * Audio engine format information
  ///  *
  ///  * Only as example shown here! See always the original structure on related header.
  ///  */
  /// typedef struct AudioEngineFormat
  /// {
  ///   enum AEDataFormat    m_dataFormat;             /* The stream's data format (eg, AE_FMT_S16LE) */
  ///   unsigned int         m_sampleRate;             /* The stream's sample rate (eg, 48000) */
  ///   unsigned int         m_encodedRate;            /* The encoded streams sample rate if a bitstream, otherwise undefined */
  ///   unsigned int         m_channelCount;           /* The amount of used speaker channels */
  ///   enum AEChannel       m_channels[AE_CH_MAX];    /* The stream's channel layout */
  ///   unsigned int         m_frames;                 /* The number of frames per period */
  ///   unsigned int         m_frameSamples;           /* The number of samples in one frame */
  ///   unsigned int         m_frameSize;              /* The size of one frame in bytes */
  ///
  ///   /* Function to compare the format structure with another */
  ///   bool compareFormat(const AudioEngineFormat *fmt);
  /// } AudioEngineFormat;
  /// @endcode
  ///
  /// ------------------------------------------------------------------------
  ///
  /// **Bit options to pass to CAELib_Stream (on Kodi by <c>IAE::MakeStream</c>)**
  ///
  /// | enum AEStreamOptions        | Value: | Description:
  /// |----------------------------:|:------:|:-----------------------------------
  /// | AUDIO_STREAM_FORCE_RESAMPLE | 1 << 0 | Force resample even if rates match
  /// | AUDIO_STREAM_PAUSED         | 1 << 1 | Create the stream paused
  /// | AUDIO_STREAM_AUTOSTART      | 1 << 2 | Autostart the stream when enough data is buffered
  ///
  ///
  /// ------------------------------------------------------------------------
  ///
  /// **Example:**
  /// ~~~~~~~~~~~~~{.cpp}
  ///
  /// #include <kodi/AudioEngine.h>
  ///
  /// using namespace kodi::audioengine;
  ///
  /// ...
  ///
  /// AudioEngineFormat format;
  /// format.m_dataFormat = AE_FMT_FLOAT;
  /// format.m_channelCount = 2;
  /// format.m_channels[0] = AE_CH_FL;
  /// format.m_channels[1] = AE_CH_FR;
  /// format.m_channels[2] = AE_CH_NULL;
  /// format.m_sampleRate = 48000;
  /// format.m_frameSize = sizeof(float)*format.m_channelCount;
  /// format.m_frames = 512;
  /// CAddonAEStream* stream = new CAddonAEStream(format, AE_STREAM_AUTOSTART);
  ///
  /// ~~~~~~~~~~~~~
  ///
  CAddonAEStream(AudioEngineFormat& format, unsigned int options = 0)
    : m_kodiBase(::kodi::addon::CAddonBase::m_interface->toKodi->kodiBase),
      m_cb(::kodi::addon::CAddonBase::m_interface->toKodi->kodi_audioengine)
  {
    m_StreamHandle = m_cb->make_stream(m_kodiBase, format, options);
    if (m_StreamHandle == nullptr)
    {
      kodi::Log(ADDON_LOG_FATAL, "CAddonAEStream: make_stream failed!");
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Class destructor
  ///
  ~CAddonAEStream()
  {
    if (m_StreamHandle)
    {
      m_cb->free_stream(m_kodiBase, m_StreamHandle);
      m_StreamHandle = nullptr;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns the amount of space available in the stream
  ///
  /// @return                 The number of bytes AddData will consume
  ///
  unsigned int GetSpace()
  {
    return m_cb->aestream_get_space(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Add planar or interleaved PCM data to the stream
  ///
  /// @param[in] data           array of pointers to the planes
  /// @param[in] offset         to frame in frames
  /// @param[in] frames         number of frames
  /// @param[in] pts            [opt] presentation timestamp, default is 0
  /// @param[in] hasDownmix     [opt] set true if downmix is present, default is false
  /// @param[in] centerMixLevel [opt] level to mix left and right to center default is 1.0
  /// @return                   The number of frames consumed
  ///
  unsigned int AddData(uint8_t* const *data, unsigned int offset, unsigned int frames,
                        double pts = 0, bool hasDownmix = false, double centerMixLevel = 1.0)
  {
    return m_cb->aestream_add_data(m_kodiBase, m_StreamHandle, data, offset, frames, pts, hasDownmix, centerMixLevel);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns the time in seconds that it will take for the next added
  /// packet to be heard from the speakers.
  ///
  /// @return seconds
  ///
  double GetDelay()
  {
    return m_cb->aestream_get_delay(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns if the stream is buffering
  ///
  /// @return True if the stream is buffering
  ///
  bool IsBuffering()
  {
    return m_cb->aestream_is_buffering(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns the time in seconds of the stream's cached audio samples.
  /// Engine buffers excluded.
  ///
  /// @return seconds
  ///
  double GetCacheTime()
  {
    return m_cb->aestream_get_cache_time(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns the total time in seconds of the cache
  ///
  /// @return seconds
  ///
  double GetCacheTotal()
  {
    return m_cb->aestream_get_cache_total(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Pauses the stream playback
  ///
  void Pause()
  {
    return m_cb->aestream_pause(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Resumes the stream after pausing
  ///
  void Resume()
  {
    return m_cb->aestream_resume(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Start draining the stream
  ///
  /// @param[in] wait         [opt] Wait until drain is finished if set to
  ///                         true, otherwise it returns direct
  ///
  /// @note Once called AddData will not consume more data.
  ///
  void Drain(bool wait = true)
  {
    return m_cb->aestream_drain(m_kodiBase, m_StreamHandle, wait);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns true if the is stream draining
  ///
  bool IsDraining()
  {
    return m_cb->aestream_is_draining(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns true if the is stream has finished draining
  ///
  bool IsDrained()
  {
    return m_cb->aestream_is_drained(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Flush all buffers dropping the audio data
  ///
  void Flush()
  {
    return m_cb->aestream_flush(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Return the stream's current volume level
  ///
  /// @return The volume level between 0.0 and 1.0
  ///
  float GetVolume()
  {
    return m_cb->aestream_get_volume(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Set the stream's volume level
  ///
  /// @param[in] volume               The new volume level between 0.0 and 1.0
  ///
  void SetVolume(float volume)
  {
    return m_cb->aestream_set_volume(m_kodiBase, m_StreamHandle, volume);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Gets the stream's volume amplification in linear units.
  ///
  /// @return The volume amplification factor between 1.0 and 1000.0
  ///
  float GetAmplification()
  {
    return m_cb->aestream_get_amplification(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Sets the stream's volume amplification in linear units.
  ///
  /// @param[in] amplify              The volume amplification factor between
  ///                                 1.0 and 1000.0
  ///
  void SetAmplification(float amplify)
  {
    return m_cb->aestream_set_amplification(m_kodiBase, m_StreamHandle, amplify);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns the size of one audio frame in bytes (channelCount * resolution)
  ///
  /// @return The size in bytes of one frame
  ///
  unsigned int GetFrameSize() const
  {
    return m_cb->aestream_get_frame_size(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns the number of channels the stream is configured to accept
  ///
  /// @return The channel count
  ///
  unsigned int GetChannelCount() const
  {
    return m_cb->aestream_get_channel_count(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Returns the stream's sample rate, if the stream is using a dynamic
  /// sample rate, this value will NOT reflect any changes made by calls to
  /// SetResampleRatio()
  ///
  /// @return The stream's sample rate (eg, 48000)
  ///
  unsigned int GetSampleRate() const
  {
    return m_cb->aestream_get_sample_rate(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Return the data format the stream has been configured with
  ///
  /// @return The stream's data format (eg, AUDIOENGINE_FMT_S16LE)
  ///
  AudioEngineDataFormat GetDataFormat() const
  {
    return m_cb->aestream_get_data_format(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Return the resample ratio
  ///
  /// @note This will return an undefined value if the stream is not resampling
  ///
  /// @return the current resample ratio or undefined if the stream is not resampling
  ///
  double GetResampleRatio()
  {
    return m_cb->aestream_get_resample_ratio(m_kodiBase, m_StreamHandle);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  /// @ingroup cpp_kodi_audioengine_CAddonAEStream
  /// @brief Sets the resample ratio
  ///
  /// @note This function may return false if the stream is not resampling, if
  /// you wish to use this be sure to set the AESTREAM_FORCE_RESAMPLE option
  ///
  /// @param[in] ratio         the new sample rate ratio, calculated by
  ///                          ((double)desiredRate / (double)GetSampleRate())
  ///
  void SetResampleRatio(double ratio)
  {
    m_cb->aestream_set_resample_ratio(m_kodiBase, m_StreamHandle, ratio);
  }
  //--------------------------------------------------------------------------

private:
  void* m_kodiBase;
  AddonToKodiFuncTable_kodi_audioengine* m_cb;
  AEStreamHandle  *m_StreamHandle;
};

//============================================================================
/// @ingroup cpp_kodi_audioengine
/// @brief Get the current sink data format
///
/// @param[in] format Current sink data format. For more details see AudioEngineFormat.
/// @return Returns true on success, else false.
///
inline bool GetCurrentSinkFormat(AudioEngineFormat& format)
{
  using namespace kodi::addon;
  return CAddonBase::m_interface->toKodi->kodi_audioengine->get_current_sink_format(CAddonBase::m_interface->toKodi->kodiBase, format);
}
//----------------------------------------------------------------------------

} /* audioengine */
} /* kodi */
#endif /* __cplusplus */
