#include "Particles.h"

using namespace glm;

void ParticleSystem::update(float dt, GameObject *playerCamera,
        vec3 camLookAt) {
    stepParticles(dt);
    addParticles(dt);
}

void ParticleSystem::stepParticles(float dt) {
    Particle *curr;
    p.reset();

    while (p.hasNext()) {
        curr = p.getNext();
        if (curr->time > 1.0) {
            p.remove();
            continue;
        }

        applyForces(curr, dt);
        curr->time += dt;
    }
}

void ParticleSystem::addParticles(float dt) {
    int i = ceil(pps * dt);
    created += i;
    time += dt;
    double rand1, rand2;
    Particle *add;

    /*if (time >= 1.0) {
        i = pps - created;
        if (i < 0) {i = 0;}

        time = 0.0;
        created = 0;
        printf("got here\n");
    }*/

    for (int a = 0; a < i; a++) {
        add = new Particle();
        rand1 = (rand() % 200 - 100.0) / 1000.0;
        rand2 = (rand() % 200 - 100.0) / 1000.0;
        add->x = spawnPoint;
        add->x.x += rand1;
        add->x.y -= 0.1;
        add->x.z += rand2;

        add->v = vec3(rand1, 1.4, rand2);
        add->time = 0.0;
        add->type = rand() % 10;
        add->a = vec3(0.0);
        add->m = 0.1;

        p.add(add);
    }
}

void ParticleSystem::applyForces(Particle *p, float dt) {
    f->applyForce(p, dt);
}

void SpringForce::applyForce(Particle *p, float dt) {
    if (p->type > 2) {
        vec3 force = -(ks * (length(p->x - center) - restLength) +
                kd * dot((p->x - center) / length(p->x - center),
                p->v))*(p->x - center) / length(p->x - center);

        force.x += (rand() % 50 - 25.0) / 20.0;
        force.z += (rand() % 50 - 25.0) / 20.0;

        force.y += 1.4 / length(p->v) + (rand() % 50 - 35) / 20.0;

        p->a = force / p->m;
        p->x += p->a * (dt * dt / 2.f) + p->v * dt;
        p->v += p->a * dt * 0.6f;
    } else {
        vec3 force = vec3((rand() % 200 - 100.0) / 50.0, 1.0,
                (rand() % 200 - 100.0) / 50.0);
        force.y = 1.0 / length(p->v);
        p->a = force / p->m;
        p->x += p->a * (dt * dt / 2.f) + p->v * dt;
        p->v += p->a * dt * 0.6f;
    }
}

std::string ParticleSystem::className() {
    return "ParticleSystem";
}

