/** \file easynirwrapper.h
 *  \brief \b �����Ƕ���ӿ�.
 *  \author wangdh
 *  \version 1.0
 *  \date 2020-03-18 15:10:00
 *  \details \b ����
 *  - �����ǲ�������ӿ�
 *	- �����ǻ�������
 */

#ifndef EASY_NIR_WRAPPER_H
#define EASY_NIR_WRAPPER_H

#include <map>
#include <list>
#include <vector>

#ifdef __cplusplus
extern "C"
{
#endif
	/**
	 * \struct ScanSection 
	 * \brief ɨ�����	
	 */
	typedef struct {
		std::string m_sectionScanType;		///< ɨ������
		double m_widthPixel;			    ///< ���ؿ��
		unsigned short m_wavelengthStart;	///< ��ʼɨ�����С��������λΪ����
		unsigned short m_wavelengthEnd;		///< ����ɨ�����С��������λΪ����
		unsigned short m_patternsNum;		///< Ƶ�����������ĵ���
		double m_exposureTime;				///< �ع�ʱ��
	}ScanSection;

	/**
	 * \brief ö�����ӵ�ϵͳ������dlp�豸.
	 * \param[out] num �豸����
	 * \return >= 0:ö�ٳɹ�, < 0:ö��ʧ��.
	 */
	int enumerateDevices(int* num);

	/**
	 * \brief �����ӵ�ϵͳ���豸.
	 * \param[in] index ��Ҫ�򿪵��豸��,��Ч��Χ��0~(N-1)֮��(NΪö�ٵ��豸����).
	 * \return >= 0:�򿪳ɹ�, < 0:��ʧ��.
	 */
	int openSpectrometer(int index);

	/**
	 * \brief �ر����ӵ�ϵͳ���豸.
	 */
	void closeSpectrometer();

	/**
	 * \brief ��ȡ�豸ɨ�����ò�������
	 * \return ɨ�����ò�������
	 */
	int getScanSectionNumber();

	/**
	 * \brief ��ȡ�豸ɨ����������
	 * \param[in] index �豸ɨ���������(�ο�getScanSectionNumber() index����С��getScanSectionNumber()����ֵ)
	 * \param[out] secName �豸ɨ����������
	 * \param[in] size �豸ɨ�����������ڴ��С
	 * \return 0:��ȡ�ɹ�, <0:��ȡʧ��
	 */
	int getScanSectionName(int index, char* secName, unsigned int size);

	/**
	 * \brief ��ȡĳһɨ�����ú��е���ɨ�����ø���
	 * \param name ɨ����������
	 * \return ��ɨ�����ø���
	 */
	int getScanSectionNameNumber(char* name);

	/**
	 * \brief ��ȡ��ɨ������
	 * \param name ��ɨ����������
	 * \param index ��ɨ������������
	 * \param scanType ɨ������
	 * \param scanTypeLen ɨ�������ڴ泤��
	 * \param widthPixel ���ؿ��
	 * \param wavelengthStart ��ʼɨ�����С��������λΪ����
	 * \param wavelengthEnd ����ɨ�����С��������λΪ����
	 * \param patternsNum Ƶ�����������ĵ���
	 * \param exposureTime �ع�ʱ��
	 * \return 0:��ȡ�ɹ�, <0:��ȡʧ��
	 */
	int getScanSectionNameCfg(char* name, int index, char* scanType, unsigned int scanTypeLen, double* widthPixel,
		unsigned short* wavelengthStart, unsigned short* wavelengthEnd,
		unsigned short* patternsNum, double* exposureTime);

	/**
	 * \brief ��ȡ�豸ɨ�������������
	 * \return ��������
	 */
	int getScanTypesNumber();

	/**
	 * \brief ��ȡ�豸ɨ�������������
	 * \param index �����������(�ο�getScanTypesNumber() index����С��getScanTypesNumber()����ֵ)
	 * \return ɨ�������������
	 */
	char* getScanTypesName(int index);

	/**
	 * \brief ��ȡ���ؿ�����͸���
	 * \return ���ؿ�����͸���
	 */
	int getWidthPixelsNumber();

	/**
	 * \brief ��ȡ���ؿ������
	 * \param index �ؿ��������(�ο�getWidthPixelsNumber() index����С��getWidthPixelsNumber()����ֵ)
	 * \return �ؿ���
	 */
	double getWidthPixel(int index);

	/**
	 * \brief ��ȡ�ع�ʱ�����͸���
	 * \return �ع�ʱ�����͸���
	 */
	int getExposureTimesNumber();

	/**
	 * \brief ��ȡ�ع�ʱ������
	 * \param index �ؿ��������(�ο�getExposureTimesNumber() index����С��getExposureTimesNumber()����ֵ)
	 * \return �ع�ʱ������
	 */
	double getExposureTime(int index);

	/**
	 * \brief ��ȡʣ��ģʽ��
	 * \param cfgName[in] �����ļ�����
	 * \param section[in] ��ǰɨ��������
	 * \param num[out] ʣ��ģʽ��(ȥ����ǰ����)
	 * \return 0:��ȡ�ɹ�, <0:��ȡʧ��
	 */
	int getRemainPatternNum(char* cfgName, unsigned char section, unsigned short* num);

	/**
	 * \brief ��ȡģʽ��Χ
	 * \param[out] start ��ʼ
	 * \param[out] end ����
	 * \return 0:��ȡ�ɹ�, <0:��ȡʧ��
	 */
	int getPatternsRange(int* start, int* end);

	/**
	 * \brief ��ȡ��Ĳ����������
	 * \param[out] index ����������
	 * \return 0:��ȡ�ɹ�, <0:��ȡʧ��.
	 */
	int getActiveScanIndex(int* index);

	/**
	 * \brief ���û�Ĳ����������
	 * \param[in] index �������
	 * \return 0:���óɹ�, <0:����ʧ��.
	 */
	int setActiveScanIndex(char index);

	/**
	 * \brief ��ȡɨ���Ԥ��ʱ�䣨���룩
	 * \return Ԥ��ʱ�䣨���룩
	 */
	int getEstimatedScanTime();

	/**
	 * \brief ����Ŀ������ò���
	 * \param name ���ò�������
	 * \param section ��������ɨ�����
	 * \param scanType ɨ������
	 * \param wavelengthStart ��ʼ����
	 * \param wavelengthEnd ��������
	 * \param widthPixel ���ؿ��
	 * \param patternsNum ģʽ��
	 * \param exposureTime �ع�ʱ��
	 * \return 0:���óɹ�, <0:����ʧ��
	 */
	int setTgtCfg(const char* name, int section, const char* scanType, unsigned short wavelengthStart,
		unsigned short wavelengthEnd, double widthPixel, unsigned short patternsNum,
		double exposureTime);

	/**
	  * \brief ����Ŀ������ò���
	  * \param cfgName ���ò�������
	  * \param averNum ɨ�����
	  * \return 0:���óɹ�, <0:����ʧ��
	  */
	int setTgtCfgs(const char* cfgName, unsigned short averNum);

	/**
	 * \brief �Ƴ�ɨ������
	 * \param name ɨ����������
	 * \return 0:�Ƴ��ɹ�, <0:�Ƴ�ʧ��
	 */
	int removeTgtCfg(const char* name);

	/**
	 * \brief ��ȡ�汾��
	 * \param[out] pTivaSwVersion Tiva�汾
	 * \param[out] pDlpcswVersion DLP�汾
	 * \param[out] pDlpcFlashBuildVersion flash�汾
	 * \param[out] pSpecLibVer �����ǿ�汾
	 * \param[out] pCalDataVer У׼�����汾
	 * \param[out] pRefCalDataVer �ο������汾
	 * \param[out] pCfgDataVer ���ò����汾
	 * \return 0:��ȡ��ȷ <0:��ȡʧ��
	 */
	int getVersions(unsigned int *pTivaSwVersion, unsigned int *pDlpcswVersion, unsigned int *pDlpcFlashBuildVersion, unsigned int *pSpecLibVer, unsigned int *pCalDataVer, unsigned int *pRefCalDataVer, unsigned int *pCfgDataVer);

	/**
	 * \brief ���ù�Դ����״̬
	 * \param[in] status 1:�� 0:��
	 * \return 0:���óɹ�, <0:����ʧ��
	 */
	int setLampStatus(int status);
		
	/**
	 * \brief ��������ϵ��
	 * \param[in] isFixed 1:�̶� 0:���̶�
	 * \param[in] gainVal 1,2,4,8,16,32 �� 64
	 * \return true:���óɹ�, false:����ʧ��
	 */
	int setPGAGain(int isFixed, unsigned char gainVal);

	/**
	 * \brief ��ȡ���ģʽ��
	 * \param cfg_name ��������
	 * \param start_nm ��ʼ����
	 * \param end_nm ��������
	 * \param width_index ���ؿ��
	 * \param scan_type ɨ������
	 * \param scan_num ɨ�����
	 * \return �������ģʽ��
	 */
	int getMaxPattern(char* cfg_name, int start_nm, int end_nm, unsigned char width_index, int scan_type, unsigned char scan_num);

	/**
	 * \brief ��ȡ�������ݳ���
	 * \param[out] fileSize ���ݳ���
	 * \return >= 0:��ȡ��ȷ < 0:��ȡʧ��
	 */
	int getFormattedSpectrumLengths(int* fileSize);

	/**
	 * \brief ���ù����ǲɼ���ƽ������
	 * \param[in] time ƽ������
	 * \return 0:���óɹ�, <0:����ʧ��
	 */
	int setSpectrumAverageTime(unsigned short time);

	/**
	 * \brief ��ȡ��������.
	 * \param[out] pWavelength ��������
	 * \param[out] pData ��������
	 * \return >= 0:��ȡ��ȷ < 0:��ȡʧ��
	 */
	int getFormattedSpectrum(double *pWavelength, unsigned int *pData);

	/**
	 * \brief ��ȡ���һ�εĴ�����Ϣ.
	 * \return ������Ϣ[��󳤶�Ϊ256�ֽ�]
	 */
	const char* getLastException();

	/**
	 * \brief ��־����.
	 * \param[in] onOff 1:������־ 0:�ر���־
	 */
	void setLogSwitch(int onOff);


#ifdef __cplusplus
}
#endif

#endif//EASY_NIR_WRAPPER_H
