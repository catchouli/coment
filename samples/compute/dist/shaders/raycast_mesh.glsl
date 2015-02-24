float intersectTriangle(vec3 orig, vec3 dir, vec3 vertices[3])
{
    vec3 u, v, n; // triangle vectors
    vec3 w0, w;  // ray vectors
    float r, a, b; // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    u = vertices[1] - vertices[0];
    v = vertices[2] - vertices[0];
    n = cross(u, v);

    w0 = orig - vertices[0];
    a = -dot(n, w0);
    b = dot(n, dir);
    if (abs(b) < 1e-5)
    {
        // ray is parallel to triangle plane, and thus can never intersect.
        return INFINITY;
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)
        return INFINITY; // ray goes away from triangle.

    vec3 I = orig + r * dir;
    float uu, uv, vv, wu, wv, D;
    uu = dot(u, u);
    uv = dot(u, v);
    vv = dot(v, v);
    w = I - vertices[0];
    wu = dot(w, u);
    wv = dot(w, v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)
        return INFINITY;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)
        return INFINITY;

    return (r > 1e-5) ? r : INFINITY;
}

vec3 interpolate(vec3 tri[3], vec3 vals[3], vec3 intersection)
{
    // Calculate barycentric coordinates
    float tri_area = 0.5f * length(cross(tri[1] - tri[0], tri[2] - tri[1]));
    float one_over_tri_area = 1.0f / tri_area;
    float u = 0.5f * one_over_tri_area * length(cross(tri[1] - intersection, tri[2] - intersection));
    float v = 0.5f * one_over_tri_area * length(cross(tri[0] - intersection, tri[2] - intersection));
    float w = 0.5f * one_over_tri_area * length(cross(tri[0] - intersection, tri[1] - intersection));

    // Interpolate value
    vec3 val = vals[0] * u + vals[1] * v + vals[2] * w;

    return val;
}

RaycastHit castMesh(vec3 ray_pos, vec3 ray_dir, sampler1D mesh, int polygon_count)
{
    // Trace ray
    RaycastHit hit_info;
    hit_info.hit_t = INFINITY;

    int hit_idx = -1;
    vec3 hit_tri[3], hit_normals[3];

    for (int i = 0; i < polygon_count; ++i)
    {
        // Load polygon (2 texels per vertex)
        // The vertices are packed (x, y, z, nx) (ny, nz, tx, ty)
        // Where x,y,z are position, nx,ny,nz are normal and tx,ty are texture coords
        vec4 vertices[] =
        {
            texelFetch(mesh, i * 6 + 0, 0),
            texelFetch(mesh, i * 6 + 1, 0),
            texelFetch(mesh, i * 6 + 2, 0),
            texelFetch(mesh, i * 6 + 3, 0),
            texelFetch(mesh, i * 6 + 4, 0),
            texelFetch(mesh, i * 6 + 5, 0)
        };

        // Unpack
        vec3 tri[3] =
        {
            vertices[0].xyz,
            vertices[2].xyz,
            vertices[4].xyz,
        };

        vec3 normals[3] =
        {
            vec3(vertices[0].w, vertices[1].x, vertices[1].y),
            vec3(vertices[2].w, vertices[3].x, vertices[3].y),
            vec3(vertices[4].w, vertices[5].x, vertices[5].y)
        };

        float hit_t = intersectTriangle(ray_pos, ray_dir, tri);

        if (hit_t < hit_info.hit_t)
        {
            hit_info.hit_t = hit_t;
            hit_idx = i;
            hit_tri = tri;
            hit_normals = normals;
        }
    }

    if (hit_idx >= 0)
    {
        hit_info.hit_pos = ray_pos + ray_dir * hit_info.hit_t;
        hit_info.hit_normal = interpolate(hit_tri, hit_normals, hit_info.hit_pos);
    }


    return hit_info;
}