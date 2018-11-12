#include "particle.h"
#include "algorithmparameters.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

Particle::Particle(size_t size)
	: size(size > 0 ? size : 8)
{
	currentState = new pbit[size];
	bestLocalState = new pbit[size];
	velocities = new float[size];

	setRandomState();
}

Particle::~Particle()
{
	if (currentState)
		delete[] currentState;
	if (bestLocalState)
		delete[] bestLocalState;
	if (velocities)
		delete[] velocities;
}

void Particle::printCurrentState()
{
	for (size_t i = 0; i < size; ++i)
		std::cout << static_cast<int>(currentState[i]);
	std::cout << std::endl;
}

void Particle::setRandomState()
{
	for (size_t i = 0; i < size; ++i)
		currentState[i] = static_cast<pbit>(rand() % 2);
}

void Particle::updateBestLocalState()
{
	for (size_t i = 0; i < size; ++i)
		bestLocalState[i] = currentState[i];
}


Particle & Particle::operator=(Particle && particle)
{
	if (this != &particle && size == particle.size)
	{
		if (currentState)
			delete[] currentState;
		if (bestLocalState)
			delete[] bestLocalState;
		if (velocities)
			delete[] velocities;

		currentState = particle.currentState;
		bestLocalState = particle.bestLocalState;
		velocities = particle.velocities;
		bestGlobalState = particle.bestGlobalState;

		particle.currentState = nullptr;
		particle.bestLocalState = nullptr;
		particle.velocities = nullptr;

	}
	return *this;
}

void Particle::updateParticle()
{
	float alpha = AlgorithmParameters::getAlgorithmParameters().getAlpha();
	float beta = AlgorithmParameters::getAlgorithmParameters().getBeta();
	float velocitySigmoid = 0.f;

	for (size_t i = 0; i < size; ++i)
	{
		// update velocity
		// need reimplementation!!!
		velocities[i] += alpha * (bestLocalState[i] - currentState[i]) + beta * (bestGlobalState[i] - currentState[i]);

		// update particle component - should be HERE or below this scope??
		velocitySigmoid = 1 / (1 + exp(-velocities[i]));
		currentState[i] = ((static_cast<float>(rand()) / RAND_MAX) < velocitySigmoid) ? 1 : 0;
	}

	//			if (f(xi) < f(pi)
	//				update particle's best known position pi <-- xi
	//				if (f(pi) < f(g))
	//					update best known global position g <-- pi
}

