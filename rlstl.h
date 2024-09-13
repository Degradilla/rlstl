#ifndef RLSTLLOADER
#define RLSTLLOADER

#include <raylib.h>
#include <stdio.h>

#define TRIGSIZE 50

Mesh LoadSTL(const char* filename){
    FILE* fp = fopen(filename, "rb");
    if (!fp) CloseWindow();

    int triangleCount;
    fseek(fp, 80, SEEK_SET);
    fread(&triangleCount, sizeof(int), 1, fp);
    int vertexCount = triangleCount * 3;

    char* buffer = (char*)MemAlloc( TRIGSIZE * triangleCount );
    fseek(fp, 84, SEEK_SET);
    fread(buffer, TRIGSIZE, triangleCount, fp);
    fclose(fp);
    
    float* normals   = (float*)MemAlloc( vertexCount * 3 * sizeof(float) );
    float* vertices  = (float*)MemAlloc( vertexCount * 3 * sizeof(float) );
    float* texcoords = (float*)MemAlloc( vertexCount * 2 * sizeof(float) );

    for (int i = 0, n = 0, v = 0, t = 0; i < triangleCount; i++){
        float* trig = (float*)( buffer + i * TRIGSIZE );

        normals[n++] = trig[1];
        normals[n++] = trig[2];
        normals[n++] = trig[0];
        normals[n++] = trig[1];
        normals[n++] = trig[2];
        normals[n++] = trig[0];
        normals[n++] = trig[1];
        normals[n++] = trig[2];
        normals[n++] = trig[0];

        vertices[v++] = trig[4];
        vertices[v++] = trig[5];
        vertices[v++] = trig[3];
        vertices[v++] = trig[7];
        vertices[v++] = trig[8];
        vertices[v++] = trig[6];
        vertices[v++] = trig[10];
        vertices[v++] = trig[11];
        vertices[v++] = trig[9];

        texcoords[t++] = 0.0f;
        texcoords[t++] = 0.0f;
    }    

    MemFree(buffer);

    Mesh mesh = {0};
    mesh.triangleCount = triangleCount;
    mesh.vertexCount   = vertexCount;
    mesh.normals       = normals;
    mesh.vertices      = vertices;
    mesh.texcoords     = texcoords;
    UploadMesh(&mesh, false);

    return mesh;
}

#undef TRIGSIZE

#endif
