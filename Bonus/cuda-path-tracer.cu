#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <curand_kernel.h>

#include <cstdio>
#include <algorithm>
#include <climits>
#include <chrono>

#include "helper_math.h"

#define SPP 65536
#define DEPTH 8
#define WIDTH 800
#define HEIGHT 600
#define SPHERE_EPSILON 0.0001f
#define BOX_EPSILON 0.001f
#define RAY_EPSILON 0.05f
#define M_PI 3.1415925

//main source used: 
//http://www.kevinbeason.com/smallpt/
//http://raytracey.blogspot.com/2015/10/gpu-path-tracing-tutorial-1-drawing.html

struct Ray
{
    __device__ Ray(float3 origin, float3 direction) :
        origin(origin), direction(direction) {}

    float3 origin;
    float3 direction;
};

enum Material { DIFFUSE, SPECULAR, REFRACTIVE };

struct Sphere
{
    float radius;
    float3 position, emissionColor, mainColor;
    Material material;
    __device__ float intersect(const Ray& ray) const
    {
        float t;
        float3 dis = position - ray.origin;
        float proj = dot(dis, ray.direction);
        float delta = proj * proj - dot(dis, dis) + radius * radius;
        if (delta < 0) return 0;
        delta = sqrtf(delta);
        return (t = proj - delta) > SPHERE_EPSILON ? t : ((t = proj + delta) > SPHERE_EPSILON ? t : 0);
    }
};
//https://github.com/matt77hias/cu-smallpt/blob/master/cu-smallpt/cu-smallpt/src/kernel.cu
__constant__ Sphere spheres[] =
{

    //{ 1e5f, { -1e5f - 50.0f, 40.0f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.25f, 0.25f }, Material::DIFFUSE }, // Left 
    //{ 1e5f, { 1e5f + 50.0f, 40.0f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.25f, 0.25f, 0.75f }, Material::DIFFUSE }, // Right 
    //{ 1e5f, { 0.0f, 40.0f, -1e5f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.75f, 0.75f }, Material::DIFFUSE }, // Back 
    //{ 1e5f, { 0.0f, 40.0f, 1e5f + 600.0f }, { 0.0f, 0.0f, 0.0f }, { 1.00f, 1.00f, 1.00f }, Material::DIFFUSE }, // Front 
    //{ 1e5f, { 0.0f, -1e5f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.75f, 0.75f }, Material::DIFFUSE }, // Bottom 
    //{ 1e5f, { 0.0f, 1e5f + 80.0f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.75f, 0.75f }, Material::DIFFUSE }, // Top 
    //{ 16.0f, { -25.0f, 16.0f, 47.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 2.0f }, Material::REFRACTIVE }, // left sphere 
    //{ 20.0f, { 25.0f, 20.0f, 78.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, Material::SPECULAR }, // right sphere
    ////{ 5.0f, { 35.0f, 74.0f, 40.0f }, { 5.6f, 5.6f, 5.6f }, { 0.0f, 0.0f, 0.0f }, Material::DIFFUSE }  // Light
    //{ 600.0f, { 0.0f, 678.8f, 80.0f }, { 1.6f, 1.6f, 1.6f }, { 0.0f, 0.0f, 0.0f }, Material::DIFFUSE }  // Light

    //{ 1e5f, { -1e5f - 50.0f, 40.0f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.6f, 0.2f, 0.2f }, Material::DIFFUSE }, // Left 
    //{ 1e5f, { 1e5f + 50.0f, 40.0f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.2f, 0.2f, 0.6f }, Material::DIFFUSE }, // Right 
    //{ 1e5f, { 0.0f, 40.0f, -1e5f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.75f, 0.75f }, Material::DIFFUSE }, // Back 
    //{ 1e5f, { 0.0f, 40.0f, 1e5f + 600.0f }, { 0.0f, 0.0f, 0.0f }, { 1.00f, 1.00f, 1.00f }, Material::DIFFUSE }, // Front 
    //{ 1e5f, { 0.0f, -1e5f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.75f, 0.75f }, Material::DIFFUSE }, // Bottom 
    //{ 1e5f, { 0.0f, 1e5f + 80.0f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.75f, 0.75f }, Material::DIFFUSE }, // Top \
    ////sphere
    //{ 12.0f, { -30.0f, 12.0f, 88.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, Material::REFRACTIVE },
    //{ 15.0f, { 25.0f, 15.0f, 47.0f }, { 0.0f, 0.0f, 0.0f }, { 0.65f, 0.65f, 0.65f }, Material::SPECULAR }, 
    //{ 8.0f, { 10.0f, 8.0f, 130.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, Material::REFRACTIVE },
    //{ 12.0f, { 25.0f, 12.0f, 180.0f }, { 0.0f, 0.0f, 0.0f }, { 0.3f, 0.8f, 0.3f }, Material::DIFFUSE }, 
    //{ 10.0f, { -15.0f, 10.0f, 200.0f }, { 0.0f, 0.0f, 0.0f }, { 0.2f, 0.9f, 0.9f }, Material::SPECULAR }, 
    //{ 6.0f, { 0.0f, 6.0f, 230.0f }, { 0.0f, 0.0f, 0.0f }, { 0.9f, 0.9f, 0.2f }, Material::REFRACTIVE },

    ////light
    //{ 5.0f, { 35.0f, 74.0f, 40.0f }, { 15.6f, 15.6f, 15.6f }, { 0.0f, 0.0f, 0.0f }, Material::DIFFUSE }, 
    //{ 5.0f, { 35.0f, 74.0f, 140.0f }, { 15.6f, 15.6f, 15.6f }, { 0.0f, 0.0f, 0.0f }, Material::DIFFUSE },
    //{ 5.0f, { 35.0f, 74.0f, 240.0f }, { 15.6f, 15.6f, 15.6f }, { 0.0f, 0.0f, 0.0f }, Material::DIFFUSE }, 
    //{ 5.0f, { 35.0f, 74.0f, 340.0f }, { 15.6f, 15.6f, 15.6f }, { 0.0f, 0.0f, 0.0f }, Material::DIFFUSE }, 
    
    
    { 1e5f, { 0.0f, -1e5f, 80.0f }, { 0.0f, 0.0f, 0.0f }, { 0.3f, 0.3f, 0.3f }, Material::DIFFUSE },// ground
    { 4e4f, { 0.0f, -4e4f-30, -3000.0f }, { 0.0f, 0.0f, 0.0f }, { 0.2f, 0.2f, 0.2f }, Material::DIFFUSE },// mountain
    { 110000.0f, { 0.0f, -110050.0f, 80.0f }, { 3.6f, 2.0f, 00.2f }, { 0.0f, 0.0f, 0.0f }, Material::DIFFUSE }, //horizon
    {1600.0f, {2000.0f, 200.0f, 8000.0f }, {37.44f, 33.696f, 29.952f} , { 0.0f, 0.0f, 0.0f }, DIFFUSE},// sun
    {1560.0f, {2000.0f, 200.0f, 8000.0f }, {150.0f, 75.0f, 7.488f} , { 0.0f, 0.0f, 0.0f }, DIFFUSE},//sun
    {10000.0f, {0.0f, 0.0f, -1060.0f}, {0.000306f, 0.01f, 0.1388315664f}, {0.175f, 0.175f , 0.25f},  DIFFUSE}, // sky

    //sphere
    
    /*{ 18.0f, { -30.0f, 18.0f, -42.0f }, { 0.0f, 0.0f, 0.0f }, { 0.8f, 0.8f, 0.8f }, Material::REFRACTIVE },
    { 25.0f, { 25.0f, 25.0f, -83.0f }, { 0.0f, 0.0f, 0.0f }, { 0.65f, 0.65f, 0.65f }, Material::SPECULAR }, 
    { 8.0f, { 10.0f, 8.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.92f, 0.92f, 0.92f }, Material::REFRACTIVE },
    { 12.0f, { 25.0f, 12.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, { 0.2f, 0.2f, 0.6f }, Material::REFRACTIVE },
    { 10.0f, { -15.0f, 10.0f, 70.0f }, { 0.0f, 0.0f, 0.0f }, { 0.2f, 0.9f, 0.9f }, Material::SPECULAR }, 
    { 6.0f, { 0.0f, 6.0f, 90.0f }, { 0.0f, 0.0f, 0.0f }, { 0.8f, 0.8f, 0.2f }, Material::REFRACTIVE },*/
    { 18.0f, { -30.0f, 18.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.2f, 0.2f, 0.6f }, Material::REFRACTIVE },
    { 25.0f, { 25.0f, 25.0f, -20.0f }, { 0.0f, 0.0f, 0.0f }, { 0.65f, 0.65f, 0.65f }, Material::SPECULAR },
    { 12.0f, { -10.0f, 12.0f, 60.0f }, { 0.0f, 0.0f, 0.0f }, { 0.7f, 0.7f, 0.7f }, Material::REFRACTIVE },

    //{1600.0f, {3000.0f, 0.0f, 6000.0f }, {37.44f, 33.696f, 29.952f} , { 0.0f, 0.0f, 0.0f }, DIFFUSE}, //sun
    //{10000.0f, {50.0f, 40.8f, -1060.0f}, {0.000306f, 0.01f, 0.1388315664f}, {0.175f, 0.175f , 0.25f},  DIFFUSE}, // sky
    //{100000.0f, {50.0f, -100000.0f, 0.0f}, { 0.0f, 0.0f, 0.0f } ,{0.3f, 0.3f, 0.3f}, DIFFUSE },
    //{110000.0f, {50.0f, -100048.5f, 0.0f}, { 0.0f, 0.0f, 0.0f } ,{3.6f, 2.0f, 00.2f}, DIFFUSE },

    //{ 13.0f, { -75.0f, 13.0f, 282.0f }, { 0.0f, 0.0f, 0.0f }, { 0.2f, 0.9f, 0.9f }, Material::SPECULAR }, 

};

