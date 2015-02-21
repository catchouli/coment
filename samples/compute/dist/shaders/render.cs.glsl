layout (local_size_x = 32, local_size_y = 32) in;

layout(binding = 0, rgba32f) uniform writeonly image2D out_tex;
layout(binding = 0) uniform sampler1D in_spheres;

uniform vec3 eye_position;
uniform mat4 eye_rotation;

void main()
{
    // The pixel of the image we're writing
    ivec2 pix = ivec2(gl_GlobalInvocationID.xy);

    // The size of the image we're writing
    vec2 size = vec2(imageSize(out_tex));

    // The aspect ratio
    float aspect = size.x / size.y;

    // Normalised (-1..1) position of this pixel
    vec2 pix_normalised = pix / size * 2.0 - vec2(1.0, 1.0);

    // Construct ray
    vec3 ray_pos = eye_position;
    vec3 ray_dir = vec3(normalize(vec4(pix_normalised * vec2(1.0, 1.0 / aspect), -1.0, 0.0)) * eye_rotation);

    RaycastHit hit_info = traceSpheres(ray_pos, ray_dir, in_spheres);

    vec3 dir = ray_dir;

    // Colour of output pixel
    vec4 col = vec4(ray_dir, 0.0) * 0.4;

    if (hit_info.hit_t < INFINITY)
    {
        // Shade
        float dot = 0.8 * dot(hit_info.hit_normal, vec3(0.0, 0.0, 1.0));

        col += vec4(dot, dot, dot, 1.0);
    }

    //if (hit_info.hit_t < INFINITY)
    //{
    //    int rec = 0;
    //    while (rec < 5)
    //    {
    //        dir = reflect(dir, hit_info.hit_normal);
    //        RaycastHit hit = traceSpheres(hit_info.hit_pos, dir, in_spheres);
    //        if (hit.hit_t < INFINITY)
    //        {
    //            hit_info = hit;
    //            float dot = 0.8 * dot(hit_info.hit_normal, vec3(0.0, 0.0, 1.0));
    //            col += vec4(dot, dot, dot, 1.0);
    //        }
    //        else
    //        {
    //            break;
    //        }
    //        rec++;
    //    }
    //}

    // Store output colour
    imageStore(out_tex, pix, clamp(col, 0.0, 1.0));
}