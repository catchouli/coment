layout (local_size_x = 32, local_size_y = 32) in;

layout(binding = 0, rgba32f) uniform writeonly image2D out_tex;
layout(binding = 0) uniform sampler1D in_spheres;
layout(binding = 1) uniform sampler1D in_mesh;

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

    // Trace spheres
    RaycastHit sphere_hit_info = castSpheres(ray_pos, ray_dir, in_spheres);

    // Trace mesh
    int polygon_count = textureSize(in_mesh, 0) / 3;
    RaycastHit polygon_hit_info = castMesh(ray_pos, ray_dir, in_mesh, polygon_count);

    // Get closest hit
    RaycastHit hit_info;

    if (polygon_hit_info.hit_t < sphere_hit_info.hit_t)
        hit_info = polygon_hit_info;
    else
        hit_info = sphere_hit_info;

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