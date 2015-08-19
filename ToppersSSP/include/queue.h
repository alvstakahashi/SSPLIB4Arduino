/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2011 by Meika Sugimoto
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)?(4) �̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE
 *  �Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�
??�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒��쌠
 *      �\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[�X
 *      �R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t
�g�E�F�A�J���Ɏg�p
 *      �ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p�҃}
 *      �j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L�̖���
 *      �؋K����f
�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg�p
 *      �ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂������ƁD
 *    (a) �Ĕz�z���
??���h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒���
 *        ���\���C���̗��p���������
??���L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS
�v���W�F�N�g�ɕ�
 *        �����邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ��
??�Q
 *      ������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD�܂��C
 *      �{�\�t�g�
?�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝�R�Ɋ��
 *      ������������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂���
 *  ��TOPPERS�v���
??�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI�ɑ΂�
 *  ��K�������܂߂āC�����Ȃ��
??�؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p
 *  �ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC��
 *  ��Ȃ��D
 * 
 */

/*
 *  �L���[����w�b�_
 *
 *  SSP�J�[�l���ł̓������ߖ�̂��߂ɃC���f�b�N�X���g�p�����L���[��p����
 */

#ifndef TOPPERS_QUEUE_H
#define TOPPERS_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif


#if defined __GNUC__
#ifndef Inline
#define Inline static inline
#endif
#endif


/* �L���[�̃C���f�b�N�X */
typedef uint8_t QUEIDX;

/* �L���[�\���� */
typedef struct
{
	QUEIDX	next;
	QUEIDX	prev;
} QUEUE;


/* �L���[�w�b�_�̏����� */
Inline void
queue_initialize(QUEUE *queue , QUEIDX queue_null)
{
	queue->next = queue->prev = queue_null;
}

/* �w�肵���v�f�̑O�ɐV���ȗv�f��ǉ� */
Inline  void
queue_insert_prev(QUEUE *top , QUEIDX queue , QUEIDX entry)
{
	top[entry].prev = top[queue].prev;
	top[entry].next = queue;
	top[top[queue].prev].next = entry;
	top[queue].prev = entry;
}


/* �w�肵���L���[�̎��̗v�f���폜���C���̃C���f�b�N�X��Ԃ� */
Inline QUEIDX
queue_delete_next(QUEUE *top , QUEIDX queue)
{
	top[top[queue].next].prev = top[queue].prev;
	top[top[queue].prev].next = top[queue].next;
	
	return top[queue].next;
}


/*
 *  �L���[���󂩂ǂ����̃e�X�g
 *
 *  queue�ɂ̓L���[�w�b�_���w�肷�邱��
 */
Inline bool_t
queue_empty(QUEUE *queue , QUEIDX queue_null)
{
	bool_t empty;
	
	if(queue->next == queue_null)
	{
		empty = true;
	}
	else
	{
		empty = false;
	}
	
	return empty;
}

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_QUEUE_H */
