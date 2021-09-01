typedef struct
{
    float m;    // 质量
    float *x;   // 位置向量
    float *v;   // 速度向量
    float *f;   // 合力
}*Particle;

typedef struct 
{
    Particle *p;
    int n;
    float t;
}*ParticleSystem;

/* length of state derivative, and force vector */
int ParticleDims(ParticleSystem p)
{
    return (6 * p->n);
}

/* gather state from the particles into dst */
int ParticleGetState(ParticleSystem p, float *dst)
{
    int i;
    for(i = 0; i < p->n; i++)
    {
        *(dst++) = p->p[i]->x[0];
        *(dst++) = p->p[i]->x[1];
        *(dst++) = p->p[i]->x[2];
        *(dst++) = p->p[i]->v[0];
        *(dst++) = p->p[i]->v[1];
        *(dst++) = p->p[i]->v[2];
    }
}

/* scatter state from src into the particles*/
int ParticleSetState(ParticleSystem p, float *src)
{
    int i;
    for(i = 0; i < p->n; i++)
    {
        p->p[i]->x[0] = *(src++);
        p->p[i]->x[1] = *(src++);
        p->p[i]->x[2] = *(src++);
        p->p[i]->v[0] = *(src++);
        p->p[i]->v[1] = *(src++);
        p->p[i]->v[2] = *(src++);
    }
}

/* calculate derivative, place in dst */
int ParticleDerivative(ParticleSystem p, float *dst)
{
    int i;
    Clear_Forces(p);
    Compute_Forces(p);
    for(i = 0; i < p->n; i++)
    {
        *(dst++) = p->p[i]->v[0];
        *(dst++) = p->p[i]->v[1];
        *(dst++) = p->p[i]->v[2];
        *(dst++) = p->p[i]->f[0];
        *(dst++) = p->p[i]->f[1];
        *(dst++) = p->p[i]->f[2]/;
    }
}