__device__ inline bool hit(const Ray& ray, float& t, int& id)
{
    t = FLT_MAX, id = -1;
    int sphereNum = sizeof(spheres) / sizeof(Sphere);
    for (int i = 0; i < sphereNum; i++)
    {
        float ct = spheres[i].intersect(ray);
        if (ct != 0 && ct < t)
        {
            t = ct;
            id = i;
        }
    }

    return id != -1;
}


inline int gammaCorrect(float c)
{
    return int(pow(clamp(c, 0.0f, 1.0f), 1 / 2.2) * 255 + .5);
}

__device__ float3 radiance(Ray& ray, curandState* rs)
{
    float3 result = make_float3(0.0f, 0.0f, 0.0f);
    float3 temp = make_float3(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < DEPTH; i++)
    {
        //http://raytracey.blogspot.com/2015/10/gpu-path-tracing-tutorial-1-drawing.html
        float t;
        int id;

        if (!hit(ray, t, id))
            break;

        const Sphere& obj = spheres[id];
        float3 hit_point = ray.origin + ray.direction * t;
        float3 n = normalize(hit_point - obj.position);
        float3 nl = dot(n, ray.direction) < 0 ? n : n * -1;

        ray.origin = hit_point + nl * RAY_EPSILON;

        result += temp * obj.emissionColor;

        if (obj.material == DIFFUSE) {
            float r1 = curand_uniform(rs) * M_PI * 2;
            float r2 = curand_uniform(rs);
            float r2s = sqrtf(r2);

            float3 w = nl;
            float3 u = normalize(cross((std::fabs(w.x) > std::fabs(w.y) ? make_float3(0.0f, 1.0f, 0.0f) : make_float3(1.0f, 0.0f, 0.0f)), w));
            float3 v = cross(w, u);

            ray.direction = normalize(u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrtf(1 - r2));

            temp *= obj.mainColor * dot(ray.direction, nl) * 2;
        }
        else if (obj.material == SPECULAR) {
            ray.direction = ray.direction - 2 * n * dot(n, ray.direction);
            temp *= obj.mainColor;
        }
        else {
            ray.origin = hit_point;
            float3 reflect = ray.direction - 2 * n * dot(n, ray.direction);

            float nc = 1, nt = 1.5, cos2t;
            float ddn = dot(ray.direction, nl);
            float nnt;
            if (dot(n, nl) > 0) {
                nnt = nc / nt;
            }
            else {
                nnt = nt / nc;
            }
            bool into = dot(n, nl) > 0;
            if ((cos2t = 1 - nnt * nnt * (1 - ddn * ddn)) < 0) {
                ray.direction = reflect;
                temp *= obj.mainColor;
            }
            else {
                float3 tdir = normalize(ray.direction * nnt - n * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t))));
                float a = nt - nc, b = nt + nc, R0 = a * a / (b * b), c = 1 - (into ? -ddn : dot(tdir, n));
                float Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re, P = .25 + .5 * Re, RP = Re / P, TP = Tr / (1 - P);

                if(curand_uniform(rs) < P)
                {
                    ray.direction = reflect;
                    temp *= obj.mainColor * RP;
                }
                else
                {
                    ray.direction = tdir;
                    temp *= obj.mainColor * TP;
                }
            }
        }
    }

    return result;
}



