/*
 * This file is part of the Advance project.
 *
 * Copyright (C) 2001, 2002, 2003, 2004 Andrea Mazzoleni
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * In addition, as a special exception, Andrea Mazzoleni
 * gives permission to link the code of this program with
 * the MAME library (or with modified versions of MAME that use the
 * same license as MAME), and distribute linked combinations including
 * the two.  You must obey the GNU General Public License in all
 * respects for all of the code used other than MAME.  If you modify
 * this file, you may extend this exception to your version of the
 * file, but you are not obligated to do so.  If you do not wish to
 * do so, delete this exception statement from your version.
 */

#ifndef __ADVANCE_H
#define __ADVANCE_H

#include "glue.h"

#include "os.h"
#include "target.h"
#include "file.h"
#include "fz.h"
#include "key.h"
#include "conf.h"
#include "generate.h"
#include "crtcbag.h"
#include "blit.h"
#include "font.h"

#ifdef USE_LCD
#include "lcd.h"
#endif

#include <time.h>
#ifdef USE_SMP
#include <pthread.h>
#endif

/***************************************************************************/
/* Strings */

#if defined(MESS)

#define ADVANCE_COPY \
	"AdvanceMESS - Copyright (C) 2001-2003 by Andrea Mazzoleni\n" \
	"MESS - Copyright (C) 1998-2003 by the MESS Team\n" \
	"MAME - Copyright (C) 1997-2003 by Nicola Salmoria and the MAME Team\n"

#define ADVANCE_TITLE "AdvanceMESS"
#define ADVANCE_NAME "advmess"
#define ADVANCE_NAME_LEGACY "mess"

#else

#define ADVANCE_COPY \
	"AdvanceMAME - Copyright (C) 1999-2003 by Andrea Mazzoleni\n" \
	"MAME - Copyright (C) 1997-2003 by Nicola Salmoria and the MAME Team\n"

#define ADVANCE_TITLE "AdvanceMAME"
#define ADVANCE_NAME "advmame"
#define ADVANCE_NAME_LEGACY "mame"

#endif

/***************************************************************************/
/* Video */

/** Software strecth (enumeration). */
/*@{*/
#define STRETCH_NONE 0 /**< No stretch. */
#define STRETCH_INTEGER_XY 1 /**< Only integer strech x2, x3, ... */
#define STRETCH_INTEGER_X_FRACTIONAL_Y 2 /**< Integer stretch on x, fractional on y. */
#define STRETCH_FRACTIONAL_XY 3 /**< Stretch fractional on x and y. */
/*@}*/

/** Hardware stretch (mask). */
/*@{*/
#define ADJUST_NONE 0 /**< No mode adjust. */
#define ADJUST_ADJUST_X 0x1 /**< Adjust the x size. */
#define ADJUST_ADJUST_CLOCK 0x2 /**< Adjuts the clock. */
#define ADJUST_GENERATE 0x4 /**< Generate. */
#define ADJUST_ADJUST_Y 0x8 /**< Adjust the y size. */
#define ADJUST_FAVORITE_SIZE_OVER_CLOCK 0x10 /**< Favorite the size over the clock. */
/*@}*/

/** Special combine effect (enumeration). */
/*@{*/
#define COMBINE_AUTO -1
#define COMBINE_NONE 0
#define COMBINE_MAXMIN 1
#define COMBINE_MEAN 2
#define COMBINE_FILTER 3
#define COMBINE_SCALE 6
#define COMBINE_LQ 7
#define COMBINE_HQ 8
/*@}*/

/** Special additional effect (enumeration). */
/*@{*/
#define EFFECT_NONE 0
#define EFFECT_RGB_TRIAD3PIX 1
#define EFFECT_RGB_TRIADSTRONG3PIX 2
#define EFFECT_RGB_TRIAD6PIX 3
#define EFFECT_RGB_TRIADSTRONG6PIX 4
#define EFFECT_RGB_TRIAD16PIX 5
#define EFFECT_RGB_TRIADSTRONG16PIX 6
#define EFFECT_RGB_SCANDOUBLEHORZ 7
#define EFFECT_RGB_SCANTRIPLEHORZ 8
#define EFFECT_RGB_SCANDOUBLEVERT 9
#define EFFECT_RGB_SCANTRIPLEVERT 10
#define EFFECT_INTERLACE_EVEN 11
#define EFFECT_INTERLACE_ODD 12
#define EFFECT_INTERLACE_FILTER 13
/*@}*/

/** Rotate mode (enumeration). */
/*@{*/
#define ROTATE_AUTO -1
#define ROTATE_NONE 0
#define ROTATE_BLIT 1
/*@}*/

/** Max number of modelines. */
#define VIDEO_CRTC_MAX 256

/** Macro SWAP utility. */
#define SWAP(type, x, y) \
	do { \
		type temp; \
		temp = x; \
		x = y; \
		y = temp; \
	} while (0)

