// OpenGLMagicCube.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include<math.h>
#include <GL/glut.h>

using namespace std;

bool mouseLeftDown = false;
bool mouseRightDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;


enum MyColors {
	//各个面的颜色
	RED, YELLOW, BLUE, GREEN, ORANGE, WHITE, BLACK, CHOSEN
};

struct CornorPoint
{
	float x, y, z;
};

struct Block
{
	MyColors front = BLACK, back = BLACK, left = BLACK, right = BLACK, top = BLACK, bottom = BLACK;
	float rotateX = 0, rotateY = 0, rotateZ = 0;
	CornorPoint FrontLeftTop, FrontRightTop, FrontLeftBottom, FrontRightBottom, BackLeftTop, BackRightTop, BackLeftBottom, BackRightBottom;
	//float x, y, z;//位置是-1，0，1
};


//方块数组，用于储存所有的魔方块
Block cubeBlocks[3][3][3];

void setGlColor(MyColors color) {
	switch (color)
	{
	case RED:
		glColor3f(0.8f, 0.2f, 0.2f);
		break;
	case YELLOW:
		glColor3f(0.8f, 0.8f, 0.2f);
		break;
	case BLUE:
		glColor3f(0.2f, 0.2f, 0.8f);
		break;
	case GREEN:
		glColor3f(0.2f, 0.8f, 0.2f);
		break;
	case ORANGE:
		glColor3f(0.8f, 0.5f, 0.2f);
		break;
	case WHITE:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	case BLACK:
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	case CHOSEN:
		glColor3f(1.0f, 1.0f, 0.0f);
	default:
		break;
	}
}

void cubeBlockInit() {
	//初始化所有魔方块
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cubeBlocks[i][j][k].FrontLeftTop.x = i  - 1.5f;
				cubeBlocks[i][j][k].FrontLeftTop.y = j - 0.5f;
				cubeBlocks[i][j][k].FrontLeftTop.z = k  - 0.5f;

				cubeBlocks[i][j][k].FrontRightTop.x = i - 0.5f;
				cubeBlocks[i][j][k].FrontRightTop.y = j  - 0.5f;
				cubeBlocks[i][j][k].FrontRightTop.z = k  - 0.5f;

				cubeBlocks[i][j][k].FrontLeftBottom.x = i  - 1.5f;
				cubeBlocks[i][j][k].FrontLeftBottom.y = j  - 1.5f;
				cubeBlocks[i][j][k].FrontLeftBottom.z = k  - 0.5f;

				cubeBlocks[i][j][k].FrontRightBottom.x = i  - 0.5f;
				cubeBlocks[i][j][k].FrontRightBottom.y = j  - 1.5f;
				cubeBlocks[i][j][k].FrontRightBottom.z = k  - 0.5f;

				cubeBlocks[i][j][k].BackLeftTop.x = i  - 1.5f;
				cubeBlocks[i][j][k].BackLeftTop.y = j  - 0.5f;
				cubeBlocks[i][j][k].BackLeftTop.z = k - 1.5f;

				cubeBlocks[i][j][k].BackRightTop.x = i  - 0.5f;
				cubeBlocks[i][j][k].BackRightTop.y = j  - 0.5f;
				cubeBlocks[i][j][k].BackRightTop.z = k  - 1.5f;

				cubeBlocks[i][j][k].BackLeftBottom.x = i - 1.5f;
				cubeBlocks[i][j][k].BackLeftBottom.y = j - 1.5f;
				cubeBlocks[i][j][k].BackLeftBottom.z = k - 1.5f;

				cubeBlocks[i][j][k].BackRightBottom.x = i - 0.5f;
				cubeBlocks[i][j][k].BackRightBottom.y = j  - 1.5f;
				cubeBlocks[i][j][k].BackRightBottom.z = k  - 1.5f;

				//

				cubeBlocks[i][j][k].FrontLeftTop.x *= 1.05f;
				cubeBlocks[i][j][k].FrontLeftTop.y *= 1.05f;
				cubeBlocks[i][j][k].FrontLeftTop.z *= 1.05f;

				cubeBlocks[i][j][k].FrontRightTop.x *= 1.05f;
				cubeBlocks[i][j][k].FrontRightTop.y *= 1.05f;
				cubeBlocks[i][j][k].FrontRightTop.z *= 1.05f;

				cubeBlocks[i][j][k].FrontLeftBottom.x *= 1.05f;
				cubeBlocks[i][j][k].FrontLeftBottom.y *= 1.05f;
				cubeBlocks[i][j][k].FrontLeftBottom.z *= 1.05f;

				cubeBlocks[i][j][k].FrontRightBottom.x *= 1.05f;
				cubeBlocks[i][j][k].FrontRightBottom.y *= 1.05f;
				cubeBlocks[i][j][k].FrontRightBottom.z *= 1.05f;

				cubeBlocks[i][j][k].BackLeftTop.x *= 1.05f;
				cubeBlocks[i][j][k].BackLeftTop.y *= 1.05f;
				cubeBlocks[i][j][k].BackLeftTop.z *= 1.05f;

				cubeBlocks[i][j][k].BackRightTop.x *= 1.05f;
				cubeBlocks[i][j][k].BackRightTop.y *= 1.05f;
				cubeBlocks[i][j][k].BackRightTop.z *= 1.05f;

				cubeBlocks[i][j][k].BackLeftBottom.x *= 1.05f;
				cubeBlocks[i][j][k].BackLeftBottom.y *= 1.05f;
				cubeBlocks[i][j][k].BackLeftBottom.z *= 1.05f;

				cubeBlocks[i][j][k].BackRightBottom.x *= 1.05f;
				cubeBlocks[i][j][k].BackRightBottom.y *= 1.05f;
				cubeBlocks[i][j][k].BackRightBottom.z *= 1.05f;
				if (k == 2)
				{
					cubeBlocks[i][j][k].front = RED;
				}
				else if (k == 0)
				{
					cubeBlocks[i][j][k].back = ORANGE;
				}
				if (i == 0)
				{
					cubeBlocks[i][j][k].left = BLUE;
				}
				else if (i == 2)
				{
					cubeBlocks[i][j][k].right = GREEN;
				}
				if (j == 2)
				{
					cubeBlocks[i][j][k].top = YELLOW;
				}
				else if (j == 0)
				{
					cubeBlocks[i][j][k].bottom = WHITE;
				}
			}
		}
	}
}

