//
// Retro graphics library
//
// Author: Johan Gardhage <johan.gardhage@gmail.com>
//

#ifndef _RETROCAMERA_H_
#define _RETROCAMERA_H_

#include <math.h> // cos, sin, fabs, M_PI

typedef float vec3_t[3];

#define CAMERA_TURN_SPEED        3.0
#define CAMERA_PITCH_SPEED       1.0
#define CAMERA_MOUSE_SENSITIVITY 0.3

struct RETRO_Camera
{
	vec3_t head;    // Position of eye
	vec3_t view;    // Forward (look) vector
	vec3_t up;      // Up vector (Quake is Z-up)

	float yaw;              // Direction of travel (degrees)
	float pitch;            // Neck angle (degrees)
	float speed;            // Accumulated speed along heading
	float strafe;           // Accumulated speed sideways
	float movementSpeed;    // Movement increment per key tick

	RETRO_Camera()
	{
		head[0] = 0.0f;
		head[1] = 0.0f;
		head[2] = 0.0f;
		yaw = 0;
		pitch = 0;
		speed = 0;
		strafe = 0;
		movementSpeed = 1.0f;
		up[0] = 0.0f;
		up[1] = 0.0f;
		up[2] = 1.0f;
	}

	void SetPosition(float x, float y, float z)
	{
		head[0] = x;
		head[1] = y;
		head[2] = z;
	}

	void SetYaw(float degrees)
	{
		yaw = degrees;
	}

	void SetPitch(float degrees)
	{
		pitch = degrees;
	}

	void SetMovementSpeed(float s)
	{
		movementSpeed = s;
	}

	//
	// Update the camera position and view vector
	//
	void UpdatePosition(void)
	{
		// Move the camera forward
		if ((fabs(speed) > 0)) {
			head[0] += speed * cos(yaw * M_PI / 180.0);
			head[1] += speed * sin(yaw * M_PI / 180.0);
			head[2] += speed * sin(pitch * M_PI / 180.0);
		}

		// Move the camera sideways
		if ((fabs(strafe) > 0)) {
			head[0] += strafe * sin(yaw * M_PI / 180.0);
			head[1] -= strafe * cos(yaw * M_PI / 180.0);
		}

		// Setup the view vector
		view[0] = cos(yaw * M_PI / 180.0);
		view[1] = sin(yaw * M_PI / 180.0);
		view[2] = sin(pitch * M_PI / 180.0);

		// Reset speed
		speed = 0;
		strafe = 0;
	}

	void Pitch(float degrees)
	{
		pitch -= degrees * CAMERA_MOUSE_SENSITIVITY;
		if (pitch > 90.0f) {
			pitch = 90.0f;
		} else if (pitch < -90.0f) {
			pitch = -90.0f;
		}
	}

	void Yaw(float degrees)
	{
		yaw -= degrees * CAMERA_MOUSE_SENSITIVITY;
		if (yaw < 0.0f) {
			yaw += 360.0f;
		} else if (yaw > 360.0f) {
			yaw -= 360.0f;
		}
	}

	void PitchUp(float scale = 1.0f)
	{
		if (pitch < 90.0f) {
			pitch += CAMERA_PITCH_SPEED * scale;
		}
	}

	void PitchDown(float scale = 1.0f)
	{
		if (pitch > -90.0f) {
			pitch -= CAMERA_PITCH_SPEED * scale;
		}
	}

	void MoveForward(float scale = 1.0f)
	{
		speed += movementSpeed * scale;
	}

	void MoveBackward(float scale = 1.0f)
	{
		speed -= movementSpeed * scale;
	}

	void TurnRight(float scale = 1.0f)
	{
		yaw -= CAMERA_TURN_SPEED * scale;
		if (yaw < 0.0f) {
			yaw += 360.0f;
		}
	}

	void TurnLeft(float scale = 1.0f)
	{
		yaw += CAMERA_TURN_SPEED * scale;
		if (yaw >= 360.0f) {
			yaw -= 360.0f;
		}
	}

	void StrafeRight(float scale = 1.0f)
	{
		strafe += movementSpeed * scale;
	}

	void StrafeLeft(float scale = 1.0f)
	{
		strafe -= movementSpeed * scale;
	}
};

#endif