/** Configuration for the video part. */
struct advance_video_config_context {
	adv_bool inlist_combinemax_flag; /**< The game requires the max effect instead of the mean effect for resizing. */
	adv_bool vsync_flag; /**< If vsync is active. */
	adv_bool wait_vsync_flag; /**< If wait vsync is active. */
	adv_bool triplebuf_flag; /**< If triple buffering is active. */
	int skiplines; /**< Centering value for screen, -1 for auto centering. */
	int skipcolumns; /**< Centering value for screen, -1 for auto centering. */
	char resolution_buffer[MODE_NAME_MAX]; /**< Name of the resolution. "auto" for automatic. */
	adv_bool scanlines_flag; /**< If hardware scanlines are active */
	int stretch; /**< Type of stretch. One of STRETCH_*. */
	int adjust; /**< Type of hardware stretch. One of ADJUST_*. */
	unsigned blit_orientation; /**< Blit orientation mask. Mask of ORIENTATION_*. */
	unsigned user_orientation; /**< User orientation mask. Mask of ORIENTATION_*. */
	unsigned game_orientation; /**< Game orientation mask. Mask of ORIENTATION_*. */
	int combine; /**< Special combine effect. Mask of COMBINE_*. */
	int rgb_effect; /**< Special additional effect. Mask of EFFECT_*. */
	int interlace_effect; /**< Special additional interlace effect. Mask of EFFECT_*. */
	double turbo_speed_factor; /**< Speed of the turbo function. Multiplicative factor. */
	double fps_speed_factor; /**< Additional speed factor over the standard value. Multiplicative factor. */
	double fps_fixed; /**< Fixed fps. If ==0 use the original fps. */
	int fastest_time; /**< Time for turbo at the startup [seconds]. */
	int measure_time; /**< Time for the speed measure [seconds]. */
	adv_bool restore_flag; /**< Reset the video mode at the exit [boolean]. */
	unsigned magnify_factor; /**< Magnify factor requested [1,2,4]. */
	unsigned index; /**< Index mode. */
	double frameskip_factor; /**< Current frameskip factor. */
	adv_bool frameskip_auto_flag; /**< boolean. */
	double aspect_expansion_factor; /**< Expansion factor of the aspect. */
	adv_monitor monitor; /**< Monitor specifications. */
	adv_generate_interpolate_set interpolate; /**< Video mode generator specifications. */
	adv_crtc_container crtc_bag; /**< All the modelines. */
	char section_name_buffer[256]; /**< Section used to store the option for the game. */
	char section_resolution_buffer[256]; /**< Section used to store the option for the resolution. */
	char section_resolutionclock_buffer[256]; /**< Section used to store the option for the resolution/freq. */
	char section_orientation_buffer[256]; /**< Section used to store the option for the orientation. */
	adv_bool smp_flag; /**< Use threads */
	adv_bool crash_flag; /**< If enable the crash menu entry. */
	unsigned monitor_aspect_x; /**< Horizontal aspect of the monitor (4 for a standard monitor) */
	unsigned monitor_aspect_y; /**< Vertical aspect of the monitor (3 for a standard monitor) */

	/**
	 * Use internal sound resampling instead of the changing MAME core sample generation.
	 * Some MAME drivers change the behaviour of the game in dependency of the number of sample requested
	 * desyncronizing any input recording.
	 */
	adv_bool internalresample_flag;

	adv_bool debug_flag; /**< Debugging is possible. */
};

/** Number of measures of the audio/video syncronization. */
#define AUDIOVIDEO_MEASURE_MAX 16

/** Number of frames on which distribuite the audio/video syncronization error. */
#define AUDIOVIDEO_DISTRIBUTE_COUNT 16

struct ui_menu_entry {
	char text_buffer[128];
	char option_buffer[128];
	adv_bool flag;
	adv_bool arrow_left_flag;
	adv_bool arrow_right_flag;
};

#define PIPELINE_MEASURE_MAX 13

/** State for the video part. */
struct advance_video_state_context {
	int av_sync_map[AUDIOVIDEO_MEASURE_MAX]; /**< Circular buffer of the most recent audio/video syncronization measures. */
	unsigned av_sync_mac; /**< Current position in the ::av_sync_map buffer. */

	/* Game info */
	adv_bool game_vector_flag; /**< If is a vector game. */
	double game_fps; /**< Frame rate of the game. */
	unsigned long long game_pixelaspect_x; /**< Pixel aspect of the game */
	unsigned long long game_pixelaspect_y; /**< Pixel aspect of the game */
	unsigned game_area_size_x; /**< Max size of the used part. */
	unsigned game_area_size_y; /**< Max size of the used part. */
	unsigned game_used_size_x; /**< Current size of the used part. */
	unsigned game_used_size_y; /**< Current size of the used part. */
	unsigned game_used_pos_x; /**< Current pos of the used part. */
	unsigned game_used_pos_y; /**< Current pos of the used part. */
	int game_bits_per_pixel; /**< Game bits per pixel. */
	int game_bytes_per_pixel; /**< Game bytes per pixel. */
	int game_colors; /**< Number of colors used by the game. */
	adv_bool game_rgb_flag; /**< If the bitmap contains direct RGB colors. */
	adv_color_def game_color_def; /**< Game color format. */

	adv_bool debugger_flag; /**< Debugger show flag. */

