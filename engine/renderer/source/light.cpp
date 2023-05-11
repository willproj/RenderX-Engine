#include "include/light.h"


namespace engine::renderer
{
	Light::Light()
		:intensity(1.0f),radius(1.0f),color(glm::vec3(1.0f))
	{

	}

	Light::Light(float intensity, float radius, const glm::vec3& color)
	{
		this->intensity = intensity;
		this->radius = radius;
		this->color = color;	
	}

	Light::~Light()
	{

	}

	float Light::getIntensity()const
	{
		return intensity;
	}

	float Light::getRadius()const
	{
		return radius;
	}

	const glm::vec3& Light::getColor()const
	{
		return color;
	}

	void Light::setIntensity(float intensity)
	{
		this->intensity = intensity;
	}

	void Light::setRadius(float radius)
	{
		this->radius = radius;
	}

	void Light::setColor(const glm::vec3& color)
	{
		this->color = color;
	}

}