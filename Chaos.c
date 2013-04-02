/* �����v���O���~���O Chaos.c */
/* ���W�X�e�B�b�N�ʑ� */
/* 2013.01.24, 10RU004, �΋��ˑ� */

#include "bmpsave.h"
#include "chaos.h"
#include <limits.h>
#include <float.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795L	/* VC++6.0�ɒ�`����ĂȂ����� */
#endif

char logisticcurve(const char *filename, unsigned char fine, unsigned long TMAX, double set,
	double XMIN, double XMAX, double YMIN, double YMAX, unsigned long XSIZE, unsigned long YSIZE)
{
	unsigned char *maps, buf[100];
	unsigned long count, mapx, mapy, y, *curvemaps, fT = 1;
	double a, *mx, *my, *x_, MAX;

	/* �g�p���铮�I���������m�� */
	if ((mx = (double *)malloc(XSIZE * fine * sizeof(double))) == NULL) return 1;
	if ((my = (double *)malloc(YSIZE * sizeof(double))) == NULL) return 1;
	if ((x_ = (double *)malloc(XSIZE * fine * sizeof(double))) == NULL) return 1;
	/*if ((maps = (unsigned char *)calloc(XSIZE * YSIZE * 3, sizeof(unsigned char))) == NULL) return 1;*/
	if ((maps = (unsigned char *)calloc(XSIZE * YSIZE, sizeof(unsigned char))) == NULL) return 1;
	if ((curvemaps = (unsigned long *)calloc(XSIZE * YSIZE, sizeof(unsigned long))) == NULL) return 1;

	for (count = 0; count < XSIZE * fine; x_[count++] = set);
	for (count = 0; count < XSIZE * fine; mx[count++] = (XMAX - XMIN) * count / XSIZE / fine + XMIN);
	for (count = 0; count < YSIZE; my[count++] = (YMAX - YMIN) * count / YSIZE + YMIN);

	for (count = 0; count < TMAX; count++)
	{
		for (mapx = 0; mapx < XSIZE * fine; mapx++)
		{
			x_[mapx] = mx[mapx] * x_[mapx] *(1 - x_[mapx]);

			/* �������W�ɍł��߂��}�b�v���W��T�� */
			for (y = 0; my[y] < x_[mapx] && y < YSIZE; y++);
			if (my[y] + my[y - 1] > x_[mapx] * 2) y--;

			if (y < 0 || YSIZE <= y) continue;	/* �`��ʏ�ɂȂ��_ */
			y = YSIZE - y - 1;

			/* �Y�������_�����Z */
			if (curvemaps[mapx / fine + XSIZE * y] != ULONG_MAX) curvemaps[mapx / fine + XSIZE * y]++;
		}
		printf("LOOP: %lu / %lu\n", count, TMAX);
		if (count > exp(log(10) * fT / 2) - 2)
		{
			fT++;
			/* �f�[�^���s�N�Z���}�b�v�ɕϊ� */
			for (mapx = 0; mapx < XSIZE; mapx++)
			{
				for (y = mapy = 0; mapy < YSIZE; mapy++)
					if (y < curvemaps[mapx + XSIZE * mapy]) y = curvemaps[mapx + XSIZE * mapy];

				for (mapy = 0; mapy < YSIZE; mapy++)
				{
					/*a = M_PI * 330 / 180 * exp(curvemaps[mapx + XSIZE * mapy]) / exp(y);
					maps[(mapx + XSIZE * mapy) * 3 + 0] = (unsigned char)(256 - 128 * (cos(a               ) + 1));
					maps[(mapx + XSIZE * mapy) * 3 + 1] = (unsigned char)(256 - 128 * (cos(a - M_PI * 2 / 3) + 1));
					maps[(mapx + XSIZE * mapy) * 3 + 2] = (unsigned char)(256 - 128 * (cos(a - M_PI * 4 / 3) + 1));*/
					maps[(mapx + XSIZE * mapy)] = (unsigned char)((double)curvemaps[mapx + XSIZE * mapy] / y * 255);
				}
			}
			/* �摜�t�@�C���ɏo�� */
			sprintf(buf, "%s_lc_%lu.bmp", filename, count + 1);
			/*bmpsave(buf, maps, XSIZE, YSIZE, 3, 1);*/
			bmpsave(buf, maps, XSIZE, YSIZE, 1, 1);
		}
	}

	free(mx);
	free(my);
	free(x_);
	free(maps);
	free(curvemaps);
	return 0;
}