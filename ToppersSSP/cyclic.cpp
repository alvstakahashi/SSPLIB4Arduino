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

/*
 *  �����n���h���@�\
 */

#include "include/kernel_impl.h"
#include "include/check.h"
#include "include/time_event.h"
#include "include/cyclic.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */
#ifndef LOG_CYC_ENTER
#define LOG_CYC_ENTER(cycidx)
#endif /* LOG_CYC_ENTER */

#ifndef LOG_CYC_LEAVE
#define LOG_CYC_LEAVE(cycidx)
#endif /* LOG_CYC_LEAVE */

#ifndef LOG_STA_CYC_ENTER
#define LOG_STA_CYC_ENTER(cycid)
#endif /* LOG_STA_CYC_ENTER */

#ifndef LOG_STA_CYC_LEAVE
#define LOG_STA_CYC_LEAVE(ercd)
#endif /* LOG_STA_CYC_LEAVE */

#ifndef LOG_STP_CYC_ENTER
#define LOG_STP_CYC_ENTER(cycid)
#endif /* LOG_STP_CYC_ENTER */

#ifndef LOG_STP_CYC_LEAVE
#define LOG_STP_CYC_LEAVE(ercd)
#endif /* LOG_STP_CYC_LEAVE */


/* �����n���h��ID���^�C���C�x���gID�ɕϊ� */
#define CYC_EVTID(cycidx)	((ID)((cycidx) + cycevtid_offset))
#define INDEX_CYC(cycid)	((uint_t)((cycid) - TMIN_CYCID))


/* �����n���h���̓����Ԃ�\���r�b�g�}�b�v */
#define CYCACT_BIT(index)	(1U << (index))

/*
 *  �����n���h���N�����[�`��
 */
void call_cychdr(uintptr_t cycidx);

/*
 *  �����n���h���@�\�̏�����
 */

#define TOPPERS_cycini
#ifdef TOPPERS_cycini

void
initialize_cyclic(void)
{
	uint_t i;
	
	/* �����n���h���̏�Ԑݒ� */
	cyccb_cycact = cycinib_cycact;
	
	for(i = 0U ; i < tnum_cyc ; i++) {
		cyccb_evttim[i] = 0U;
		
		/* �����n���h���̏����N�� */
		if((cycinib_cycact & CYCACT_BIT(i)) != 0U) {
			time_event_enqueue(CYC_EVTID(i) ,
				(EVTTIM)cycinib_cycphs[i] , call_cychdr , i);
			cyccb_evttim[i] = cycinib_cycphs[i];
		}
	}
}

#endif /* TOPPERS_cycini */

#define TOPPERS_sta_cyc
#ifdef TOPPERS_sta_cyc

ER
sta_cyc(ID cycid)
{
	ER ercd;
	uint_t index = INDEX_CYC(cycid);
	EVTTIM evttim;
	
	LOG_STA_CYC_ENTER(cycid);
//	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	
	t_lock_cpu();
	
	if((cyccb_cycact & CYCACT_BIT(index)) != 0U) {
		time_event_dequeue(CYC_EVTID(index));
	}
	else {
		cyccb_cycact |= CYCACT_BIT(index);
	}

	evttim = current_time + cycinib_cycphs[index];
	time_event_enqueue(CYC_EVTID(index) ,
		 evttim , call_cychdr , index);
	cyccb_evttim[index] = evttim;
	
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_STA_CYC_LEAVE(ercd);
	return ercd;
}

#endif /* TOPPERS_sta_cyc */


#define TOPPERS_stp_cyc
#ifdef TOPPERS_stp_cyc

ER
stp_cyc(ID cycid)
{
	ER ercd;
	uint_t index = INDEX_CYC(cycid);
	
	LOG_STP_CYC_ENTER(cycid);
//	CHECK_TSKCTX_UNL();
	CHECK_CYCID(cycid);
	
	t_lock_cpu();
	
	if((cyccb_cycact & CYCACT_BIT(index)) != 0U) {
		cyccb_cycact &= ~CYCACT_BIT(index);
		time_event_dequeue(CYC_EVTID(index));
	}
	ercd = E_OK;
	t_unlock_cpu();
	
  error_exit:
	LOG_STA_CYC_LEAVE(ercd);
	return ercd;
}

ER
istp_cyc(ID cycid)
{
	ER ercd;
	uint_t index = INDEX_CYC(cycid);
	
//	CHECK_INTCTX_UNL();
	CHECK_CYCID(cycid);
	
	i_lock_cpu();
	
	if((cyccb_cycact & CYCACT_BIT(index)) != 0U) {
		cyccb_cycact &= ~CYCACT_BIT(index);
		time_event_dequeue(CYC_EVTID(index));
	}
	ercd = E_OK;
	i_unlock_cpu();
	
  error_exit:
	return ercd;
}

#endif /* TOPPERS_stp_cyc */

#define TOPPERS_cyccal
#ifdef TOPPERS_cyccal

void
call_cychdr(uintptr_t cycidx)
{
	cyccb_evttim[cycidx] += cycinib_cyctim[cycidx];

	/* �������̃^�C���C�x���g��o�^ */
	time_event_enqueue((ID)cycidx ,
		cyccb_evttim[cycidx] , call_cychdr , cycidx);
	
	i_unlock_cpu();
	
	/* �����n���h�������s */
	LOG_CYC_ENTER(cycidx);
	(*cycinib_cychdr[cycidx])(cycinib_exinf[cycidx]);
	LOG_CYC_LEAVE(cycidx);
	
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

#endif /* TOPPERS_cyccal */
