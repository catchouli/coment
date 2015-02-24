layout(local_size_x = 1) in;

layout(binding = 0, rgba32f) uniform image1D in_out_spheres;
layout(binding = 1, rgba32f) uniform image1D in_out_velocities;

layout(location = 0) uniform float delta_time;

void main()
{
    int sphereIdA = int(gl_GlobalInvocationID.x);
    int sphereIdB = int(gl_GlobalInvocationID.y);

    vec4 sphereA = imageLoad(in_out_spheres, sphereIdA);
    vec4 sphereB = imageLoad(in_out_spheres, sphereIdB);

    vec4 velocityA = imageLoad(in_out_velocities, sphereIdA);
    vec4 velocityB = imageLoad(in_out_velocities, sphereIdB);

    if (sphereIdA != sphereIdB)
    {
        const float G = 1000.0;

        vec4 diff = vec4(vec3(sphereA - sphereB), 0.0);
        vec4 dir = normalize(diff);
        float dist = length(diff);

        // Resolve intersections
        float rad_combined = sphereA.w + sphereB.w;

        if (dist < rad_combined)
        {
            float penetration = rad_combined - dist;
            sphereA += 0.1 * dir * penetration * 0.5f;
        }

        // Calculate gravity
        float F = G * ((sphereA.w * sphereB.w) / (dist * dist));
        float a_magnitude = F / sphereA.w;
        vec4 a_diff = dir * -a_magnitude;

        velocityA += a_diff * delta_time;

        // Write back values
        imageStore(in_out_spheres, sphereIdA, sphereA);
        imageStore(in_out_velocities, sphereIdA, velocityA);
    }
}