__global__ void launchkernel(float3* cpu_out)
{
    uint x = blockIdx.x * blockDim.x + threadIdx.x;
    uint y = blockIdx.y * blockDim.y + threadIdx.y;

    uint i = (HEIGHT - y - 1) * WIDTH + x;

    curandState rs;
    curand_init(i, 0, 0, &rs);

    /*Ray cam(make_float3(0.0f, 52.0f, 300.0f), normalize(make_float3(0.0f, -0.05f, -1.0f)));*/
    Ray cam(make_float3(0.0f, 42.0f, 250.0f), normalize(make_float3(0.0f, -0.035f, -1.0f)));
    float3 cx = make_float3(WIDTH * 0.5135 / HEIGHT, 0.0f, 0.0f);
    float3 cy = normalize(cross(cx, cam.direction)) * 0.5135;
    float3 pixel = make_float3(0.0f);

    //http://www.kevinbeason.com/smallpt/
    for (int sy = 0; sy < 2; sy++) {
        for (int sx = 0; sx < 2; sx++) { 
            for(int s = 0; s < SPP; s++) {
                float r1 = curand_uniform(&rs);
                float dx = r1 < 1 ? sqrtf(r1) - 1 : 1-sqrtf(2 - r1);
                float r2 = curand_uniform(&rs);
                float dy = r2 < 1 ? sqrtf(r2) - 1 : 1-sqrtf(2 - r2);
                float3 d = cam.direction + cx*((((sx + dx + .5) / 2) + x) / WIDTH - .5) + cy*((((sy + dy + .5) / 2) + y) / HEIGHT - .5);
                Ray tRay(cam.origin + d * 140, normalize(d));
                tRay.direction = normalize(d);
                tRay.origin = cam.origin + d * 140;
                pixel += radiance(tRay, &rs) *(0.25f / SPP);
            }
        }
    }

    cpu_out[i] = clamp(pixel, 0.0f, 1.0f);
    
}

int main() {
    float3* cpu_out = new float3[WIDTH * HEIGHT];
    float3* gpu_out;
    cudaMalloc(&gpu_out, WIDTH * HEIGHT * sizeof(float3));
    dim3 block(32, 32);
    dim3 grid(WIDTH / block.x, HEIGHT / block.y);
    launchkernel << <grid, block >> > (gpu_out);
    cudaMemcpy(cpu_out, gpu_out, WIDTH * HEIGHT * sizeof(float3), cudaMemcpyDeviceToHost);
    cudaFree(gpu_out);
    FILE* f = fopen("cudayes3.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", WIDTH, HEIGHT, 255);
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        fprintf(f, "%d %d %d ", gammaCorrect(cpu_out[i].x),  gammaCorrect(cpu_out[i].y), gammaCorrect(cpu_out[i].z));
    delete[] cpu_out;

    return 0;
}