	double gamma_effect_factor; /**< Gamma value required by the display effect. */

	adv_mode mode; /**< Video mode. */
	adv_bool mode_flag; /**< If the mode is set */
	unsigned mode_index; /**< Mode index. */
	double mode_vclock; /**< Vertical clock (normalized) */
	unsigned mode_best_size_x;
	unsigned mode_best_size_y;
	unsigned mode_best_size_2x;
	unsigned mode_best_size_2y;
	unsigned mode_best_size_3x;
	unsigned mode_best_size_3y;
	unsigned mode_best_size_4x;
	unsigned mode_best_size_4y;
	double mode_best_vclock;

	/* Palette */
	unsigned palette_total; /**< Number of entry in the palette. */
	unsigned palette_dirty_total; /**< Number of entry in the palette dirty. */
	adv_color_rgb* palette_map; /**< Current palette RGB triplets. */
	osd_mask_t* palette_dirty_map; /**< If the palette is dirty this is the list of dirty colors. */
	osd_mask_t palette_dirty_mask; /**< Mask for the last dirty element. */
	adv_bool palette_dirty_flag; /**< If the current palette dirty, it need to be updated. */
	uint32* palette_index32_map; /**< Software palette at 32 bit. */
	uint16* palette_index16_map; /**< Software palette at 16 bit. */
	uint8* palette_index8_map; /**< Software palette at 8 bit. */

	/* Syncronization */
	adv_bool sync_warming_up_flag; /**< Initializing flag. */
	double sync_pivot; /**< Syncronization error, > 0 if early, < 0 if late. */
	double sync_last; /**< Time of the last syncronization. */
	adv_bool sync_throttle_flag; /**< Throttle mode flag. */
	unsigned sync_skip_counter; /**< Number of frames skipped. */

	/* Frameskip */
	adv_bool skip_warming_up_flag; /**< Initializing flag. */
	adv_bool skip_flag; /**< Skip the next frame flag. */
	double skip_step; /**< Time for one frame. */
	unsigned skip_level_counter; /**< Current position in the cycle. */
	unsigned skip_level_full; /**< Number of frames to draw in the cycle. */
	unsigned skip_level_skip; /**< Number of frames to skip in the cycle. */
	unsigned skip_level_sum; /**< Total number of frame in the cycle. */
	adv_bool skip_level_disable_flag; /**< If skipping was disabled for some reasons. */

	int latency_diff; /**< Current sound latency error in samples. */

#ifdef USE_SMP
	/* Thread */
	pthread_t thread_id; /**< Thread identifier. */
	pthread_cond_t thread_video_cond; /**< Thread start/stop condition. */
	pthread_mutex_t thread_video_mutex; /**< Thread access control. */
	adv_bool thread_exit_flag; /**< If the thread must exit. */
	adv_bool thread_state_ready_flag; /**< If the thread data is ready. */
	struct osd_bitmap* thread_state_game; /**< Thread game bitmap to draw. */
	short* thread_state_sample_buffer; /**< Thread game sound to play. */
	unsigned thread_state_sample_count;
	unsigned thread_state_sample_recount;
	unsigned thread_state_sample_max;
	unsigned thread_state_led; /**< Thread game led to set. */
	unsigned thread_state_input; /**< Thread input to process. */
	adv_bool thread_state_skip_flag; /**< Thread frame skip_flag to use. */
#endif

	/* Fastest startup */
	unsigned fastest_counter; /**< Startup frame counter (it isn't reset during the game play) */
	adv_bool fastest_flag; /**< Fastest active flag. */

	/* Measure */
	unsigned measure_counter; /**< Measure frame counter. */
	adv_bool measure_flag; /**< Measure active flag. */
	target_clock_t measure_start; /**< Start of the measure. */
	target_clock_t measure_stop; /**< End of the measure. */

	/* Turbo */
	adv_bool turbo_flag; /**< Turbo speed is active flag. */

	/* Vsync */
	adv_bool vsync_flag; /**< Vsync is active flag. */

	/* Info */
	adv_bool info_flag; /**< Show the on screen information. */
	unsigned info_counter; /**< Back counter for temp info. */

	/* Blit info */
	int blit_src_dp; /**< Source pixel step of the game bitmap. */
	int blit_src_dw; /**< Source row step of the game bitmap. */
	int blit_src_offset; /**< Pointer at the first pixel of the game bitmap. */

	/* Buffer info */
	int buffer_src_dp; /**< Source pixel step of the game bitmap. */
	int buffer_src_dw; /**< Source row step of the game bitmap. */
	int buffer_src_offset; /**< Pointer at the first pixel of the game bitmap. */

	unsigned char* buffer_ptr; /**< Buffer used for bufferized output. */
	unsigned char* buffer_ptr_alloc; /**< Real data allocated. */
	unsigned buffer_bytes_per_scanline; /**< Byte per scanline in the buffer. */
	unsigned buffer_size_x; /**< Width of the buffer image. */
	unsigned buffer_size_y; /**< Height of the buffer image. */

	int combine; /**< One of the COMBINE_ effect. */
	int rgb_effect; /**< One of the EFFECT_ effect. */
	int interlace_effect; /**< One of the EFFECT_INTERLACE_ effect. */

