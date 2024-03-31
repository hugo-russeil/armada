#ifndef PARTICLESYSTEM_HPP
#define PARTICSYSTEM_HPP

#include "raylib.h"
#include "raymath.h"

#include <vector>


struct Particle {
    Vector2 position;
    Vector2 velocity;
    float lifetime;
};

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();
    std::vector<Particle> particles;
    float emissionRate;
    float maxLifetime;
    void Update();
    void Draw();
    void Emit(Vector2 position);
    void Explode(Vector2 position, int numParticles);
    
};

extern ParticleSystem* particleSystem;

#endif // PARTICLESYSTEM_HPP