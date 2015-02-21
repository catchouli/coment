layout(local_size_x = 1) in;

layout(binding = 0) uniform sampler1D in_velocities;
layout(binding = 0, rgba32f) uniform image1D in_out_spheres;

layout(location = 0) uniform float delta_time;

void main()
{
    int sphereId = int(gl_GlobalInvocationID.x);

    vec4 spherePosition = imageLoad(in_out_spheres, sphereId);
    vec4 sphereVelocity = texelFetch(in_velocities, sphereId, 0);

    spherePosition += sphereVelocity * delta_time;

    imageStore(in_out_spheres, sphereId, spherePosition);
}