	unsigned game_visible_size_x; /**< Size of the visible part of the game. */
	unsigned game_visible_size_y; /**< Size of the visible part of the game. */
	unsigned mode_visible_size_x; /**< Size of the visible part of the video mode. */
	unsigned mode_visible_size_y; /**< Size of the visible part of the video mode. */

	int game_visible_pos_x; /**< Position of the visibile part of the game in the used part. */
	int game_visible_pos_y; /**< Position of the visibile part of the game in the used part. */

	/** Basic increment of number of pixel for mantaining the alignement. */
	unsigned game_visible_pos_x_increment;

	/* Blit pipeline */
	adv_bool blit_pipeline_flag; /**< !=0 if blit_pipeline is computed. */
	struct video_pipeline_struct blit_pipeline_video; /**< Put pipeline to video. */
	struct video_pipeline_struct buffer_pipeline_video; /**< Put pipeline to buffer. */

	adv_bool pipeline_measure_flag; /**< !=0 if the time measure is active. */
	double pipeline_measure_direct_map[PIPELINE_MEASURE_MAX];
	unsigned pipeline_measure_direct_mac;
	double pipeline_measure_buffer_map[PIPELINE_MEASURE_MAX];
	unsigned pipeline_measure_buffer_mac;
	adv_bool pipeline_measure_bestisdirect_flag;
	double pipeline_measure_direct_result;
	double pipeline_measure_buffer_result;

	const adv_crtc* crtc_selected; /**< Current crtc, pointer in the crtc_vector. */
	adv_crtc crtc_effective; /**< Current modified crtc. */
	const adv_crtc* crtc_map[VIDEO_CRTC_MAX];
	unsigned crtc_mac;

	/* Event */
	unsigned event_mask_old; /**< Previous event bitmask. */

	adv_bool pause_flag; /**< The emulation is paused. */

	/* Menu state */
	adv_bool menu_sub_flag; /**< If the sub menu is active. */
	int menu_sub_selected; /**< Index of the selected sub menu voice. */
};

struct advance_video_context {
	struct advance_video_config_context config;
	struct advance_video_state_context state;
};

void video_aspect_reduce(unsigned long long* a, unsigned long long* b);
double video_rate_scale_down(double rate, double reference);
int crtc_scanline(const adv_crtc* crtc);
void crtc_sort(const struct advance_video_context* context, const adv_crtc** map, unsigned mac);

const char* mode_current_name(const struct advance_video_context* context);
unsigned mode_current_magnify(const struct advance_video_context* context);
int mode_current_stretch(const struct advance_video_context* context);
void mode_desc_print(struct advance_video_context* context, char* buffer, unsigned size, const adv_crtc* crtc);
int mode_current_stretch(const struct advance_video_context* context);

adv_error advance_video_init(struct advance_video_context* context, adv_conf* cfg_context);
void advance_video_done(struct advance_video_context* context);
adv_error advance_video_inner_init(struct advance_video_context* context, struct mame_option* option);
void advance_video_inner_done(struct advance_video_context* context);
adv_error advance_video_config_load(struct advance_video_context* context, adv_conf* cfg_context, struct mame_option* option);
void advance_video_change(struct advance_video_context* context, struct advance_video_config_context* config);
void advance_video_save(struct advance_video_context* context, const char* section);

/***************************************************************************/
/* Record */

struct advance_record_config_context {
	unsigned sound_time; /**< Max recording time in seconds. */
	unsigned video_time; /**< Max recording time in seconds. */
	char dir_buffer[FILE_MAXPATH]; /**< Directory to store the recording. */
	adv_bool video_flag; /**< Main activation flag for video recording. */
	adv_bool sound_flag; /**< Main activation flag for sound recording. */
	unsigned video_interlace; /**< Interlace factor for the video recording. */
};

struct advance_record_state_context {
#ifdef USE_SMP
	pthread_mutex_t access_mutex;
#endif

	adv_bool sound_active_flag; /**< Main activation flag for sound recording. */
	adv_bool video_active_flag; /**< Main activation flag for video recording. */
	adv_bool snapshot_active_flag; /**< Main activatio flag for snapshot recording. */

	adv_bool sound_stereo_flag; /**< Number of channels 1 (==0) or 2 (!=0) channels. */
	double sound_frequency; /**< Frequency. */
	unsigned sound_sample_counter; /**< Samples saved. */
	unsigned sound_sample_size; /**< Size in byte of one sample. */
	adv_bool sound_stopped_flag; /**< If the sound recording is stopped. */

	double video_frequency;
	unsigned video_sample_counter;
	unsigned video_freq_step; /**< Frequency base value. */
	unsigned video_freq_base; /**< Frequency step value. */
	adv_bool video_stopped_flag; /**< If the video recording is stopped. */

	char sound_file_buffer[FILE_MAXPATH]; /**< Sound file */
	FILE* sound_f; /**< Sound handle */

	char video_file_buffer[FILE_MAXPATH]; /**< Video file */
	adv_fz* video_f; /**< Video handle */

