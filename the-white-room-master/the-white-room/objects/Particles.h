#include "LinkedList.h"
#include "GameObject.h"
#include "MeshLoader.h"

using namespace glm;

class Particle {
public:
    vec3 x, v, a;
    float m;//mass of this particle
    float time;
    int type;
};

class Force {
public:
    virtual void applyForce(Particle *p, float dt) = 0;
};

class SpringForce: public Force {
    //spring constant (ks), and damping constant (kd)
    float ks, kd;
    vec3 center;
    float restLength;

public:
    SpringForce(float KS, float KD, vec3 Center, float RestLength) {
        ks = KS;
        kd = KD;
        center = Center;
        restLength = RestLength;
    }
    void applyForce(Particle *p, float dt);
};

class ParticleSystem: public GameObject {
    LinkedList<Particle> p;
    float time;
    //how many particles are created per second
    int pps;
    int created;
    SpringForce *f;
    vec3 spawnPoint;

    void applyForces(Particle *p, float dt);
    void stepParticles(float dt);
    void addParticles(float dt);

public:
    void update(float dt, GameObject *playerCamera, vec3 camLookAt);
    void draw(vec3 cameraPos, vec3 lookAt, vec3 lightPos, vec3 lightColor,
            GameConstants *gc);
    void drawHighlight(vec3 camera, vec3 lookAt, vec3 lightPos, 
            vec3 lightColor, GameConstants *gc) { }
    std::string className();
    bool doesCollide(GameObject *other) { return false; }

    void onClick(SoundPlayer *soundPlayer) { return; }
    void onEvent(SoundPlayer *soundPlayer) { return; }
    void resetEvent(SoundPlayer *soundPlayer) { return; }

    vec3 getAABBmin() { return vec3(0.0); }
    vec3 getAABBmax() { return vec3(0.0); }

    ParticleSystem();

    virtual ~ParticleSystem();
};