void drawCornerPoint(CornorPoint cp) {
	glVertex3f(cp.x, cp.y, cp.z);
}

// 绘制正方体
void drawBlock(Block block) {
	glBegin(GL_QUADS);

	// 前面
	setGlColor(block.front);
	drawCornerPoint(block.FrontLeftTop);
	drawCornerPoint(block.FrontRightTop);
	drawCornerPoint(block.FrontRightBottom);
	drawCornerPoint(block.FrontLeftBottom);

	// 后面
	setGlColor(block.back);
	drawCornerPoint(block.BackLeftTop);
	drawCornerPoint(block.BackRightTop);
	drawCornerPoint(block.BackRightBottom);
	drawCornerPoint(block.BackLeftBottom);

	// 左面
	setGlColor(block.left);
	drawCornerPoint(block.FrontLeftTop);
	drawCornerPoint(block.FrontLeftBottom);
	drawCornerPoint(block.BackLeftBottom);
	drawCornerPoint(block.BackLeftTop);

	// 右面
	setGlColor(block.right);
	drawCornerPoint(block.FrontRightTop);
	drawCornerPoint(block.FrontRightBottom);
	drawCornerPoint(block.BackRightBottom);
	drawCornerPoint(block.BackRightTop);

	// 顶面
	setGlColor(block.top);
	drawCornerPoint(block.FrontLeftTop);
	drawCornerPoint(block.FrontRightTop);
	drawCornerPoint(block.BackRightTop);
	drawCornerPoint(block.BackLeftTop);

	// 底面
	setGlColor(block.bottom);
	drawCornerPoint(block.FrontLeftBottom);
	drawCornerPoint(block.FrontRightBottom);
	drawCornerPoint(block.BackRightBottom);
	drawCornerPoint(block.BackLeftBottom);
	glEnd();
}

// 绘制函数
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//摄像机视角
	gluLookAt(
		0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	// 实现鼠标旋转的核心
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	Block testBlock;
	testBlock.back = RED;
	testBlock.front = ORANGE;
	testBlock.left = BLUE;
	testBlock.right = GREEN;
	testBlock.top = YELLOW;
	testBlock.bottom = WHITE;

	//drawBlock(testBlock);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				drawBlock(cubeBlocks[i][j][k]);
			}
		}
	}

	glFlush();
	glutSwapBuffers();
}

void resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 鼠标事件
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//设定旋转初始值
		mouseRightDown = true;
		xdiff = x - yrot;
		ydiff = y - xrot;
		//cout << "xdiff:" << xdiff << "\tydiff" << ydiff << endl;
	}
	else
		mouseRightDown = false;
}

// 鼠标移动事件
void mouseMotion(int x, int y) {
	if (mouseRightDown) {
		//鼠标滑动旋转
		yrot = x - xdiff;
		xrot = y - ydiff;
		//cout << "yrot:" << yrot << "\txrot" << xrot << endl;

		glutPostRedisplay();
	}
}

int main(int argc, char* argv[]) {
	cubeBlockInit();
	
	glutInit(&argc, argv);

	glutInitWindowPosition(400, 100);
	glutInitWindowSize(800, 800);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutCreateWindow("Magic Cube");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(resize);

	glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	glutMainLoop();
	return 0;
}