	char snapshot_file_buffer[FILE_MAXPATH]; /**< Shapshot file */
};

struct advance_record_context {
	struct advance_record_config_context config;
	struct advance_record_state_context state;
};

adv_error advance_record_init(struct advance_record_context* context, adv_conf* cfg_context);
void advance_record_done(struct advance_record_context* context);
adv_error advance_record_config_load(struct advance_record_context* context, adv_conf* cfg_context);

void advance_record_sound_update(struct advance_record_context* context, const short* sample_buffer, unsigned sample_count);
void advance_record_video_update(struct advance_record_context* context, const void* video_buffer, unsigned video_width, unsigned video_height, unsigned video_bytes_per_pixel, unsigned video_bytes_per_scanline, adv_color_def color_def, adv_color_rgb* palette_map, unsigned palette_max, unsigned orientation);
void advance_record_snapshot_update(struct advance_record_context* context, const void* video_buffer, unsigned video_width, unsigned video_height, unsigned video_bytes_per_pixel, unsigned video_bytes_per_scanline, adv_color_def color_def, adv_color_rgb* palette_map, unsigned palette_max, unsigned orientation);

adv_bool advance_record_sound_is_active(struct advance_record_context* context);
adv_bool advance_record_video_is_active(struct advance_record_context* context);
adv_bool advance_record_snapshot_is_active(struct advance_record_context* context);

adv_error advance_record_png_write(adv_fz* f, const void* video_buffer, unsigned video_width, unsigned video_height, unsigned video_bytes_per_pixel, unsigned video_bytes_per_scanline, adv_color_def color_def, adv_color_rgb* palette_map, unsigned palette_max, unsigned orientation);

/***************************************************************************/
/* Sound */

/** Sound mode (enumeration). */
/*@{*/
#define SOUND_MODE_AUTO -1
#define SOUND_MODE_MONO 0
#define SOUND_MODE_STEREO 1
#define SOUND_MODE_SURROUND 2
/*@}*/

struct advance_sound_config_context {
	double latency_time; /**< Requested minimum latency in seconds */
	int mode; /**< Channel mode. */
	int attenuation; /**< Sound attenuation in db (0 == full volume). */
	adv_bool adjust_flag; /**< Adjust the sound volume. */
};

struct advance_sound_state_context {
	adv_bool active_flag; /**< Flag for active sound. */
	double volume; /**< Current volume. [0 - 1]. */
	unsigned latency_min; /**< Expected minum latency in samples. */
	unsigned latency_max; /**< Maximum latency, limitated by the lower driver buffer. */
	unsigned rate; /**< Current sample rate */
	int input_mode; /**< Input mode format. */
	int output_mode; /**< Output mode format. */
	unsigned input_bytes_per_sample; /**< Input data sample size. */
	unsigned output_bytes_per_sample; /**< Output data sample size. */
	unsigned snapshot_counter; /**< Current snapshot counter */
	int adjust_limit; /**< Current high sample value. */
	unsigned adjust_mult; /**< Sample multiplicator. */
};

struct advance_sound_context {
	struct advance_sound_config_context config;
	struct advance_sound_state_context state;
};

adv_error advance_sound_init(struct advance_sound_context* context, adv_conf* cfg_context);
void advance_sound_done(struct advance_sound_context* context);
adv_error advance_sound_config_load(struct advance_sound_context* context, adv_conf* cfg_context, struct mame_option* game_options);
void advance_sound_update(struct advance_sound_context* context, struct advance_record_context* record_context, struct advance_video_context* video_context, const short* sample_buffer, unsigned sample_count, unsigned sample_recount);
int advance_sound_latency_diff(struct advance_sound_context* context, double extra_latency);

/***************************************************************************/
/* Estimate */

struct advance_estimate_context {
	double estimate_mame_full; /**< Estimate time for a MAME full frame */
	double estimate_mame_skip; /**< Estimate time for a MAME skip frame */
	double estimate_osd_full; /**< Estimate time for a OSD full frame */
	double estimate_osd_skip; /**< Estimate time for a OSD skip frame */
	double estimate_common_full;
	double estimate_common_skip;
	double estimate_frame; /**< Estimate time for a MAME+OSD frame */
	adv_bool estimate_mame_flag; /**< If last time at point 1 is set */
	adv_bool estimate_osd_flag; /**< If last time at point 2 is set */
	adv_bool estimate_frame_flag; /**< If last time at point 3 is set */
	adv_bool estimate_common_flag;
	double estimate_mame_last; /**< Last time at point 1 */
	double estimate_osd_last; /**< Last time at point 2 */
	double estimate_frame_last; /**< Last time at point 3 */
	double estimate_common_last;
};

void advance_estimate_init(struct advance_estimate_context* context, double step);

void advance_estimate_mame_begin(struct advance_estimate_context* context);
void advance_estimate_mame_end(struct advance_estimate_context* context, adv_bool skip_flag);
void advance_estimate_osd_begin(struct advance_estimate_context* context);
void advance_estimate_osd_end(struct advance_estimate_context* context, adv_bool skip_flag);
void advance_estimate_frame(struct advance_estimate_context* context);
void advance_estimate_common_begin(struct advance_estimate_context* context);
void advance_estimate_common_end(struct advance_estimate_context* context, adv_bool skip_flag);

