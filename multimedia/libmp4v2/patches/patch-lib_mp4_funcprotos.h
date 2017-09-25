$NetBSD: patch-lib_mp4_funcprotos.h,v 1.2 2017/09/25 22:30:06 joerg Exp $

Match new return types.

--- lib/mp4/funcprotos.h.orig	2001-08-01 00:34:00.000000000 +0000
+++ lib/mp4/funcprotos.h
@@ -9,81 +9,81 @@ quicktime_trak_t* quicktime_add_track(qu
 quicktime_trak_t* quicktime_find_track_by_id(quicktime_moov_t *moov, int trackId);
 
 /* initializers for every atom */
-int quicktime_matrix_init(quicktime_matrix_t *matrix);
-int quicktime_edts_init_table(quicktime_edts_t *edts);
-int quicktime_edts_init(quicktime_edts_t *edts);
-int quicktime_elst_init(quicktime_elst_t *elst);
-int quicktime_elst_init_all(quicktime_elst_t *elst);
-int quicktime_elst_table_init(quicktime_elst_table_t *table); /* initialize a table */
+void quicktime_matrix_init(quicktime_matrix_t *matrix);
+void quicktime_edts_init_table(quicktime_edts_t *edts);
+void quicktime_edts_init(quicktime_edts_t *edts);
+void quicktime_elst_init(quicktime_elst_t *elst);
+void quicktime_elst_init_all(quicktime_elst_t *elst);
+void quicktime_elst_table_init(quicktime_elst_table_t *table); /* initialize a table */
 int quicktime_tkhd_init(quicktime_tkhd_t *tkhd);
-int quicktime_tkhd_init_video(quicktime_t *file, quicktime_tkhd_t *tkhd, int frame_w, int frame_h);
+void quicktime_tkhd_init_video(quicktime_t *file, quicktime_tkhd_t *tkhd, int frame_w, int frame_h);
 int quicktime_ctab_init(quicktime_ctab_t *ctab);
-int quicktime_mjqt_init(quicktime_mjqt_t *mjqt);
-int quicktime_mjht_init(quicktime_mjht_t *mjht);
-int quicktime_stsd_table_init(quicktime_stsd_table_t *table);
-int quicktime_stsd_init(quicktime_stsd_t *stsd);
-int quicktime_stsd_init_table(quicktime_stsd_t *stsd);
-int quicktime_stsd_init_video(quicktime_t *file, quicktime_stsd_t *stsd, int frame_w, int frame_h, float frame_rate, char *compression);
-int quicktime_stsd_init_audio(quicktime_t *file, quicktime_stsd_t *stsd, int channels, int sample_rate, int bits, char *compressor);
-int quicktime_stts_init(quicktime_stts_t *stts);
-int quicktime_stts_init_table(quicktime_stts_t *stts);
-int quicktime_stts_init_video(quicktime_t *file, quicktime_stts_t *stts, int time_scale, float frame_rate);
-int quicktime_stts_init_audio(quicktime_t *file, quicktime_stts_t *stts, int time_scale, int sample_duration);
-int quicktime_stts_init_hint(quicktime_t *file, quicktime_stts_t *stts, int sample_duration);
-int quicktime_stss_init(quicktime_stss_t *stss);
-int quicktime_stss_init_common(quicktime_t *file, quicktime_stss_t *stss);
-int quicktime_stsc_init(quicktime_stsc_t *stsc);
-int quicktime_stsc_init_video(quicktime_t *file, quicktime_stsc_t *stsc);
-int quicktime_stsc_init_audio(quicktime_t *file, quicktime_stsc_t *stsc);
-int quicktime_stsz_init(quicktime_stsz_t *stsz);
-int quicktime_stsz_init_video(quicktime_t *file, quicktime_stsz_t *stsz);
-int quicktime_stsz_init_audio(quicktime_t *file, quicktime_stsz_t *stsz, int sample_size);
-int quicktime_stco_init(quicktime_stco_t *stco);
-int quicktime_stco_init_common(quicktime_t *file, quicktime_stco_t *stco);
-int quicktime_stbl_init(quicktime_stbl_t *tkhd);
-int quicktime_stbl_init_video(quicktime_t *file, quicktime_stbl_t *stbl, int frame_w, int frame_h, int time_scale, float frame_rate, char *compressor);
-int quicktime_stbl_init_audio(quicktime_t *file, quicktime_stbl_t *stbl, int channels, int sample_rate, int bits, int sample_size, int time_scale, int sample_duration, char *compressor);
-int quicktime_stbl_init_hint(quicktime_t *file, quicktime_stbl_t *stbl, quicktime_trak_t *refTrak, int maxPktSize, int timeScale, int sampleDuration);
-int quicktime_vmhd_init(quicktime_vmhd_t *vmhd);
-int quicktime_vmhd_init_video(quicktime_t *file, quicktime_vmhd_t *vmhd, int frame_w, int frame_h, float frame_rate);
-int quicktime_smhd_init(quicktime_smhd_t *smhd);
-int quicktime_dref_table_init(quicktime_dref_table_t *table);
-int quicktime_dref_init_all(quicktime_dref_t *dref);
-int quicktime_dref_init(quicktime_dref_t *dref);
-int quicktime_dinf_init_all(quicktime_dinf_t *dinf);
-int quicktime_dinf_init(quicktime_dinf_t *dinf);
-int quicktime_minf_init(quicktime_minf_t *minf);
-int quicktime_minf_init_video(quicktime_t *file, quicktime_minf_t *minf, int frame_w, int frame_h, int time_scale, float frame_rate, char *compressor);
-int quicktime_minf_init_audio(quicktime_t *file, quicktime_minf_t *minf, int channels, int sample_rate, int bits, int sample_size, int time_scale, int sample_duration, char *compressor);
-int quicktime_minf_init_hint(quicktime_t *file, quicktime_minf_t *minf, quicktime_trak_t *refTrak, int maxPktSize, int timeScale, int sampleDuration);
-int quicktime_mdhd_init(quicktime_mdhd_t *mdhd);
-int quicktime_mdhd_init_video(quicktime_t *file, quicktime_mdhd_t *mdhd, int time_scale);
-int quicktime_mdhd_init_audio(quicktime_t *file, quicktime_mdhd_t *mdhd, int time_scale);
-int quicktime_mdia_init(quicktime_mdia_t *mdia);
-int quicktime_mdia_init_video(quicktime_t *file, quicktime_mdia_t *mdia, int frame_w, int frame_h, float frame_rate, int time_scale, char *compressor);
-int quicktime_mdia_init_audio(quicktime_t *file, quicktime_mdia_t *mdia, int channels, int sample_rate, int bits, int sample_size, int time_scale, int sample_duration, char *compressor);
-int quicktime_mdia_init_hint(quicktime_t *file, quicktime_mdia_t *mdia, quicktime_trak_t *refTrak, int maxPktSize, int time_scale, int sampleDuration);
+void quicktime_mjqt_init(quicktime_mjqt_t *mjqt);
+void quicktime_mjht_init(quicktime_mjht_t *mjht);
+void quicktime_stsd_table_init(quicktime_stsd_table_t *table);
+void quicktime_stsd_init(quicktime_stsd_t *stsd);
+void quicktime_stsd_init_table(quicktime_stsd_t *stsd);
+void quicktime_stsd_init_video(quicktime_t *file, quicktime_stsd_t *stsd, int frame_w, int frame_h, float frame_rate, char *compression);
+void quicktime_stsd_init_audio(quicktime_t *file, quicktime_stsd_t *stsd, int channels, int sample_rate, int bits, char *compressor);
+void quicktime_stts_init(quicktime_stts_t *stts);
+void quicktime_stts_init_table(quicktime_stts_t *stts);
+void quicktime_stts_init_video(quicktime_t *file, quicktime_stts_t *stts, int time_scale, float frame_rate);
+void quicktime_stts_init_audio(quicktime_t *file, quicktime_stts_t *stts, int time_scale, int sample_duration);
+void quicktime_stts_init_hint(quicktime_t *file, quicktime_stts_t *stts, int sample_duration);
+void quicktime_stss_init(quicktime_stss_t *stss);
+void quicktime_stss_init_common(quicktime_t *file, quicktime_stss_t *stss);
+void quicktime_stsc_init(quicktime_stsc_t *stsc);
+void quicktime_stsc_init_video(quicktime_t *file, quicktime_stsc_t *stsc);
+void quicktime_stsc_init_audio(quicktime_t *file, quicktime_stsc_t *stsc);
+void quicktime_stsz_init(quicktime_stsz_t *stsz);
+void quicktime_stsz_init_video(quicktime_t *file, quicktime_stsz_t *stsz);
+void quicktime_stsz_init_audio(quicktime_t *file, quicktime_stsz_t *stsz, int sample_size);
+void quicktime_stco_init(quicktime_stco_t *stco);
+void quicktime_stco_init_common(quicktime_t *file, quicktime_stco_t *stco);
+void quicktime_stbl_init(quicktime_stbl_t *tkhd);
+void quicktime_stbl_init_video(quicktime_t *file, quicktime_stbl_t *stbl, int frame_w, int frame_h, int time_scale, float frame_rate, char *compressor);
+void quicktime_stbl_init_audio(quicktime_t *file, quicktime_stbl_t *stbl, int channels, int sample_rate, int bits, int sample_size, int time_scale, int sample_duration, char *compressor);
+void quicktime_stbl_init_hint(quicktime_t *file, quicktime_stbl_t *stbl, quicktime_trak_t *refTrak, int maxPktSize, int timeScale, int sampleDuration);
+void quicktime_vmhd_init(quicktime_vmhd_t *vmhd);
+void quicktime_vmhd_init_video(quicktime_t *file, quicktime_vmhd_t *vmhd, int frame_w, int frame_h, float frame_rate);
+void quicktime_smhd_init(quicktime_smhd_t *smhd);
+void quicktime_dref_table_init(quicktime_dref_table_t *table);
+void quicktime_dref_init_all(quicktime_dref_t *dref);
+void quicktime_dref_init(quicktime_dref_t *dref);
+void quicktime_dinf_init_all(quicktime_dinf_t *dinf);
+void quicktime_dinf_init(quicktime_dinf_t *dinf);
+void quicktime_minf_init(quicktime_minf_t *minf);
+void quicktime_minf_init_video(quicktime_t *file, quicktime_minf_t *minf, int frame_w, int frame_h, int time_scale, float frame_rate, char *compressor);
+void quicktime_minf_init_audio(quicktime_t *file, quicktime_minf_t *minf, int channels, int sample_rate, int bits, int sample_size, int time_scale, int sample_duration, char *compressor);
+void quicktime_minf_init_hint(quicktime_t *file, quicktime_minf_t *minf, quicktime_trak_t *refTrak, int maxPktSize, int timeScale, int sampleDuration);
+void quicktime_mdhd_init(quicktime_mdhd_t *mdhd);
+void quicktime_mdhd_init_video(quicktime_t *file, quicktime_mdhd_t *mdhd, int time_scale);
+void quicktime_mdhd_init_audio(quicktime_t *file, quicktime_mdhd_t *mdhd, int time_scale);
+void quicktime_mdia_init(quicktime_mdia_t *mdia);
+void quicktime_mdia_init_video(quicktime_t *file, quicktime_mdia_t *mdia, int frame_w, int frame_h, float frame_rate, int time_scale, char *compressor);
+void quicktime_mdia_init_audio(quicktime_t *file, quicktime_mdia_t *mdia, int channels, int sample_rate, int bits, int sample_size, int time_scale, int sample_duration, char *compressor);
+void quicktime_mdia_init_hint(quicktime_t *file, quicktime_mdia_t *mdia, quicktime_trak_t *refTrak, int maxPktSize, int time_scale, int sampleDuration);
 int quicktime_trak_init(quicktime_trak_t *trak);
 int quicktime_trak_init_video(quicktime_t *file, quicktime_trak_t *trak, int frame_w, int frame_h, float frame_rate, int time_scale, char *compressor);
 int quicktime_trak_init_audio(quicktime_t *file, quicktime_trak_t *trak, int channels, int sample_rate, int bits, int sample_size, int time_scale, int sample_duration, char *compressor);
 int quicktime_trak_init_hint(quicktime_t *file, quicktime_trak_t *trak, quicktime_trak_t *refTrak, int maxPktSize, int time_scale, int sample_duration);
-int quicktime_tref_init(quicktime_tref_t *tref);
-int quicktime_tref_init_hint(quicktime_tref_t *tref, quicktime_trak_t *refTrak);
+void quicktime_tref_init(quicktime_tref_t *tref);
+void quicktime_tref_init_hint(quicktime_tref_t *tref, quicktime_trak_t *refTrak);
 int quicktime_udta_init(quicktime_udta_t *udta);
 int quicktime_mvhd_init(quicktime_mvhd_t *mvhd);
 int quicktime_moov_init(quicktime_moov_t *moov);
-int quicktime_mdat_init(quicktime_mdat_t *mdat);
+void quicktime_mdat_init(quicktime_mdat_t *mdat);
 int quicktime_init(quicktime_t *file);
-int quicktime_hdlr_init(quicktime_hdlr_t *hdlr);
-int quicktime_hdlr_init_video(quicktime_hdlr_t *hdlr);
-int quicktime_hdlr_init_audio(quicktime_hdlr_t *hdlr);
-int quicktime_hdlr_init_data(quicktime_hdlr_t *hdlr);
+void quicktime_hdlr_init(quicktime_hdlr_t *hdlr);
+void quicktime_hdlr_init_video(quicktime_hdlr_t *hdlr);
+void quicktime_hdlr_init_audio(quicktime_hdlr_t *hdlr);
+void quicktime_hdlr_init_data(quicktime_hdlr_t *hdlr);
 
 /* utilities for reading data types */
 int quicktime_read_data(quicktime_t *file, char *data, int size);
 int quicktime_write_data(quicktime_t *file, char *data, int size);
-int quicktime_read_pascal(quicktime_t *file, char *data);
-int quicktime_write_pascal(quicktime_t *file, char *data);
+void quicktime_read_pascal(quicktime_t *file, char *data);
+void quicktime_write_pascal(quicktime_t *file, char *data);
 float quicktime_read_fixed32(quicktime_t *file);
 int quicktime_write_fixed32(quicktime_t *file, float number);
 float quicktime_read_fixed16(quicktime_t *file);
@@ -98,9 +98,9 @@ int quicktime_read_int16(quicktime_t *fi
 int quicktime_write_int16(quicktime_t *file, int number);
 int quicktime_read_char(quicktime_t *file);
 int quicktime_write_char(quicktime_t *file, char x);
-int quicktime_read_char32(quicktime_t *file, char *string);
+void quicktime_read_char32(quicktime_t *file, char *string);
 int quicktime_write_char32(quicktime_t *file, char *string);
-int quicktime_copy_char32(char *output, char *input);
+void quicktime_copy_char32(char *output, char *input);
 long quicktime_position(quicktime_t *file);
 int quicktime_read_mp4_descr_length(quicktime_t *file);
 int quicktime_write_mp4_descr_length(quicktime_t *file, int length, bool compact);
@@ -157,4 +157,296 @@ int quicktime_update_tables(quicktime_t 
 							long renderingOffset);
 unsigned long quicktime_current_time();
 
+int quicktime_atom_is(quicktime_atom_t *atom, char *type);
+int quicktime_atom_read_header(quicktime_t *file, quicktime_atom_t *atom);
+int quicktime_atom_skip(quicktime_t *file, quicktime_atom_t *atom);
+int quicktime_chunk_of_sample(long *chunk_sample, long *chunk, quicktime_trak_t *trak, long sample);
+int quicktime_ctab_delete(quicktime_ctab_t *ctab);
+int quicktime_delete_audio_map(quicktime_audio_map_t *atrack);
+int quicktime_delete_trak(quicktime_moov_t *moov, quicktime_trak_t *trak);
+int quicktime_delete_video_map(quicktime_video_map_t *vtrack);
+int quicktime_dump_hint_tlv(u_char* hintBuf);
+int quicktime_esds_delete(quicktime_esds_t *esds);
+int quicktime_esds_get_decoder_config(quicktime_esds_t* esds, u_char** ppBuf, int* pBufSize);
+int quicktime_esds_init(quicktime_esds_t *esds);
+int quicktime_esds_set_decoder_config(quicktime_esds_t* esds, u_char* pBuf, int bufSize);
+int quicktime_get_packet_size(u_char* hintBuf);
+int quicktime_init_audio_map(quicktime_audio_map_t *atrack, quicktime_trak_t *trak);
+int quicktime_init_video_map(quicktime_video_map_t *vtrack, quicktime_trak_t *trak);
+int quicktime_iods_delete(quicktime_iods_t *iods);
+int quicktime_iods_init(quicktime_iods_t *iods);
+int quicktime_match_32(char *input, char *output);
+int quicktime_moov_delete(quicktime_moov_t *moov);
+int quicktime_mvhd_delete(quicktime_mvhd_t *mvhd);
+int quicktime_read_ctab(quicktime_t *file, quicktime_ctab_t *ctab);
+int quicktime_read_esds(quicktime_t *file, quicktime_esds_t *esds);
+int quicktime_read_mdia(quicktime_t *file, quicktime_mdia_t *mdia, quicktime_atom_t *trak_atom);
+int quicktime_read_minf(quicktime_t *file, quicktime_minf_t *minf, quicktime_atom_t *parent_atom);
+int quicktime_read_moov(quicktime_t *file, quicktime_moov_t *moov, quicktime_atom_t *parent_atom);
+int quicktime_read_stbl(quicktime_t *file, quicktime_minf_t *minf, quicktime_stbl_t *stbl, quicktime_atom_t *parent_atom);
+int quicktime_read_trak(quicktime_t *file, quicktime_trak_t *trak, quicktime_atom_t *trak_atom);
+int quicktime_read_udta(quicktime_t *file, quicktime_udta_t *udta, quicktime_atom_t *udta_atom);
+int quicktime_read_udta_string(quicktime_t *file, char **string, int *size);
+int quicktime_set_position(quicktime_t *file, long position);
+int quicktime_set_udta_string(char **string, int *size, char *new_string);
+int quicktime_shift_offsets(quicktime_moov_t *moov, long offset);
+int quicktime_tkhd_delete(quicktime_tkhd_t *tkhd);
+int quicktime_trak_dump(quicktime_trak_t *trak);
+int quicktime_trak_duration(quicktime_trak_t *trak, long *duration, long *timescale);
+int quicktime_trak_fix_counts(quicktime_t *file, quicktime_trak_t *trak);
+int quicktime_trak_shift_offsets(quicktime_trak_t *trak, long offset);
+int quicktime_udta_delete(quicktime_udta_t *udta);
+int quicktime_update_stsc(quicktime_stsc_t *stsc, long chunk, long samples);
+int quicktime_write_trak(quicktime_t *file, quicktime_trak_t *trak, long moov_time_scale);
+int quicktime_write_udta_string(quicktime_t *file, char *string, int size);
+long quicktime_track_end(quicktime_trak_t *trak);
+void quicktime_atom_write_footer(quicktime_t *file, quicktime_atom_t *atom);
+void quicktime_atom_write_header(quicktime_t *file, quicktime_atom_t *atom, char *text);
+void quicktime_ctab_dump(quicktime_ctab_t *ctab);
+void quicktime_ctts_delete(quicktime_ctts_t *ctts);
+void quicktime_ctts_dump(quicktime_ctts_t *ctts);
+void quicktime_ctts_init(quicktime_ctts_t *ctts);
+void quicktime_ctts_init_common(quicktime_t *file, quicktime_ctts_t *ctts);
+void quicktime_dimm_delete(quicktime_dimm_t *dimm);
+void quicktime_dimm_dump(quicktime_dimm_t *dimm);
+void quicktime_dimm_init(quicktime_dimm_t *dimm);
+void quicktime_dinf_delete(quicktime_dinf_t *dinf);
+void quicktime_dinf_dump(quicktime_dinf_t *dinf);
+void quicktime_dmax_delete(quicktime_dmax_t *dmax);
+void quicktime_dmax_dump(quicktime_dmax_t *dmax);
+void quicktime_dmax_init(quicktime_dmax_t *dmax);
+void quicktime_dmed_delete(quicktime_dmed_t *dmed);
+void quicktime_dmed_dump(quicktime_dmed_t *dmed);
+void quicktime_dmed_init(quicktime_dmed_t *dmed);
+void quicktime_dref_delete(quicktime_dref_t *dref);
+void quicktime_dref_dump(quicktime_dref_t *dref);
+void quicktime_drep_delete(quicktime_drep_t *drep);
+void quicktime_drep_dump(quicktime_drep_t *drep);
+void quicktime_drep_init(quicktime_drep_t *drep);
+void quicktime_edts_delete(quicktime_edts_t *edts);
+void quicktime_edts_dump(quicktime_edts_t *edts);
+void quicktime_elst_delete(quicktime_elst_t *elst);
+void quicktime_elst_dump(quicktime_elst_t *elst);
+void quicktime_esds_dump(quicktime_esds_t *esds);
+void quicktime_gmhd_delete(quicktime_gmhd_t *gmhd);
+void quicktime_gmhd_dump(quicktime_gmhd_t *gmhd);
+void quicktime_gmhd_init(quicktime_gmhd_t *gmhd);
+void quicktime_gmin_delete(quicktime_gmin_t *gmin);
+void quicktime_gmin_dump(quicktime_gmin_t *gmin);
+void quicktime_gmin_init(quicktime_gmin_t *gmin);
+void quicktime_hdlr_delete(quicktime_hdlr_t *hdlr);
+void quicktime_hdlr_dump(quicktime_hdlr_t *hdlr);
+void quicktime_hdlr_init_hint(quicktime_hdlr_t *hdlr);
+void quicktime_hinf_delete(quicktime_hinf_t *hinf);
+void quicktime_hinf_dump(quicktime_hinf_t *hinf);
+void quicktime_hinf_init(quicktime_hinf_t *hinf);
+void quicktime_hint_delete(quicktime_hint_t *hint);
+void quicktime_hint_dump(quicktime_hint_t *hint);
+void quicktime_hint_hnti_delete(quicktime_hint_hnti_t *hnti);
+void quicktime_hint_hnti_dump(quicktime_hint_hnti_t *hnti);
+void quicktime_hint_hnti_init(quicktime_hint_hnti_t *hnti);
+void quicktime_hint_init(quicktime_hint_t *hint);
+void quicktime_hint_set(quicktime_hint_t *hint, quicktime_trak_t *refTrak);
+void quicktime_hint_udta_delete(quicktime_hint_udta_t *hint_udta);
+void quicktime_hint_udta_dump(quicktime_hint_udta_t *hint_udta);
+void quicktime_hint_udta_init(quicktime_hint_udta_t *hint_udta);
+void quicktime_hmhd_delete(quicktime_hmhd_t *hmhd);
+void quicktime_hmhd_dump(quicktime_hmhd_t *hmhd);
+void quicktime_hmhd_init(quicktime_hmhd_t *hmhd);
+void quicktime_hnti_delete(quicktime_hnti_t *hnti);
+void quicktime_hnti_dump(quicktime_hnti_t *hnti);
+void quicktime_hnti_init(quicktime_hnti_t *hnti);
+void quicktime_iods_dump(quicktime_iods_t *iods);
+void quicktime_iods_set_audio_profile(quicktime_iods_t* iods, int id);
+void quicktime_iods_set_video_profile(quicktime_iods_t* iods, int id);
+void quicktime_matrix_dump(quicktime_matrix_t *matrix);
+void quicktime_maxr_delete(quicktime_maxr_t *maxr);
+void quicktime_maxr_delete(quicktime_maxr_t *maxr);
+void quicktime_maxr_dump(quicktime_maxr_t *maxr);
+void quicktime_maxr_init(quicktime_maxr_t *maxr);
+void quicktime_mdat_delete(quicktime_mdat_t *mdat);
+void quicktime_mdhd_delete(quicktime_mdhd_t *mdhd);
+void quicktime_mdhd_dump(quicktime_mdhd_t *mdhd);
+void quicktime_mdhd_init_hint(quicktime_t *file, quicktime_mdhd_t *mdhd, quicktime_trak_t *refTrak, int time_scale);
+void quicktime_mdia_delete(quicktime_mdia_t *mdia);
+void quicktime_mdia_dump(quicktime_mdia_t *mdia);
+void quicktime_minf_delete(quicktime_minf_t *minf);
+void quicktime_minf_dump(quicktime_minf_t *minf);
+void quicktime_mjht_delete(quicktime_mjht_t *mjht);
+void quicktime_mjht_dump(quicktime_mjht_t *mjht);
+void quicktime_mjqt_delete(quicktime_mjqt_t *mjqt);
+void quicktime_mjqt_dump(quicktime_mjqt_t *mjqt);
+void quicktime_moov_dump(quicktime_moov_t *moov);
+void quicktime_mvhd_dump(quicktime_mvhd_t *mvhd);
+void quicktime_nump_delete(quicktime_nump_t *nump);
+void quicktime_nump_dump(quicktime_nump_t *nump);
+void quicktime_nump_init(quicktime_nump_t *nump);
+void quicktime_payt_delete(quicktime_payt_t *payt);
+void quicktime_payt_dump(quicktime_payt_t *payt);
+void quicktime_payt_init(quicktime_payt_t *payt);
+void quicktime_pmax_delete(quicktime_pmax_t *pmax);
+void quicktime_pmax_dump(quicktime_pmax_t *pmax);
+void quicktime_pmax_init(quicktime_pmax_t *pmax);
+void quicktime_print_chars(char *desc, char *input, int len);
+void quicktime_read_ctts(quicktime_t *file, quicktime_ctts_t *ctts);
+void quicktime_read_dimm(quicktime_t *file, quicktime_dimm_t *dimm);
+void quicktime_read_dinf(quicktime_t *file, quicktime_dinf_t *dinf, quicktime_atom_t *dinf_atom);
+void quicktime_read_dmax(quicktime_t *file, quicktime_dmax_t *dmax);
+void quicktime_read_dmed(quicktime_t *file, quicktime_dmed_t *dmed);
+void quicktime_read_dref(quicktime_t *file, quicktime_dref_t *dref);
+void quicktime_read_drep(quicktime_t *file, quicktime_drep_t *drep);
+void quicktime_read_edts(quicktime_t *file, quicktime_edts_t *edts, quicktime_atom_t *edts_atom);
+void quicktime_read_elst(quicktime_t *file, quicktime_elst_t *elst);
+void quicktime_read_gmhd(quicktime_t *file, quicktime_gmhd_t *gmhd, quicktime_atom_t *parent_atom);
+void quicktime_read_gmin(quicktime_t *file, quicktime_gmin_t *gmin);
+void quicktime_read_hdlr(quicktime_t *file, quicktime_hdlr_t *hdlr);
+void quicktime_read_hinf(quicktime_t *file, quicktime_hinf_t *hinf, quicktime_atom_t *parent_atom);
+void quicktime_read_hint(quicktime_t *file, quicktime_hint_t *hint, quicktime_atom_t *parent_atom);
+void quicktime_read_hint_hnti(quicktime_t *file, quicktime_hint_hnti_t *hnti, quicktime_atom_t *parent_atom);
+void quicktime_read_hint_udta(quicktime_t *file, quicktime_hint_udta_t *hint_udta, quicktime_atom_t *parent_atom);
+void quicktime_read_hmhd(quicktime_t *file, quicktime_hmhd_t *hmhd);
+void quicktime_read_hnti(quicktime_t *file, quicktime_hnti_t *hnti, quicktime_atom_t *parent_atom);
+void quicktime_read_iods(quicktime_t *file, quicktime_iods_t *iods);
+void quicktime_read_matrix(quicktime_t *file, quicktime_matrix_t *matrix);
+void quicktime_read_maxr(quicktime_t *file, quicktime_maxr_t *maxr);
+void quicktime_read_mdat(quicktime_t *file, quicktime_mdat_t *mdat, quicktime_atom_t *parent_atom);
+void quicktime_read_mdhd(quicktime_t *file, quicktime_mdhd_t *mdhd);
+void quicktime_read_mvhd(quicktime_t *file, quicktime_mvhd_t *mvhd);
+void quicktime_read_nump(quicktime_t *file, quicktime_nump_t *nump);
+void quicktime_read_payt(quicktime_t *file, quicktime_payt_t *payt);
+void quicktime_read_pmax(quicktime_t *file, quicktime_pmax_t *pmax);
+void quicktime_read_rtp(quicktime_t *file, quicktime_rtp_t *rtp, quicktime_atom_t* rtp_atom);
+void quicktime_read_sdp(quicktime_t *file, quicktime_sdp_t *sdp, quicktime_atom_t* sdp_atom);
+void quicktime_read_smhd(quicktime_t *file, quicktime_smhd_t *smhd);
+void quicktime_read_stco(quicktime_t *file, quicktime_stco_t *stco);
+void quicktime_read_stsc(quicktime_t *file, quicktime_stsc_t *stsc);
+void quicktime_read_stsd(quicktime_t *file, quicktime_minf_t *minf, quicktime_stsd_t *stsd);
+void quicktime_read_stsd_audio(quicktime_t *file, quicktime_stsd_table_t *table, quicktime_atom_t *parent_atom);
+void quicktime_read_stsd_hint(quicktime_t *file, quicktime_stsd_table_t *table, quicktime_atom_t *parent_atom);
+void quicktime_read_stsd_table(quicktime_t *file, quicktime_minf_t *minf, quicktime_stsd_table_t *table);
+void quicktime_read_stsd_video(quicktime_t *file, quicktime_stsd_table_t *table, quicktime_atom_t *parent_atom);
+void quicktime_read_stss(quicktime_t *file, quicktime_stss_t *stss);
+void quicktime_read_stsz(quicktime_t *file, quicktime_stsz_t *stsz);
+void quicktime_read_stts(quicktime_t *file, quicktime_stts_t *stts);
+void quicktime_read_tims(quicktime_t *file, quicktime_tims_t *tims);
+void quicktime_read_tkhd(quicktime_t *file, quicktime_tkhd_t *tkhd);
+void quicktime_read_tmax(quicktime_t *file, quicktime_tmax_t *tmax);
+void quicktime_read_tmin(quicktime_t *file, quicktime_tmin_t *tmin);
+void quicktime_read_tpyl(quicktime_t *file, quicktime_tpyl_t *tpyl);
+void quicktime_read_tref(quicktime_t *file, quicktime_tref_t *tref, quicktime_atom_t *parent_atom);
+void quicktime_read_trpy(quicktime_t *file, quicktime_trpy_t *trpy);
+void quicktime_read_vmhd(quicktime_t *file, quicktime_vmhd_t *vmhd);
+void quicktime_rtp_delete(quicktime_rtp_t *rtp);
+void quicktime_rtp_dump(quicktime_rtp_t *rtp);
+void quicktime_rtp_init(quicktime_rtp_t *rtp);
+void quicktime_rtp_set(quicktime_rtp_t *rtp, char *string);
+void quicktime_sdp_append(quicktime_sdp_t *sdp, char *appendString);
+void quicktime_sdp_delete(quicktime_sdp_t *sdp);
+void quicktime_sdp_dump(quicktime_sdp_t *sdp);
+void quicktime_sdp_init(quicktime_sdp_t *sdp);
+void quicktime_sdp_set(quicktime_sdp_t *sdp, char *string);
+void quicktime_smhd_delete(quicktime_smhd_t *smhd);
+void quicktime_smhd_dump(quicktime_smhd_t *smhd);
+void quicktime_stbl_delete(quicktime_stbl_t *stbl);
+void quicktime_stbl_dump(void *minf_ptr, quicktime_stbl_t *stbl);
+void quicktime_stco_delete(quicktime_stco_t *stco);
+void quicktime_stco_dump(quicktime_stco_t *stco);
+void quicktime_stsc_delete(quicktime_stsc_t *stsc);
+void quicktime_stsc_dump(quicktime_stsc_t *stsc);
+void quicktime_stsd_audio_dump(quicktime_stsd_table_t *table);
+void quicktime_stsd_delete(quicktime_stsd_t *stsd);
+void quicktime_stsd_dump(void *minf_ptr, quicktime_stsd_t *stsd);
+void quicktime_stsd_hint_dump(quicktime_stsd_table_t *table);
+void quicktime_stsd_init_hint(quicktime_t *file, quicktime_stsd_t *stsd, int maxPktSize, int timeScale);
+void quicktime_stsd_table_delete(quicktime_stsd_table_t *table);
+void quicktime_stsd_table_dump(void *minf_ptr, quicktime_stsd_table_t *table);
+void quicktime_stsd_video_dump(quicktime_stsd_table_t *table);
+void quicktime_stss_delete(quicktime_stss_t *stss);
+void quicktime_stss_dump(quicktime_stss_t *stss);
+void quicktime_stsz_delete(quicktime_stsz_t *stsz);
+void quicktime_stsz_dump(quicktime_stsz_t *stsz);
+void quicktime_stts_delete(quicktime_stts_t *stts);
+void quicktime_stts_dump(quicktime_stts_t *stts);
+void quicktime_tims_init(quicktime_tims_t *tims);
+void quicktime_tkhd_dump(quicktime_tkhd_t *tkhd);
+void quicktime_tkhd_init_hint(quicktime_t *file, quicktime_tkhd_t *tkhd);
+void quicktime_tmax_delete(quicktime_tmax_t *tmax);
+void quicktime_tmax_dump(quicktime_tmax_t *tmax);
+void quicktime_tmax_init(quicktime_tmax_t *tmax);
+void quicktime_tmin_delete(quicktime_tmin_t *tmin);
+void quicktime_tmin_dump(quicktime_tmin_t *tmin);
+void quicktime_tmin_init(quicktime_tmin_t *tmin);
+void quicktime_tpyl_delete(quicktime_tpyl_t *tpyl);
+void quicktime_tpyl_dump(quicktime_tpyl_t *tpyl);
+void quicktime_tpyl_init(quicktime_tpyl_t *tpyl);
+void quicktime_tref_dump(quicktime_tref_t *tref);
+void quicktime_trpy_delete(quicktime_trpy_t *trpy);
+void quicktime_trpy_dump(quicktime_trpy_t *trpy);
+void quicktime_trpy_init(quicktime_trpy_t *trpy);
+void quicktime_udta_dump(quicktime_udta_t *udta);
+void quicktime_update_ctts(quicktime_ctts_t *ctts, long sample_offset);
+void quicktime_update_durations(quicktime_moov_t *moov);
+void quicktime_update_stco(quicktime_stco_t *stco, long chunk, long offset);
+void quicktime_update_stss(quicktime_stss_t *stss, long sample);
+void quicktime_update_stsz(quicktime_stsz_t *stsz, long sample, long sample_size);
+void quicktime_update_stts(quicktime_stts_t *stts, long sample_duration);
+void quicktime_vmhd_delete(quicktime_vmhd_t *vmhd);
+void quicktime_vmhd_dump(quicktime_vmhd_t *vmhd);
+void quicktime_write_ctts(quicktime_t *file, quicktime_ctts_t *ctts);
+void quicktime_write_dimm(quicktime_t *file, quicktime_dimm_t *dimm);
+void quicktime_write_dinf(quicktime_t *file, quicktime_dinf_t *dinf);
+void quicktime_write_dmax(quicktime_t *file, quicktime_dmax_t *dmax);
+void quicktime_write_dmed(quicktime_t *file, quicktime_dmed_t *dmed);
+void quicktime_write_dref(quicktime_t *file, quicktime_dref_t *dref);
+void quicktime_write_drep(quicktime_t *file, quicktime_drep_t *drep);
+void quicktime_write_edts(quicktime_t *file, quicktime_edts_t *edts, long duration);
+void quicktime_write_elst(quicktime_t *file, quicktime_elst_t *elst, long duration);
+void quicktime_write_esds_audio(quicktime_t *file, quicktime_esds_t *esds, int esid);
+void quicktime_write_esds_video(quicktime_t *file, quicktime_esds_t *esds, int esid);
+void quicktime_write_gmhd(quicktime_t *file, quicktime_gmhd_t *gmhd);
+void quicktime_write_gmin(quicktime_t *file, quicktime_gmin_t *gmin);
+void quicktime_write_hdlr(quicktime_t *file, quicktime_hdlr_t *hdlr);
+void quicktime_write_hinf(quicktime_t *file, quicktime_hinf_t *hinf);
+void quicktime_write_hint(quicktime_t *file, quicktime_hint_t *hint);
+void quicktime_write_hint_hnti(quicktime_t *file, quicktime_hint_hnti_t *hnti);
+void quicktime_write_hint_udta(quicktime_t *file, quicktime_hint_udta_t *hint_udta);
+void quicktime_write_hmhd(quicktime_t *file, quicktime_hmhd_t *hmhd);
+void quicktime_write_hnti(quicktime_t *file, quicktime_hnti_t *hnti);
+void quicktime_write_iods(quicktime_t *file, quicktime_iods_t *iods);
+void quicktime_write_matrix(quicktime_t *file, quicktime_matrix_t *matrix);
+void quicktime_write_maxr(quicktime_t *file, quicktime_maxr_t *maxr);
+void quicktime_write_mdat(quicktime_t *file, quicktime_mdat_t *mdat);
+void quicktime_write_mdhd(quicktime_t *file, quicktime_mdhd_t *mdhd);
+void quicktime_write_mdia(quicktime_t *file, quicktime_mdia_t *mdia);
+void quicktime_write_minf(quicktime_t *file, quicktime_minf_t *minf);
+void quicktime_write_moov(quicktime_t *file, quicktime_moov_t *moov);
+void quicktime_write_moov(quicktime_t *file, quicktime_moov_t *moov);
+void quicktime_write_mvhd(quicktime_t *file, quicktime_mvhd_t *mvhd);
+void quicktime_write_nump(quicktime_t *file, quicktime_nump_t *nump);
+void quicktime_write_payt(quicktime_t *file, quicktime_payt_t *payt);
+void quicktime_write_pmax(quicktime_t *file, quicktime_pmax_t *pmax);
+void quicktime_write_rtp(quicktime_t *file, quicktime_rtp_t *rtp);
+void quicktime_write_sdp(quicktime_t *file, quicktime_sdp_t *sdp);
+void quicktime_write_smhd(quicktime_t *file, quicktime_smhd_t *smhd);
+void quicktime_write_stbl(quicktime_t *file, quicktime_minf_t *minf, quicktime_stbl_t *stbl);
+void quicktime_write_stco(quicktime_t *file, quicktime_stco_t *stco);
+void quicktime_write_stsc(quicktime_t *file, quicktime_stsc_t *stsc);
+void quicktime_write_stsd(quicktime_t *file, quicktime_minf_t *minf, quicktime_stsd_t *stsd);
+void quicktime_write_stsd_audio(quicktime_t *file, quicktime_stsd_table_t *table);
+void quicktime_write_stsd_hint(quicktime_t *file, quicktime_stsd_table_t *table);
+void quicktime_write_stsd_table(quicktime_t *file, quicktime_minf_t *minf, quicktime_stsd_table_t *table);
+void quicktime_write_stsd_video(quicktime_t *file, quicktime_stsd_table_t *table);
+void quicktime_write_stss(quicktime_t *file, quicktime_stss_t *stss);
+void quicktime_write_stsz(quicktime_t *file, quicktime_stsz_t *stsz);
+void quicktime_write_stts(quicktime_t *file, quicktime_stts_t *stts);
+void quicktime_write_tims(quicktime_t *file, quicktime_tims_t *tims);
+void quicktime_write_tkhd(quicktime_t *file, quicktime_tkhd_t *tkhd);
+void quicktime_write_tmax(quicktime_t *file, quicktime_tmax_t *tmax);
+void quicktime_write_tmin(quicktime_t *file, quicktime_tmin_t *tmin);
+void quicktime_write_tpyl(quicktime_t *file, quicktime_tpyl_t *tpyl);
+void quicktime_write_tref(quicktime_t *file, quicktime_tref_t *tref);
+void quicktime_write_trpy(quicktime_t *file, quicktime_trpy_t *trpy);
+void quicktime_write_udta(quicktime_t *file, quicktime_udta_t *udta);
+void quicktime_write_vmhd(quicktime_t *file, quicktime_vmhd_t *vmhd);
+
 #endif
