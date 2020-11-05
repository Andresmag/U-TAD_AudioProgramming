#pragma once

#ifndef LITE
#include <litegfx.h>
#define LITE
#endif // !LITE

class Vec2;
class Sprite;
class Collider;

//-----------------
class AudioBuffer;
class AudioSource;
//-----------------

typedef void (*CallbackFunc)(Sprite&, float);

class Sprite
{
public:
	// Tipos de colisiones que pueden tener los sprite
	enum CollisionType
	{
		COLLISION_NONE,
		COLLISION_CIRCLE,
		COLLISION_RECT,
		COLLISION_PIXELS
	};

	// Num frames que tiene la imagen del sprite
	Sprite(const ltex_t* _tex, int _iHFrames = 1, int _iVFrames = 1);
	Sprite(const Sprite& _sValue);

	~Sprite();

	// Puntero a la funcion callback
	void setCallback(CallbackFunc _func);
	CallbackFunc getCallback() const;

	// Puntero generico a datos (datos del sprite que va a utilizar la funci�n callback)
	void* getUserData() const;
	void setUserData(void* _Data);

	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* _tex, int _iHFrames = 1, int _iVFrames = 1);

	lblend_t getBlend() const;
	void setBlend(lblend_t _bMode);

	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;
	void setColor(float _fR, float _fG, float _fB, float _fA);

	const Vec2& getPosition() const;
	void setPosition(const Vec2& _vPos);

	float getAngle() const;
	void setAngle(float _fAngle);

	const Vec2& getScale() const;
	void setScale(const Vec2& _vScale);

	// Tama�o de un frame multiplicado por la escala
	Vec2 getSize() const;

	// Valor para indicar el pivote de rotaxion en el pintado
	const Vec2& getPivot() const;
	void setPivot(const Vec2& _vPivot);

	int getHframes() const;
	int getVframes() const;

	// Veces por segundo que se cambia el frame de animacion
	int getFps() const;
	void setFps(int _iFPS);

	// Frame actual de animacion
	int getCurrentFrame() const;
	void setCurrentFrame(int _iFrame);

	void update(float _fDeltaTime);
	void draw() const;

	// Datos de colisiones
	void setCollisionType(CollisionType type);
	CollisionType getCollisionType() const;
	const Collider* getCollider() const;
	bool collides(const Sprite& other) const;

	void setTime(float time);
	float getTime() const;

	//--------------------
	void setAudioSource(AudioBuffer* buffer);
	AudioSource* getAudioSource() const;
	//--------------------

private:
	const ltex_t* m_texture;
	int m_iHFrames, m_iVFrames;
	float m_fRed, m_fGreen, m_fBlue, m_fAlpha;
	float m_fAngle;
	lblend_t m_blendMode;
	Vec2 m_vPosition, m_vScale, m_vPivot;
	int m_iFPS, m_iFrame;
	CallbackFunc m_func;
	void* m_userData;
	unsigned char* m_pPixels;
	CollisionType m_cType;
	Collider* m_pCollider;
	float m_fTime;

	//--------------------
	AudioSource* m_pSource;
	//--------------------
};