/***************************************************************************/
/* SafeQuit */

#define SAFEQUIT_ENTRY_MAX 256

enum {
	safequit_event_zerocoin = 0,
	safequit_event_demomode = 1,
	safequit_event_event1 = 2,
	safequit_event_event2 = 3,
	safequit_event_event3 = 4,
	safequit_event_event4 = 5,
	safequit_event_event5 = 6,
	safequit_event_event6 = 7,
	safequit_event_event7 = 8,
	safequit_event_event8 = 9,
	safequit_event_event9 = 10,
	safequit_event_event10 = 11,
	safequit_event_event11 = 12,
	safequit_event_event12 = 13,
	safequit_event_event13 = 14,
	safequit_event_event14 = 15
};

enum {
	safequit_action_match = 0,
	safequit_action_nomatch = 1,
	safequit_action_on = 2,
	safequit_action_off = 3
};

struct safequit_entry {
	unsigned char event;
	unsigned char cpu;
	unsigned address;
	unsigned char action;
	unsigned char mask;
	unsigned char result;
	unsigned frame_count;
};

struct advance_safequit_config_context {
	char file_buffer[FILE_MAXPATH]; /**< File safequit.dat to load. */
	adv_bool debug_flag; /**< Show the debug flag on the screen. */
        adv_bool safe_exit_flag; /**< Flag for safe exit. */
};

struct advance_safequit_state_context {
	struct safequit_entry entry_map[SAFEQUIT_ENTRY_MAX];
	unsigned entry_mac;
	unsigned status;
	unsigned coin; /**< Number of coins. */
	adv_bool coin_set; /**< If the number of coins is valid. */
};

struct advance_safequit_context {
	struct advance_safequit_config_context config;
	struct advance_safequit_state_context state;
};

adv_error advance_safequit_init(struct advance_safequit_context* context, adv_conf* cfg_context);
void advance_safequit_done(struct advance_safequit_context* context);
adv_error advance_safequit_inner_init(struct advance_safequit_context* context, struct mame_option* option);
void advance_safequit_inner_done(struct advance_safequit_context* context);
adv_error advance_safequit_config_load(struct advance_safequit_context* context, adv_conf* cfg_context);
adv_bool advance_safequit_can_exit(struct advance_safequit_context* context);
adv_bool advance_safequit_event_mask(struct advance_safequit_context* context);
void advance_safequit_update(struct advance_safequit_context* context);

/***************************************************************************/
/* Input */

/** Max supported input devices. */
/*@{*/
#define INPUT_PLAYER_MAX 4 /**< Max numer of player. */

#define INPUT_ANALOG_MAX 4 /**< Max number of analog control for player. */
#define INPUT_TRAK_MAX 2 /**< Max number of trak control for player. */
#define INPUT_DIGITAL_MAX 2048 /**< Max number of digital port definition. */

#define INPUT_MAP_MAX 16 /**< Max number of mapping codes. */

#define INPUT_KEYBOARD_MAX 4 /**< Max number of keyboard. */
#define INPUT_JOY_MAX 8 /**< Max number of joysticks. */
#define INPUT_STICK_MAX 8 /**< Max number of sticks for a joystick. */
#define INPUT_AXE_MAX 8 /**< Max number of axes for a stick or mouse. */
#define INPUT_DIR_MAX 2 /**< Max number of direction for an axe (up/down or left/right). */
#define INPUT_MOUSE_MAX 8 /**< Max number of mouses. */
#define INPUT_BUTTON_MAX 16 /**< Max number buttons for a joystick or mouses. */

#define INPUT_HELP_MAX 512 /**< Max number of help entry. */

/*@}*/

struct help_entry {
	unsigned code;
	unsigned x;
	unsigned y;
	unsigned dx;
	unsigned dy;
};

struct analog_map_entry {
	unsigned seq[INPUT_MAP_MAX]; /**< Sequence assigned. */
};

struct trak_map_entry {
	unsigned seq[INPUT_MAP_MAX]; /**< Sequence assigned. */
};

struct advance_input_config_context {
	int input_idle_limit; /**< Limit of no input to exit. */
	adv_bool steadykey_flag; /**< Enable the steady-key management. */
	adv_bool disable_special_flag; /**< Disable the special OS key sequences. */

	struct analog_map_entry analog_map[INPUT_PLAYER_MAX][INPUT_ANALOG_MAX]; /**< Mapping of the analog controls. */
	struct trak_map_entry trak_map[INPUT_PLAYER_MAX][INPUT_TRAK_MAX]; /**< Mapping of the trak controls. */
};

struct advance_input_state_context {
	adv_bool active_flag; /**< Flag for active input. */

	target_clock_t input_current_clock; /**< Current clock. */
	target_clock_t input_idle_clock; /**< Clock of last input. */

	adv_bool input_forced_exit_flag; /**< Flag to signal the forced exit. */
	adv_bool input_on_this_frame_flag; /**< Flag used to signal an input on the current frame. */

