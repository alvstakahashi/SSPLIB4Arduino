/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2011 by Meika Sugimoto
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE
 *  �Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒��쌠
 *      �\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[�X
 *      �R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg�p
 *      �ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p�҃}
 *      �j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L�̖���
 *      �؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg�p
 *      �ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂������ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒���
 *        ���\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g�ɕ�
 *        �����邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹�Q
 *      ������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD�܂��C
 *      �{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝�R�Ɋ��
 *      ������������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂���
 *  ��TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI�ɑ΂�
 *  ��K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p
 *  �ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC��
 *  ��Ȃ��D
 * 
 */

#include "include/kernel_impl.h"

#include "include/time_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ���݂̃V�X�e�������i�P��: 1�~���b�j
 *
 *  �����ɂ́C�O�̃^�C���e�B�b�N�̃V�X�e�������D
 */
EVTTIM	current_time;

/*
 *  �^�C���C�x���g�q�[�v���ŗL���ȍŏ��̃V�X�e�������i�P��: 1�~���b�j
 */
EVTTIM	min_time;


/*
 *  �^�C���C�x���g�L���[�̃L���[�w�b�_
 *
 *  �^�C���C�x���g�L���[�u���b�N�̏I�[�Ɋm�ۂ���D
 */
#define TMEVT_HEAD()	(tmevt_queue[tnum_tmevt_queue])
#define TMEVT_NULL		((QUEIDX)tnum_tmevt_queue)

/*
 *  �C�x���g����������r�}�N��
 *
 *  �C�x���g���������́Cmin_time����̑��Βl�Ŕ�r����D���Ȃ킿�C
 *  min_time���ŏ��l�i�ł��߂������j�Cmit_time-1���ő�l�i�ł����������j
 *  �Ƃ݂Ȃ��Ĕ�r����D
 */
#define	EVTTIM_LT(t1, t2) (((t1) - min_time) < ((t2) - min_time))
#define	EVTTIM_LE(t1, t2) (((t1) - min_time) <= ((t2) - min_time))

/*
 *  �^�C���C�x���g�̏�����
 */

#define TOPPERS_tmevtini
#ifdef TOPPERS_tmevtini

void
initialize_time_event(void)
{
	/* �ϐ��̏����� */
	current_time = 0U;
	min_time = 0U;
	
	/* �^�C���C�x���g�L���[�̏����� */
	queue_initialize(&TMEVT_HEAD() , (QUEIDX)tnum_tmevt_queue);
}

#endif /* TOPPERS_tmevtini */

/*
 *  �^�C���C�x���g�̓o�^
 */

#define TOPPERS_tmevtenq
#ifdef TOPPERS_tmevtenq

void
time_event_enqueue(ID tmevtid , EVTTIM evttim , CBACK callback , uintptr_t arg)
{
	QUEIDX pos = TMEVT_HEAD().next;
	
	/* �}���ʒu������ */
	while((pos != TMEVT_NULL)
			&& (EVTTIM_LE(tmevt_time[pos] , evttim))) {
		pos = tmevt_queue[pos].next;
	}
	
	/* �L���[�ɑ}�� */
	queue_insert_prev(&(tmevt_queue[0]) , pos , (QUEIDX)tmevtid);
	tmevt_callback[tmevtid] = (CBACK)callback;
	tmevt_arg[tmevtid] = arg;
	tmevt_time[tmevtid] = evttim;
}

#endif /* TOPPERS_tmevtenq */

/*
 *  �^�C���C�x���g�̍폜
 */

#define TOPPERS_tmevtdeq
#ifdef TOPPERS_tmevtdeq

void
time_event_dequeue(ID tmevtid)
{
	/* �L���[����폜 */
	(void)queue_delete_next(&(tmevt_queue[0]) , (QUEIDX)tmevtid);
}

#endif /* TOPPERS_tmevtdeq */

/*
 *  �V�X�e�������̒ʒm
 */

#define TOPPERS_sig_tim
#ifdef TOPPERS_sig_tim

void
signal_time(void)
{
	QUEIDX pos = TMEVT_HEAD().next , evtid;
	
	i_lock_cpu();
	
	/* ���ݎ����̍X�V */
	current_time += (EVTTIM)TIC_NUME;
	
	/* �R�[���o�b�N�̎��s */
	while((pos != TMEVT_NULL)
			&& EVTTIM_LT(tmevt_time[pos] , current_time)) {
		(void)queue_delete_next(&(tmevt_queue[0]) , pos);
		evtid = pos;
		pos = tmevt_queue[pos].next;
		(*tmevt_callback[evtid])(tmevt_arg[evtid]);
	}

	/* min_time�̍X�V */
	min_time = current_time;
	
	i_unlock_cpu();
}
#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_sig_tim */
