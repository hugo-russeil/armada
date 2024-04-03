#include "particleSystem.h"

ParticleSystem::ParticleSystem() {
    emissionRate = 1.0f;
    maxLifetime = 2.0f;
}

ParticleSystem::~ParticleSystem() = default;

void ParticleSystem::Explode(Vector2 position, int numParticles) {
    for (int i = 0; i < numParticles; i++) {
        Emit(position);
    }
}

void ParticleSystem::Emit(Vector2 position) {
    Particle particle;
    particle.position = position;
    particle.velocity = { (float)(GetRandomValue(-20, 20) / 200.0), (float)(GetRandomValue(-20, 20) / 100.0) };
    particle.lifetime = GetRandomValue(0.5f, maxLifetime);
    particles.push_back(particle);
}

void ParticleSystem::Update() {
    for (int i = 0; i < particles.size(); i++) {
        particles[i].position = Vector2Add(particles[i].position, particles[i].velocity);
        particles[i].lifetime -= GetFrameTime();
        if (particles[i].lifetime <= 0) {
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}

void ParticleSystem::Draw() {
    for (Particle& particle : particles) {
        DrawPoly(particle.position, 4, 1, 45, ORANGE);
    }
}