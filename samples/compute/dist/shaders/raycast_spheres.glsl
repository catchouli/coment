RaycastHit traceSpheres(vec3 ray_pos, vec3 ray_dir, sampler1D spheres)
{
    // Trace ray
    RaycastHit hit_info;
    hit_info.hit_t = INFINITY;

    float sphere_count = textureSize(spheres, 0);

    for (int i = 0; i < sphere_count; ++i)
    {
        vec4 sphere = texelFetch(spheres, i, 0);

        const vec3 pos = sphere.xyz;
        const float radius = sphere.w;

        const float radius_sqr = radius * radius;

        float t0, t1;

        vec3 l = pos - ray_pos;

        float tca = dot(l, ray_dir);
        if (tca > 0)
        {
            float d2 = dot(l, l) - tca * tca;

            if (d2 < radius_sqr)
            {
                float thc = sqrt(radius_sqr - d2);
                t0 = tca - thc;
                t1 = tca + thc;

                if (t0 < hit_info.hit_t)
                {
                    hit_info.hit_t = t0;
                    hit_info.hit_idx = i;
                    hit_info.hit_pos = ray_pos + ray_dir * hit_info.hit_t;
                    hit_info.hit_normal = normalize(hit_info.hit_pos - pos);
                }
            }
        }
    }

    return hit_info;
}