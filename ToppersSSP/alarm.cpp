/*
 *  TOPPERS/SSP Kernel
 *      Smallest Set Profile Kernel
 *
 *  Copyright (C) 2011 by Meika Sugimoto
 *  Copyright (C) 2015 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
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

/*
 *  �A���[���n���h���@�\
 */

#include "include/alarm.h"
#include "include/check.h"
#include "include/time_event.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */

#ifndef LOG_ALM_ENTER
#define LOG_ALM_ENTER(almidx)
#endif /* LOG_ALM_ENTER */

#ifndef LOG_ALM_LEAVE
#define LOG_ALM_LEAVE(almidx)
#endif /* LOG_ALM_LEAVE */

#ifndef LOG_STA_ALM_ENTER
#define LOG_STA_ALM_ENTER(almid, almtim)
#endif /* LOG_STA_ALM_ENTER */

#ifndef LOG_STA_ALM_LEAVE
#define LOG_STA_ALM_LEAVE(ercd)
#endif /* LOG_STA_ALM_LEAVE */

#ifndef LOG_ISTA_ALM_ENTER
#define LOG_ISTA_ALM_ENTER(almid, almtim)
#endif /* LOG_ISTA_ALM_ENTER */

#ifndef LOG_ISTA_ALM_LEAVE
#define LOG_ISTA_ALM_LEAVE(ercd)
#endif /* LOG_ISTA_ALM_LEAVE */

#ifndef LOG_STP_ALM_ENTER
#define LOG_STP_ALM_ENTER(almid)
#endif /* LOG_STP_ALM_ENTER */

#ifndef LOG_STP_ALM_LEAVE
#define LOG_STP_ALM_LEAVE(ercd)
#endif /* LOG_STP_ALM_LEAVE */

#ifndef LOG_ISTP_ALM_ENTER
#define LOG_ISTP_ALM_ENTER(almid)
#endif /* LOG_ISTP_ALM_ENTER */

#ifndef LOG_ISTP_ALM_LEAVE
#define LOG_ISTP_ALM_LEAVE(ercd)
#endif /* LOG_ISTP_ALM_LEAVE */


/* �����n���h��ID���^�C���C�x���gID�ɕϊ� */
#define ALM_EVTID(almid)	((ID)(INDEX_ALM(almid) + almevtid_offset))
#define INDEX_ALM(almid)	((uint_t)((almid) - TMIN_ALMID))

/* �A���[���n���h���̌� */
#define tnum_alm			((uint_t)(tmax_almid - TMIN_ALMID + 1))

/* �A���[���̓����Ԃ�\���r�b�g�}�b�v */
#define ALMACT_BIT(index)	(1U << (index))


/* �A���[���n���h�����s�^�C���C�x���g */
void call_almhdr(uintptr_t almidx);


/*
 *  �A���[���n���h���@�\�̏�����
 */

#define TOPPERS_almcal
#ifdef TOPPERS_almcal

void
initialize_alarm(void)
{
	/* �S�ẴA���[�����~��Ԃɂ��� */
	almcb_almact = 0U;
}

#endif /* TOPPERS_almcal */

/*
 *  �A���[���̊J�n
 */

#define TOPPERS_sta_alm
#ifdef TOPPERS_sta_alm

ER
sta_alm(ID almid , RELTIM almtim)
{
	ER ercd;
	uint_t index = INDEX_ALM(almid);
	
	LOG_STA_ALM_ENTER(almid, almtim);
//	CHECK_TSKCTX_UNL();
	CHECK_ALMID(almid);
	
	t_lock_cpu();
	
	if((almcb_almact & ALMACT_BIT(index)) != 0U) {
		time_event_dequeue(ALM_EVTID(almid));
	}
	else {
		almcb_almact |= ALMACT_BIT(index);
	}
	
	time_event_enqueue(ALM_EVTID(almid) ,
		current_time + (EVTTIM)almtim , (CBACK)call_almhdr , index);
	
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_STA_ALM_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_sta_alm */

/*
 *  �A���[���̊J�n(��^�X�N�R���e�L�X�g�p)
 */

#define TOPPERS_ista_alm
#ifdef TOPPERS_ista_alm

ER
ista_alm(ID almid , RELTIM almtim)
{
	ER ercd;
	uint_t index = INDEX_ALM(almid);
	
	LOG_ISTA_ALM_ENTER(almid, almtim);
//	CHECK_INTCTX_UNL();
	CHECK_ALMID(almid);
	
	i_lock_cpu();
	
	if((almcb_almact & ALMACT_BIT(index)) != 0U) {
		time_event_dequeue(ALM_EVTID(almid));
	}
	else {
		almcb_almact |= ALMACT_BIT(index);
	}
	
	time_event_enqueue(ALM_EVTID(almid) ,
		current_time + (EVTTIM)almtim , (CBACK)call_almhdr , index);
	
	ercd = E_OK;
	i_unlock_cpu();
	
  error_exit:
	LOG_ISTA_ALM_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_ista_alm */

/*
 *  �A���[���̒�~
 */

#define TOPPERS_stp_alm
#ifdef TOPPERS_stp_alm

ER
stp_alm(ID almid)
{
	ER ercd;
	uint_t index = INDEX_ALM(almid);
	
	LOG_STP_ALM_ENTER(almid);
//	CHECK_TSKCTX_UNL();
	CHECK_ALMID(almid);
	
	t_lock_cpu();
	
	if((almcb_almact & ALMACT_BIT(index)) != 0U) {
		almcb_almact &= ~ALMACT_BIT(index);
		time_event_dequeue(ALM_EVTID(almid));
	}
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_STP_ALM_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_stp_alm */

/*
 *  �A���[���̒�~(��^�X�N�R���e�L�X�g�p)
 */

#define TOPPERS_istp_alm
#ifdef TOPPERS_istp_alm

ER
istp_alm(ID almid)
{
	ER ercd;
	uint_t index = INDEX_ALM(almid);
	
	LOG_ISTP_ALM_ENTER(almid);
//	CHECK_INTCTX_UNL();
	CHECK_ALMID(almid);
	
	i_lock_cpu();
	
	if((almcb_almact & ALMACT_BIT(index)) != 0U) {
		almcb_almact &= ~ALMACT_BIT(index);
		time_event_dequeue(ALM_EVTID(almid));
	}
	ercd = E_OK;
	i_unlock_cpu();
	
  error_exit:
	LOG_ISTP_ALM_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_istp_alm */

/*
 *  �A���[���n���h���N�����[�`��
 */

#define TOPPERS_almcal
#ifdef TOPPERS_almcal

void
call_almhdr(uintptr_t almidx)
{
	/* �A���[���n���h�����~��Ԃɂ��� */
	almcb_almact &= ~ALMACT_BIT(almidx);
	
	i_unlock_cpu();
	
	/* �A���[���n���h���̎��s */
	LOG_ALM_ENTER(almidx);
	(*alminib_almhdr[almidx])(alminib_exinf[almidx]);
	LOG_ALM_LEAVE(almidx);
	
#ifdef ARDUINO
	if (1) {
#else
	if (!i_sense_lock()) {
#endif
		i_lock_cpu();
	}
}
#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_almcal */