ParticleSystem::ParticleSystem() {
    printf("got here1\n");
    MeshLoader::loadVertexBufferObjectFromMesh(
            "objects/meshes/particles/Billboard.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    printf("got here2\n");

    shininess = 2.0f;
    specStrength = 1.0f;
    ambColor = vec3(0.f);
    diffColor = vec3(0.f);
    specColor = vec3(0.f);
    ambAlpha = diffAlpha = specAlpha = 1.f;
    isClicked = false;

    glGenTextures(1, &texNum);
    printOpenGLError();
    Load32NonMipmap((char *) "objects/meshes/particles/flame.bmp", texNum);
    printOpenGLError();
    hasTex = true;

    pps = 520;
    f = new SpringForce(0.6, 0.3,
            vec3(0.1, getRoomFloorHeight().y + 0.4, -ROOM_SIZE + 0.5), 3.0);
    spawnPoint = vec3(0.1, getRoomFloorHeight().y + 0.4,
            -ROOM_SIZE + 0.5);

}

//need camera for billboarding

void ParticleSystem::draw(vec3 cameraPos, vec3 lookAt, vec3 lightPos,
        vec3 lightColor, GameConstants *gc) {
    if (VBO == -1 || IBO == -1 || IBOlen <= 0 || NBO == -1) {
        return;
    }

    // glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    printOpenGLError();
    glUseProgram(gc->shader);
    printOpenGLError();
    //TODO Set matrix stuff
    glm::mat4 projection = glm::perspective(80.0f, gc->aspectRatio, 0.1f, 100.f);
    safe_glUniformMatrix4fv(gc->h_uProjMatrix, glm::value_ptr(projection));

    glm::mat4 view = glm::lookAt(cameraPos, lookAt, glm::vec3(0.f, 1.f, 0.f));
    safe_glUniformMatrix4fv(gc->h_uViewMatrix, glm::value_ptr(view));


    //Do transformations
    safe_glEnableVertexAttribArray(gc->h_aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    safe_glVertexAttribPointer(gc->h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    safe_glEnableVertexAttribArray(gc->h_aNormal);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    safe_glVertexAttribPointer(gc->h_aNormal, 3, GL_FLOAT, GL_TRUE, 0, 0);

    glUniform3f(gc->h_uCamTrans, cameraPos.x, cameraPos.y, cameraPos.z);

    if (hasTex) {
        printOpenGLError();
        glEnable(GL_TEXTURE_2D);
        printOpenGLError();
        safe_glUniform1i(gc->h_uTexUnit, 0);
        printOpenGLError();
        safe_glEnableVertexAttribArray(gc->h_aTexCoord);
        printOpenGLError();
        glBindBuffer(GL_ARRAY_BUFFER, TBO);
        printOpenGLError();
        safe_glVertexAttribPointer(
                gc->h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
        printOpenGLError();
        glActiveTexture(GL_TEXTURE0);
        printOpenGLError();
        glBindTexture(GL_TEXTURE_2D, texNum);
        printOpenGLError();
        glDisable(GL_TEXTURE_2D);
    }
    printOpenGLError();
    safe_glUniform1i(gc->h_uUseTex, 2);
    printOpenGLError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glUniform4f(gc->h_uAmbColor, ambColor.x, ambColor.y, ambColor.z,
            ambAlpha);
    glUniform4f(gc->h_uSpecColor, ambColor.x, ambColor.y, ambColor.z,
            ambAlpha);
    glUniform4f(gc->h_uDiffColor, ambColor.x, ambColor.y, ambColor.z,
            ambAlpha);

    glUniform3f(gc->h_uLightPos, lightPos.x, lightPos.y, lightPos.z);
    glUniform4f(gc->h_uLightColor, lightColor.x, lightColor.y, lightColor.z,
            gc->lightAlpha);

    float rotY, rotA;
    this->rotate = mat4(1.0f);
    vec3 up = vec3(0.f, 1.f, 0.f);
    vec3 loc = cameraPos - spawnPoint;
    vec3 axis = cross(up, loc);

    if (loc.z == 0 && loc.x == 0) {
        rotY = 0;
    } else rotY = atan2(loc.x, loc.z) * 180.0 / 3.1415926 - 90.0;

    rotA = 90 - asin(length(axis) / length(loc)) * 180.0 / 3.141592653;
    if (loc.y > 0) {
        rotA = -rotA;
    }

    doRotate(axis, rotA);
    doRotate(up, rotY);
    doRotate(up, 180);



    //start drawParticleLoop
    Particle *cur;
    mat4 scaleMat = glm::scale(mat4(), vec3(0.5f));
    p.reset();

    while (p.hasNext()) {
        cur = p.getNext();
        mat4 transMat = translate(glm::mat4(), cur->x);


        glm::mat4 model = transMat * rotate * scaleMat;
        safe_glUniformMatrix4fv(gc->h_uModelMatrix, glm::value_ptr(model));
        safe_glUniformMatrix4fv(gc->h_uNormalMatrix,
                glm::value_ptr(glm::transpose(glm::inverse(model))));
        printOpenGLError();
        //end drawParticleLoop

        float rotY, rotA;
        this->rotate = mat4(1.0f);
        vec3 up = vec3(0.f, 1.f, 0.f);
        vec3 loc = cameraPos - cur->x;
        vec3 axis = cross(up, loc);

        if (loc.z == 0 && loc.x == 0) {
            rotY = 0;
        } else rotY = atan2(loc.x, loc.z) * 180.0 / 3.1415926 - 90.0;

        rotA = 90 - asin(length(axis) / length(loc)) * 180.0 / 3.141592653;
        if (loc.y > 0) {
            rotA = -rotA;
        }

        doRotate(axis, rotA);
        doRotate(up, rotY);
        doRotate(up, 180);


        glDrawElements(GL_TRIANGLES, IBOlen, GL_UNSIGNED_SHORT, 0);
    }

    safe_glDisableVertexAttribArray(gc->h_aNormal);
    safe_glDisableVertexAttribArray(gc->h_aPosition);
    safe_glDisableVertexAttribArray(gc->h_aTexCoord);
    glUseProgram(0);

    //glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
}

ParticleSystem::~ParticleSystem() {
    if (!(p.isEmpty())) {
        p.reset();

        while (p.hasNext()) {
            Particle *cur = p.getNext();
            p.remove();
            //delete cur;
        }
    }
    delete f;
}