	unsigned char key_old[INPUT_KEYBOARD_MAX][KEYB_MAX]; /**< Keyboard previous frame state. */
	unsigned char key_current[INPUT_KEYBOARD_MAX][KEYB_MAX]; /**< Keyboard current frame state. */

	int joystick_button_current[INPUT_JOY_MAX][INPUT_BUTTON_MAX]; /**< Joystick button state. */
	int joystick_analog_current[INPUT_JOY_MAX][INPUT_STICK_MAX][INPUT_AXE_MAX]; /**< Joystick analog state. */
	int joystick_digital_current[INPUT_JOY_MAX][INPUT_STICK_MAX][INPUT_AXE_MAX][INPUT_DIR_MAX]; /**< Joystick digital state. */
	int ball_analog_current[INPUT_JOY_MAX][INPUT_AXE_MAX]; /**< Joystick ball analog state. */

	int mouse_button_current[INPUT_MOUSE_MAX][INPUT_BUTTON_MAX]; /**< Mouse button state. */
	int mouse_analog_current[INPUT_MOUSE_MAX][INPUT_AXE_MAX]; /**< Mouse analog state. */
};

struct advance_input_context {
	struct advance_input_config_context config;
	struct advance_input_state_context state;
};

adv_error advance_input_init(struct advance_input_context* context, adv_conf* cfg_context);
void advance_input_done(struct advance_input_context* context);
adv_error advance_input_inner_init(struct advance_input_context* context, adv_conf* cfg_context);
void advance_input_inner_done(struct advance_input_context* context);
void advance_input_update(struct advance_input_context* context, struct advance_safequit_context* safequit_context, adv_bool is_pause);
adv_error advance_input_config_load(struct advance_input_context* context, adv_conf* cfg_context);
int advance_input_exit_filter(struct advance_input_context* context, struct advance_safequit_context* safequit_context, adv_bool result_memory);
void advance_input_force_exit(struct advance_input_context* context);
adv_error advance_input_parse_digital(unsigned* seq_map, unsigned seq_max, char* buffer);
adv_error advance_input_parse_analogname(unsigned* type, const char* buffer);
adv_error advance_input_parse_analogvalue(int* delta, int* sensitivity, int* reverse, int* center, char* buffer);
adv_error advance_input_print_analogname(char* buffer, unsigned buffer_size, unsigned type);
void advance_input_print_analogvalue(char* buffer, unsigned buffer_size, int delta, int sensitivity, int reverse, int center);
adv_bool advance_input_digital_pressed(struct advance_input_context* context, unsigned code);

/***************************************************************************/
/* Global */

/** Difficult level (enumeration). */
/*@{*/
#define DIFFICULTY_NONE -1 /**< Don't change the value stored in the .cfg file. */
#define DIFFICULTY_EASIEST 0
#define DIFFICULTY_EASY 1
#define DIFFICULTY_MEDIUM 2
#define DIFFICULTY_HARD 3
#define DIFFICULTY_HARDEST 4
/*@}*/

struct advance_global_config_context {
	int difficulty; /**< Difficulty level. */
	adv_bool quiet_flag; /**< Be quiet on message printing. */
	double pause_brightness; /**< Display brightness when paused. */
	char lcd_server_buffer[256]; /**< Server (address:port) for the LCD output. */
	int lcd_timeout; /**< LCD timeout in ms. */
	int lcd_speed; /**< LCD speed. */
};

struct advance_global_state_context {
	adv_bool is_config_writable; /**< Is the configuration file writable ? */
	char message_buffer[256]; /**< Next message to be displayed. */
#ifdef USE_LCD
	adv_lcd* lcd; /**< LCD context. */
#endif
};

struct advance_global_context {
	struct advance_global_config_context config;
	struct advance_global_state_context state;
};

void advance_global_message_va(struct advance_global_context* context, const char* text, va_list arg);
void advance_global_message(struct advance_global_context* context, const char* text, ...) __attribute__((format(printf, 2, 3)));
void advance_global_lcd(struct advance_global_context* context, unsigned row, const char* text);

adv_error advance_global_init(struct advance_global_context* context, adv_conf* cfg_context);
adv_error advance_global_inner_init(struct advance_global_context* context);
void advance_global_inner_done(struct advance_global_context* context);
adv_error advance_global_config_load(struct advance_global_context* context, adv_conf* cfg_context);
void advance_global_done(struct advance_global_context* context);

/***************************************************************************/
/* Fileio */

struct advance_fileio_state_context {
	adv_fz* diff_handle; /**< Diff file handle. */
	char diff_file_buffer[FILE_MAXPATH]; /**< Diff file path. */
};

struct advance_fileio_context {
	struct advance_fileio_state_context state;
};

void advance_fileio_default_dir(void);
adv_error advance_fileio_init(struct advance_fileio_context* context, adv_conf* cfg_context);
void advance_fileio_done(struct advance_fileio_context* context);
adv_error advance_fileio_config_load(struct advance_fileio_context* context, adv_conf* cfg_context, struct mame_option* option);

/***************************************************************************/
/* UI */

