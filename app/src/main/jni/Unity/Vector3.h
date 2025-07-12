#pragma once

struct Vector6{
	//这边重定义一个xzy形式的坐标(因为u3d是xzy);
	float x;
	float z;
	float y;

	Vector6() {
		this->x = 0;
		this->z = 0;
		this->y = 0;
	}

	Vector6(float x, float z, float y) {
		this->x = x;
		this->z = z;
		this->y = y;
	}

};