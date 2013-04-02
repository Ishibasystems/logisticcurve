/* �����v���O���~���O logisticcurve.c */
/* ���W�X�e�B�b�N�ʑ� �o�̓��j���[ */
/* 2013.01.30, 10RU004, �΋��ˑ� */

#include <time.h>
#include "chaos.h"

long input(char *, long);

void main(void)
{
	char mjmode, colmode, bmpmode, buf[256], file[256] = "\0", type[2][4] = {"ppm", "bmp"};
	unsigned char count;
	unsigned long XSIZE, YSIZE;
	double XMIN = 3.56995/*1.0*/, XMAX = 4.0, YMIN = -0.0, YMAX = 1.0, hoge;

	time_t timer;

	YSIZE = 1080;
	XSIZE = 1920;

	//printf("\n�F�ʃ��[�h�I��\n1:\t�ω���\n2:\t�W�{���U\n3:\t�W���΍�\n4:\t���U�ɗv�����񐔂̋t��\nOther:\t�I��\n>> ");
	colmode = 3;
/*
	if (YSIZE * (XMAX - XMIN) < XSIZE * (YMAX - YMIN))
	{
		hoge = (XSIZE * (YMAX - YMIN) / YSIZE - XMAX + XMIN) / 2;
		XMAX += hoge;
		XMIN -= hoge;
	}
	else
	{
		hoge = (YSIZE * (XMAX - XMIN) / XSIZE - YMAX + YMIN) / 2;
		YMAX += hoge;
		YMIN -= hoge;
	}*/
	printf("�`��͈�:\nX %f to %f\nY %f to %f\n���w�肳��܂���\n", XMIN, XMAX, YMIN, YMAX);

	buf[count = 0] = '\0';

	/*if (count < 5 || buf[count - 4] != '.' || strcmp(&buf[count - 3], type[bmpmode]) != 0)*/
	if (!(count > 4 && buf[count - 4] == '.' && strcmp(&buf[count - 3], type[0]) == 0))
	{
		if (count == 0)
		{
			time(&timer);
			sprintf(buf, "%s", ctime(&timer));
			for(count = 0; count < strlen(buf); count++)
			{
				if (buf[count] == ':') buf[count] = '_';	/* ctime�֐��ŕԂ������񒆂̃t�@�C�����Ɏw��ł��Ȃ�������u�� */
				if (buf[count] == '\n') buf[count] = '\0';
			}
		sprintf(file, "%s", buf);
		}
	}

	printf("\n�o�̓t�@�C���� : \"%s\"\n�o�͒�... ���΂炭���҂���������\n", file);

	if (logisticcurve(file, 10, 3300000, 0.1, XMIN, XMAX, YMIN, YMAX, XSIZE, YSIZE) != 0)
		 printf("�G���[���������܂���\n");
	else printf("�o�͂��I�����܂���\n");

	return;
}

long input(char *s, long len)
{
	fgets(s, len, stdin);
	s[len - 1] = '\0';

	if (strchr(s, '\n') != 0) s[strlen(s) - 1] = '\0';
	else while(getchar() != '\n');

	return atol(s);
}
