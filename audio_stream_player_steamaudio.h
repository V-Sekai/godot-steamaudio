/**************************************************************************/
/*  audio_stream_player_steamaudio.h                                      */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

//Above notice retained as this is largely based on AudioStreamPlayer

#ifndef AUDIO_STREAM_PLAYER_STEAMAUDIO_H
#define AUDIO_STREAM_PLAYER_STEAMAUDIO_H

#include "audio_stream_steamaudio.h"
#include "core/templates/safe_refcount.h"
#include "godot_steamaudio.h"
#include "scene/3d/node_3d.h"
#include "servers/audio/audio_stream.h"
class AudioStreamPlayerSteamAudio : public Node3D {
	GDCLASS(AudioStreamPlayerSteamAudio, Node3D);

public:
	enum MixTarget {
		MIX_TARGET_STEREO,
		MIX_TARGET_SURROUND,
		MIX_TARGET_CENTER
	};

private:
	Vector<Ref<AudioStreamPlaybackSteamAudio>> stream_playbacks;
	Ref<AudioStreamSteamAudio> stream;

	SafeFlag active;

	float pitch_scale = 1.0;
	float volume_db = 0.0;
	bool autoplay = false;
	StringName bus = SNAME("Master");
	int max_polyphony = 1;

	MixTarget mix_target = MIX_TARGET_STEREO;

	void _mix_internal(bool p_fadeout);
	void _mix_audio();
	static void _mix_audios(void *self) { reinterpret_cast<AudioStreamPlayerSteamAudio *>(self)->_mix_audio(); }

	void _set_playing(bool p_enable);
	bool _is_active() const;

	void _bus_layout_changed();
	void _mix_to_bus(const AudioFrame *p_frames, int p_amount);

	Vector<AudioFrame> _get_volume_vector();

protected:
	void _validate_property(PropertyInfo &p_property) const;
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_stream(Ref<AudioStreamSteamAudio> p_stream);
	Ref<AudioStreamSteamAudio> get_stream() const;

	void set_volume_db(float p_volume);
	float get_volume_db() const;

	void set_pitch_scale(float p_pitch_scale);
	float get_pitch_scale() const;

	void set_max_polyphony(int p_max_polyphony);
	int get_max_polyphony() const;

	void play(float p_from_pos = 0.0);
	void seek(float p_seconds);
	void stop();
	bool is_playing() const;
	float get_playback_position();

	void set_bus(const StringName &p_bus);
	StringName get_bus() const;

	void set_autoplay(bool p_enable);
	bool is_autoplay_enabled();

	void set_mix_target(MixTarget p_target);
	MixTarget get_mix_target() const;

	void set_stream_paused(bool p_pause);
	bool get_stream_paused() const;

	bool has_stream_playback();
	Ref<AudioStreamPlaybackSteamAudio> get_stream_playback();

	bool init_source_steamaudio();

	AudioStreamPlayerSteamAudio();
	~AudioStreamPlayerSteamAudio();
};

VARIANT_ENUM_CAST(AudioStreamPlayerSteamAudio::MixTarget)

#endif // AUDIO_STREAM_PLAYER_STEAMAUDIO_H
