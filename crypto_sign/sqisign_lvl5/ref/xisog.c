#include "isog.h"
#include "ec.h"
#include <assert.h>

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

// Degree-2 isogeny with kernel generated by P != (0 ,0)
// Outputs the curve coefficient in the form A24=(A+2C:4C)
void
xisog_2(ec_kps2_t *kps, ec_point_t *B, const ec_point_t P)
{
    fp2_sqr(&B->x, &P.x);
    fp2_sqr(&B->z, &P.z);
    fp2_sub(&B->x, &B->z, &B->x);
    fp2_add(&kps->K.x, &P.x, &P.z);
    fp2_sub(&kps->K.z, &P.x, &P.z);
}

void
xisog_2_singular(ec_kps2_t *kps, ec_point_t *B24, ec_point_t A24)
{
    // No need to check the square root, only used for signing.
    fp2_t t0, four;
    fp2_set_small(&four, 4);
    fp2_add(&t0, &A24.x, &A24.x);
    fp2_sub(&t0, &t0, &A24.z);
    fp2_add(&t0, &t0, &t0);
    fp2_inv(&A24.z);
    fp2_mul(&t0, &t0, &A24.z);
    fp2_copy(&kps->K.x, &t0);
    fp2_add(&B24->x, &t0, &t0);
    fp2_sqr(&t0, &t0);
    fp2_sub(&t0, &t0, &four);
    fp2_sqrt(&t0);
    fp2_neg(&kps->K.z, &t0);
    fp2_add(&B24->z, &t0, &t0);
    fp2_add(&B24->x, &B24->x, &B24->z);
    fp2_add(&B24->z, &B24->z, &B24->z);
}

// Degree-4 isogeny with kernel generated by P such that [2]P != (0 ,0)
// Outputs the curve coefficient in the form A24=(A+2C:4C)
void
xisog_4(ec_kps4_t *kps, ec_point_t *B, const ec_point_t P)
{
    ec_point_t *K = kps->K;

    fp2_sqr(&K[0].x, &P.x);
    fp2_sqr(&K[0].z, &P.z);
    fp2_add(&K[1].x, &K[0].z, &K[0].x);
    fp2_sub(&K[1].z, &K[0].z, &K[0].x);
    fp2_mul(&B->x, &K[1].x, &K[1].z);
    fp2_sqr(&B->z, &K[0].z);

    // Constants for xeval_4
    fp2_add(&K[2].x, &P.x, &P.z);
    fp2_sub(&K[1].x, &P.x, &P.z);
    fp2_add(&K[0].x, &K[0].z, &K[0].z);
    fp2_add(&K[0].x, &K[0].x, &K[0].x);
}