struct advance_ui_config_context {
	unsigned help_mac; /**< Number of help entries. */
	struct help_entry help_map[INPUT_HELP_MAX]; /**< Help map. */
	char help_image_buffer[256]; /**< File name of the help image. */
	char ui_font_buffer[256]; /**< File name of the font. */
	unsigned ui_font_orientation; /**< Orientation for the font. */
	unsigned ui_font_sizex; /**< X size of the font. */
	unsigned ui_font_sizey; /**< Y size of the font. */
};

struct advance_ui_state_context {
	adv_bool ui_extra_flag; /**< Extra frame to be drawn to clear the off game border. */
	adv_bool ui_message_flag; /**< User interface message display flag. */
	double ui_message_stop_time; /**< Time to stop thee interface message display. */
	char ui_message_buffer[256]; /**< User interface message buffer. */
	adv_bool ui_help_flag; /**< User interface help display flag. */
	adv_font* ui_font; /**< User interface font. */
	adv_font* ui_font_oriented; /**< User interface font with blit orientation. */
	adv_bool ui_menu_flag; /**< Menu display flag. */
	struct ui_menu_entry* ui_menu_map;
	unsigned ui_menu_mac;
	unsigned ui_menu_sel;
	adv_bool ui_osd_flag; /**< On Screen Display display flag. */
	char ui_osd_buffer[256];
	int ui_osd_value;
	int ui_osd_max;
	int ui_osd_min;
	int ui_osd_def;
	adv_bool ui_scroll_flag; /**< Scroll display flag. */
	char* ui_scroll_begin;
	char* ui_scroll_end;
	unsigned ui_scroll_pos;

	adv_bool ui_direct_text_flag; /**< Direct text on screen flag. */
	char ui_direct_buffer[256]; /**< Direct text on screen message. */
	adv_bool ui_direct_slow_flag; /**< Direct slow tag on screen flag. */

	adv_bitmap* help_image; /**< Help image. */
	adv_color_rgb help_rgb_map[256]; /**< Help image palette. */
	unsigned help_rgb_max; /**< Help image palette size. */
};

struct advance_ui_context {
	struct advance_ui_config_context config;
	struct advance_ui_state_context state;
};

void advance_ui_message_va(struct advance_ui_context* context, const char* text, va_list arg);
void advance_ui_message(struct advance_ui_context* context, const char* text, ...) __attribute__((format(printf, 2, 3)));
void advance_ui_direct_text(struct advance_ui_context* context, const char* text);
void advance_ui_direct_slow(struct advance_ui_context* context, int flag);
void advance_ui_help(struct advance_ui_context* context);
void advance_ui_menu(struct advance_ui_context* context, struct ui_menu_entry* menu_map, unsigned menu_mac, unsigned menu_sel);
void advance_ui_menu_vect(struct advance_ui_context* context, const char** items, const char** subitems, char* flag, int selected, int arrowize_subitem);
void advance_ui_buffer_update(struct advance_ui_context* context, void* ptr, unsigned dx, unsigned dy, unsigned dw, adv_color_def color_def, adv_color_rgb* palette_map, unsigned palette_max);
void advance_ui_direct_update(struct advance_ui_context* context, void* ptr, unsigned dx, unsigned dy, unsigned dw, adv_color_def color_def, adv_color_rgb* palette_map, unsigned palette_max);
adv_error advance_ui_init(struct advance_ui_context* context, adv_conf* cfg_context);
adv_error advance_ui_config_load(struct advance_ui_context* context, adv_conf* cfg_context, struct mame_option* option);
void advance_ui_done(struct advance_ui_context* context);
adv_error advance_ui_inner_init(struct advance_ui_context* context, adv_conf* cfg_context);
void advance_ui_inner_done(struct advance_ui_context* context);
adv_bool advance_ui_buffer_active(struct advance_ui_context* context);
adv_bool advance_ui_direct_active(struct advance_ui_context* context);
adv_error advance_ui_parse_help(struct advance_ui_context* context, char* s);
void advance_ui_changefont(struct advance_ui_context* context, unsigned screen_width, unsigned screen_height, unsigned aspect_x, unsigned aspect_y);

/***************************************************************************/
/* State */

struct advance_context {
	const mame_game* game;
	adv_conf* cfg; /**< Context of the current configuration. */
	struct advance_global_context global;
	struct advance_video_context video;
	struct advance_estimate_context estimate;
	struct advance_input_context input;
	struct advance_sound_context sound;
	struct advance_record_context record;
	struct advance_safequit_context safequit;
	struct advance_fileio_context fileio;
	struct advance_ui_context ui;
};

/**
 * Complete Advance MAME context.
 * All the state and configuration variable are stored in this structure.
 */
extern struct advance_context CONTEXT;

/***************************************************************************/
/* Interface */

/* Glue */
adv_error mame_init(struct advance_context* context);
void mame_done(struct advance_context* context);
adv_error mame_config_load(adv_conf* context, struct mame_option* option);
int mame_game_run(struct advance_context* context, const struct mame_option* option);

/* Timer */
static inline double advance_timer(void)
{
	return target_clock() / (double)TARGET_CLOCKS_PER_SEC;
}

#endif
