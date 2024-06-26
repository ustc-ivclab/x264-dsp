/*****************************************************************************
 * pixel.h: pixel metrics
 *****************************************************************************/

#ifndef X264_PIXEL_H
#define X264_PIXEL_H

// SSD assumes all args aligned
// other cmp functions assume first arg aligned
typedef int (*x264_pixel_cmp_t)(pixel *, intptr_t, pixel *, intptr_t);
typedef void (*x264_pixel_cmp_x3_t)(pixel *, pixel *, pixel *, pixel *, intptr_t, int[3]);
typedef void (*x264_pixel_cmp_x4_t)(pixel *, pixel *, pixel *, pixel *, pixel *, intptr_t, int[4]);

enum {
	PIXEL_16x16 = 0,
	PIXEL_16x8 = 1,
	PIXEL_8x16 = 2,
	PIXEL_8x8 = 3,
	PIXEL_8x4 = 4,
	PIXEL_4x8 = 5,
	PIXEL_4x4 = 6,

	/* Subsampled chroma only */
	PIXEL_4x16 = 7, /* 4:2:2 */
	PIXEL_4x2 = 8,
	PIXEL_2x8 = 9, /* 4:2:2 */
	PIXEL_2x4 = 10,
	PIXEL_2x2 = 11,
};

static const struct {
	uint8_t w, h;
} x264_pixel_size[12] =
    {
	{16, 16},
	{16, 8},
	{8, 16},
	{8, 8},
	{8, 4},
	{4, 8},
	{4, 4},
	{4, 16},
	{4, 2},
	{2, 8},
	{2, 4},
	{2, 2},
};

static const uint8_t x264_size2pixel[5][5] =
    {
	{
	    0,
	},
	{0, PIXEL_4x4, PIXEL_8x4, 0, 0},
	{0, PIXEL_4x8, PIXEL_8x8, 0, PIXEL_16x8},
	{
	    0,
	},
	{0, 0, PIXEL_8x16, 0, PIXEL_16x16}};

static const uint8_t x264_luma2chroma_pixel[4][7] =
    {
	{0},
	{PIXEL_8x8, PIXEL_8x4, PIXEL_4x8, PIXEL_4x4, PIXEL_4x2, PIXEL_2x4, PIXEL_2x2},	   /* 4:2:0 */
	{PIXEL_8x16, PIXEL_8x8, PIXEL_4x16, PIXEL_4x8, PIXEL_4x4, PIXEL_2x8, PIXEL_2x4},   /* 4:2:2 */
	{PIXEL_16x16, PIXEL_16x8, PIXEL_8x16, PIXEL_8x8, PIXEL_8x4, PIXEL_4x8, PIXEL_4x4}, /* 4:4:4 */
};

