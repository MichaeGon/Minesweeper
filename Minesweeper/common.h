// ���ʃw�b�_
#ifndef ___COMMONHEADER___
#define ___COMMONHEADER___

const int SENTINEL = -2; // �ԕ������
extern int sqrNum; // ��ӂ̃}�X�ڂ̐�
extern int width; // �E�B���h�E�̉���
extern int height; // �E�B���h�E�̏c��
extern char* title; // �A�v���^�C�g��

// �ȉ�OpenGL�֘A

void display(); // �`��̍یĂяo�����֐��B�`�悵�����Ƃ��͂��̒��ɏ������ނ���
void displayBoard(); // �{�[�h�̊�Ղ�`�悷��
void displayPiece(int x, int y, double color[]); //x,y�Ŏw�肵���}�X�ڂ�color[]={R,G,B}��RGB�w�肵���F�œh��Ԃ�(�e�l��0~1)
void displayPushedPiece(int x, int y, int num); // x,y�Ŏw�肵���}�X�ڂ�num��`�悷��
void displayFlagPiece(int x, int y); // x,y�Ŏw�肵���}�X�ڂɃt���O��`�悷��

void resize(int w, int h); // �ĕ`��O�̏����ɌĂяo�����
void mouse(int button, int state, int x, int y); // �}�E�X
void keyboard(unsigned char key, int x, int y); // �L�[�{�[�h

void left(int x, int y);
void right(int x, int y);

#endif