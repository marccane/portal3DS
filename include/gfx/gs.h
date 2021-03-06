#ifndef GS_H
#define GS_H

#include <3ds.h>
#include "utils/math.h"

#define GS_MATRIXSTACK_SIZE (8)

#define RGBA8(r,g,b,a) ((((r)&0xFF)<<24) | (((g)&0xFF)<<16) | (((b)&0xFF)<<8) | (((a)&0xFF)<<0))

typedef enum
{
	GS_PROJECTION = 0,
	GS_MODELVIEW = 1,
	GS_MATRIXTYPES
}GS_MATRIX;

typedef struct
{
	u8* data;
	u32 currentSize; // in bytes
	u32 maxSize; // in bytes
	u32 numVertices;
	u32* commands;
	u32 commandsSize;
}gsVbo_s;

typedef void (*gsRenderModeCallback)(void);

typedef struct
{
	gsRenderModeCallback init;
	gsRenderModeCallback exit;
	bool used;
}gsRenderMode_s;

typedef void (*gsCallback)(u32* outBuffer, u32* outDepthBuffer);

void gsInit(shaderProgram_s* shader, gsCallback drawTop, gsCallback drawBottom);
void gsDrawFrame();
void gsExit(void);

int gsRegisterRenderMode(gsRenderModeCallback init, gsRenderModeCallback exit);
void gsUnregisterRenderMode(int mode);
void gsSwitchRenderMode(int mode);

void gsSetShader(shaderProgram_s* shader);
void gsSetBackgroundColor(u32 color);

void gsStartFrame(void);
void gsAdjustBufferMatrices(mtx44 transformation);

void* gsLinearAlloc(size_t size);
void gsLinearFree(void* mem);

float* gsGetMatrix(GS_MATRIX m);
int gsLoadMatrix(GS_MATRIX m, float* data);
int gsPushMatrix();
int gsPopMatrix();
int gsMatrixMode(GS_MATRIX m);
void gsInvalidateMatrixStack();
int gsUpdateTransformation();

void gsLoadIdentity();
void gsProjectionMatrix(float fovy, float aspect, float near, float far);
void gsRotateX(float x);
void gsRotateY(float y);
void gsRotateZ(float z);
void gsScale(float x, float y, float z);
void gsTranslate(float x, float y, float z);
int gsMultMatrix(float* data);
int gsMultMatrix3(float* data);

int gsVboInit(gsVbo_s* vbo);
int gsVboCreate(gsVbo_s* vbo, u32 size);
int gsVboFlushData(gsVbo_s* vbo);
int gsVboDestroy(gsVbo_s* vbo);
int gsVboDraw(gsVbo_s* vbo);
void* gsVboGetOffset(gsVbo_s* vbo);
int gsVboAddData(gsVbo_s* vbo, void* data, u32 size, u32 units);

#endif