typedef struct
{
	x264_pixel_cmp_t sad[8];
	x264_pixel_cmp_t ssd[8];
	x264_pixel_cmp_t satd[8];
	x264_pixel_cmp_t mbcmp[8];	     /* either satd or sad for subpel refine and mode decision */
	x264_pixel_cmp_t mbcmp_unaligned[8]; /* unaligned mbcmp for subpel */
	x264_pixel_cmp_t fpelcmp[8];	     /* either satd or sad for fullpel motion search */
	x264_pixel_cmp_x3_t fpelcmp_x3[7];
	x264_pixel_cmp_x4_t fpelcmp_x4[7];
	x264_pixel_cmp_t sad_aligned[8]; /* Aligned SAD for mbcmp */

	uint64_t (*var[4])(pixel *pix, intptr_t stride);
	int (*var2[4])(pixel *pix1, intptr_t stride1, pixel *pix2, intptr_t stride2, int *ssd);

#ifdef _DEBUG
	void (*ssd_nv12_core)(pixel *pixuv1, intptr_t stride1,
			      pixel *pixuv2, intptr_t stride2, int width, int height,
			      uint64_t *ssd_u, uint64_t *ssd_v);
	void (*ssim_4x4x2_core)(const pixel *pix1, intptr_t stride1,
				const pixel *pix2, intptr_t stride2, int sums[2][4]);
	float (*ssim_end4)(int sum0[5][4], int sum1[5][4], int width);
#endif

	/* multiple parallel calls to cmp. */
	x264_pixel_cmp_x3_t sad_x3[7];
	x264_pixel_cmp_x4_t sad_x4[7];
	x264_pixel_cmp_x3_t satd_x3[7];
	x264_pixel_cmp_x4_t satd_x4[7];

	/* calculate satd or sad of V, H, and DC modes. */
	void (*intra_mbcmp_x3_16x16)(pixel *fenc, pixel *fdec, int res[3]);
	void (*intra_satd_x3_16x16)(pixel *fenc, pixel *fdec, int res[3]);
	void (*intra_sad_x3_16x16)(pixel *fenc, pixel *fdec, int res[3]);

	void (*intra_mbcmp_x3_4x4)(pixel *fenc, pixel *fdec, int res[3]);
	void (*intra_satd_x3_4x4)(pixel *fenc, pixel *fdec, int res[3]);
	void (*intra_sad_x3_4x4)(pixel *fenc, pixel *fdec, int res[3]);

	void (*intra_mbcmp_x4_4x4_h)(pixel *fenc, pixel *fdec, int res[9]);
	void (*intra_satd_x4_4x4_h)(pixel *fenc, pixel *fdec, int res[9]);
	void (*intra_sad_x4_4x4_h)(pixel *fenc, pixel *fdec, int res[9]);

	void (*intra_mbcmp_x4_4x4_v)(pixel *fenc, pixel *fdec, int res[9]);
	void (*intra_satd_x4_4x4_v)(pixel *fenc, pixel *fdec, int res[9]);
	void (*intra_sad_x4_4x4_v)(pixel *fenc, pixel *fdec, int res[9]);

	void (*intra_mbcmp_x3_chroma)(pixel *fenc, pixel *fdec, int res[3]);
	void (*intra_satd_x3_chroma)(pixel *fenc, pixel *fdec, int res[3]);
	void (*intra_sad_x3_chroma)(pixel *fenc, pixel *fdec, int res[3]);

	void (*intra_mbcmp_x3_8x8c)(pixel *fenc, pixel *fdec, int res[3]);
	void (*intra_satd_x3_8x8c)(pixel *fenc, pixel *fdec, int res[3]);
	void (*intra_sad_x3_8x8c)(pixel *fenc, pixel *fdec, int res[3]);

	/* find minimum satd or sad of all modes, and set fdec.
	 * may be NULL, in which case just use pred+satd instead. */
	int (*intra_mbcmp_x9_4x4)(pixel *fenc, pixel *fdec, uint16_t *bitcosts);
	int (*intra_satd_x9_4x4)(pixel *fenc, pixel *fdec, uint16_t *bitcosts);
	int (*intra_sad_x9_4x4)(pixel *fenc, pixel *fdec, uint16_t *bitcosts);

} x264_pixel_function_t;

void x264_pixel_init(int cpu, x264_pixel_function_t *pixf);

#ifdef _DEBUG
void x264_pixel_ssd_nv12(x264_pixel_function_t *pf, pixel *pix1, intptr_t i_pix1, pixel *pix2, intptr_t i_pix2,
			 int i_width, int i_height, uint64_t *ssd_u, uint64_t *ssd_v);
uint64_t x264_pixel_ssd_wxh(x264_pixel_function_t *pf, pixel *pix1, intptr_t i_pix1, pixel *pix2, intptr_t i_pix2,
			    int i_width, int i_height);
float x264_pixel_ssim_wxh(x264_pixel_function_t *pf, pixel *pix1, intptr_t i_pix1, pixel *pix2, intptr_t i_pix2,
			  int i_width, int i_height, void *buf, int *cnt);
#endif

#endif
