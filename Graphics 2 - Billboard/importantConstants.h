#ifndef IMPORTANT_CONSTANTS_H
#define IMPORTANT_CONSTANTS_H

//important constants that are used in several places

#define DESCRIPTOR_SET_BINDING_POINT 0

#define BATCH_SIZE					128

//things in per-mesh descriptor set
#define BASE_TEXTURE_SAMPLER_SLOT              0
#define BASE_TEXTURE_SLOT                      1
#define EMISSIVE_TEXTURE_SLOT                  2
#define UNIFORM_BUFFER_SLOT                    3
#define NORMAL_TEXTURE_SLOT                    4
#define METALLICROUGHNESS_TEXTURE_SLOT         5
#define SKYBOX_TEXTURE_SLOT               6
#define ENVMAP_TEXTURE_SLOT                      6
#define DEPTH_TEXTURE_SLOT           METALLICROUGHNESS_TEXTURE_SLOT
#define BILLBOARD_TEXTURE_SLOT                  7
#define NEAREST_SAMPLER_SLOT                   8


#define POSITION_SLOT               0
#define TEXCOORD_SLOT               1
#define NORMAL_SLOT                 2
#define TANGENT_SLOT				3
#define TEXCOORD2_SLOT				4

#endif
