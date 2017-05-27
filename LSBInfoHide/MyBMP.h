//���ޣ���������������ʦ�ġ����ݽṹ���㷨�ۺ�ʵ�������õ�ѧ��ʹ��
//�Ͻ�����������������ͬѧ�����������û�б�Ҫ�����ǿ��ܷǳ����ص��鷳
//���򣬽�ֱ�ӵ���֮���Ҳ����ٰ���������������������鷳�Ĺ�����

// MyBMP.h: interface for the MyBMP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYBMP_H__2885B02E_A32F_464B_87F9_A07E5A8FFBAC__INCLUDED_)
#define AFX_MYBMP_H__2885B02E_A32F_464B_87F9_A07E5A8FFBAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MyBMP
{
public:

    int getWidth();

    int getHeight();

    MyBMP(const char *filename);			//��һ���ļ�������һ������ĿǰΪ�˴����ϵļ��ԣ�Ҫ��ͼƬ�����4�ı���
    
	virtual ~MyBMP();						//��������
    
	MyBMP(const MyBMP &bmp);				//�������캯��
    
	MyBMP &operator = (const MyBMP &bmp);	//��ֵ���������
    
	//================================================================================================
   
	BITMAPINFOHEADER getInfoheader();		//��ȡλͼ��Ϣ���ݽṹ
   
	BITMAPFILEHEADER getFileheader();		//��ȡλͼͷ�ļ����ݽṹ
    
	int getnumQuad();						//��ȡ��ɫ��Ĵ�С
    
	RGBQUAD *getRGBQUAD();					//��ȡ��ɫ������
    
	BYTE *getImagedata();					//��ȡλͼ����
    
	//================================================================================================
    
	void outputFileheader();				//����Ļ�����λͼͷ�ļ����ݽṹ��Ϣ
    
	void outputInfoheader();				//����Ļ�����λͼ��Ϣ���ݽṹ
    
	//================================================================================================

protected:
    BITMAPFILEHEADER fileheader;			//λͼͷ�ļ����ݽṹ

    BITMAPINFOHEADER infoheader;			//λͼ��Ϣ���ݽṹ

    int numQuad;
    //��ɫ��Ĵ�С����RGBQUAD�ṹ������������BITMAPINFOHEADER�ṹ��biBitCount��ֵ��ȷ��

    RGBQUAD *quad;							//��ɫ�����ݣ���RGBQUAD�ṹ�����飬�����СΪnumQuad

    BYTE *imagedata;
    //λͼ���ݣ�����ɫ���������������ÿһ��������Ҫ���ٱ�����BITMAPINFOHEADER�ṹ��biBitCount��ֵ��ȷ��

};

#endif // !defined(AFX_MYBMP_H__2885B02E_A32F_464B_87F9_A07E5A8FFBAC__INCLUDED_)
